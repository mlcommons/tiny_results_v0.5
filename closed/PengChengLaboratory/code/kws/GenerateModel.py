import os
import binascii

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
    toByteBuffer("kws_ref_model.tflite","model.cc")