#!/bin/sh
#加载GUUID函数库

#导入Dota_Generate_PBX_UUID函数库
currentPath=`dirname $0`

. $currentPath/Dota_Generate_PBX_UUID.sh
 

#--------工程根路径
baseProjectPath=$dota_path/DotaMain.svn/code/project/DOTATribe
pbProjectPath=$baseProjectPath/proj.ios/DOTATribe.xcodeproj/project.pbxproj
includeFloderPath=$baseProjectPath/include
srcFloderPath=$baseProjectPath/src


#--------文件名称
includeFilesNameArray=(0)
srcFilesNameArray=(0)


#---------文件唯一索引ID
srcFilesIDentifyArray=(0)
srcFilesIDentifyArray2=(0)
srcFilesIDentifyArray3=(0)
srcFilesIDentifyArray4=(0)
 

#---------文件引用ID
includeFilesRefrenceIDArray=(0)
srcFilesRefrenceIDArray=(0)

#----------Target数目--------
targetCount=0
PBXNativeUUIDArray=(0)


#----------同步路径初始化----------------------------------------------------------------------
function  initPathHandlerForImportSource()
{
	baseProjectPath=$dota_path/DotaMain.svn/code/project/DOTATribe
	pbProjectPath=$baseProjectPath/proj.ios/DOTATribe.xcodeproj/project.pbxproj
	includeFloderPath=$baseProjectPath/include
	srcFloderPath=$baseProjectPath/src
}
 
#------------计算工程Target数目----------------
function   calConfigurationTargetCount()
{
	PBXNativeTargetSourceLine=`gsed -n '/\/\* Sources \*\/,/=' $pbProjectPath`
	for targetSourceItem in $PBXNativeTargetSourceLine
	do 
		PBXNativeUUIDArray[targetCount]=`gsed -n "$targetSourceItem p" $pbProjectPath |awk -F ' ' '{print $1}'`
		targetCount=$[$targetCount+1]
	done
}



 
function importIncludeFloder()
{
	fileIndex=0
	for fileName in `find $1 -type f -name '*.h' -exec basename {} \;|sort `
	do
	 includeFilesNameArray[$fileIndex]=$fileName
	 GeneraterUUID
	 includeFilesRefrenceIDArray[$fileIndex]=$GUUID
	 fileIndex=$[$fileIndex+1]
	done
	fileIndex=0
}


function importSrcFloder()
{
	fileIndex=0
	srcContent=`find $1 -type f -name "*.m"  -o  -name "*.mm"  -o  -name "*.cc"  -o  -name "*.cpp"`
	for fileName in  $srcContent
	do
	  fileName=`basename $fileName`
	  srcFilesNameArray[$fileIndex]=$fileName
	  if [ $targetCount -gt 0 ];then
	  	 GeneraterUUID
	     srcFilesIDentifyArray[$fileIndex]=$GUUID
	  fi
	  if [ $targetCount -gt 1 ];then
	  	 GeneraterUUID
	     srcFilesIDentifyArray2[$fileIndex]=$GUUID
	  fi
	  if [ $targetCount -gt 2 ];then
	  	 GeneraterUUID
	     srcFilesIDentifyArray3[$fileIndex]=$GUUID
	  fi
	  if [ $targetCount -gt 3 ];then
	  	 GeneraterUUID
	     srcFilesIDentifyArray4[$fileIndex]=$GUUID
	  fi  
	  GeneraterUUID
	  srcFilesRefrenceIDArray[$fileIndex]=$GUUID
	  fileIndex=$[$fileIndex+1]
	done	
	fileIndex=0
}

  

#---------导入需要清除的文件标示----------------------------------------------------------

CLASSGROUPLineID=0
includeGroupUUIDLineID=0
srcGroupUUIDLineID=0
preIncludeContent=''
preSrcContent=''
preIncludeState=1
preSrcState=1



