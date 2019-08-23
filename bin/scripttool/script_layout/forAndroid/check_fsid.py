##############################
#Check FontStyle ID, if it's CCLabel, Assert the FontStyleID can not be 0
#if FSID is 0, it should be edited to 3
#Author:Johny

###
import os,re
###############The Params Should be Set First#########
CLASS_COLUMN=5
CHECK_COLUMN=9
CHECK_CLASS=r'DTAwardBoard'
ERROR_VALUE=r'0'
EDIT_VALUE=r'3'
##########File Config######################
SP_FLAG='\t'			#the signal need to be split
END_FLAG='\n'
#####################CONST#####################
PATH_LAYOUT=r'E:/Project/dota/bin/trunk/client/dotatribe/resource/layout/'		#the directory path for layout
PATH_LAYOUT_BRANCH=r'E:/Project/dota/bin/branches/2014-03-13-19-07/dotatribe/resource/layout/'
PATH_CUR=PATH_LAYOUT
######################################################

############The sub method##############
def checkFSID(row,line,file):
	if(row==0):
		return line
	newline=''
	file_flag=False
	tmp=line.split(SP_FLAG)
	length=len(tmp)
	#firstly check and edit the des value
	classname=tmp[CLASS_COLUMN]
	if(CHECK_CLASS in classname):
		fsid=tmp[CHECK_COLUMN]
		if(fsid == ERROR_VALUE):
			print '============ERROR File:  %s============='  %file
			tmp[CHECK_COLUMN]=EDIT_VALUE
			file_flag=True

			
	for column in range(0,length):
		newline+=r'%s' %tmp[column]
		if(column!=length-1):
			newline+=SP_FLAG	
			
	return newline



######The main method should be invoked firstly######
def	foo():
	for file in os.listdir(PATH_CUR):
		theFile=PATH_CUR+file
		input=open(theFile,'r')
		lines=input.readlines()
		input.close()
		output=open(theFile,'w')
		row=0
		newline=''
		for line in lines:
			newline=checkFSID(row,line,file)
			output.write(newline)
			row+=1
		output.close()

			
		
###########MAIN###############
if __name__=="__main__":
    print("Now We Start!!!")
    foo()
    print("We Are Finish!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The Author is Johny!!!!!!!!!!!!!!!!!!!!!!!")