# from tedivm in github pydicom
#function: read dicom images e.g. 321165
import numpy as np
import png
import pydicom
import os
import glob

def read_dicom_to_png(path, destination):
    # path: a dicom file **.dcm ; destination: a png or jpeg file
    ds = pydicom.dcmread(path)

    shape = ds.pixel_array.shape
        
        # Convert to float to avoid overflow or underflow losses.
    image_2d = ds.pixel_array.astype(float)

    # Rescaling grey scale between 0-255
    image_2d_scaled = (np.maximum(image_2d,0) / image_2d.max()) * 255.0
            
    # Convert to uint
    image_2d_scaled = np.uint8(image_2d_scaled)
        
    # Write the PNG file
    with open(destination, 'wb') as png_file:
       w = png.Writer(shape[1], shape[0], greyscale=True)
       w.write(png_file, image_2d_scaled)

if __name__ == "__main__":
    main_path = "./DICOM/32-2/Me1453569863/DICOM/ST00001/"
    for i in range(10,16):
     name = "SE000"+str(i)
     dicom_path = main_path + name + '/'
     #savepath = main_path + "imgJing/"
     savepath = main_path + name + "imgJing/"
     if not os.path.exists(savepath):
        os.makedirs(savepath)
     files_list = [f for f in os.listdir(dicom_path)]# if f.endswith(".dcm")]
     #files_list = [f for f in os.listdir(dicom_path)]# if f.endswith(".dcm")]

     for file in files_list:#glob.glob(dicom_path + "*.dcm"):
        img_file = file + '.png'#
        #img_file = file[:-4] + '.png'
        read_dicom_to_png(dicom_path + file, savepath + img_file)

