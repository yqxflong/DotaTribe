#!/bin/sh

#压缩纹理

ProcessPath_Resource=../mmsanguo/client/project/GirlKingdom/Resources/resource

PngEncryptKeyPngEncryptKey=com.cyou.mrd.girlkindomimage901218

#data加密key
DataEncryptKey=com.cyou.mrd.girlkindom901218

#加密长度
EncryptDataLen=200

#加密png
function encryptPNG()
{
	PNG_Root=$ProcessPath_Resource
	echo  "-------Start Encrypt PNG : " $PNG_Root " ---------------"
	
	
	imageNumber=0

	for filename in `find $PNG_Root -name "*.png"`
	do
	   ./EncryptPacker $filename $PngEncryptKey $EncryptDataLen	 
	   imageNumber=$[imageNumber+1]
	done

	echo  "-------End Encrypt PNG with ImageNumber: "  $imageNumber  "Success Finished ! ---------------"

	configFile=$DestinyPath_Resource/config/system.xml
	sed -i -e "s/ResourceEncryptioned value=\"*.*\"/ResourceEncryptioned value=\"1\"/g" $configFile
	rm -rf $configFile-e 

}

function encryptTableData()
{
	TableData_Root=$ProcessPath_Resource/data
	echo  "-------Start Encrypt Table Data : " $TableData_Root " ---------------"

	
	fileNumber=0

	for filename in `find $TableData_Root -name "*.txt"`
	do
	   ./EncryptPacker $filename $DataEncryptKey 0
	   fileNumber=$[fileNumber+1]
	done

	echo  "-------End Encrypt TXT with file Number: "  $fileNumber  "Success Finished ! ---------------"

	configFile=$DestinyPath_Resource/config/system.xml
	sed -i -e "s/DataEncryptioned value=\"*.*\"/DataEncryptioned value=\"1\"/g" $configFile
	rm -rf $configFile-e 

}



encryptPNG
encryptTableData