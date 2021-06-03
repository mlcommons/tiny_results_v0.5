# Tiny MLPerf™ v0.1 `hls4ml` Xilinx PYNQ-Z2 Open Submission

By `hls4ml` team
<p float="left">
   <a href="https://fastmachinelearning.org/"><img src="https://fastmachinelearning.org/hls4ml/_images/hls4ml_logo.png" alt="hls4ml" width="400"/></a>
</p>

## Hardware
* Board is a TUL PYNQ-Z2 based on Xilinx Zynq SoC (See https://www.tul.com.tw/productspynq-z2.html for more information).
<p float="left">
   <img src="PYNQ-Z2.jpg" alt="PYNQ-Z2" width="400"/></a>
</p>

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
* Under `training`, there are scripts to train the model with `QKeras` (`train.py`) and convert it to an HLS project using `hls4ml` (`convert.py`).
* For convenience the pretrained models in `.h5` format are provided in the repository as indicated.
* Under `inference`, Xilinx SDK 2019.1 projects will be automatically created after successfully running `convert.py`.

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
* Download Pynq-Z2 board files (from https://d2m32eurp10079.cloudfront.net/Download/pynq-z2.zip) and install appropriately
```bash
<path_to_Vivado>/Vivado/2019.1/data/boards
```
* Setup Vivado 2019.1:
```bash
source <path_to_Vivado>/Vivado/2019.1/settings64.sh
```
* Ensure Pynq-Z2 board is connected (and powered) by USB and visible.
<p float="left">
   <img src="RN06_running.jpg" alt="RN06 running" width="400"/>
</p>
* For power measurements, solder connections [add instructions + screenshots]

## Training with `QKeras`
### AD03 model

* Change directory
```bash
cd code/ad/AD03/training/
```
* Download dataset for AD03:
```bash
./get_dataset.sh
```
* Train AD03:
```bash
python train.py -c AD03.yml
```

### RN06 model

* Change directory
```bash
cd code/ic/RN06/training/
```
* Train RN06:
```bash
python train.py -c RN06_pynqz2.yml
```

## Conversion with `hls4ml`

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

* Open Xilinx SDK GUI and program bit file [add screenshot]
* Run test harness software [add screenshot]
* Open EEMBC runner GUI and perform measurements [add screenshot]
