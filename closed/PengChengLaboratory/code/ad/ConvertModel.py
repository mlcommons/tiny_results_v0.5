import os
import binascii
import argparse

parser = argparse.ArgumentParser(description="Convert tensorflow lite model into mmap")
parser.add_argument('--quantized', action='store_true', help = "Convert quantized version")
args = parser.parse_args()

Quantized = args.quantized

def str2bool(v):
    if isinstance(v, bool):
       return v
    if v.lower() in ('yes', 'true', 't', 'y', '1'):
        return True
    elif v.lower() in ('no', 'false', 'f', 'n', '0'):
        return False
    else:
        raise argparse.ArgumentTypeError('Boolean value expected.')

def toByteBuffer(inputFilename: str, outputFilename: str):
    def convert_to_c_array(bytes) -> str:
        hexstr = binascii.hexlify(bytes).decode("UTF-8")
        hexstr = hexstr.upper()
        array = ["0x" + hexstr[i:i + 2] for i in range(0, len(hexstr), 2)]
        array = [array[i:i+10] for i in range(0, len(array), 10)]
        return ",\n  ".join([", ".join(e) for e in array])
    
    if not os.path.isfile(inputFilename):
        raise FileNotFoundError(inputFilename + "Not Found!")

    tflite_binary = open(inputFilename, 'rb').read()
    ascii_bytes = convert_to_c_array(tflite_binary)
    c_file = \
            '#include "tinymlperf/model.h"\n\n' + \
            "alignas(8) const unsigned char g_model[] = {\n  " +\
             ascii_bytes +\
             "\n};\nconst unsigned int g_model_len = " + \
            str(len(tflite_binary)) + ";"
    open(outputFilename, "w").write(c_file)
if __name__ == "__main__":
    if not Quantized:
        toByteBuffer("tiny/v0.1/training/anomaly_detection/trained_models/ToyCar/baseline_tf23/model/model_ToyCar.tflite",\
                    "tinymlperf/anomaly_detection/model.cc")
        toByteBuffer("tiny/v0.1/training/image_classification/trained_models/pretrainedResnet.tflite",\
                    "tinymlperf/image_classification/model.cc")
        toByteBuffer("tiny/v0.1/training/visual_wake_words/trained_models/vww_96_float.tflite",\
                    "tinymlperf/person_detection/model.cc")
    else:            
        toByteBuffer("tiny/v0.1/training/anomaly_detection/trained_models/ToyCar/baseline_tf23/model/model_ToyCar_quant_fullint_micro.tflite",\
                    "tinymlperf/anomaly_detection/model.cc")
        toByteBuffer("tiny/v0.1/training/image_classification/trained_models/pretrainedResnet_quant.tflite",\
                    "tinymlperf/image_classification/model.cc")
        toByteBuffer("tiny/v0.1/training/visual_wake_words/trained_models/vww_96_int8.tflite",\
                    "tinymlperf/person_detection/model.cc")
    toByteBuffer("tiny/v0.1/training/keyword_spotting/trained_models/aww_ref_model.tflite",\
                    "tinymlperf/keyword_spotting/model.cc")