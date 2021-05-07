PROJECT_HLS=$(BOARD)_$(ACC)_m_axi_8_serial_prj

PROJECT = $(ACC)_standalone

help:
	@echo "INFO: make <TAB> to show targets"
.PHONY: help

setup:
	xsct script.tcl $(ACC)
.PHONY: setup

sdk: setup data
	rm -f $(PROJECT)/src/helloworld.c
	cd  $(PROJECT)/src && cp ../../../common/$(ACC)/main_microblaze.c main.c
	sed -i 's/^_STACK_SIZE.*$$/_STACK_SIZE = DEFINED(_STACK_SIZE) ? _STACK_SIZE : 0x400000;/g' ./$(PROJECT)/src/lscript.ld
	sed -i 's/^_HEAP_SIZE.*$$/_HEAP_SIZE = DEFINED(_HEAP_SIZE) ? _HEAP_SIZE : 0x4000000;/g' ./$(PROJECT)/src/lscript.ld
.PHONY: sdk

sdk-harness: setup data
	rm -f $(PROJECT)/src/helloworld.c
	cd  $(PROJECT)/src && cp ../../../common/$(ACC)/main_microblaze_harness.c main.c && cp -r ../../../common/$(ACC)/profile_microblaze profile && cp -r ../../../common/$(ACC)/monitor_microblaze monitor
	sed -i 's/^_STACK_SIZE.*$$/_STACK_SIZE = DEFINED(_STACK_SIZE) ? _STACK_SIZE : 0x400000;/g' ./$(PROJECT)/src/lscript.ld
	sed -i 's/^_HEAP_SIZE.*$$/_HEAP_SIZE = DEFINED(_HEAP_SIZE) ? _HEAP_SIZE : 0x4000000;/g' ./$(PROJECT)/src/lscript.ld

.PHONY: sdk-harness

gui:
	xsdk --workspace .
.PHONY: gui

clean:
	rm -rf $(PROJECT)
	rm -rf $(PROJECT)_bsp
	rm -rf $(PROJECT_I2C)
	rm -rf $(PROJECT_I2C)_bsp
	rm -rf $(ACC)_platform
	rm -rf RemoteSystemsTempFiles
	rm -rf SDK.log
	rm -rf webtalk
	rm -rf .sdk
	rm -rf .Xil
	rm -rf .metadata
	rm -rf updatemem*
.PHONY: clean
