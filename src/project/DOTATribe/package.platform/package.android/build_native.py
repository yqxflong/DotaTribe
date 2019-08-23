#!/use/bin/python
# build_native.py
# anthor: Shaobing
# funtcion: Use to build dynamic library


import sys
import os, os.path
import shutil
import re
from optparse import OptionParser

def get_num_of_cpu():
	''' The build process can be accelerated by running multiple concurrent job processes using the -j-option.
	'''
	try:
		platform = sys.platform
		if platform == 'win32':
			if 'NUMBER_OF_PROCESSORS' in os.environ:
				return int(os.environ['NUMBER_OF_PROCESSORS'])
			else:
				return 1
		else:
			from numpy.distutils import cpuinfo
			return cpuinfo.cpu._getNCPUs()
	except Exception:
		print "Can't know cpuinfo, use default 1 cpu"
		return 1

def check_environment_variables_ndk():
	'''
	'''
	try:
		NDK_ROOT = os.environ['NDK_ROOT']
	except Exception:
		print 'NDK_ROOT not defined. Please define NDK_ROOT in your environment'
		sys.exit(1)
	return NDK_ROOT




def build(buildexternal):
	'''
	'''
	ndk_root = check_environment_variables_ndk()
	project_root = os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../../")
	ndk_module_path = ''

	num_of_cpu = get_num_of_cpu()
	platform = sys.platform
	if platform == 'win32':
		if buildexternal == True:
			ndk_module_path = 'NDK_MODULE_PATH=%s;%s/cocos2dx/platform/third_party/android/source' % (project_root,project_root)
		else:
			ndk_module_path = 'NDK_MODULE_PATH=%s;%s/cocos2dx/platform/third_party/android/prebuilt' % (project_root,project_root)
	else:
		if buildexternal == True:
			ndk_module_path = 'NDK_MODULE_PATH=%s:%s/cocos2dx/platform/third_party/android/source' % (project_root,project_root)
		else:
			ndk_module_path = 'NDK_MODULE_PATH=%s:%s/cocos2dx/platform/third_party/android/prebuilt' % (project_root,project_root)


	#proj.android path
	path_proj_android=os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../proj.android")

	command = '%s -j%d -C %s %s' % (os.path.join(ndk_root,"ndk-build"), num_of_cpu, path_proj_android, ndk_module_path)
	print "[build]===========command: %s"  %command
	if os.system(command) != 0:
		raise Exception("Build dynamic library for project fails!")
		sys.exit(1)

def generate_source_cpp():
	''' update the newest source.cpp file
	'''
	sourcecpp = os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../source.cpp")
	print "[generate_source_cpp]=====sourcecpp: %s"  %sourcecpp
	if os.path.exists(sourcecpp):
		os.remove(sourcecpp)
	output = open(sourcecpp,'w+')
	srcdir = os.path.join(os.path.dirname(os.path.realpath(__file__)),"../../src")
	print "[generate_source_cpp]=====srcdir: %s"  %srcdir
	for item in os.listdir(srcdir):
		if not ((item.endswith(".c")) or (item.endswith(".cpp"))):
			continue
		header = '#include "%s"\n' % os.path.join(srcdir,item)
		output.write(header)


#-----------------------main--------------------
if __name__ == '__main__':
	parser = OptionParser()
	parser.add_option("-s",action="store_true",dest="buildexternal",help='Build externals from source')
	parser.add_option("-g",action="store_true",dest="buildsource",default=False,help='Generate source.cpp or not. Has -g means build.')
	(opts,args) = parser.parse_args()
	print opts
	if opts.buildsource == True:
		generate_source_cpp()
	build(opts.buildexternal)

