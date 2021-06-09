import tensorflow as tf
from qkeras.utils import _add_supported_quantized_objects
import numpy as np
from sklearn.metrics import accuracy_score
from sklearn import metrics
from sklearn.utils import shuffle
import matplotlib.pyplot as plt
import numpy
import hls4ml
import matplotlib.pyplot as plt
import os
import sys
import common as com
import keras_model

def print_dict(d, indent=0):
    align=20
    for key, value in d.items():
        print('  ' * indent + str(key), end='')
        if isinstance(value, dict):
            print()
            print_dict(value, indent+1)
        else:
            print(':' + ' ' * (20 - len(key) - 2 * indent) + str(value))

# load parameter.yml of HLS CONFIG
args = com.command_line_chk()
param = com.yaml_load(args.config)

def is_tool(name):
    from distutils.spawn import find_executable
    return find_executable(name) is not None

print('-----------------------------------')
if not is_tool('vivado_hls'):
    print('Xilinx Vivado HLS is NOT in the PATH')
else:
    print('Xilinx Vivado HLS is in the PATH')
print('-----------------------------------')

# AD03
model_file = param['model_dir']
board_name = param['board_name']
acc_name = param['acc_name']
    
if not os.path.exists(model_file):
    print("{} model not found at path ".format(model_file))
model = keras_model.load_model(model_file)
model.summary()

interface = 'm_axi' # 's_axilite', 'm_axi', 'hls_stream'
axi_width = 8 # 16, 32, 64
implementation = 'serial' # 'serial', 'dataflow'

#hls4ml.model.optimizer.OutputRoundingSaturationMode.layers = ['Activation']
#hls4ml.model.optimizer.OutputRoundingSaturationMode.rounding_mode = 'AP_RND'
#hls4ml.model.optimizer.OutputRoundingSaturationMode.saturation_mode = 'AP_SAT'

# for AD03+Pynq (original)
hls_config = param['HLSConfig']
# for AD04+Arty (new, can work for both)
#hls_config = hls4ml.utils.config_from_keras_model(model, granularity='name')
#hls_config['Model']['ReuseFactor'] = param['REUSE']
#hls_config['Model']['Strategy'] = param['Strategy']
#hls_config['Model']['Precision'] = param['accum_t']
#hls_config['LayerName']['input_1']['Precision'] = param['input_precision']
#for layer in hls_config['LayerName'].keys():
#    hls_config['LayerName'][layer]['accum_t'] = param['accum_t']
#    hls_config['LayerName'][layer]['ReuseFactor'] = param['REUSE']

output_dir = param['output_dir']
backend_config = hls4ml.converters.create_backend_config(fpga_part=param['fpga_part'])
backend_config['ProjectName'] = acc_name
backend_config['KerasModel'] = model
backend_config['HLSConfig'] = hls_config
backend_config['OutputDir'] = param['output_dir']
backend_config['Backend'] = param['Backend']
backend_config['Interface'] = interface
backend_config['IOType'] = param['IOType']
backend_config['AxiWidth'] = str(axi_width)
backend_config['Implementation'] = implementation
backend_config['ClockPeriod'] = 10
backend_config['InputData'] = 'input_features.dat'
backend_config['OutputPredictions'] = 'input_features.dat'

print("-----------------------------------")
print_dict(backend_config)
print("-----------------------------------")

# This is under the assumption that 
# 1. all the machines have the same number of wave files
# 2. all of the wave files have the same number of frames
# 3. all of the frames have the same length

X_npy = './test_data/downsampled_128_5_to_32_4_skip_method.npy'
y_npy = './test_data/downsampled_128_5_to_32_4_ground_truths_skip_method.npy'

#load processed test data
from sklearn.utils import shuffle
X = np.load(X_npy, allow_pickle=True)
y = np.load(y_npy, allow_pickle=True)
y_keras = []
#use a quarter of the test_set to save time
for i in range(len(X)):
    quarter = int(len(X[i])/4)
    assert len(X) == len(y)
    X[i], y[i] = X[i][0:quarter],  y[i][0:quarter]

machine_count=len(X)
wav_count=len(X[0])
frame_count=len(X[0][0])
frame_length=len(X[0][0][0])

print('Machine count: {}'.format(machine_count))
print('Wave count: {}'.format(wav_count))
print('Frame count: {}'.format(frame_count))
print('Frame length: {}'.format(frame_length))

# Save the first N frames of the first wave file of the first machine
N=1
f = open('input_features.dat', 'w')
for j in range(N):
    for k in range(frame_length):
        f.write('{} '.format(X[0][0][j][k]))
    f.write('\n')
f.close()

y_pred = model.predict(X[0][0][0:N].reshape((N,128)))

f = open('output_predictions.dat', 'w')
for j in range(N):
    for k in range(frame_length):
        f.write('{} '.format(y_pred[j][k]))
    f.write('\n')
f.close()

hls_model = hls4ml.converters.keras_to_hls(backend_config)
_ = hls_model.compile()

y_hls = hls_model.predict(X[0][0][0:N].reshape((N,128)))
print('model     :', y_pred)
print('hls_model :', y_hls)

# to be updated to work automatically later
#hls_model.build(csim=False,synth=True,export=True,cosim=False,validation=False)

# perform synth
os.system('/bin/bash -c "cp ../inference/hls/patches/anomaly_detector_axi.* {output_dir}/firmware/"'.format(output_dir=output_dir))
os.system('/bin/bash -c "cp ../inference/hls/patches/anomaly_detector_test.cpp {output_dir}/"'.format(output_dir=output_dir))
os.system('/bin/bash -c "cd {output_dir} && vivado_hls -f build_prj.tcl csim=1 synth=1 export=1 cosim=0 validation=0"'.format(output_dir=output_dir))

# perform CSIM on written test bench
os.system('/bin/bash -c "cd ../inference/sys/{board_name} && make clean sys ACC={acc_name} INTERFACE={interface}"'.format(board_name=board_name,acc_name=acc_name,interface=interface))

#perform IP integration of synthesized HLS
os.system('/bin/bash -c "cd ../inference/sdk/{board_name} && make clean sdk-harness ACC={acc_name} SAMPLE_COUNT=10"'.format(board_name=board_name,acc_name=acc_name))

#write SDK project and flash to board
os.system('/bin/bash -c "cd ../inference/sdk/{board_name} && make gui"'.format(board_name=board_name))
