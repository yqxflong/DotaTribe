#! /bin/sh
#-------------IOS自动编译导出IPA------------------------------------------------------------ 
#-------------author:xiaobo.wu------------------------------------------------------------
#-------------date:03.05.2014------------------------------------------------------------

#------------------签名标示----------------------------------------------------------------
signIdentiy="iPhone Distribution: Beijing Changyou Gamespace Software Technology Co.,Ltd/"
provisionIdentiy="334C5C50-FD80-436D-815C-F508BDC4A4F3"
debugSignIdentiy="iPhone Developer: jun yang (FKXM6S27R7)"

#------------------工程根目录---------------------------------------------------------------
baseProjectPath=$dota_path/DotaMain.svn
#------------------XCodeProject目录路径-----------------------------------------------------
pBXProjectPath=$baseProjectPath/code/project/DOTATribe/proj.ios
#------------------APP存放目录路径---------------------------------------------------------
appPath=$baseProjectPath/output_ios/bin/release/MINITriple
#------------------IPA存放目录路径----------------------------------------------------------
ipaPath=/Users/test/Project/Dota/IPA

dotaProjectTargetArray=("DOTA_CY" "DOTA_PP" "DOTA_91" "DOTA_TBT")
targetArrayNum=${#dotaProjectTargetArray[@]}
finalyIPAArray=()
 

#----------同步路径初始化----------------------------------------------------------------------
function  initPathHandlerForAutoIPA()
{
	baseProjectPath=$dota_path/DotaMain.svn
	#------------------XCodeProject目录路径-----------------------------------------------------
	pBXProjectPath=$baseProjectPath/code/project/DOTATribe/proj.ios
	#------------------APP存放目录路径---------------------------------------------------------
	appPath=$baseProjectPath/output_ios/bin/release/MINITriple
	#------------------IPA存放目录路径----------------------------------------------------------
}

#---------自动化编译生成IPA--------------------------------------------------------------------
function  autoBuildForTargetAndGenerateIPA()
{
	cd  $pBXProjectPath 
	for((i=0;i<$targetArrayNum;i++))
	do
		echo "-----------Start Build For Target: " ${dotaProjectTargetArray[i]} " --------------------------------"
		xcodebuild -sdk iphoneos -target ${dotaProjectTargetArray[i]} clear 
		xcodebuild -sdk iphoneos -target ${dotaProjectTargetArray[i]} -configuration release CODE_SIGN_IDENTITY="$signIdentiy" PROVISIONING_PROFILE="$provisionIdentiy"
	    xcrun -sdk iphoneos PackageApplication -v  $appPath/${dotaProjectTargetArray[i]}.app -o $ipaPath/${dotaProjectTargetArray[i]}.ipa --sign "$signIdentiy"
		echo "-----------Generate IPA SuccessFor Target: " ${dotaProjectTargetArray[i]} " ------------------------"
	done 
}
 

#---------更换IPA名称--------------------------------------------------------------------
function   renameTargetForIAP()
{
	read -p "please Input a name to Append DOTA_XX_ : " appendIPAName
	for((i=0;i<$targetArrayNum;i++))
	do	
	   finalyIPAArray[i]=${dotaProjectTargetArray[i]}_$appendIPAName.ipa
	   mv  $ipaPath/${dotaProjectTargetArray[i]}.ipa  $ipaPath/${finalyIPAArray[i]}
	   echo "Rename  " ${dotaProjectTargetArray[i]}.ipa " >>>>>>>>>>> " ${finalyIPAArray[i]} "Success!"
	done  
	echo  "---------------All Target IAP Modify Append Name Success!------------------------" 
}


#---------上传IAP至FTP---------------------------------------------------------------------  
function   upLoadIPAToFTP()
{ 
	ftpIPAddir="10.6.155.209"
	ftpUserName="wuxiaobo"
	ftpUserPassWord="6pZZR6Kl"
	ftpIPAPath=刀塔联盟/日构建包/ipa/
	ipaTargetNum=${#finalyIPAArray[@]} 
	echo "----------------Start UpLoad IPA To FTP -----------------------------------------"

	ftp -n $ftpIPAddir <<-EOF
	user $ftpUserName $ftpUserPassWord
	type  binary
	prompt
	epsv4 off
	passive 
	cd $ftpIPAPath    
	put $ipaPath/${finalyIPAArray[0]} ${finalyIPAArray[0]}
	put $ipaPath/${finalyIPAArray[1]} ${finalyIPAArray[1]}
	put $ipaPath/${finalyIPAArray[2]} ${finalyIPAArray[2]}
	put $ipaPath/${finalyIPAArray[3]} ${finalyIPAArray[3]}
	done
	quit
	bye
	EOF
	echo "----------------UpLoad IPA To FTP Success ----------------------------------------"
}

function  mainBuildExportIPAHandler()
{
	initPathHandlerForAutoIPA
	autoBuildForTargetAndGenerateIPA
	renameTargetForIAP
	upLoadIPAToFTP
	echo "----------------Finish IAP Handler Success ----------------------------------------"
}

  


