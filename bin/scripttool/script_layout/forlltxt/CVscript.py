##############################
#Change Column For Special Class
#Author:Johny
###
import os,re,string
###############The Params Should be Set First#########
CLASS=r'CCLabelTTF'
CLASS_IDX=5
FS_IDX=9
FS_VALUE_D=r'3'
FSIZE_IDX=10
C_R_IDX=11
C_G_IDX=12
C_B_IDX=13
#####################CONST#####################
SP_FLAG='\t'			#the signal need to be split
END_FLAG='\n'
FILE_EXT=r".txt"	#the type of file need work
FILE_KEY=r'll_'		#the key of the file
PATH_BASE=r'resource/layout/'				#the base path
PATH_RESOURCE=r'./'+PATH_BASE			#the directory path for resource
######################################################


#######check if is the path########
###if the ext is png,it's destination value###
def isPath(value):
	fname,fext=os.path.splitext(value)
	if(fext==FILEID):
		return True
	return False


############The sub method##############
def checkClassAndChangeColumn(row,line):
	ret=False
	if row==0:
		return line,ret
	#prepare var
	tmp=line.split(SP_FLAG)
	theClass=tmp[CLASS_IDX]
	if CLASS in theClass:
		theValue=tmp[FS_IDX]
		if theValue == r'0':
			ret=True
			tmp[FS_IDX]=FS_VALUE_D
		tmp[FSIZE_IDX]=r'0'
		tmp[C_R_IDX]=r'0'
		tmp[C_G_IDX]=r'0'
		tmp[C_B_IDX]=r'0'
	
		
############integrate arr to newline##############
	line_d=r''
	for item_d in tmp:
		line_d+=SP_FLAG+item_d
	#remove the first \t
	line_d=string.replace(line_d,SP_FLAG,'',1)
	return line_d,ret



######The main method should be invoked firstly######
def	handleFile(path):
	for file in os.listdir(path):
		fname,fext=os.path.splitext(file)
		#check if the file extention and file's keyname meet the requirement
		if(fext==FILE_EXT and FILE_KEY in fname):
			file=path+file
			input=open(file,'r')
			lines=input.readlines()
			input.close()
			output=open(file,'w')
			row=0
			for line in lines:
				newline,flag=checkClassAndChangeColumn(row,line)
				output.write(newline)
				row+=1
				if flag == True:
					print "==============Changed File=====%s"  %file
			output.close()
			
def	foo():
	handleFile(PATH_RESOURCE)
		
###########MAIN###############
if __name__=="__main__":
    print("Now We Start!!!")
    foo()
    print("We Are Finish!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The Author is Johny!!!!!!!!!!!!!!!!!!!!!!!")