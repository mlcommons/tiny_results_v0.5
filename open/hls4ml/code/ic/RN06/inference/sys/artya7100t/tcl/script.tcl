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
create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 clk_wiz_0
apply_board_connection -board_interface "sys_clock" -ip_intf "clk_wiz_0/clock_CLK_IN1" -diagram $design_name
set_property name clk_wizard [get_bd_cells clk_wiz_0]
set_property -dict [list CONFIG.CLKOUT2_USED {true} CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {166.667} CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {200.00} CONFIG.MMCM_CLKOUT0_DIVIDE_F {6.000} CONFIG.MMCM_CLKOUT1_DIVIDE {5} CONFIG.NUM_OUT_CLKS {2} CONFIG.CLKOUT1_JITTER {118.758} CONFIG.CLKOUT2_JITTER {114.829} CONFIG.CLKOUT2_PHASE_ERROR {98.575}] [get_bd_cells clk_wizard]
#set_property -dict [list CONFIG.RESET_TYPE {ACTIVE_LOW} CONFIG.RESET_PORT {resetn}] [get_bd_cells clk_wizard]

# Create MIG
create_bd_cell -type ip -vlnv xilinx.com:ip:mig_7series:4.2 mig_7series_0
apply_board_connection -board_interface "ddr3_sdram" -ip_intf "mig_7series_0/mig_ddr_interface" -diagram $design_name

# Wire MIG and clock wizard
delete_bd_objs [get_bd_nets clk_ref_i_1] [get_bd_ports clk_ref_i]
delete_bd_objs [get_bd_nets sys_clk_i_1] [get_bd_ports sys_clk_i]
connect_bd_net [get_bd_pins clk_wizard/clk_out2] [get_bd_pins mig_7series_0/clk_ref_i]
connect_bd_net [get_bd_pins clk_wizard/clk_out1] [get_bd_pins mig_7series_0/sys_clk_i]

# Setup reset
#set_property -dict [list CONFIG.RESET_BOARD_INTERFACE {reset}] [get_bd_cells clk_wizard]
apply_bd_automation -rule xilinx.com:bd_rule:board -config { Board_Interface {reset ( System Reset ) } Manual_Source {New External Port (ACTIVE_LOW)}}  [get_bd_pins mig_7series_0/sys_rst]

# Create instance of MicroBlaze
create_bd_cell -type ip -vlnv xilinx.com:ip:microblaze:11.0 microblaze_mcu
apply_bd_automation -rule xilinx.com:bd_rule:microblaze -config { \
    axi_intc {0} \
    axi_periph {Enabled} \
    cache {16KB} \
    clk {/mig_7series_0/ui_clk (83 MHz)} \
    debug_module {Debug Only} \
    ecc {None} \
    local_mem {128KB} \
    preset {None} } [get_bd_cells microblaze_mcu]

# Enable full FPU
set_property -dict [list CONFIG.C_USE_FPU {2}] [get_bd_cells microblaze_mcu]

# Create UART interface
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_uartlite:2.0 axi_uartlite_0
apply_board_connection -board_interface "usb_uart" -ip_intf "axi_uartlite_0/UART" -diagram $design_name
set_property -dict [list CONFIG.C_BAUDRATE {115200}] [get_bd_cells axi_uartlite_0]

apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { \
    Clk_master {/mig_7series_0/ui_clk (83 MHz)} \
    Clk_slave {/mig_7series_0/ui_clk (83 MHz)} \
    Clk_xbar {/mig_7series_0/ui_clk (83 MHz)} \
    Master {/microblaze_mcu (Cached)} \
    Slave {/mig_7series_0/S_AXI} \
    intc_ip {Auto} master_apm {0} } [get_bd_intf_pins mig_7series_0/S_AXI]

apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { \
    Clk_master {/mig_7series_0/ui_clk (83 MHz)} \
    Clk_slave {Auto} \
    Clk_xbar {Auto} \
    Master {/microblaze_mcu (Periph)} \
    Slave {/axi_uartlite_0/S_AXI} \
    intc_ip {New AXI Interconnect} \
    master_apm {0} } [get_bd_intf_pins axi_uartlite_0/S_AXI]

# Add accelerator and connect s-axi interface
create_bd_cell -type ip -vlnv xilinx.com:hls:$top_module:1.0 $top_module
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {/mig_7series_0/ui_clk (83 MHz)} Clk_slave {Auto} Clk_xbar {/mig_7series_0/ui_clk (83 MHz)} Master {/microblaze_mcu (Periph)} Slave {/$acc\_axi/s_axi_CTRL_BUS} intc_ip {/microblaze_mcu_axi_periph} master_apm {0}}  [get_bd_intf_pins $acc\_axi/s_axi_CTRL_BUS]

# Connect m-axi interfaces
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {/mig_7series_0/ui_clk (83 MHz)} Clk_slave {/mig_7series_0/ui_clk (83 MHz)} Clk_xbar {/mig_7series_0/ui_clk (83 MHz)} Master {/$acc\_axi/m_axi_IN_BUS} Slave {/mig_7series_0/S_AXI} intc_ip {/axi_smc} master_apm {0}}  [get_bd_intf_pins $acc\_axi/m_axi_IN_BUS]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {/mig_7series_0/ui_clk (83 MHz)} Clk_slave {/mig_7series_0/ui_clk (83 MHz)} Clk_xbar {/mig_7series_0/ui_clk (83 MHz)} Master {/$acc\_axi/m_axi_OUT_BUS} Slave {/mig_7series_0/S_AXI} intc_ip {/axi_smc} master_apm {0}}  [get_bd_intf_pins $acc\_axi/m_axi_OUT_BUS]

# Reset
apply_bd_automation -rule xilinx.com:bd_rule:board -config { Board_Interface {reset ( System Reset ) } Manual_Source {Auto}}  [get_bd_pins clk_wizard/reset]

# Add timer
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_timer:2.0 axi_timer_mcu

# Wire timer
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {/mig_7series_0/ui_clk (83 MHz)} Clk_slave {Auto} Clk_xbar {/mig_7series_0/ui_clk (83 MHz)} Master {/microblaze_mcu (Periph)} Slave {/axi_timer_mcu/S_AXI} intc_ip {/microblaze_mcu_axi_periph} master_apm {0}}  [get_bd_intf_pins axi_timer_mcu/S_AXI]

# Validate the design block we created
validate_bd_design

# Save design
save_bd_design

## Create verilog top
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

