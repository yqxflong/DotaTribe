#!/usr/bin/python
# dotatribe_outapk.py
# Author: Shaobing
# Function: Build Apk for dotatribe

import sys
import os, os.path
import shutil
import string
import re
import xml.dom.minidom
from optparse import OptionParser
from ftplib import FTP


#
#The settings from 'config.xml' file
#
config_xml="config.xml"
#
#

class Channel:
	''' Channel Class. Include id, name, path, dependent path, target platform etc..
	'''
	def __init__(self,name,path,dependent_path,target_platform,ip,port):
		self.name = name
		self.path = path
		self.dependent_path = dependent_path
		self.target_platform = target_platform
		self.ip = ip
		self.port = port 

	def output(self):
		print self.name,self.path,self.dependent_path,self.target_platform,self.ip,self.port


Channel_List = {}


config_h_status = "win32"
isFirstBuild = True


def read_xml(file):
	global resource_path,output_dir,Channel_List
	dom = xml.dom.minidom.parse(file)
	root = dom.documentElement
	for node in root.childNodes:
		if node.nodeType == node.ELEMENT_NODE:
			if node.nodeName == "resource":
				resource_path = node.childNodes[0].nodeValue
			elif node.nodeName == "outputdir":
				output_dir = node.childNodes[0].nodeValue
			elif node.nodeName == "channelconfig":
				for _node in node.getElementsByTagName("channel"):
					_name = _node.getAttribute("name")
					_projdir = _node.getElementsByTagName("projectdir")[0].childNodes[0].nodeValue.encode('utf-8','ignore')
					_targetplatform = int(_node.getElementsByTagName("targetplatform")[0].childNodes[0].nodeValue)
					_ip = node.getElementsByTagName("ip")[0].childNodes[0].nodeValue.encode('utf-8','ignore')
					_port = node.getElementsByTagName("port")[0].childNodes[0].nodeValue.encode('utf-8','ignore')
					_dependdir = ""
					if _node.getElementsByTagName("dependentdir"):
						_dependdir = _node.getElementsByTagName("dependentdir")[0].childNodes[0].nodeValue.encode('utf-8','ignore')
					ch = Channel(_name,_projdir,_dependdir,_targetplatform,_ip,_port)
					Channel_List[_name] = ch
					#Channel_List[_name].output()

def clean_all():
	'''
	'''
	for ch in Channel_List:
		clean(ch)

def clean(channel):
	'''
	'''
	pChannel = Channel_List[channel]
	# remove .so
	so_path = os.path.join(pChannel.path,"libs/armeabi/libgame.so")
	if os.path.isfile(so_path):
		os.remove(so_path)
	# remove resources in proj_dir
	asset_path = os.path.join(pChannel.path,"assets/resource")
	if os.path.exists(asset_path):
		shutil.rmtree(asset_path)
	# remove obj dir in proj_dir
	obj_path = os.path.join(pChannel.path,"obj")
	if os.path.exists(obj_path):
		shutil.rmtree(obj_path)
	# clean proj
	cmd = 'ant clean -buildfile %s' % (pChannel.path)
	if os.system(cmd) != 0:
		raise Exception("Clean Project Failed.")
		return -1


def build_all_channel():
	'''
	'''
	for ch in Channel_List:
		build_channel(ch)

def build_channel(channel):
	'''
	'''
	pChannel = Channel_List[channel]
	if pChannel.name == "original":
		config_h_android_to_win32()
	else:
		config_h_win32_to_android()
	build_template(pChannel.name,pChannel.path,pChannel.target_platform,resource_path,pChannel.dependent_path)
	src = os.path.join(pChannel.path,"bin")
	global output_dir
	dst = output_dir
	for _file in os.listdir(src):
		if _file.endswith(".apk"):
			shutil.copy(os.path.join(src,_file),dst)




