PROJECT_HLS=$(BOARD)_$(ACC)_m_axi_8_serial_prj

PROJECT = $(ACC)_standalone
PROJECT_I2C = i2c_test

help:
	@echo "INFO: make <TAB> to show targets"
.PHONY: help

setup:
	xsct script.tcl $(ACC)
.PHONY: setup

sdk: setup data
	rm -f $(PROJECT)/src/helloworld.c
	cd  $(PROJECT)/src && cp ../../../common/$(ACC)/main.c
.PHONY: sdk

sdk-harness: setup data
	rm -f $(PROJECT)/src/helloworld.c
	cd  $(PROJECT)/src && cp ../../../common/$(ACC)/main_harness.c main.c && cp -r ../../../common/$(ACC)/profile profile && cp -r ../../../common/$(ACC)/monitor monitor

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
.PHONY: clean
