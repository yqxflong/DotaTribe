##############################
#The script used to Insert the column for all files in 3 folders-ipad,iphone5,iphone4
#Put the script in bin\client\debug\dotatribe
#Author:Johny
#Others:this script can not insert column to the end of line
###
import os,re,string
###############The Params Should be Set First#########
columnNum=29			#the column need to be added
columnHead=r'ANDROID-POS-Y'	#the column head need to be added
columnContent=r'0'	#the column content need to be added
SP_FLAG='\t'			#the signal need to be split
END_FLAG='\n'
#####################File Setting#####################
filetype=r".txt"	#the type of file need work
filekey=r'll_'		#the key of the file
PATH_BASE=r'resource/layout/'				#the base path
PATH_IPHONE4=r'./'+PATH_BASE			#the directory path for iphone4
PATH_IPAD=r'./ipad/'+PATH_BASE			#the directory path for ipad
PATH_IPHONE5=r'./iphone5/'+PATH_BASE			#the directory path for iphone5
######################################################

############The sub method##############
###The row is identify current row num##
def addStringByNum(row,line,num,head):
	newline=""
	tmp=line.split(SP_FLAG)
	length=len(tmp)
	#remove the last \n
	tmp[length-1]=string.replace(tmp[length-1],END_FLAG,'')
	for column in range(0,length):
		if(column==num):
			#add new content
			if(row==0):
				newline+=SP_FLAG+head
			else:
				newline+=SP_FLAG+columnContent
			#add the old content in the same column
			newline+=SP_FLAG+tmp[column]
		#add the old content
		else:
			newline+=SP_FLAG+tmp[column]
	#add the last \n
	newline+=END_FLAG
	#remove the first \t
	newline=string.replace(newline,SP_FLAG,'',1)
	return newline

###############handle One Device layout files####################
def handle_One_layout(path):
	for file in os.listdir(path):
		fname,fext=os.path.splitext(file)
		if(fext==filetype and filekey in fname):
			file=path+file
			input=open(file,'r')
			lines=input.readlines()
			input.close()
			output=open(file,'w')
			row=0
			for line in lines:
				newline=addStringByNum(row,line,columnNum,columnHead)
				print newline
				output.write(newline)
				row+=1
			output.close()

######The main method should be invoked firstly######
def	foo():
	handle_One_layout(PATH_IPHONE4);
		
###########MAIN###############
if __name__=="__main__":
    print("Now We Start Insert The Column!!!")
    foo()
    print("We Are Finish!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The Author is Johny!!!!!!!!!!!!!!!!!!!!!!!")