function  ParsePreIncludeContent()
{ 
	if [ -z $1 ] ;then
		return 
	else 
		#---------------导入include文件------Begin---------
		includeGrupUUID=`gsed -n "$includeGroupUUIDLineID p" $pbProjectPath  |awk -F ' ' '{print $1}'` 
		includeStartLine=`gsed -n "/$includeGrupUUID \/\* include \*\/ = {/=" $pbProjectPath`
		includeStartLine=$[$includeStartLine+2]
		includeEndLine=`gsed -n "$includeStartLine,/);/{/);/=}" $pbProjectPath`
		includeStartLine=$[$includeStartLine+1]
		if [ $includeStartLine -eq $includeEndLine ] ;then
			echo "-------------Include Floder Empty"
			preIncludeState=0
			return
		fi
		includeEndLine=$[$includeEndLine-1]
		preIncludeContent=`gsed -n "$includeStartLine,$includeEndLine p" $pbProjectPath | awk -F '*' '{print $2}' |awk -F ' ' '{print $1}'`
		#------------------------------------End------------
	fi
}
 
function ParsePreSrcContent()
{ 
	if [ -z $1 ] ;then
		return 
	else 
		#---------------导入src文件----------Begin---------
		srcGrupUUID=`gsed -n "$srcGroupUUIDLineID p" $pbProjectPath  |awk -F ' ' '{print $1}'` 
		srcStartLine=`gsed -n "/$srcGrupUUID \/\* src \*\/ = {/=" $pbProjectPath`
		srcStartLine=$[$srcStartLine+2]
		srcEndLine=`gsed -n "$srcStartLine,/);/{/);/=}" $pbProjectPath`
		srcStartLine=$[$srcStartLine+1]
		if [ $srcStartLine -eq $srcEndLine ] ;then
			echo "-------------Src Floder Empty"
			preSrcState=0
			return
		fi
		srcEndLine=$[$srcEndLine-1]
		preSrcContent=`gsed -n "$srcStartLine,$srcEndLine p" $pbProjectPath | awk -F '*' '{print $2}' |awk -F ' ' '{print $1}'`
	#------------------------------------End----------------
	fi
}


#-------------------------准备解析旧source------------------------------
function  PreparedParsePreSourceCotent()
{
	CLASSGROUPLineID=`gsed -n "/\* Class \*\/ = {/=" $pbProjectPath`
	includeGroupUUIDLineID=`gsed -n "$CLASSGROUPLineID,/);/{/include/=}" $pbProjectPath`
	srcGroupUUIDLineID=`gsed -n "$CLASSGROUPLineID,/);/{/src/=}" $pbProjectPath`

 	ParsePreIncludeContent   $includeGroupUUIDLineID
	ParsePreSrcContent   	 $srcGroupUUIDLineID
}



#-------------------清除之前的CLASS源码----------------------
function   clearPreSource()
{
	includePater=''
	srcPater=''
	pater="\|"

    if [ $preIncludeState -eq 1 ]; then
	  for includeItem in $preIncludeContent 
	    do 
		    includePater=${includePater}${includeItem}${pater}
		done
	  gsed -i "{/$includePater XXXXXXXXXXXX/d}" $pbProjectPath
    fi

    if [ $preSrcState -eq 1 ];then
     for srcItem in $preSrcContent 
	  do 
	    srcPater=${srcPater}${srcItem}${pater}
	  done
	  gsed -i "{/$srcPater XXXXXXXXXXXX/d}" $pbProjectPath
    fi  
    echo "-------------clear Pre Source Success!"
} 
 
#---------------------------------------------------

normal_include_type="*.h"
normal_cpp_type="*.cpp"
mux_cpp_type="*.mm"
oc_src_type="*.m"
normal_cc_type="*.cc"
normal_c_type="*.c"
lastKowunFileTYpe=''


