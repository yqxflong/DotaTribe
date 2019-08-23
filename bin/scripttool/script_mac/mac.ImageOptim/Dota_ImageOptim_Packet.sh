#! /bin/sh

#image root path   Do not Append / 
image_root_path=/Users/admin/PAT1/Program/在研项目/刀塔英雄/DOTATribe/resource/spine

#sort install path
soft_app_path=/Users/admin/PAT1/Tools/ImageOptim.app/Contents/MacOS/

cd  $soft_app_path

echo "start ImageOptim Procedure: "

./ImageOptim 2>/dev/null  $image_root_path

echo "end ImageOptim Procedure  Success Finished !"






