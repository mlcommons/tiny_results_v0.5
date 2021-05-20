# Training + converting RN06 with hls4ml

* Install miniconda from here: https://docs.conda.io/en/latest/miniconda.html

* Create the environment:
```bash
conda-env create -f environment.yml
```

* Activate the environment:
```bash
conda activate tiny-mlperf-env
```

* Train RN06:
```bash
python train.py -c RN06_pynqz2.yml
```

* Setup Vivado 2019.1
```bash
source <path_to_Vivado>/Vivado/2019.1/settings64.sh
```
* Get test data:
```bash
source get_test_data.sh
```

* Convert RN06:
```bash
python convert.py -c RN06_pynqz2.yml
```
