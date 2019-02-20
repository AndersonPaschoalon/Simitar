import xml.etree.ElementTree as ET

class XmlFirst:
    def __init__(self, xmlfile):
        self.tree = ET.ElementTree(file=xmlfile)
        self.root = self.tree.getroot()

    def getText(self, xpath):
        return self.root.find(xpath).text

    def getAttribute(self, xpath, atrib):
        return self.root.find(xpath).attrib.get(atrib)
