#!/bin/sh
#-----------自动更新工程Svn脚步---------------------------------------
#--------author:xiaobo.wu-------------------------------------------
#--------SVN---账户信息---------
svnUserName=wuxiaobo
svnUserPassword=789632147

#--------SVN工程Root路径--------
baseSvnPath=$dota_path/DotaMain.svn
projectSvnCodePath=$baseSvnPath/code/
projectSvnBinPath=$baseSvnPath/bin/
resulrValue=0
 
#----------同步路径初始化----------------------------------------------------------------------
function  initPathHandlerForSVNUpdate()
{
	baseSvnPath=$dota_path/DotaMain.svn
	projectSvnCodePath=$baseSvnPath/code/
	projectSvnBinPath=$baseSvnPath/bin/
}

function updateSvnHandler()
{
	initPathHandlerForSVNUpdate
	echo  "-------Start Update Svn For : " $baseSvnPath " ---------------"
	svn --username $svnUserName --password $svnUserPassword up $projectSvnCodePath
	svn --username $svnUserName --password $svnUserPassword up $projectSvnBinPath
	echo  "-------End   Update Svn For : " $baseSvnPath " ---------------"
	resulrValue=1
}
#-------------------------------------------------------------------
