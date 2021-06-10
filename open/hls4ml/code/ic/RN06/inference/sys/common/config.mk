PROJECT = $(ACC)_project

help:
	@echo "INFO: make <TAB> for targets"
.PHONY: help

sys-gui:
	vivado -source tcl/script.tcl -mode gui -tclargs $(ACC) $(INTERFACE)
.PHONY: sys-gui

sys:
	vivado -source tcl/script.tcl -mode batch -tclargs $(ACC) $(INTERFACE)
.PHONY: sys

gui:
	vivado $(PROJECT)/$(PROJECT).xpr
.PHONY: gui

clean:
	rm -rf *.log *.txt *.jou *.str $(ACC)_project NA
.PHONY: clean