function  checkFileKownType()
{
   case $1 in 
   	$normal_include_type)
  	lastKowunFileTYpe="sourcecode.c.h"
    ;;
    $normal_cpp_type)
	lastKowunFileTYpe="sourcecode.cpp.cpp"
    ;;
    $mux_cpp_type)
	lastKowunFileTYpe="sourcecode.cpp.objcpp"
    ;;
    $oc_src_type)
	lastKowunFileTYpe="sourcecode.c.objc"
    ;;
    $normal_cc_type)
    lastKowunFileTYpe="sourcecode.cpp.cc"
    ;;
    $normal_c_type)
    lastKowunFileTYpe="sourcecode.c.c"
    ;;
    *)
	lastKowunFileTYpe="sourcecode.cpp.cpp"
   esac
}

#-------------------------------------------------------------------------------------------
#-----开始清除之前的源码文件------------------------------------------------------------------
#-------------------------------------------------------------------------------------------
function clearUpPreProjectHandler()
{ 
	initPathHandlerForImportSource
	calConfigurationTargetCount
  	PreparedParsePreSourceCotent
	clearPreSource 
}
#-------------------------------------------------------------------------------------------
#-----清除文件结束
#-------------------------------------------------------------------------------------------
 
 
#-------------------------------------------------------------------------------------------
#-----------------开始PBXProjectModify-------------------------------------------------------
     
#-------------------------------CCommonHead-------------------------------------------------
tmpFileIndex=0
tmpRepleceLine='\\'
srcFileArrayLength=0    
includeFileArrayLenth=0  
frexxAppendChar='\n'


#------------------<1>--PBXBuildSection-----------------------------------------------------------
function   pBXBuildSectionHandler()
{ 
	targetCountValue=0
	targetCountValue=$[$targetCount-1]
	for((i=0;i<$targetCount;i++))
	do 
		tmpFileIndex=0
		tmpRepleceLine='\\'
		frexxAppendChar='\n'
		for srcFileItem in ${srcFilesNameArray[*]}
		do
			if [[ $tmpFileIndex -eq $srcFileArrayLength ]];then
			    frexxAppendChar=''
		    fi
		    if ((i==0));then
		       tmpRepleceLine=${tmpRepleceLine}"		${srcFilesIDentifyArray[$tmpFileIndex]} /* $srcFileItem in Sources */ = {isa = PBXBuildFile; fileRef = ${srcFilesRefrenceIDArray[$tmpFileIndex]} /* $srcFileItem */; };$frexxAppendChar" 
		    elif ((i==1)); then
		       tmpRepleceLine=${tmpRepleceLine}"		${srcFilesIDentifyArray2[$tmpFileIndex]} /* $srcFileItem in Sources */ = {isa = PBXBuildFile; fileRef = ${srcFilesRefrenceIDArray[$tmpFileIndex]} /* $srcFileItem */; };$frexxAppendChar"
		    elif ((i==2)); then
		       tmpRepleceLine=${tmpRepleceLine}"		${srcFilesIDentifyArray3[$tmpFileIndex]} /* $srcFileItem in Sources */ = {isa = PBXBuildFile; fileRef = ${srcFilesRefrenceIDArray[$tmpFileIndex]} /* $srcFileItem */; };$frexxAppendChar"
		    elif ((i==3)); then
			   tmpRepleceLine=${tmpRepleceLine}"		${srcFilesIDentifyArray4[$tmpFileIndex]} /* $srcFileItem in Sources */ = {isa = PBXBuildFile; fileRef = ${srcFilesRefrenceIDArray[$tmpFileIndex]} /* $srcFileItem */; };$frexxAppendChar"
		    fi 
			tmpFileIndex=$[$tmpFileIndex+1] 
		done
		PBXBuildFileSectionEndLine=`gsed -n '/End PBXBuildFile section/=' $pbProjectPath`
		gsed -i "$PBXBuildFileSectionEndLine i $tmpRepleceLine" $pbProjectPath
	done  
   echo   "-------------PBXBuildSection----------------------导入预编辑编译文件------------------------------"
} 
#------------------------------------END------------------------------------------------------------

 

