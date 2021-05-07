setws .
if { $::argc == 1 } {
    set accname [lindex $::argv 0]
    createhw -name $accname\_platform -hwspec hdf/$accname\_design_m_axi_8_serial_wrapper.hdf
    createapp -name $accname\_standalone -app {Hello World} -proc ps7_cortexa9_0 -hwproject $accname\_platform -os standalone
}
