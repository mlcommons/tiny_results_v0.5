# Tiny MLperf  v0.1 on PCL Scepu02

By: Peng Cheng Laboratory
[![pcl](http://www.szpclab.com/webimages/logo.png)](http://www.szpclab.com/)

Engineers:
* Niu Wenxu
    * email: wniu@connect.ust.hk
    * github: https://github.com/ninn55

* Xu Xuesong
    * email: xuxs@pcl.ac.cn
    * github: https://github.com/coolbacon

You can contact either of us for an evaluation board or faulty submission.

## Background

PCL Scepu02 is a evaluation board of RV32-A. It has a RV32-A SoC which implementing RV32IMAC. Designed by Peng Cheng Laboratory and fabricated with SMIC 55nm process.

## The Hardware

The board schematic:
![SCEPU01 Design-A](https://i.loli.net/2021/05/07/i2uDjlAMXxQEswC.png)

Before every SPI flash you need to switch on,therefore connect 2 and 7 on SW1. After every flash, you need to switch it off and reset.

![Switch](https://i.loli.net/2021/05/07/R82kKcLwjDhbBy6.png)

Then connect your jlink adapter with the spi flash

![Flash](https://i.loli.net/2021/05/07/uEYbfFXhrWBIOcs.png)

![jlink](https://i.loli.net/2021/05/07/lJiFUjItu4HZGyv.png)

| Number  | Jtag name  | SPI name  |
|---|---|---|
|5   | TDI  | MOSI  |
| 7  | TMS  | NSS  |
| 9  | TCK  | SCK  |
|13   | TDO  | MISO  |

You can download the full schematic from [here](https://drive.google.com/file/d/1q_uKU2rHQ6LAZEVzQqkY5DeXxF4AG_Ns/view?usp=sharing).

The board with jtag and serial uart connected:

![DSC04840-min.JPG](https://i.loli.net/2021/05/18/LuiaMmdzOs154fE.jpg)

## Build instruction

We are using a special build system called waf. First you need to install waf using documents from [here](https://waf.io/).

```bash
curl -o waf https://waf.io/waf-2.0.20
chmod +x waf
export PATH=$PATH:$(pwd)
```

Then install riscv32 gnu toolchain with our abi.

```bash
git clone —recursive https://github.com/riscv/riscv-gnu-toolchain
git submodule foreach git reset —hard
./configure —prefix=/usr/local —with-abi=ilp32f —with-arch=rv32imaf
sudo make
```

Then you need to install jlink software from [here](https://www.segger.com/downloads/jlink/).

### Anomaly Detection

Build the firmware with
```bash
cd closed/PengChengLaboratory/code/ad/
python tinymlperf/GenerateModel.py
waf distclean
waf distclean configure build --tinymlperf --pclrv32
```

Flash the firmware with
```bash
cd closed/PengChengLaboratory/code/ad/
waf flash --flashtarget ad
```
or flash `build/anomaly_detection.bin` directly using `JFlashSPI`.


### Image Classification

Build the firmware with

```bash
cd closed/PengChengLaboratory/code/ic/
waf distclean
waf configure build
```

Flash the firmware with

```bash
waf flash
```
or flash `build/image_classification.bin` directly using `JFlashSPI`.

### Keyword Spotting


Build the firmware with

```bash
cd closed/PengChengLaboratory/code/kws/
waf distclean
waf configure build
```

Flash the firmware with

```bash
waf flash
```
or flash `build/keyword_spotting.bin` directly using `JFlashSPI`.

### Visual wake word

Build the firmware with

```bash
cd closed/PengChengLaboratory/code/vww/
waf distclean
waf configure build
```

Flash the firmware with

```bash
waf flash
```
or flash `build/keyword_spotting.bin` directly using `JFlashSPI`.