#----------------<2>---- PXBFileRefrenceSection-------------Begin------------------------------------
function   pBXRefrenceSectionHandler()
{  
	PXBFileRefrenceSectionEndLine=`gsed -n '/End PBXFileReference section/=' $pbProjectPath`

	#--------------------------------import-Include----------------------------------------------------
	tmpFileIndex=0
	tmpRepleceLine='\\'
	frexxAppendChar='\n'
	for inclduFileItem in ${includeFilesNameArray[*]}
	do 
		tmpRepleceLine=${tmpRepleceLine}"		${includeFilesRefrenceIDArray[$tmpFileIndex]} /* $inclduFileItem */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = sourcecode.c.h; path = \"$inclduFileItem\"; sourceTree = \"<group>\"; };$frexxAppendChar"
		tmpFileIndex=$[$tmpFileIndex+1]
	done 

	#--------------------------------import-SRC-------------------------------------------------------
	tmpFileIndex=0
	for srcFileItem in ${srcFilesNameArray[*]}
	do 
		if [ $tmpFileIndex -eq $srcFileArrayLength ];then
		    frexxAppendChar=''
	    fi
		 checkFileKownType $srcFileItem
		 tmpRepleceLine=${tmpRepleceLine}"		${srcFilesRefrenceIDArray[$tmpFileIndex]} /* $srcFileItem */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = $lastKowunFileTYpe; path = \"$srcFileItem\"; sourceTree = \"<group>\"; };$frexxAppendChar"
		 tmpFileIndex=$[$tmpFileIndex+1]
	done

	gsed -i "$PXBFileRefrenceSectionEndLine i $tmpRepleceLine" $pbProjectPath
	echo   "-------------PXBFileRefrenceSection----------------导入文件引用完毕----------------------------"

} 
#-------------------------------END-------------------------------------------------------------------


#-----------------<3>---PBXGroupSection ----------------------BEGIN-----------------------------------
function  pBXGroupClassSectionHandler()
{
	PXBGroupSrcSectionEndLine=`gsed -n '/name = src/=' $pbProjectPath`
	PXBGroupSrcSectionEndLine=$[$PXBGroupSrcSectionEndLine-1]
	#-------------------------------------SRC_GROUP----------------------------------------------------
	tmpFileIndex=0
	tmpRepleceLine='\\'
	frexxAppendChar='\n'
	for srcFileItem in ${srcFilesNameArray[*]}
	do  
		if [ $tmpFileIndex -eq $srcFileArrayLength ];then
		    frexxAppendChar=''
	    fi
		 tmpRepleceLine=${tmpRepleceLine}"				${srcFilesRefrenceIDArray[$tmpFileIndex]} /* $srcFileItem */,$frexxAppendChar"
		 tmpFileIndex=$[$tmpFileIndex+1]
	done

	gsed -i "$PXBGroupSrcSectionEndLine i $tmpRepleceLine" $pbProjectPath

	#-------------------------------------INCLUDE_GROUP---------------------------------------------------- 
	CLASSGROUPLineID=`gsed -n "/\* Class \*\/ = {/=" $pbProjectPath`
	includeGroupUUIDLineID=`gsed -n "$CLASSGROUPLineID,/);/{/include/=}" $pbProjectPath`
	includeGrupUUID=`gsed -n "$includeGroupUUIDLineID p" $pbProjectPath  |awk -F ' ' '{print $1}'` 
	PBXGroupIncludeSectionEndLine=`gsed -n "/$includeGrupUUID \/\* include \*\/ = {/=" $pbProjectPath`
	PBXGroupIncludeSectionEndLine=$[$PBXGroupIncludeSectionEndLine+2]
	  
	tmpFileIndex=0
	tmpRepleceLine='\\'
	frexxAppendChar='\n'
	for includeFileItem in ${includeFilesNameArray[*]}
	do  
		if [ $tmpFileIndex -eq $includeFileArrayLenth ];then
		    frexxAppendChar=''
	    fi
		 tmpRepleceLine=${tmpRepleceLine}"				${includeFilesRefrenceIDArray[$tmpFileIndex]} /* $includeFileItem */,$frexxAppendChar"
		 tmpFileIndex=$[$tmpFileIndex+1]
	done

	gsed -i "$PBXGroupIncludeSectionEndLine a $tmpRepleceLine" $pbProjectPath
	echo   "-------------PBXGroupSection---------------------导入CLASS文件完毕------------------------------------" 
}
#------------------------------------------------------END----------------------------------------------
 

