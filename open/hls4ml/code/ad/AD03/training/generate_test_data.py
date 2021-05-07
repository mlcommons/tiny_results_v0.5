"""
 @file   01_test.py
 @brief  Script for test
 @author Toshiki Nakamura, Yuki Nikaido, and Yohei Kawaguchi (Hitachi Ltd.)
 Copyright (C) 2020 Hitachi, Ltd. All right reserved.
"""

########################################################################
# import default python-library
########################################################################
import setGPU
import os
import os
os.environ['TF_CPP_MIN_LOG_LEVEL']='3'#jules: removes cuda alert for connecting to gpu
import glob
import sys
########################################################################
import pdb

########################################################################
# import additional python-library
########################################################################
import numpy
# from import
from tqdm import tqdm
from sklearn import metrics
# original lib
import common as com
import keras_model
########################################################################
# main 01_test.py
########################################################################
if __name__ == "__main__":

    args = com.command_line_chk()
    
    # load parameter.yaml
    param = com.yaml_load(args.config)

    # make output result directory
    os.makedirs(param["result_directory"], exist_ok=True)

    # load base directory
    dirs = com.select_dirs(param=param)

    # initialize lines in csv for AUC and pAUC
    csv_lines = []

    test_data_save_load_directory = "./test_data/downsampled_128_5_to_32_4_skip_method.npy"
    test_data_ground_truths_save_load_directory = "./test_data/downsampled_128_5_to_32_4_ground_truths_skip_method.npy"

    # loop of the base directory
    for idx, target_dir in enumerate(dirs):
        print("\n===========================")
        print("[{idx}/{total}] {dirname}".format(dirname=target_dir, idx=idx+1, total=len(dirs)))
        machine_type = os.path.split(target_dir)[1]

        print("============== MODEL LOAD ==============")
        # set model path
        model_file = "{model}/model_{machine_type}.h5".format(model=param["model_directory"],
                                                                machine_type=machine_type)

        machine_id_list = com.get_machine_id_list_for_test(target_dir)
        test_data = []
        test_data_ground_truths = []
        for id_str in machine_id_list:
            machine_test_data = []
            # load test file
            test_files, y_true = com.test_file_list_generator(target_dir, id_str)

            # setup anomaly score file path
            anomaly_score_csv = "{result}/anomaly_score_{machine_type}_{id_str}.csv".format(
                                                                                     result=param["result_directory"],
                                                                                     machine_type=machine_type,
                                                                                     id_str=id_str)
            anomaly_score_list = []

            print("\n============== BEGIN TEST FOR A MACHINE ID ==============")
            y_pred = [0. for k in test_files]
            for file_idx, file_path in tqdm(enumerate(test_files), total=len(test_files)):
                try:
                    data = com.file_to_vector_array(file_path,
                                                    n_mels=param["feature"]["n_mels"],
                                                    frames=param["feature"]["frames"],
                                                    n_fft=param["feature"]["n_fft"],
                                                    hop_length=param["feature"]["hop_length"],
                                                    power=param["feature"]["power"])
                except:
                    com.logger.error("file broken!!: {}".format(file_path))
                machine_test_data.append(data)
            test_data.append(machine_test_data)
            test_data_ground_truths.append(y_true)


            print("Shape of test_data is {}, shape of test_data_ground_truths is {}".format(numpy.shape(test_data), numpy.shape(test_data_ground_truths)))
            print("\n============ END OF TEST FOR A MACHINE ID ============")
        if not os.path.exists('./test_data'):
            os.makedirs('./test_data')
        numpy.save(test_data_save_load_directory,test_data)
        numpy.save(test_data_ground_truths_save_load_directory, test_data_ground_truths)
        print("Saved test data to {}".format(test_data_save_load_directory))
