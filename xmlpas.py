import lxml.etree as et
#author: Jing jiw2026@med.cornell.edu
#function: read xml annotation from Medis software
#time: Sept. 14th 2018
f = open("attraction_points_vessel_wall.xml","r")
#f = open("attraction_points_lumen.xml","r")
xml = f.read()
#wfile = open("lumen_pos.txt","w")
wfile = open("vesselwall_pos.txt","w") # _* is the tag
tree = et.fromstring(xml)
for name in tree.xpath("//pos"):
  wfile.write(name.text.strip()+'\n')

  #print name.text.strip()
f.close()
wfile.close()
'''

tree = et.fromstring(xml)
# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        print ("Encountered a start tag:", tag)

    def handle_endtag(self, tag):
        print ("Encountered an end tag :", tag)

    def handle_data(self, data):
        print ("Encountered some data  :", data)

# instantiate the parser and fed it some HTML
parser = MyHTMLParser()
parser.feed('<html><head><title>Test</title></head>'
            '<body><h1>Parse me!</h1></body></html>')
'''
