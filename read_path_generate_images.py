# author: jiw2026@med.cornell.edu
# time: Oct. 25th
# function: read path which contains dicom images and generate images

import time
import os
import re
from readDicom import read_dicom_to_png
import multiprocessing
from joblib import Parallel, delayed
import pydicom 
def generatepng(subdir, main_dir):
    pid = re.split('/', subdir)
    save_dir = main_dir + pid[5] + '/'
    if not os.path.exists(save_dir):  # pid[4] is like 31234234-1
        os.makedirs(save_dir)
    if len(os.listdir(save_dir)) == 0: 
    #if abs(len(os.listdir(save_dir))-len(os.listdir(subdir))) >1:
        print(subdir)
        print("%s %d %d" %(save_dir,len(os.listdir(save_dir)),len(os.listdir(subdir))))
        for dicom_file in os.listdir(subdir):
            start_time = time.time()
            if os.path.isfile(subdir + '/' + dicom_file):
                #if dicom_file != 'DICOMDIR' and dicom_file!='DicomDir':
                if dicom_file.endswith('.dcm'):
                  img_file = dicom_file[:-4] + '.png' 
                elif dicom_file.startswith('IM'):
                  img_file = dicom_file + '.png'
                else:
                  continue
                if not os.path.exists(save_dir + img_file):
                  read_dicom_to_png(subdir + '/' + dicom_file, save_dir + img_file)
                  print("---%s time %s seconds ---" % (dicom_file, (time.time() - start_time)))
        
def read_path_generate_png(path_file, main_dir):
    num_cores = multiprocessing.cpu_count()

    #path_file: files_dicom_path_200.txt
    with open(path_file) as f:
        pathes = f.read().splitlines()
    f.close()
    results = Parallel(n_jobs=num_cores)(delayed(generatepng)(i,main_dir) for i in pathes)

if __name__ == '__main__':
    # path_file contains the path of the dicom file, e.g. ***.dioom
    path_file = 'files_dicom_path_200.txt'
    read_path_generate_png(path_file, './paradymDICOMpng/')
