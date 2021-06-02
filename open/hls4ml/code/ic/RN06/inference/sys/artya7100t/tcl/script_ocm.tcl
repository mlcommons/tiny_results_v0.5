# Script

set acc ""
set interface ""

if { $argc == 2 } {
    set acc [lindex $argv 0]
    set interface [lindex $argv 1]
} else {
    puts "Error!"
}

# Set accelerator
set top_module $acc\_axi

# Set directory
set proj_dir "./$acc\_project"

# Set project
set proj "$acc\_project"

# Set design name
set design_name $acc\_design

# Set board
set board "artya7100t"

# Create project
create_project $proj $proj_dir -part xc7a100tcsg324-1

# Set project properties
set_property board_part digilentinc.com:arty-a7-100:part0:1.0 [current_project]

# Set IP repository paths
set_property ip_repo_paths ../../hls/$board\_$acc\_m_axi_8_serial_prj/$acc\_prj [current_project]
update_ip_catalog -rebuild

# Create the design block
create_bd_design $design_name

# Create clock wizard
create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 clk_wizard
set_property -dict [list CONFIG.RESET_TYPE {ACTIVE_LOW} CONFIG.RESET_PORT {resetn}] [get_bd_cells clk_wizard]
apply_board_connection -board_interface "sys_clock" -ip_intf "clk_wizard/clock_CLK_IN1" -diagram $design_name

# Setup reset
set_property -dict [list CONFIG.RESET_BOARD_INTERFACE {reset}] [get_bd_cells clk_wizard]
apply_bd_automation -rule xilinx.com:bd_rule:board -config { Board_Interface {reset ( System Reset ) } Manual_Source {New External Port (ACTIVE_LOW)}}  [get_bd_pins clk_wizard/resetn]

# Create UART interface
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_uartlite:2.0 axi_uartlite_0
apply_board_connection -board_interface "usb_uart" -ip_intf "axi_uartlite_0/UART" -diagram $design_name

# Create instance of MicroBlaze
create_bd_cell -type ip -vlnv xilinx.com:ip:microblaze:11.0 microblaze
apply_bd_automation -rule xilinx.com:bd_rule:microblaze \
  -config { \
      axi_intc {0} \
      axi_periph {Enabled} \
      cache {None} \
      clk {/clk_wizard/clk_out1 (100 MHz)} \
      debug_module {Debug Only} \
      ecc {None} \
      local_mem {128KB} \
      preset {None} }  [get_bd_cells microblaze]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 \
  -config { \
      Clk_master {/clk_wizard/clk_out1 (100 MHz)} \
      Clk_slave {Auto} \
      Clk_xbar {Auto} \
      Master {/microblaze (Periph)} \
      Slave {/axi_uartlite_0/S_AXI} \
      intc_ip {New AXI Interconnect} \
      master_apm {0} }  [get_bd_intf_pins axi_uartlite_0/S_AXI]

# Enable full FPU
set_property -dict [list CONFIG.C_USE_FPU {2}] [get_bd_cells microblaze]

# Add accelerator and connect s-axi interface
create_bd_cell -type ip -vlnv xilinx.com:hls:$top_module:1.0 $top_module
apply_bd_automation -rule xilinx.com:bd_rule:axi4 \
  -config { Clk_master {/clk_wizard/clk_out1 (100 MHz)} \
            Clk_slave {Auto} \
            Clk_xbar {/clk_wizard/clk_out1 (100 MHz)} \
            Master {/microblaze (Periph)} \
            Slave {/$top_module/s_axi_CTRL_BUS} \
            intc_ip {/microblaze_axi_periph} \
            master_apm {0} }  [get_bd_intf_pins $top_module/s_axi_CTRL_BUS]

# Reconfigure local memory to support accelerator DMA
set_property -dict [list CONFIG.C_NUM_LMB {2}] [get_bd_cells microblaze_local_memory/dlmb_bram_if_cntlr]
delete_bd_objs [get_bd_intf_nets microblaze_local_memory/microblaze_ilmb_bus]
connect_bd_intf_net [get_bd_intf_pins microblaze_local_memory/ilmb_v10/LMB_Sl_0] [get_bd_intf_pins microblaze_local_memory/dlmb_bram_if_cntlr/SLMB1]
delete_bd_objs [get_bd_intf_nets microblaze_local_memory/microblaze_ilmb_cntlr] [get_bd_cells microblaze_local_memory/ilmb_bram_if_cntlr]

