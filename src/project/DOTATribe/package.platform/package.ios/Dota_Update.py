#Dota_Update
#The main entry to auto packet ipa
#Johny

######################config#####################
dota_path='/Users/test/Project/Dota'
#
dota_des_code=dota_path+'/DotaMain.svn/code/project/DOTATribe/proj.ios'
dota_des_resource=dota_path+'/DotaMain.svn/bin/client/dotatribe/resource'
######################config#####################
######################Info.plist###################
#
project_cy_info_plist=dota_des_code+'/CY_Package/DOTA_CY-Info.plist'
project_pp_info_plist=dota_des_code+'/PP_Package/DOTA_PP-Info.plist'
project_91_info_plist=dota_des_code+'/91_Package/DOTA_91-Info.plist'
project_tbt_info_plist=dota_des_code+'/TBT_Package/DOTA_TBT-Info.plist'
#
######################Info.plist###################
#################file config#######################
project_system_config=dota_des_resource+'/config/system.xml'
dotatribeappcontroller_path=dota_path+'/DotaMain.svn/code/project/DOTATribe/include/DOTATribeAppController.h'
dotatribegameconfig_path=dota_path+'/DotaMain.svn/code/project/DOTATribe/include/DotaGameConfig.h'
#################file config#######################

#code project path
project_code_root=dota_des_code  


###################更新SVN########################## 
 
def configDotaGateURLHandler():
	#网关服务器地址哦  目前使用GateWayURL2
	#GateWayURL=111.206.12.161
	#GateWayURL2=http://111.206.12.161:12007/
	ipnum=raw_input('输入当前网关服务器地址: ')
	port=raw_input('端口号: ')

	GateWayURL2='http://'+ipnum+':'+port+'/'

	filepath = project_system_config
	filepath_n = project_system_config+'.tmp'
	f1 = open(filepath,"r+")
	f2 = open(filepath_n,"w")
	f2.write(
			re.sub(r'<GateWayURL value="http://\S+:\S+/"',r'<GateWayURL value="http://%s:%s/"' % (ipnum,port))
		)
	f1.close()
	f2.close()
	os.remove(filepath)
	os.rename(filepath_n,filepath)

	print 'Chanage  GateWayURL IP: '+ GateWayURL2  + 'Success'


hadFoundFirstBundler=0
hadFoundSecondBundler=0

lineNumber=0
lineNumberpp=0
lineNumber91=0
lineNumbertbt=0

def  hadFoundBundler():
	echo $1 | grep -q "CFBundleShortVersionString"
	tempValue=$(echo $?)
	if [ $tempValue -eq 0 ];
	then
	hadFoundFirstBundler=1
	fi
	echo $1 | grep -q "CFBundleVersion"
	tempValue=$(echo $?)
	if [ $tempValue -eq 0 ];
	then
	hadFoundSecondBundler=1
	fi
	return $tempValue

 
def configDotaProVersionHandler():
	vesionID=raw_input('please input  Dotatribe  VersionID and press enter to finish: ')
	filepath = project_system_config
	filepath_n = project_system_config+'.tmp'
	f1 = open(filepath,"r+")
	f2 = open(filepath_n,"w")
	f2.write(
			re.sub(r'Version value=*.*',r'Version value=%s' % versionID)
		)
	f1.close()
	f2.close()
	os.remove(filepath)
	os.rename(filepath_n,filepath)

