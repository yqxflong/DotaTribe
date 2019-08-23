##############################
#Check if The Column Existed
#Author:Johny
###
import os,re

CHECK_COLUMN=5
CHECK_FLAG=r'CNode'
##########File Config######################
SP_FLAG='\t'			#the signal need to be split
END_FLAG='\n'
#####################CONST#####################
PATH_LAYOUT=r'E:/Project/dota/bin/trunk/client/dotatribe/resource/layout/'		#the directory path for layout
######################################################

############The sub method##############
def CheckColumn(line,row):
	if(row==0):
		return False
	tmp=line.split(SP_FLAG)
	theColumn=tmp[CHECK_COLUMN]
	# print "=======Check Culumn: %s ING====="  %theColumn

	if(CHECK_FLAG == theColumn):
		return True

	return False



######The main method should be invoked firstly######
def	foo():
	for file in os.listdir(PATH_LAYOUT):
		theFile=PATH_LAYOUT+file
		input=open(theFile,'r')
		lines=input.readlines()
		input.close()
		row=0
		for line in lines:
			result=CheckColumn(line,row)
			if(result):
				print r'===========FILE:  %s==========='  %file
				break
			row+=1
			
			
		
###########MAIN###############
if __name__=="__main__":
    print("Now We Start!!!")
    foo()
    print("We Are Finish!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The Author is Johny!!!!!!!!!!!!!!!!!!!!!!!")