# Add AXI interconnect
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_interconnect_0
set_property -dict [list CONFIG.NUM_SI {2} CONFIG.NUM_MI {1}] [get_bd_cells axi_interconnect_0]

# Add AXI BRAM controller
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_bram_ctrl:4.1 axi_bram_ctrl
set_property -dict [list CONFIG.SINGLE_PORT_BRAM {1}] [get_bd_cells axi_bram_ctrl]

#
apply_bd_automation -rule xilinx.com:bd_rule:board -config { Board_Interface {reset ( System Reset ) } Manual_Source {Auto}}  [get_bd_pins rst_clk_wizard_100M/ext_reset_in]

# Interconnect ports
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins axi_interconnect_0/M00_AXI] [get_bd_intf_pins axi_bram_ctrl/S_AXI]
connect_bd_intf_net [get_bd_intf_pins axi_bram_ctrl/BRAM_PORTA] [get_bd_intf_pins microblaze_local_memory/lmb_bram/BRAM_PORTB]
move_bd_cells [get_bd_cells microblaze_local_memory] [get_bd_cells axi_bram_ctrl]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins axi_interconnect_0/S00_AXI] [get_bd_intf_pins $top_module/m_axi_IN_BUS]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins axi_interconnect_0/S01_AXI] [get_bd_intf_pins $top_module/m_axi_OUT_BUS]
apply_bd_automation -rule xilinx.com:bd_rule:clkrst -config {Clk "/clk_wizard/clk_out1 (100 MHz)" }  [get_bd_pins axi_interconnect_0/ACLK]
apply_bd_automation -rule xilinx.com:bd_rule:clkrst -config {Clk "/clk_wizard/clk_out1 (100 MHz)" }  [get_bd_pins axi_interconnect_0/S00_ACLK]
apply_bd_automation -rule xilinx.com:bd_rule:clkrst -config {Clk "/clk_wizard/clk_out1 (100 MHz)" }  [get_bd_pins axi_interconnect_0/M00_ACLK]
apply_bd_automation -rule xilinx.com:bd_rule:clkrst -config {Clk "/clk_wizard/clk_out1 (100 MHz)" }  [get_bd_pins axi_interconnect_0/S01_ACLK]

# Assign the address in memory for the accelerator execution
assign_bd_address [get_bd_addr_segs {microblaze_local_memory/dlmb_bram_if_cntlr/SLMB1/Mem }]
assign_bd_address [get_bd_addr_segs {microblaze_local_memory/axi_bram_ctrl/S_AXI/Mem0 }]

# Renaming
set_property name microblaze_mcu [get_bd_cells microblaze]

