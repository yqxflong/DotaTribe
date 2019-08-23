##############################
#The script used to remove the column for all files in folder
#Author:Johny
#Others:this script can not insert column to the end of line
###
import os,re
###############The Params Should be Set First#########
columnNum=3			#the column need to be removed
path='.'			#the directory path
flag='\t'			#the signal need to be split
filetype=r".txt"	#the type of file need work
######################################################

############The sub method###########
def removeStringByNum(line,num):
	newline=""
	tmp=line.split(flag)
	length=len(tmp)
	for column in range(0,length):
		if(column!=num):
			if(column!=length-1):
				newline+=tmp[column]+flag
			else:
				newline+=tmp[column]
	return newline



######The main method should be invoked firstly######
def	foo():
	for file in os.listdir(path):
		fname,fext=os.path.splitext(file)
		if(fext==filetype):
			input=open(file,'r')
			lines=input.readlines()
			input.close()
			output=open(file,'w')
			for line in lines:
				newline=removeStringByNum(line,columnNum)
				print newline
				output.write(newline)
			output.close()
		
###########MAIN###############
if __name__=="__main__":
    print("Now We Start Remove The Column!!!")
    foo()
    print("We Are Finish!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The Author is Johny!!!!!!!!!!!!!!!!!!!!!!!")