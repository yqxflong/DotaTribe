# !/bin
#anchor xiaobo.wu
#
# 为了lua的pkg，将小波写的"property_unit_ronlyc"类似的缩写打开 
#
# 定位pkg路径
 
fileNameUnit=`find . -type f -name "*.pkg"`
 
for fileline in $fileNameUnit
do
  reSetContainArray
  startFileName=$fileline
  checkIsContainArrayKey $startFileName
  main $? $startFileName
done

echo "Replace Finish !"




keyArray=("property_unit_ronlyc" "property_unit_ronly" "property_unit_rwc" "property_unit_rw") 

containArray={0,0,0,0,0} 

replaceLine=""
replaceID=0
replaceType=nil
replaceName=nil


startFileName=demo.cpp
tmpFileName=$startFileName

function checkIsContainArrayKey()
{
	resultCode=0 
	for((i=0;i<4;i++))
	do 
	  containArray[i]=$(echo $(grep -c ${keyArray[i]} $1))
	  resultCode=$[$resultCode+${containArray[i]}]
  done 
    return $resultCode
}

 
function reSetContainArray()
{
	for((i=0;i<4;i++))
	do
	  containArray[i]=0
	done
}

  
function startAnllayseHandler()
{
	echo "Star Parse Handler"
   for((index=0;index<4;index++))
   do
      if [ ${containArray[index]} -gt 0 ];then
        parseReplaceHandler $1  $index
      fi 
   done
   echo "End Parse Handler"
}


function getReplaceLineFromIndex()
{ 
    case $1 in
    0) 
      replaceLine="$replaceType \& get$replaceName(void);"  ;;
    1) 
      replaceLine="$replaceType  get$replaceName(void);"  ;;
    2) 
      replaceLine="$replaceType  get$replaceName(void);   void set$replaceName($replaceType \& var);" ;;  
    3) 
      replaceLine="$replaceType  get$replaceName(void);   void set$replaceName($replaceType var);"  ;;  
    *) ;;
    esac
}
 

function  parseReplaceHandler()
{
   sed -i "s#//.*##" $1
   resultLineID=0
   resultCount=`cat $1 | grep -c ${keyArray[$2]}`
   if [ $resultCount -gt 0 ] ; then
     result=`cat $1 | grep -n ${keyArray[$2]}`
     for line in $result
     do
        if [ $[$resultLineID%2] -eq 0 ] ;then 
            replaceID=`echo $line | awk -F ":" '{print $1}'`
        else  
           tmpLine=`echo $line | awk -F "," '{print $3}'`
           replaceName=`echo $tmpLine |awk -F ")" '{print $1}'`
           tmpLine=`echo $line | awk -F "," '{print $1}'`
           replaceType=`echo $tmpLine|awk -F "(" '{print $2}'` 
           if [ "$replaceType"x = "IByte"x ]; then
            replaceType="unsigned char"
          elif [ "$replaceType"x = "UShort"x ]; then
            replaceType="unsigned short"
          elif [ "$replaceType"x = "IString"x ]; then
            replaceType="std::string"
           fi
           getReplaceLineFromIndex  $2  
           sed -i -e "$replaceID s/^.*$/$replaceLine/" $1
        fi
        resultLineID=$[$resultLineID+1]
    done 
   fi 
}
 

function main()
{
   if [ $1 -gt 0 ] ; then
   	startAnllayseHandler $2
   else
   echo "No Found In File : " $2
   fi
}
  



