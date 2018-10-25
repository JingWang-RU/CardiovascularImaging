# author:jiw2026@med.cornell.edu
# time: Oct 24th 2018
# function: each folder has many subfolders, find the subfoler with maximum number of files given id in ct2_file
import re
import os
import time
from collections import defaultdict

def main():
    # the files with two CTA
    # only read the directory in ct2_file
    ct2_file = './files_with_2CTs.txt'
    start_time = time.time()
    with open(ct2_file) as f:
        unique_id = f.read().splitlines()
    f.close()
    print("--- read ct2_file %s seconds ---" % (time.time() - start_time))

    dirName = '/Volumes/HD-***/****DICOM***/'
    dict_dicom = defaultdict(list)

    i = 0
    s_time = time.time()
    for path, subdir, files in os.walk(dirName):
        pid = re.split('/', path)
        #print(pid)
        if os.path.isdir(path) and pid[4] in unique_id:
            num_files = len(os.listdir(path))
            if pid[4] not in dict_dicom:
                i += 1
                if i%100==0:
                   print("--- number of files %d ---" % i)
                dict_dicom[pid[4]].append(path)
                dict_dicom[pid[4]].append(num_files)
            else:
                if num_files > dict_dicom[pid[4]][-1]:
                    dict_dicom[pid[4]] = [path, num_files]
    w1 = open('./files_dicom_path_200.txt', "w")
    w2 = open('./files_dicom_path_200_num.txt', "w")
    for v in dict_dicom.keys():
        w1.write(dict_dicom[v][0] + "\n")
        w2.write(dict_dicom[v][0] + "  " + str(dict_dicom[v][-1]) + "\n")
    w1.close()
    w2.close()
    print("--- read subdir %s seconds ---" % (time.time() - s_time))

if __name__ == '__main__':
    main()
