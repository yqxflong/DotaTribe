#!/bin/sh
    
generaterInnerArray1=(0 C 8 7 2 9 8 0)
generaterInnerArray2=(9 0 5 3 B 5 D 0)
generaterInnerArray3=(7 0 0 2 E 4 9 1)
  
GUUID=0
tmpNumber=0

function  ToHexInteger()
{
  case $1 in
	10)
	tmpNumber=A
	;;
	11)
	tmpNumber=B
	;;
	12)
	tmpNumber=C
	;;
	13)
	tmpNumber=D
	;;
	14)
	tmpNumber=E
	;;
	15)
	tmpNumber=F
	;;
	*)
	tmpNumber=$1
	;;
	esac
}
 
function  GeneraterInnerUUID()
{
   if [ $1 -eq 0 ]; then
   echo "OverFlow Error!"
   return 
   fi
   
   if [ $2 -eq 0 ]; then
      #进入secondArray
	  GeneraterInnerUUID  $[$1-1]  7
   fi
    
   case $1 in 
   3)
   tmpValue=$[$((16#${generaterInnerArray1[$2]}))+1]
   ;;
   2)
   tmpValue=$[$((16#${generaterInnerArray2[$2]}))+1]
   ;;
   1)
   tmpValue=$[$((16#${generaterInnerArray3[$2]}))+1]
   ;;
   *)
   return 
   ;;
   esac
     
   if [ $tmpValue -ge 16 ];then
  
   case $1 in 
   3)
   generaterInnerArray1[$2]=0
   ;;
   2)
   generaterInnerArray2[$2]=0
   ;;
   1)
   generaterInnerArray3[$2]=0
   ;;
   *)
   return 
   ;;
   esac

   GeneraterInnerUUID  $1 $[$2-1]
   else
   ToHexInteger  $tmpValue
    
   case $1 in 
   3)
   generaterInnerArray1[$2]=$tmpNumber
   ;;
   2)
   generaterInnerArray2[$2]=$tmpNumber
   ;;
   1)
   generaterInnerArray3[$2]=$tmpNumber
   ;;
   *)
   return 
   ;;
   esac
 
   fi
   # echo $tmpValue
}

function GeneraterUUID()
{
  GeneraterInnerUUID 3 7
  GUUID=${generaterInnerArray3[0]}

  for((i=1;i<24;i++))
  do
     if((i<8)); then
        GUUID=${GUUID}${generaterInnerArray3[i]}
     elif((i<16)); then  
        GUUID=${GUUID}${generaterInnerArray2[i-8]}
     elif((i<24)); then  
         GUUID=${GUUID}${generaterInnerArray1[i-16]}
     fi
  done 
}
 