##############can not parse, imreadable################
	while read line
	do
	lineNumber=$[$lineNumber+1]
	if [ $hadFoundFirstBundler -eq 1 ];
	then
	hadFoundFirstBundler=0
	sed -i -e "$lineNumber s/<string>*.*</<string>$vesionID</" $project_cy_info_plist
	rm -rf $project_cy_info_plist-e
	fi
	if [ $hadFoundSecondBundler -eq 1 ];
	then
	sed -i -e "$lineNumber s/<string>*.*</<string>$vesionID</" $project_cy_info_plist
	hadFoundSecondBundler=0
	rm -rf $project_cy_info_plist-e
	fi
	hadFoundBundler $line
	done <$project_cy_info_plist
	echo  " Cy Info-plist Vesion Success "


	while read line1
	do
	lineNumberpp=$[$lineNumberpp+1]
	if [ $hadFoundFirstBundler -eq 1 ];
	then
	hadFoundFirstBundler=0
	sed -i -e "$lineNumberpp s/<string>*.*</<string>$vesionID</" $project_pp_info_plist
	rm -rf $project_pp_info_plist-e
	fi
	if [ $hadFoundSecondBundler -eq 1 ];
	then
	sed -i -e "$lineNumberpp s/<string>*.*</<string>$vesionID</" $project_pp_info_plist
	hadFoundSecondBundler=0
	rm -rf $project_pp_info_plist-e
	fi
	hadFoundBundler $line1
	done <$project_pp_info_plist
	echo  " PP Info-plist Vesion Success "

	while read line2
	do
	lineNumber91=$[$lineNumber91+1]
	if [ $hadFoundFirstBundler -eq 1 ];
	then
	hadFoundFirstBundler=0
	sed -i -e "$lineNumber91 s/<string>*.*</<string>$vesionID</" $project_91_info_plist
	rm -rf $project_91_info_plist-e
	fi
	if [ $hadFoundSecondBundler -eq 1 ];
	then
	sed -i -e "$lineNumber91 s/<string>*.*</<string>$vesionID</" $project_91_info_plist
	hadFoundSecondBundler=0
	rm -rf $project_91_info_plist-e
	fi
	hadFoundBundler $line2
	done <$project_91_info_plist
	echo  " 91 Info-plist Vesion Success "

	while read line3
	do
	lineNumbertbt=$[$lineNumbertbt+1]
	if [ $hadFoundFirstBundler -eq 1 ];
	then
	hadFoundFirstBundler=0
	sed -i -e "$lineNumbertbt s/<string>*.*</<string>$vesionID</" $project_tbt_info_plist
	rm -rf $project_tbt_info_plist-e
	fi
	if [ $hadFoundSecondBundler -eq 1 ];
	then
	sed -i -e "$lineNumbertbt s/<string>*.*</<string>$vesionID</" $project_tbt_info_plist
	hadFoundSecondBundler=0
	rm -rf $project_tbt_info_plist-e
	fi
	hadFoundBundler $line3
	done <$project_tbt_info_plist
	echo  " TBT Info-plist Vesion Success " 



function	configDotaIPAModeHandler()
{ 
	#宏定义
	define91='#define kSDK_91_ENABEL'
	definepp='#define kSDK_PP_ENABEL'
	definetbt='#define kSDK_TONGBUTUI_ENABEL'
	definecyou='#define kSDK_CYOU_ENABEL'

	###############提问是否内部版还是正式版####################
	echo 	"0:kMODE_RELEASE_INNER			1:kMODE_RELEASE_REAL"
	read -p "please Input Here :  " optionmode

	configmode='static int DOTA_CONFIG_MODE=kMODE_RELEASE_INNER;'
	case $optionmode in
	0)
	configmode='static int DOTA_CONFIG_MODE=kMODE_RELEASE_INNER;'
	;;
	1)
	configmode='static int DOTA_CONFIG_MODE=kMODE_RELEASE_REAL;'
	;;
	esac
	 
	#######################配置ios sdk######################
	defineappstore='//#define kENABLE_PLATFORM_PC'
	definesdkios='#define kENABLE_PLATFORM_SDKIOS'
	definesdkandroid='//#define kENABLE_PLATFORM_SDKANDROID'

	#加1：将DotaGameConfig.h中的static int DOTA_CONFIG_MODE=后边改为kMODE_RELEASE_INNER
	sed  -i -e "s#.*DOTA_CONFIG_MODE.*#$configmode#"  $dotatribegameconfig_path
	rm  -rf  $dotatribegameconfig_path-e

	#加2: 确保DotaGameConfig.h中仅#define kENABLE_PLATFORM_SDKIOS为打开状态
	sed  -i -e "s;.*#define kENABLE_PLATFORM_PC;$defineappstore;"  $dotatribegameconfig_path
	rm  -rf  $dotatribegameconfig_path-e

	sed  -i -e "s;.*#define kENABLE_PLATFORM_SDKIOS;$definesdkios;"  $dotatribegameconfig_path
	rm  -rf  $dotatribegameconfig_path-e

	sed  -i -e "s;.*#define kENABLE_PLATFORM_SDKANDROID;$definesdkandroid;"  $dotatribegameconfig_path
	rm  -rf  $dotatribegameconfig_path-e 
}

#######################工程信息配置##########################
function  mainConfigHandler()
{
   echo  "Start To Modify Projet Info "
   #######################更改网关和端口######################
   configDotaGateURLHandler
   #######################更改工程版本######################
   configDotaProVersionHandler
   #######################更改工程IPAMode######################
   configDotaIPAModeHandler
   echo	  "Update Project Info Success !" 
}


#######################DotaShell总控制##########################
def foo():
	#######################更新SVN######################
	updateSvnHandler()

 	#######################更新工程配置######################
	mainConfigHandler()

	#######################清理之前工程源码######################
	clearUpPreProjectHandler()

	#######################导入最新源码######################
	RepleaceSourceHanlder()

	#######################编译生成IPA######################
	mainBuildExportIPAHandler()


###########MAIN###############
if __name__=="__main__":
    print("Welcome to use Dota_Update.py!")
    foo()
    print("All finish, Thank you!")


