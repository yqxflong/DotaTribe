##############################
#The script used to change all column heads for all files in folder
#Author:Johny
###
import os,re
###############The Params Should be Set First#########
columnHeads=[r'INDEX',r'HIDE',r'ZORDER',r'CLASS',r'TPRIORITY',r'SWALLOW',r'SYSLANGID',r'FSYLEID',r'FSIZE',r'COLOR-R',r'COLOR-G',r'COLOR-B',r'COLOR-ALPHA',r'FILE1',r'FILE2',r'FILE3',r'WIDTH',r'HEIGHT',r'ANCHOR-X',r'ANCHOR-Y',r'POS-X',r'POS-Y',r'OTHERS']		#the column head list
##########File Config######################
path='.'			#the directory path
flag='\t'			#the signal need to be split
end='\n'			#the signal need to be end
filetype=r'.txt'	#the type of file need work
filekey=r'll_'		#the signal of the file need work
######################################################

############The sub method##############
def changeHead(row,line):
	if(row>0):
		return line
	newline=""
	length=len(columnHeads)
	for column in range(0,length):
		newline+=columnHeads[column]
		if(column<length-1):
			newline+=flag	
		else:
			newline+=end
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
				newline=changeHead(row,line)
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