#----------------<4>---PBXSourceSection--------------------------------------------------------------------
function  pBXNativeTargetSourceHandler()
{
	PBXNativeTargetSourceLine=`gsed -n '/\/\* Sources \*\/,/=' $pbProjectPath` 
	targetSourceCount=0
	for  targetUUID  in ${PBXNativeUUIDArray[*]}
	do
		 tUUID=${PBXNativeUUIDArray[$targetSourceCount]}
	     tmpLineID=`gsed -n "/$tUUID \/\* Sources \*\/ = {/=" $pbProjectPath`
	     tmpLineID=$[$tmpLineID+3]
	     # do samething----------------------------------------------------BEGIN----------------------------
		 tmpFileIndex=0
		 tmpRepleceLine='\\'
		 frexxAppendChar='\n'

		 for srcFileItem in ${srcFilesNameArray[*]}
		 do  
		 	if [ $tmpFileIndex -eq $srcFileArrayLength ];then
	 	    frexxAppendChar=''
	        fi
	        case $targetSourceCount in
	        0)
			tmpRepleceLine=${tmpRepleceLine}"				${srcFilesIDentifyArray[$tmpFileIndex]} /* $srcFileItem in Sources */,$frexxAppendChar"
			;;
			1)
			tmpRepleceLine=${tmpRepleceLine}"				${srcFilesIDentifyArray2[$tmpFileIndex]} /* $srcFileItem in Sources */,$frexxAppendChar"
			;;
			2)
			tmpRepleceLine=${tmpRepleceLine}"				${srcFilesIDentifyArray3[$tmpFileIndex]} /* $srcFileItem in Sources */,$frexxAppendChar"
			;;
			3)
			tmpRepleceLine=${tmpRepleceLine}"				${srcFilesIDentifyArray4[$tmpFileIndex]} /* $srcFileItem in Sources */,$frexxAppendChar"
			;;
			*)
			esac
	 		tmpFileIndex=$[$tmpFileIndex+1] 
		 done 
	 	 gsed -i "$tmpLineID a $tmpRepleceLine" $pbProjectPath
		 #------------------------------------------------------------------END-------
	     targetSourceCount=$[$targetSourceCount+1]
	     # echo $tmpLineID
	done
	echo  "-------------PBXSourceSection---------------------生成srouce包含的CPP文件-----------------------" 
}
 
#-----------------------------------------------------------------------END-------------------------------


#----------------------------导入Class-------------------------------------------------------------------- 
function   RepleaceSourceHanlder()
{
	#---------------------------------导入源码文件夹--------------------------------------------------------
	importIncludeFloder  $includeFloderPath
	importSrcFloder  $srcFloderPath

	tmpFileIndex=0
	tmpRepleceLine='\\'
	srcFileArrayLength=$[${#srcFilesNameArray[@]}-1]
	includeFileArrayLenth=$[${#includeFilesNameArray[@]}-1]
	frexxAppendChar='\n'
 
	pBXBuildSectionHandler
	pBXRefrenceSectionHandler
	pBXGroupClassSectionHandler
	pBXNativeTargetSourceHandler
	echo  "-------------All RepleaceSourceHanlder Done Finish!--------------------"
} 
   
