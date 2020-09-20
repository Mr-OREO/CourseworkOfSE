#文件名:entrance.sh
#作者:王子腾 3180102173
#创建日期:2020-07-27
#最后修改:2020-07-30

#! /bin/bash

#身份验证提示
echo "选择权限:"
echo "1 管理员"
echo "2 教师"
echo "3 学生"
echo "q 退出"

#获取用户输入身份码
read type
#将相应文件包含在本段中,并启动入口文件
case $type in
    #管理员
    1)  . ./adm.sh
        admin;;
    #教师
    2)  . ./teach.sh;
        teacher;;
    #学生
    3)  . ./stu.sh
        student;;
    #正常退出
    q)  exit 0;;
    #其他输入,非法
    *)  echo "错误输入!"
        exit 1;;
esac
#错误退出
exit 1