def build_template(channel,project_path,target_platform,resource_path,dependent_path):
	''' 1. Build Dynamic Library
		2. Copy .so library to project_path
		3. Operate Particular Resource Files
		4. Build apk
		5. Re-Operate Particular Resource Files
	'''
	# Build Dynamic Library
	so_path = build_dynamic_library()
	# Copy Dynamic Library. If channel is original, dont copy
	if not channel == "original" :
		n_so_path = os.path.join(project_path,"libs/armeabi/")
		shutil.copy(so_path,n_so_path)
	# Operate Particular Resource Files
	operate_particular_resource_files(channel,resource_path)
	# Build Apk
	buildapk_path = os.path.join(os.path.dirname(os.path.realpath(__file__)),"buildandroid.py")
	if dependent_path == "" :
		buildapk_options = '-c %s -p %s -t %s -r %s' % (channel,project_path,target_platform,resource_path)
	else:
		buildapk_options = '-c %s -p %s -t %s -r %s -d %s' % (channel,project_path, target_platform, resource_path, dependent_path)
	cmd = '%s %s %s' % ("python", buildapk_path, buildapk_options)
	print "[build_template]=====cmd===%s" %cmd
	if os.system(cmd) != 0:
		raise Exception('Build %s Apk Failed. [%s]' % (channel,cmd))
		sys.exit(1)
	# Re-Operate Particular Resource Files
	re_operate_particular_resource_files(channel,resource_path)



def operate_particular_resource_files(channel,resource_path):
	''' Change Ip And Port
		91 change resource/config/system.xml
		uc change resource/logo/logo.png
	'''
	global Channel_List
	filepath = os.path.join(resource_path,"config/system.xml")
	filepath_n = os.path.join(resource_path,"config/system.xml.tmp")
	f1 = open(filepath,"r+")
	f2 = open(filepath_n,"w")
	f2.write(
			re.sub(r'<GateWayURL value="http://\S+:\S+/"',r'<GateWayURL value="http://%s:%s/"' % (Channel_List[channel].ip,Channel_List[channel].port),f1.read())
		)
	f1.close()
	f2.close()
	os.remove(filepath)
	os.rename(filepath_n,filepath)

	if channel == "91" :
		filepath = os.path.join(resource_path,"config/system.xml")
		filepath_n = os.path.join(resource_path,"config/system.xml.tmp")
		f1 = open(filepath,"r+")
		f2 = open(filepath_n,'w')
		f2.write(
			re.sub(r'<LogoProcedureIdleTime value="1"/>',r'<LogoProcedureIdleTime value="3"/>',f1.read())
		)	
		f1.close()
		f2.close()
		os.remove(filepath)
		os.rename(filepath_n,filepath)
	elif channel == "uc" :
		normal_logo = os.path.join(resource_path,"image/logo/logo.png")
		other_logo = os.path.join(Channel_List["uc"].path,"logo.png")
		tmp_logo = os.path.join(Channel_List["uc"].path,"logo.png.tmp")
		shutil.copy(normal_logo,tmp_logo)
		os.remove(normal_logo)
		shutil.copy(other_logo,normal_logo)

def re_operate_particular_resource_files(channel,resource_path):
	''' Change Ip And Port
		91 change resource/config/system.xml
		uc change resource/logo/logo.png
	''' 
	global Channel_List
	filepath = os.path.join(resource_path,"config/system.xml")
	filepath_n = os.path.join(resource_path,"config/system.xml.tmp")
	f1 = open(filepath,"r+")
	f2 = open(filepath_n,"w")
	f2.write(
			re.sub(r'<GateWayURL value="http://\S+:\S+/"',r'<GateWayURL value="http://10.127.133.26:12007/"',f1.read())
		)
	f1.close()
	f2.close()
	os.remove(filepath)
	os.rename(filepath_n,filepath)

	if channel == "91" :
		filepath = os.path.join(resource_path,"config/system.xml")
		filepath_n = os.path.join(resource_path,"config/system.xml.tmp")
		f1 = open(filepath,"r+")
		f2 = open(filepath_n,'w')
		f2.write(
			re.sub(r'<LogoProcedureIdleTime value="3"/>',r'<LogoProcedureIdleTime value="1"/>',f1.read())
		)	
		f1.close()
		f2.close()
		os.remove(filepath)
		os.rename(filepath_n,filepath)
	elif channel == "uc" :
		normal_logo = os.path.join(resource_path,"image/logo/logo.png")
		other_logo = os.path.join(Channel_List["uc"].path,"logo.png")
		tmp_logo = os.path.join(Channel_List["uc"].path,"logo.png.tmp")
		shutil.copy(tmp_logo,normal_logo)
		os.remove(tmp_logo)

