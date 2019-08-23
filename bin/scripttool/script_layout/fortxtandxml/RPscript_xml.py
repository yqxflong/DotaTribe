##############################
#The script used to remove Path and change Value for xml for all files in folder
#Author:Johny
###
from xml.etree.ElementTree import ElementTree,Element
import os
###############The Params Should be Set First#########
VALUE_KEY=r'.png'   #the key of the value
TAG_NAME=r'Name'    #xml tag
PROP_NAME=r'value'  #property of node
DST_PROP_NAME=r'Frame' #the destination of property name
##########File Config######################
path='.'			#the directory path
FILEEXT=r'.xml'     #the extension of the kind of files
######################################################



#######################handle xml Lib##########################
def getRoot(tree):
    root = tree.getroot()
    return root

def read_xml(in_path):
    tree = ElementTree()
    tree.parse(in_path)
    return tree

def write_xml(tree, out_path):
    tree.write(out_path, encoding="utf-8",xml_declaration=True)

def if_match(node, kv_map):
    for key in kv_map:
        if node.get(key) != kv_map.get(key):
            return False
    return True

#---------------search -----

def find_nodes(tree, path):
    return tree.findall(path)


def get_node_by_keyvalue(nodelist, kv_map):
    result_nodes = []
    for node in nodelist:
        if if_match(node, kv_map):
            result_nodes.append(node)
    return result_nodes

#---------------change -----

def change_node_properties(node, kv_map, is_delete=False):
    for key in kv_map:
        if is_delete:
            if key in node.attrib:
                 del node.attrib[key]
        else:
             node.set(key, kv_map.get(key))

def change_node_text(nodelist, text, is_add=False, is_delete=False):
    for node in nodelist:
        if is_add:
            node.text += text
        elif is_delete:
            node.text = ""
        else:
            node.text = text

def create_node(tag, property_map, content):
    element = Element(tag, property_map)
    element.text = content
    return element

def add_child_node(nodelist, element):
    for node in nodelist:
        node.append(element)

def del_node_by_tagkeyvalue(nodelist, tag, kv_map):
    for parent_node in nodelist:
        children = parent_node.getchildren()
        for child in children:
            if child.tag == tag and if_match(child, kv_map):
                parent_node.remove(child)
#####################################################################
###if the ext is png,it's destination value###
def isPath(value):
	fname,fext=os.path.splitext(value)
	if(fext==VALUE_KEY):
		return True
	return False
#####################################################################
#print the node detail
def print_node(node):
     print "node.tag:%s" % node.tag
     print "node.attrib:%s" % node.attrib

#real method to change the property under the rules
def handle_xmlfile_node(node):
    value=node.attrib[PROP_NAME]
    if(isPath(value)):
    	#delete old prop
    	change_node_properties(node,{PROP_NAME:value},True)
    	#add new prop
    	newValue=os.path.basename(value)
    	change_node_properties(node,{DST_PROP_NAME:newValue})
    	print_node(node)

#recursion for all nodes
def check_node(node):
	if(node.tag==TAG_NAME):
		handle_xmlfile_node(node)
	childs=node.getchildren()
	for child in childs:
		check_node(child)

def handle_xmlfile(file):
    tree=read_xml(file)
    root=getRoot(tree)
    nodes=root.getchildren()
    #find all nodes,and check each of them
    for node in nodes:
    	check_node(node)
    write_xml(tree,file)


######The main method should be invoked firstly######
def	foo():
	for file in os.listdir(path):
            fname,fext=os.path.splitext(file)
            if(fext==FILEEXT):
                print file
                handle_xmlfile(file)

			
		
###########MAIN###############
if __name__=="__main__":
    print("Now We Start!!!")
    foo()
    print("We Are Finish to remove path for all xml files!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The Author is Johny!!!!!!!!!!!!!!!!!!!!!!!")