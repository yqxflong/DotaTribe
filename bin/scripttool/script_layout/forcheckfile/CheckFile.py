##############################
#Check CCLabelTTF's FontStyleID
#Put the script in bin\client\debug\dotatribe
#Author:Johny
#Others:this script can not insert column to the end of line
###
import os,re,string
###############The Params Should be Set First#########
CLASS=r'CCLabelTTF'
COLUMN_CLASS=5
COLUMN_FSID=9
#####################CONST#####################
filetype=r".txt"	#the type of file need work
filekey=r'll_'		#the key of the file
PATH_BASE=r'resource/layout/'				#the base path
PATH_IPHONE4=r'./'+PATH_BASE			#the directory path for iphone4
PATH_IPAD=r'./ipad/'+PATH_BASE			#the directory path for ipad
PATH_IPHONE5=r'./iphone5/'+PATH_BASE			#the directory path for iphone5
######################################################

############Check in iPAD##############
def check_file(path,srcFile):
	haveFile=False
	for file in os.listdir(path):
		fname,fext=os.path.splitext(file)
		if(fext==filetype and filekey in fname):
			#print fname
			if(srcFile==fname):
				haveFile=True
	if(haveFile==False):
		print r"The File is: %s" %srcFile

###############handle One Device layout files####################
def handle_One_layout(path):
	for file in os.listdir(path):
		fname,fext=os.path.splitext(file)
		if(fext==filetype and filekey in fname):
			#print fname
			check_file(PATH_IPAD,fname)

######The main method should be invoked firstly######
def	foo():
	handle_One_layout(PATH_IPHONE4)
		
###########MAIN###############
if __name__=="__main__":
    print("Now We Start Check!!!")
    foo()
    print("We Are Finish!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The Author is Johny!!!!!!!!!!!!!!!!!!!!!!!")