def config_h_win32_to_android():
	''' Update DotaGameConfig.h file. This function convert it from Win32 version to Android version
	'''
	global config_h_status
	if config_h_status == "win32":
		dotaconfig_header = os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../include/DotaGameConfig.h")
		dotaconfig_header_t = os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../include/DotaGameConfig.h.tmp")
		f1 = open(dotaconfig_header,"r+")
		f2 = open(dotaconfig_header_t,'w')
		f2.write(
			re.sub(r"/*#define kENABLE_PLATFORM_SDKANDROID",r"#define kENABLE_PLATFORM_SDKANDROID",
				re.sub(r"/*#define kENABLE_PLATFORM_SDKIOS",r"//#define kENABLE_PLATFORM_SDKIOS",
					re.sub(r"/*#define kENABLE_PLATFORM_PC",r"//#define kENABLE_PLATFORM_PC",f1.read())
					)
				)
			)
		f1.close()
		f2.close()
		os.remove(dotaconfig_header)
		os.rename(dotaconfig_header_t,dotaconfig_header)
		config_h_status = "android"

def config_h_android_to_win32(): 
	''' Recover DotaGameConfig.h file. This function convert it from Android version to Win32 version.
	'''
	global config_h_status
	if config_h_status == "android":
		dotaconfig_header = os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../include/DotaGameConfig.h")
		dotaconfig_header_t = os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../include/DotaGameConfig.h.tmp")
		f1 = open(dotaconfig_header,"r+")
		f2 = open(dotaconfig_header_t,'w')
		f2.write(
			re.sub(r"/*#define kENABLE_PLATFORM_SDKANDROID",r"//#define kENABLE_PLATFORM_SDKANDROID",
				re.sub(r"/*#define kENABLE_PLATFORM_SDKIOS",r"#define kENABLE_PLATFORM_SDKIOS",
					re.sub(r"/*#define kENABLE_PLATFORM_PC",r"#define kENABLE_PLATFORM_PC",f1.read())
					)
				)
			)
		f1.close()
		f2.close()
		os.remove(dotaconfig_header)
		os.rename(dotaconfig_header_t,dotaconfig_header)
		config_h_status = "win32"


def build_dynamic_library():
	'''
	'''
	global isFirstBuild
	buildnative_path = os.path.join(os.path.dirname(os.path.realpath(__file__)),"./build_native.py")
	# buildnative options. [-s] NUM(0 or 1, 0 is default)
	# 0: Using prebuilt external
	# 1: Building external dependencies from source 
	buildnative_options = ""
	if isFirstBuild == True:
		buildnative_options = "-g"
		isFirstBuild = False
	else:
		buildnative_options = ""
	cmd = '%s %s' % (buildnative_path,buildnative_options)
	if os.system(cmd) != 0:
		raise Exception("Build dynamic library Failed!")
		sys.exit(1)	
	so_filepath = os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../proj.android/libs/armeabi/libgame.so")
	return so_filepath

def dobuild(channel):
	'''
	'''
	global output_dir
	for _file in os.listdir(output_dir):
		if _file.endswith(".apk"):
			os.remove(os.path.join(output_dir,_file))
	if channel == "All":
		build_all_channel()
		return
	channels = channel.split(';');
	for item in channels:
		build_channel(item)



def doclean(channel):
	'''
	'''
	global output_dir
	for _file in os.listdir(output_dir):
		if _file.endswith(".apk"):
			os.remove(os.path.join(output_dir,_file))
	if channel == "All":
		clean_all()
		return

	channels = channel.split(';');
	for item in channels:
		clean(item)



#------------------------------main------------------------------
if __name__ == '__main__':
	read_xml(config_xml)

	parser = OptionParser(usage="%prog [-c] CHANNEL",version="%prog 1.0")

	strChannels=', '.join(Channel_List.keys())
	strHelp='''The Channel of apk packet. Support Values: 
		%s, All; Muti-choice use ';' apart. Default is original.
		'''   %strChannels
	parser.add_option("-c","--channel",dest="channel",action="store",default="original",
		help=strHelp)
	parser.add_option("-r","--clean",action="store_true",dest="isclean",help="Means Clean Project. Not Build")
	(opts,args) = parser.parse_args()
	

	if opts.isclean == True:
		doclean(opts.channel)
	else:
		dobuild(opts.channel)

	config_h_android_to_win32()



	