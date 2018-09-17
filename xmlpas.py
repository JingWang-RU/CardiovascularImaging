import lxml.etree as et
import os,sys
#author: Jing jiw2026@med.cornell.edu
#function: read xml annotation from Medis software
#time: Sept. 14th 2018
# example:
# python xmlpas.py lad attraction_points_vessel_wall pos  original_image_tags studyddate
# python xmlpas.py ./lad/ attraction_points_lumen pos
# python xmlpas.py ./lad/ pathline pos
# python xmlpas.py ./lad/ transformation_matrices Item
def readxmltotxt(path, xmlf, tag):
  wpath = path + '/xml/'
  if not os.path.exists(wpath):
    os.makedirs(wpath)
  f = open(path + xmlf + '.xml', "r")
  #f = open("attraction_points_lumen.xml","r")
  xml = f.read()
  #wfile = open("lumen_pos.txt","w")
  wfile = open(wpath + xmlf + '_' + tag + '.txt',"w") # _* is the tag
  tree = et.fromstring(xml)
  for name in tree.xpath('//' + tag):
    wfile.write(name.text.strip()+'\n')
    #print name.text.strip()
  f.close()
  wfile.close()

if __name__ == "__main__":
     readxmltotxt(sys.argv[1], sys.argv[2], sys.argv[3])
