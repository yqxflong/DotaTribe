#!/use/bin/python
# buildandroid.py
# Anthor: ShaoBing
# Function: Use to build apk


import sys
import os, os.path
import shutil
import string
from optparse import OptionParser





def copy_files(src,dst):
	'''
	'''
	for item in os.listdir(src):
		path = os.path.join(src,item)
		if not item.startswith('.') and not item.endswith('.gz') and os.path.isfile(path):
			shutil.copy(path,dst)
		if os.path.isdir(path):
			new_dst = os.path.join(dst,item)
			os.mkdir(new_dst)
			copy_files(path, new_dst)

def copy_resource(resources_dir,assets_dir):
	'''
	'''
	# remove assets_dir if existed
	if os.path.isdir(assets_dir):
		shutil.rmtree(assets_dir)

	# copy resources
	os.mkdir(assets_dir)
	if os.path.isdir(resources_dir):
		copy_files(resources_dir,assets_dir)

def ParseDependenceDirs(dependence_dirs):
	if dependence_dirs == "":
		return ""
	else:
		return dependence_dirs.split(';')


def BuildAndroidProject(channel,android_project_dir,target_platform):
	if not os.path.isdir(android_project_dir):
		raise Exception('android project directory %s is not a available path.' % (android_project_dir))
		sys.exit(1)

	# COMMAND: Update the project's build.xml file.
	projectconfig = 'android update project -p %s -t android-%s -n DOTA_%s' % (android_project_dir,target_platform,channel)
	# COMMAND: Clean Project
	projectclean  = 'ant clean -buildfile %s' % (android_project_dir)
	# COMMAND: Build Project
	projectBuild  = 'ant debug -buildfile %s' % (os.path.join(android_project_dir,"build.xml"))

	if os.system(projectconfig) != 0:
		raise Exception("Update the project's build.xml file Failed.")
		return -1

	if os.system(projectclean) != 0:
		raise Exception("Clean Project Failed.")
		return -1

	if os.system(projectBuild) != 0:
		raise Exception('Build Project Failed. [%s]' % projectBuild)
		return -1

	return 0


def doBuild(channel,android_project_dir,target_platform,android_project_dependence,resources_dir):
	depend_dirs = ParseDependenceDirs(android_project_dependence)
	for d_dir in depend_dirs:
		if BuildAndroidProject(channel,d_dir,target_platform) < 0:
			raise Exception("Build the project Failed")
			sys.exit(1)

	print "Copy Resources..."
	assets_dir = os.path.join(android_project_dir,"assets/resource")
	print 'From %s to %s' % (resources_dir, assets_dir)
	copy_resource(resources_dir,assets_dir)
	print "Copy Done."

	if BuildAndroidProject(channel,android_project_dir,target_platform) < 0:
		raise Exception("Build the porject Success")
		sys.exit(1)

def BuildDynamicLibrary(android_project_dir):
	buildnative = '%s %s'% ("python",os.path.join(android_project_dir,"build_native.py"))
	if os.system(buildnative) != 0:
		raise Exception('BuildDynamicLibrary Falied! [%s]' % buildnative)
		sys.exit(1)


#--------------------------main-------------------------
if __name__ == '__main__':
	parser = OptionParser(usage="%prog [-p] PROJECT_DIR [-t] TARGET_PLATFORM [-r] RESOURCES_DIR [-d] DEPENDENCE_DIRS", version="%prog 1.0")
	parser.add_option("-c","--channel",action="store",dest="channel",default="Empty",
		help="Channel.Default is Empty.")
	parser.add_option("-p",action="store",dest="project_dir",default="",
		help='Android Project Path. Default is NULL')
	parser.add_option("-t",action="store",dest="target_platform",default="10",type="int",
		help="Target Android Platform. Default is 10")
	parser.add_option("-d","--dependence",action="store",dest="dependence_dirs",default="",
		help="Android Project's Addtional library. Default is NULL. Muti-Directory use ';' apart.")
	parser.add_option("-r","--resources",action="store",dest="resources_dir",default="",
		help="Project's resources directory. Default is NULL.")
	(opts,args) = parser.parse_args()
	if opts.project_dir == "" :
		parser.print_usage()
		sys.exit(1)

	doBuild(opts.channel,opts.project_dir,opts.target_platform,opts.dependence_dirs,opts.resources_dir)
