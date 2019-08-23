##############################
#To Change Specify Column
#Author:Johny

###
import os,re
###############The Params Should be Set First#########
CHECK_COLUMN=5
EDIT_COLUMN=14
CHECK_CLASS=r'CPriorityLayerColor'
EDIT_VALUE=125
##########File Config######################
SP_FLAG='\t'			#the signal need to be split
END_FLAG='\n'
#####################CONST#####################
filetype=r".txt"	#the type of file need work
filekey=r'll_'		#the key of the file
PATH_CURR=r'./'
PATH_BASE=r'resource/layout/'				#the base path
PATH_IPHONE4=r'./'+PATH_BASE			#the directory path for iphone4
PATH_IPAD=r'./ipad/'+PATH_BASE			#the directory path for ipad
PATH_IPHONE5=r'./iphone5/'+PATH_BASE			#the directory path for iphone5
######################################################

############The sub method##############
def changeValue(row,line):
	if(row==0):
		return line
	newline=''
	tmp=line.split(SP_FLAG)
	length=len(tmp)
	#firstly check and edit the des value
	classname=tmp[CHECK_COLUMN]
	if(CHECK_CLASS in classname):
		tmp[EDIT_COLUMN]=EDIT_VALUE
	else:
		return line	
	#circle will edit the value
	for column in range(0,length):
		newline+=r'%s' %tmp[column]
		if(column!=length-1):
			newline+=SP_FLAG	
	return newline



######The main method should be invoked firstly######
def	foo():
	for file in os.listdir(PATH_CURR):
		fname,fext=os.path.splitext(file)
		if(fext==filetype and filekey in fname):
			input=open(file,'r')
			lines=input.readlines()
			input.close()
			output=open(file,'w')
			row=0
			newline=''
			for line in lines:
				newline=changeValue(row,line)
				print newline
				output.write(newline)
				row+=1
			output.close()
			
			
		
###########MAIN###############
if __name__=="__main__":
    print("Now We Start!!!")
    foo()
    print("We Are Finish!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The Author is Johny!!!!!!!!!!!!!!!!!!!!!!!")