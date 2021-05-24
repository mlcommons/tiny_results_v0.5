# Training + converting AD03 with hls4ml

* Install miniconda from here: https://docs.conda.io/en/latest/miniconda.html

* Create the environment:
```bash
conda-env create -f environment.yml
```

* Activate the environment:
```bash
conda activate tiny-mlperf-env
```
* download dataset for AD03:
```bash
./get_dataset.sh
```

* Train AD03:
```bash
python train.py -c AD03.yml
```

* Setup Vivado 2019.1
```bash
source <path_to_Vivado>/Vivado/2019.1/settings64.sh
```

* Get test data
```bash
python generate_test_data.py -c AD03.yml
```

* Convert AD03:
```bash
python convert.py -c pynqz2.yml
```
