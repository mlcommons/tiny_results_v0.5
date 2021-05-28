ACC ?= resnet
SAMPLE_COUNT ?= 10

BOARD = artya7100t

data:
	make -C ../../utils/dat2header/sim clean
	make -C ../../utils/dat2header/sim W_AXI_WIDTH=8 I_AXI_WIDTH=8 W_WIDTH=8 I_WIDTH=8
	../../utils/dat2header/sim/dat2header ../../hls/$(PROJECT_HLS)/tb_data/tb_input_features.dat $(PROJECT)/src/src.h src $(SAMPLE_COUNT)
	make -C ../../utils/dat2header/sim clean
	make -C ../../utils/dat2header/sim W_AXI_WIDTH=8 I_AXI_WIDTH=6 W_WIDTH=8 I_WIDTH=6
	../../utils/dat2header/sim/dat2header ../../hls/$(PROJECT_HLS)/tb_data/csim_results.log $(PROJECT)/src/dst.h dst $(SAMPLE_COUNT)
.PHONY: data

include ../common/config_microblaze.mk
