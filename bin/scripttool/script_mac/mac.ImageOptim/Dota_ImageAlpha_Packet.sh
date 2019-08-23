#!bin/sh

#image root path   Do not Append / 
image_root_path=/Users/admin/PAT1/imageres/highquaily

#sort install path
soft_app_path=/Users/admin/PAT1/Tools/ImageAlpha.app/Contents/Resources/

imageNumber=0

cd $soft_app_path

echo  $soft_app_path

echo "start ImageAlpha Procedure: "

tmpfilename=nill
for filename in `find $image_root_path -name "*.png"`
do
   ./pngquant  256 --ext _tmp.png   $filename
   rm -rf  $filename
   imageNumber=$[imageNumber+1]
done

echo  "start to rename Procedure!"

for filename in `find $image_root_path -name "*.png"`
do
    tmpfilename=`echo ${filename%*_tmp*}`
    mv $filename  $tmpfilename.png
done

echo "end ImageAlpha Procedure with ImageNumber: "  $imageNumber  "Success Finished !"










