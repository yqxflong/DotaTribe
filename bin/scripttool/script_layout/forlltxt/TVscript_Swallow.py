##############################
#The script used to transfer value from the column to other column for all files in folder
#Author:Johny
#Others:this script can not transfer the end column
###
import os,re
###############The Params Should be Set First#########
classColumn=3		#the class column
#################
CN1=r'CMenu'
CN2=r'CPriorityLayerColor'
CN3=r'CTableView'
CN4=r'CNode'
CN5=r'CCMenu'
CN6=r'CImMenu'
CN7=r'CTabMenu'
CN8=r'HWMoreItem'
#################
sourceColumn=9		#the source column
desColumn=5			#the destination column
newSourceValue=r'0'	#the new value of source column should be set
##########File Config######################
path='.'			#the directory path
flag='\t'			#the signal need to be split
filetype=r'.txt'	#the type of file need work
filekey=r'll_'		#the signal of the file need work
######################################################

############The sub method##############
def transferValue(row,line,source,des,classcolumn):
	if(row==0):
		return line
	newline=""
	tmp=line.split(flag)
	length=len(tmp)
	#firstly get the Desvalue
	classname=tmp[classcolumn]
	if(CN1 in classname or CN2 in classname or CN3 in classname or CN4 in classname or CN5 in classname or CN6 in classname or CN7 in classname or CN8 in classname):
		if(tmp[source]==r'1'):
			tmp[desColumn]=r'0'
		else:
			tmp[desColumn]=r'1'
		tmp[source]=newSourceValue
	else:
		return line	
	#circle will transfer the value
	for column in range(0,length):
		newline+=tmp[column]
		if(column!=length-1):
			newline+=flag	
	return newline



######The main method should be invoked firstly######
def	foo():
	for file in os.listdir(path):
		fname,fext=os.path.splitext(file)
		if(fext==filetype and filekey in fname):
			input=open(file,'r')
			lines=input.readlines()
			input.close()
			output=open(file,'w')
			row=0
			for line in lines:
				newline=transferValue(row,line,sourceColumn,desColumn,classColumn)
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