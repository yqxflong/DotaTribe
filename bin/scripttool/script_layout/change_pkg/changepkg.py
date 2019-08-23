##############################
#The script used to cocos2d.h change pkg
#Author:yunlong
###
import os,re

##########File Config######################
path='.'			#the directory path
flag='\t'			#the signal need to be split
filetype=r'.h'	#the type of file need work
filekey=r'll_'		#the signal of the file need work
######################################################
findpublic=False
findenumindex=False
findclass=False
#########################################################
ignore_line=['default_construct_destroy','default_construct_vdestroy','property_unit_rw','property_unit_rwc','property_unit_ronly','property_unit_ronlyc','CREATE_FUNC']
delstr=['cocos2d::','extension::','virtual']

tyenum='typedef enum'

############The sub method##############
def transferValue(line):

	global findpublic
	global findenumindex
	global findclass
	newline=line
	for each in ignore_line :
		m = newline.find(each)
		if m!=-1:
			return False ,newline

	for streach in delstr :
		n = newline.find(streach)
		if n!=-1:
			newline=newline.replace(streach,'')
	f1=newline.find('public:')
	f2=newline.find('{')
	f3=newline.find('};')
	f5=newline.find('class')
	f6=newline.find('enum')
	if f6 != -1:
		f9=newline.find('typedef')
		if f9==-1:
			newline=newline.replace('enum',tyenum)	
	f7=newline.find('private:')
	f8=newline.find('protected:')

	if findenumindex :
		if f3==0:
			findenumindex = False
		return True,newline
	if findclass:
		if f3==0:
			findclass=False	
			findpublic=False
			return	True,newline		
	if findclass:
		if f2==0:
			return True,newline		
	if f6==0:
		findenumindex = True
		return True,newline
	if f5==0:
		findclass=True
		findpublic=False
		return True,newline	
	if f7==0 or f8==0:
		findpublic=False
		return False,newline	
	if f1==0 and findclass==True:
		findpublic =True
		return False,newline
	if findclass and findpublic:
		return True,newline
	return False,newline

######The main method should be invoked firstly######
def	foo():
	for file in os.listdir(path):
		fname,fext=os.path.splitext(file)
		if(fext==filetype):
			print file
			input=open(file,'r')
			lines=input.readlines()
			input.close()
			file = file.replace('.h','.pkg')
			output=open(file,'w')
			for line in lines:
				isline,newline=transferValue(line)
				if isline :
					output.write(newline)
			output.close()
###########MAIN###############
if __name__=="__main__":
    print("Now We Start!!!")
    foo()
    print("We Are Finish!!!")
    print("!!!!!!!!!!!!!!!!!!!!!The cocos2d.h change pkg!!!!!!!!!!!!!!!!!!!!!!!")
