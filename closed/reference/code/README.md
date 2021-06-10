The code for this reference submission is pulled from the [Tiny MLPerf V0.5 github repo](https://github.com/mlcommons/tiny/tree/master/v0.5). 

The structure of the repository is as follows:
* The pre-trained models are found in training along with the dataset, training and quantization scripts.
* The benchmark API is defined in API which includes the required submitter implemented functions.
* All four benchmarks have a reference submission which implement the benchmarks using TensorFlow Lite for Microcontrollers and Mbed on the reference platform.