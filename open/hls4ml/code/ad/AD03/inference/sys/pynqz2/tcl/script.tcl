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

# Set board
set board "pynqz2"

# Create project
create_project $proj $proj_dir -part xc7z020clg400-1

# Set project properties
#set_property board_part www.digilentinc.com:pynq-z1:part0:1.0 [current_project]
set_property board_part tul.com.tw:pynq-z2:part0:1.0 [current_project]

# Set IP repository paths
set_property ip_repo_paths ../../hls/$board\_$acc\_$interface\_8_serial_prj/$acc\_prj [current_project]
update_ip_catalog -rebuild

# Create the design block
set design_name $acc\_design
create_bd_design $design_name

# Name of the processing system (PS)
set ps "xilinx.com:ip:processing_system7:5.5"

# Name of the IP to connect the accelerator with AXI
set axi_inter "xilinx.com:ip:axi_interconnect:2.1"

# Create instance: accelerator acc and set properties
set acc_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:$top_module:1.0 $top_module]

# Create instance: processing_system_0, and set properties
set zynq_ps [ create_bd_cell -type ip -vlnv $ps zynq_ps ]

# Create instance: axi_interconnect_0, and set properties
set axi_interconnect_0 [ create_bd_cell -type ip -vlnv $axi_inter axi_interconnect_0 ]
set_property -dict [ list CONFIG.NUM_MI {1} ] $axi_interconnect_0

# Create instance: axi_interconnect_1, and set properties
set axi_interconnect_1 [ create_bd_cell -type ip -vlnv $axi_inter axi_interconnect_1 ]
set_property -dict [ list CONFIG.NUM_SI {2} CONFIG.NUM_MI {1} ] $axi_interconnect_1

# Set some properties for processing_system_0 after running design automation
apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 \
     -config { make_external "FIXED_IO, DDR" apply_board_preset "1" Master "Disable" Slave "Disable" }  $zynq_ps
set_property -dict [ list CONFIG.PCW_USE_M_AXI_GP0 {1} ] $zynq_ps
set_property -dict [ list CONFIG.PCW_USE_S_AXI_GP0 {1} ] $zynq_ps

#set_property -dict [ list CONFIG.PCW_QSPI_PERIPHERAL_ENABLE {0} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_QSPI_GRP_SINGLE_SS_ENABLE {1} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_SD0_PERIPHERAL_ENABLE {0} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_SD1_PERIPHERAL_ENABLE {0} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_ENET0_PERIPHERAL_ENABLE {0} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_UART1_PERIPHERAL_ENABLE {1} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_I2C0_PERIPHERAL_ENABLE {0} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_UART0_PERIPHERAL_ENABLE {0} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_USB0_PERIPHERAL_ENABLE {0} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_GPIO_MIO_GPIO_ENABLE {0} ] $zynq_ps
#set_property -dict [ list CONFIG.PCW_GPIO_EMIO_GPIO_ENABLE {0} ] $zynq_ps

# Set clock frequency of programmable logic to match the HLS core frequency
set_property -dict [ list CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {100} ] $zynq_ps

## Connection of the interrupt signal
#connect_bd_net [get_bd_pins $top_module/interrupt] \
#    [get_bd_pins zynq_ps/pl_ps_irq0]

# Connections of the different AXI channels
connect_bd_intf_net [get_bd_intf_pins $top_module/m_axi_IN_BUS] \
   -boundary_type upper [get_bd_intf_pins axi_interconnect_1/S00_AXI]
connect_bd_intf_net [get_bd_intf_pins $top_module/m_axi_OUT_BUS] \
   -boundary_type upper [get_bd_intf_pins axi_interconnect_1/S01_AXI]
connect_bd_intf_net [get_bd_intf_pins $top_module/s_axi_CTRL_BUS] \
   -boundary_type upper [get_bd_intf_pins axi_interconnect_0/M00_AXI]
connect_bd_intf_net [get_bd_intf_pins zynq_ps/M_AXI_GP0] \
   -boundary_type upper [get_bd_intf_pins axi_interconnect_0/S00_AXI]
connect_bd_intf_net [get_bd_intf_pins zynq_ps/S_AXI_GP0] \
   -boundary_type upper [get_bd_intf_pins axi_interconnect_1/M00_AXI]

# Connection for the clock signals (done with run connect automation)
apply_bd_automation -rule xilinx.com:bd_rule:clkrst -config \
    {Clk "/zynq_ps/FCLK_CLK0 (50 MHz)" }  [get_bd_pins $top_module/ap_clk]
apply_bd_automation -rule xilinx.com:bd_rule:clkrst -config \
    {Clk "/zynq_ps/FCLK_CLK0 (50 MHz)" }  [get_bd_pins zynq_ps/M_AXI_GP0_ACLK]
apply_bd_automation -rule xilinx.com:bd_rule:clkrst -config \
    {Clk "/zynq_ps/FCLK_CLK0 (50 MHz)" }  [get_bd_pins zynq_ps/S_AXI_GP0_ACLK]
apply_bd_automation -rule xilinx.com:bd_rule:clkrst -config \
    {Clk "/zynq_ps/FCLK_CLK0 (50 MHz)" }  [get_bd_pins axi_interconnect_0/ACLK]
apply_bd_automation -rule xilinx.com:bd_rule:clkrst -config \
    {Clk "/zynq_ps/FCLK_CLK0 (50 MHz)" }  [get_bd_pins axi_interconnect_1/ACLK]

# Assign the address in memory for the accelerator execution
assign_bd_address
delete_bd_objs [get_bd_addr_segs -excluded $top_module/Data_m_axi_IN_BUS/SEG_zynq_ps_GP0_IOP]
delete_bd_objs [get_bd_addr_segs -excluded $top_module/Data_m_axi_IN_BUS/SEG_zynq_ps_GP0_M_AXI_GP0]
delete_bd_objs [get_bd_addr_segs -excluded $top_module/Data_m_axi_OUT_BUS/SEG_zynq_ps_GP0_IOP]
delete_bd_objs [get_bd_addr_segs -excluded $top_module/Data_m_axi_OUT_BUS/SEG_zynq_ps_GP0_M_AXI_GP0]
delete_bd_objs [get_bd_addr_segs -excluded $top_module/Data_m_axi_IN_BUS/SEG_zynq_ps_GP0_QSPI_LINEAR]
delete_bd_objs [get_bd_addr_segs -excluded $top_module/Data_m_axi_OUT_BUS/SEG_zynq_ps_GP0_QSPI_LINEAR]

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
    ../../sdk/$board/hdf/$design_name\_$interface\_8_serial_wrapper.hdf

