# Tiny MLPerf™ v0.1 `hls4ml` Xilinx PYNQ-Z2 Open Submission

By `hls4ml` team
<a href="https://fastmachinelearning.org/"><img src="https://fastmachinelearning.org/hls4ml/_images/hls4ml_logo.png" alt="hls4ml" width="400"/></a>

* Contacts:
  * Ben Hawks, email: <bhawks@fnal.gov>, GitHub: [@ben-hawks](https://github.com/ben-hawks)
  * Nhan Tran, email: <ntran@fnal.gov>, GitHub: [@nhanvtran](https://github.com/nhanvtran)
  * Javier Duarte, email: <jduarte@ucsd.edu>, GitHub: [@jmduarte](https://github.com/jmduarte)
  * Giuseppe DiGuglielmo, email: <giuseppe.diguglielmo@columbia.edu>, GitHub: [@GiuseppeDiGuglielmo](https://github.com/GiuseppeDiGuglielmo)
* Team members:
  * Nicolò Ghielmetti, CERN
  * Jules Muhizi, Fermilab/Harvard
  * Shvetank Prakash, Columbia/Harvard
  * Rushil Roy, UCSD
  
## Hardware
* Board is a TUL PYNQ-Z2 based on Xilinx Zynq SoC (See https://www.tul.com.tw/productspynq-z2.html for more information).
<img src="https://user-images.githubusercontent.com/4932543/120665525-b47d6580-c440-11eb-9e74-fb3d86673683.jpg" alt="PYNQ-Z2" width="400"/>

## Code structure
The code is structured as follows
```
hls4ml
├── code
│   ├── ad
│   │   └── AD03
│   │       ├── inference
│   │       │   ├── hls
│   │       │   ├── sdk
│   │       │   ├── sys
│   │       │   └── utils
│   │       └── training
│   │           ├── convert.py
│   │           ├── model
│   │           │   └── ad03
│   │           │       └── model_ToyCar.h5
│   │           ├── train.py
│   └── ic
│       └── RN06
│           ├── inference
│           │   ├── hls
│           │   ├── sdk
│           │   ├── sys
│           │   └── utils
│           └── training
│               ├── convert.py
│               ├── resnet_v1_eembc_RN06
│               │   └── model_best.h5
│               └── train.py
├── results
│   └── pynqz2
│       ├── ad
│       │   ├── accuracy
│       │   └── performance
│       └── ic
│           ├── accuracy
│           └── performance
└── systems

```
* For both the anomaly detection model (AD03) and the image classification model (RN06), there are `training` and `inference` subdirectories.
* Under `training`, there are scripts to train the model with `QKeras` (`train.py`) and convert it to a Xilinx HLS/Vivado/SDK project using `hls4ml` (`convert.py`).
* The configruation is controlled by `yml` files.
* For convenience, the pretrained models in `.h5` format are provided in the repository as indicated.
* Under `inference`, the Xilinx HLS, Vivado, and SDK projects will be automatically created after successfully running `convert.py` in the `hls`, `sys`, and `sdk` folders respectively.

## Setup

* Install miniconda from here: https://docs.conda.io/en/latest/miniconda.html
* Create the environment:
```bash
conda-env create -f environment.yml
```
* Activate the environment:
```bash
conda activate tiny-mlperf-env
```
* Install Vivado 2019.1 from https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/archive.html
* Download PYNQ-Z2 board files (from https://dpoauwgwqsy2x.cloudfront.net/Download/pynq-z2.zip) and [install appropriately](https://pynq.readthedocs.io/en/v2.5/overlay_design_methodology/board_settings.html) by extracting and copying files to:
```bash
<path_to_Vivado>/Vivado/2019.1/data/boards/board_files
```
* Setup Vivado 2019.1:
```bash
source <path_to_Vivado>/Vivado/2019.1/settings64.sh
```
* Ensure PYNQ-Z2 board is connected (and powered) by USB and visible.
<img src="https://user-images.githubusercontent.com/4932543/120665682-d971d880-c440-11eb-8154-215034d89c01.jpg" alt="RN06 running" width="400"/>

## Training with `QKeras`

In this step, you will download the dataset and perform a quantization-aware training with QKeras.  

### AD03 model

* Change directory
```bash
cd code/ad/AD03/training/
```
* Download dataset for AD03:
```bash
./get_dataset.sh
```
* Train AD03, pretrained model is provided as `model/ad03/model_ToyCar.h5`:
```bash
python train.py -c AD03.yml
```
_n.b. if you don't have a GPU, you can comment out the `import setGPU` (true also for later python scripts)_

### RN06 model

* Change directory
```bash
cd code/ic/RN06/training/
```
* Train RN06, pretrained model is provided as `resnet_v1_eembc_RN06/model_best.h5`:
```bash
python train.py -c RN06_pynqz2.yml
```

## Conversion with `hls4ml`

In this step, you will ingest the quantization-aware training performed in the previous step and convert it to firmware using hls4ml.  The hls4ml configuration, `pynqz2.yml` has details such as the implementation architecture.  

### AD03 model

* Change directory
```bash
cd code/ad/AD03/training/
```
* Get test data:
```bash
python generate_test_data.py -c AD03.yml
```
* Convert AD03:
```bash
python convert.py -c pynqz2.yml
```

### RN06 model

* Change directory
```bash
cd code/ic/RN06/training/
```
* Get test data:
```bash
source get_test_data.sh
```
* Convert RN06:
```bash
python convert.py -c RN06_pynqz2.yml
```

## Program FPGA and run software

* Change directory
```bash
cd code/ic/<model_name>/inference/sdk/
```
* Open Xilinx SDK GUI
```bash
make gui
```
* Program the FPGA with the bit file in SDK
   * <img width="600" alt="Screen Shot 2021-06-06 at 10 20 14 PM" src="https://user-images.githubusercontent.com/4932543/120962896-78ceee00-c715-11eb-8888-540dcf3bed39.png"/>
* Run test harness software in SDK
   * <img width="600" alt="Screen Shot 2021-06-06 at 10 22 07 PM" src="https://user-images.githubusercontent.com/4932543/120963020-b6337b80-c715-11eb-93c7-e0de1fa2c070.png"/>
* Download EEMBC runner GUI and AD/IC benchmark datasets (See https://github.com/eembc/ulpmark-ml) 
* Open EEMBC runner GUI and and perform measurements, follow the instructions on the eembc README 
   * <img width="400" alt="Screen Shot 2021-06-06 at 10 18 51 PM" src="https://user-images.githubusercontent.com/4932543/120962751-32798f00-c715-11eb-816a-c1ab4f11da47.png"/>

## Boot from Flash

The PYNQ--Z2 supports Quad SPI Flash. Please follow these [instructions](code/ad/AD03/inference/sdk/pynqz2/README.md) to program and boot from the Flash memory.
