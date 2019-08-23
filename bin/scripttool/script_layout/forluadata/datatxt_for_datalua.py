#!/usr/bin/env python
# -*- coding: utf-8 -*-
#By data.txt Create db.lua
#Author:yunlong

###

######################################################
import os,sys
import re
import string
import chardet
#import codecs
#####################################################
path='./gamedata/'			#the directory path
SP_FLAG='\t'			#the signal need to be split
filetype=r'.txt'	#the type of file need work
filekey=r'db_'		#the signal of the file need work
outfile = './out'
replace_dictionary = {
    '<FILENAME>'        :'',
    '<KEYNOTES>'        :'',
    '<VAR_KEY>'		    :'',
    '<TABLENAME>'       :'',
    '<VAR_TABLE>'		:'',
}


def foo():
	for file in os.listdir(path):	
		fname,fext=os.path.splitext(file)
		if(fext==filetype):
			print file
			if not os.path.isdir(outfile):
				os.makedirs(outfile)
			input=open('./gamedata/'+file,'r')		
			lines = input.readlines()
			codeing = chardet.detect(lines[0])['encoding'] 
			#print codeing
			input.close()
			fnametemp = fname
			replace_dictionary['<FILENAME>'] = fnametemp
			fnametemp = fnametemp.replace(filekey,'')
			replace_dictionary['<TABLENAME>'] = fnametemp

			linecount = 1
			temp={}
			strindex = 0;
			table_data = ''
			ket_table_str =''
			for line in lines:
				line =  unicode(line, codeing).encode('utf-8')
				line = line.replace('\n','')
				if linecount == 1:
					key_notes_str = '--{'
					key_notes_str += line
					key_notes_str +='}'
					replace_dictionary['<KEYNOTES>'] = key_notes_str
					
				if linecount == 2:
					tmp=line.split(SP_FLAG)
					for index in tmp:
						if index.find('STR') != -1:
							temp[strindex] = 1
						else:
							temp[strindex] = 0	
						strindex += 1				
						ket_table_str += '"' + index + '" ,'
					strindex = 0	
					replace_dictionary['<VAR_KEY>'] = ket_table_str
				if linecount >= 3:
					tmp=line.split(SP_FLAG)
					if linecount == 3:
						temp_line_data = 'id_' + tmp[0] + ' = {'
					else:
						temp_line_data = '	id_' + tmp[0] + ' = {'

					for index in tmp:
						if temp[strindex] == 1:
							temp_line_data += '"' + index + '", '
						else:
							if index == '':
							   index = 'nil'	
							temp_line_data += index +', '
						strindex += 1
					strindex = 0			
					temp_line_data += '},\n'
					table_data += temp_line_data	
				linecount += 1
			replace_dictionary['<VAR_TABLE>'] = table_data
			template_lua_file = open('./db_template.lua','r')	
      		template_lua_file_dat = template_lua_file.read()
        

      		outfname = file
      		outfname = outfname.replace('.txt','.lua')

      		lua_data_file = open(outfile + '/' + outfname,'w')

      		for key in replace_dictionary:
      			template_lua_file_dat = re.sub(key,replace_dictionary[key],template_lua_file_dat)

      		lua_data_file.write(template_lua_file_dat)
       		template_lua_file.close()
       		lua_data_file.close()
		
       	
###########MAIN###############
if __name__=="__main__":
    print("Now We Start!!!")
    foo()
    print("We Are Finish!!!")
