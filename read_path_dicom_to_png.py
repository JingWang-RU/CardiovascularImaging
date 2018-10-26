# author: jiw2026@med.cornell.edu
# time: Oct. 26th
# function: read path which contains dicom images and generate images

import time
import os
import re
from readDicom import read_dicom_to_png

def read_path_generate_png(path_file, main_dir):
    #path_file: files_dicom_path_200.txt
    start_time = time.time()
    with open(path_file) as f:
        pathes = f.read().splitlines()
    f.close()
    for subdir in pathes:
        pid = re.split('/', subdir)
        save_dir = main_dir + pid[4] + '/'
        if ~os.path.exists(save_dir): #pid[4] is like 31234234-1
            os.makedirs(save_dir)
            for dicom_file in os.listdir(subdir): # there maybe files other than dicom
                if dicom_file != 'DICOMDIR':
                    if dicom_file.endswith('.dcm'):
                        img_file = dicom_file[:-4] + '.png'
                    else:
                        img_file = dicom_file + '.png'

                    read_dicom_to_png(subdir + '/' + dicom_file, save_dir + img_file)
    print("--- time %s seconds ---" % (time.time() - start_time))

if __name__ == '__main__':
    # path_file contains the path of the dicom file, e.g. ***.dioom
    #path_file = 'test_dicom_path.txt'
    path_file ='files_dicom_path_200.txt'
    read_path_generate_png(path_file, './paradymDICOMpng/')
