# Note regarding the dataset used for benchmarks

- This benchmark generated a fp32 version of the `kws` dataset provided by the EEMBC Runner. To generate this dataset, please refer to `training/make_bin_files.py` in this directory.

- This script is a modification of the provided `make_bin_files.py` script provided by TinyML, which can be found [here](https://github.com/mlcommons/tiny/blob/master/v0.1/training/keyword_spotting/make_bin_files.py).

- For instructions regarding usage, refer to [here](https://github.com/mlcommons/tiny/tree/master/v0.1/training/keyword_spotting#create-binary-test-files).

- Once the dataset is generated, replace the dataset provided by the EEMBC Runner with the new fp32 dataset. Information regarding where to place this dataset is mentioned [here](https://github.com/eembc/ulpmark-ml#selecting-performance-mode).