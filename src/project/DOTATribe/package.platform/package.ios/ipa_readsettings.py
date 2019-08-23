import os  

SETTINGS_FILE='ipatable.txt'
SP_FLAG='\t'

#member var
list_tablecontent=[]

file_object=open(SETTINGS_FILE,'rb')
try:
	list_of_all_the_lines = file_object.readlines()
finally:
	file_object.close()


#parse each row
counter=0
for line in list_of_all_the_lines:
	print line
	if counter==0:
		counter+=1
		continue
	else:
		list_of_all_the_column=line.split(SP_FLAG)
		list_tablecontent.append(list_of_all_the_column)
	counter+=1


#print out content to verify
for list_per in list_tablecontent:
	print "idx= %s" %list_per[0]
	print "channel= %s" %list_per[1]
	print "packagename= %s" %list_per[2]
	print "url= %s" %list_per[3] 