# Rewiring reset signals
#disconnect_bd_net /rst_clk_wizard_100M_peripheral_aresetn [get_bd_pins rst_clk_wizard_100M/peripheral_aresetn]
#disconnect_bd_net /rst_clk_wizard_100M_peripheral_aresetn [get_bd_pins anomaly_detector_axi/ap_rst_n]
#disconnect_bd_net /rst_clk_wizard_100M_peripheral_aresetn [get_bd_pins axi_uartlite_0/s_axi_aresetn]
#disconnect_bd_net /rst_clk_wizard_100M_peripheral_aresetn [get_bd_pins microblaze_axi_periph/S00_ARESETN]
#disconnect_bd_net /rst_clk_wizard_100M_peripheral_aresetn [get_bd_pins microblaze_axi_periph/M00_ARESETN]
#disconnect_bd_net /rst_clk_wizard_100M_peripheral_aresetn [get_bd_pins microblaze_axi_periph/M01_ARESETN]
#disconnect_bd_net /rst_clk_wizard_100M_peripheral_aresetn [get_bd_pins axi_interconnect_0/S01_ARESETN] [get_bd_pins axi_interconnect_0/M00_ARESETN] [get_bd_pins axi_interconnect_0/S00_ARESETN]
#connect_bd_net [get_bd_pins rst_clk_wizard_100M/peripheral_aresetn] [get_bd_pins anomaly_detector_axi/ap_rst_n]
#connect_bd_net [get_bd_pins rst_clk_wizard_100M/interconnect_aresetn] [get_bd_pins microblaze_axi_periph/S00_ARESETN]
#connect_bd_net [get_bd_pins axi_uartlite_0/s_axi_aresetn] [get_bd_pins rst_clk_wizard_100M/peripheral_aresetn]
#connect_bd_net [get_bd_pins axi_interconnect_0/S00_ARESETN] [get_bd_pins axi_interconnect_0/M00_ARESETN] -boundary_type upper
#connect_bd_net [get_bd_pins axi_interconnect_0/M00_ARESETN] [get_bd_pins axi_interconnect_0/S01_ARESETN] -boundary_type upper
#connect_bd_net [get_bd_pins microblaze_axi_periph/S00_ARESETN] [get_bd_pins microblaze_axi_periph/M00_ARESETN] -boundary_type upper
#connect_bd_net [get_bd_pins microblaze_axi_periph/M00_ARESETN] [get_bd_pins microblaze_axi_periph/M01_ARESETN] -boundary_type upper
#connect_bd_net [get_bd_pins microblaze_axi_periph/M01_ARESETN] [get_bd_pins rst_clk_wizard_100M/peripheral_aresetn]
#connect_bd_net [get_bd_pins axi_interconnect_0/S01_ARESETN] [get_bd_pins rst_clk_wizard_100M/peripheral_aresetn]

# Add timer
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_timer:2.0 axi_timer_0
set_property name axi_timer_mcu [get_bd_cells axi_timer_0]

# Wire timer
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {/clk_wizard/clk_out1 (100 MHz)} Clk_slave {Auto} Clk_xbar {/clk_wizard/clk_out1 (100 MHz)} Master {/microblaze_mcu (Periph)} Slave {/axi_timer_mcu/S_AXI} intc_ip {/microblaze_axi_periph} master_apm {0}}  [get_bd_intf_pins axi_timer_mcu/S_AXI]
set_property -dict [list CONFIG.mode_64bit {1}] [get_bd_cells axi_timer_mcu]

# Create interrupt controller
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_intc:4.1 axi_intc_0
set_property name axi_intc_mcu [get_bd_cells axi_intc_0]

# Wire interrupt controller
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {/clk_wizard/clk_out1 (100 MHz)} Clk_slave {Auto} Clk_xbar {/clk_wizard/clk_out1 (100 MHz)} Master {/microblaze_mcu (Periph)} Slave {/axi_intc_mcu/s_axi} intc_ip {/microblaze_axi_periph} master_apm {0}}  [get_bd_intf_pins axi_intc_mcu/s_axi]

connect_bd_net [get_bd_pins axi_timer_mcu/interrupt] [get_bd_pins axi_intc_mcu/intr]
connect_bd_intf_net [get_bd_intf_pins axi_intc_mcu/interrupt] [get_bd_intf_pins microblaze_mcu/INTERRUPT]

# Validate the design block we created
validate_bd_design

# Save design
save_bd_design

# Create verilog top
make_wrapper -files [get_files $proj_dir/$proj.srcs/sources_1/bd/$design_name/$design_name.bd] -top
add_files -norecurse $proj_dir/$proj.srcs/sources_1/bd/$design_name/hdl/$design_name\_wrapper.v

# Run the synthesis step
launch_runs synth_1
wait_on_run -timeout 360 synth_1

# Run the implementation step
puts "INFO: Run bistream generation..."
launch_runs impl_1 -to_step write_bitstream
wait_on_run -timeout 360 impl_1

if {[get_property PROGRESS [get_runs impl_1]] != "100%"} {
    error "ERROR: bitstream generation failed!"
}

# Export the bitstream and the hardware for the SDK
puts "INFO: Export hardware..."
file copy -force $proj_dir/$proj.runs/impl_1/$design_name\_wrapper.sysdef \
    ../../sdk/$board/hdf/$design_name\_m_axi_8_serial_wrapper.hdf

