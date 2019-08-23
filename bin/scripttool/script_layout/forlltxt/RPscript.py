##############################
#The script used to remove Path for Files for all files in folder
#Author:Johny
###
import os,re,string
###############The Params Should be Set First#########
flag='\t'
end='\n'
FILEID=r'.png'
##########File Config######################
path='.'			#the directory path
filetype=r'.txt'	#the type of file need work
filekey=r'll_'		#the signal of the file need work
######################################################


#######check if is the path########
###if the ext is png,it's destination value###
def isPath(value):
	fname,fext=os.path.splitext(value)
	if(fext==FILEID):
		return True
	return False


############The sub method##############
def removeFilePath(line):
	#prepare var
	newline=""
	tmp=line.split(flag)
	length=len(tmp)
	#remove last '\n'
	tmp[length-1]=re.sub(end,"",tmp[length-1])
	for column in range(0,length):
		theValue=tmp[column]
		if(isPath(theValue)):
			newline+=flag+os.path.basename(theValue)	
		else:
			newline+=flag+theValue
	#remove first '\t'
	newline=string.replace(newline,flag,'',1)
	#add the end symbol
	newline+=end
	return newline



######The main method should be invoked firstly######
def	foo():
	for file in os.listdir(path):
		fname,fext=os.path.splitext(file)
		#check if the file extention and file's keyname meet the requirement
		if(fext==filetype and filekey in fname):
			input=open(file,'r')
			lines=input.readlines()
			input.close()
			output=open(file,'w')
			for line in lines:
				newline=removeFilePath(line)
				print newline
				output.write(newline)
			output.close()
			
			
		
###########MAIN###############
if __name__=="__main__":
    print("Now We Start!!!")
    foo()
    print("We Are Finish!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The Author is Johny!!!!!!!!!!!!!!!!!!!!!!!")