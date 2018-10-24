# time: Oct. 24th 2018
# function: read files in a txt; each id should have 2 folders,like ***-1, ***-2
# author: jiw2026@med.cornell.edu

import os
import os.path

def write_filelist(main_path, save_file, id_file):
   files = os.listdir(main_path)
   #there maybe space or slash in the filename, e.g. 2343123 -1, 23413-2
   
   d = {}
   if ~os.path.exists(id_file):
    write_id_file = open(id_file, "w")
    for filename in files:
      # length of filename is never larger than 50
      if filename.find(' ')>0:
         pos = min(filename.find(' '), filename.find('-'))
      else:
         pos = filename.find('-')
      id = filename[:pos]
      if id not in d:
          d[id] = 1
          write_id_file.write(id + "\n")
      else:
          d[id] +=1
      
   write_id_file.close()
   
   miss_id = './ids_without_2CTs.txt'
   ct2_id = './ids_with_2CTs.txt'
   if ~os.path.exists(miss_id):
     w = open(miss_id, "w")
     wct = open(ct2_id, "w")
     for idx in d.keys():
        if d[idx] != 2:
           w.write(str(idx) + " " + str(d[idx]) + "\n")
        else:
           wct.write(str(idx) + "\n")
     w.close()
     wct.close()
   if ~os.path.exists(save_file):
     write_file = open(save_file, "w")
     for filename in files:
       write_file.write(filename+'\n')
     write_file.close()

if __name__ == "__main__":
   path = '/Volumes/HD-**/** DICOM_***/'
   save_file = './dicom_***_ids_oct24.txt'
   unique_file = './dicom_unique_id.txt'
   write_filelist(path, save_file, unique_file)
