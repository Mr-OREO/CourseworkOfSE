#文件名:stu.sh
#作者:王子腾 3180102173
#创建日期:2020-07-28
#最后修改:2020-07-28

#!/bin/bash

#学生主入口
student()
{
    echo -n "请输入学号-> "
    read sid
    #检测是否存在该学号
    if test 0 = $(cat data/info/student | grep $sid | wc -l)
    then
        echo "用户不存在"
        exit 1
    fi
    #进入登陆功能
    login_student
    echo "欢迎同学登陆!"
    #进入主界面
    operation_student
    #函数因未知错误返回,退出码 1
    exit 1
}

#学生登陆功能
login_student()
{
    #获取该学号密码
    passwd=$(cat data/passwd | grep "^s$sid" | awk '{print $2}')
    #5次试错机会
    for((i=0; i<5; i++))
    do
        echo -n "登录密码-> "
        read input
        #检测输入是否正确
        if test $passwd = $input
        then
            #正确,返回
            return 0
        else
            #错误提示
            j=$((4-$i));
            echo "密码错误! 您还有 $j 次机会"
        fi
    done
    #连续五次失败,退出
    exit 2
}

#学生操作主界面
operation_student()
{
    echo ""
    echo "请选择课程:"
    #声明整数变量
    declare -i i=1

    #获取所有选课信息
    for c in $(ls -d data/stu_course/$sid* | cut -d "/" -f 3 | cut -d "_" -f 2 | sort)
    do
        #格式化输出
        echo $i $c $(cat data/info/course | grep "^$c" | awk '{print $2}')
        i=i+1
    done
    read num

    #检测输入num是否合法
    if test $num -le $(ls -d data/stu_course/$sid* | wc -l)
    then
        #获取课程号 课程名
        cid=$(ls -d data/stu_course/$sid* | cut -d "/" -f 3 | cut -d "_" -f 2 | sort | sed -n $num"p")
        cname=$(cat data/info/course | grep "^$cid" | awk '{print $2}')
        manage_course
        #函数因未知错误返回,退出码 1
        exit 1
    else
        echo "输入错误!"
        operation_student 
        #函数因未知错误返回,退出码 1
        exit 1
    fi        
}

#管理选课信息
manage_course()
{
    #操作菜单提示
    echo ""
    echo "请选择操作:"
    echo "1 上传作业"
    echo "2 编辑作业"
    echo "3 查看完成情况"
    echo "r 返回上一层"
    echo "q 退出系统"
    read op
    case $op in
        1)  add_hw;;
        2)  mod_hw;;
        3)  show_hw
            manage_course;;
        r)  operation_student;;
        q)  exit 0;;
        #其他输入,错误
        *)  echo "错误输入!"
            operation_student;;
    esac
    #函数因未知错误返回,退出码 1
    exit 1
}

#提交作业文件
add_hw()
{
    #展示作业
    show_hw
    echo ""
    echo -n "请选择要提交的作业-> "
    #作业序号
    read num
    #检测输入是否合法
    if test $num -le $(ls $d | wc -l)
    then
        #作业名
        wname=$(ls $d | sort | sed -n $num"p")
        echo -n "请输入要提交文件的路径-> "
        read fname
        #拷贝该文件至提交作业文件夹
        cp $fname $d/$wname
        echo "提交成功!"
        manage_course
        #函数因未知错误返回,退出码 1
        exit 1
    else
        echo "输入错误!"
        manage_course
        #函数因未知错误返回,退出码 1
        exit 1
    fi
}

#修改作业
mod_hw()
{
    #展示作业
    show_hw
    echo ""
    echo -n "请选择要修改的作业-> "
    read num
    #检测输入合法性
    if test $num -le $(ls $d | wc -l)
    then
        #获取作业名
        wname=$(ls $d | sort | sed -n $num"p")
        echo -n "请输入要提交的文件路径-> "
        read fname
        #删除旧作业
        rm $d/$wname/* 
        #加入新作业
        cp $fname $d/$wname
        echo "提交成功!"
        manage_course
        #函数因未知错误返回,退出码 1
        exit 1
    else
        echo "输入错误!"
        manage_course
        #函数因未知错误返回,退出码 1
        exit 1
    fi
}

#检查作业完成情况
show_hw()
{
    #获取所在目录
    d=$(ls -d data/stu_course/*$cid | head -1)
    echo ""
    echo "该课程任务为:"
    #声明整数变量
    declare -i i=1
    #列举作业
    for hw in $(ls $d | sort)
    do
        echo -n $i $hw " "
        #检测是否提交作业
        if test 0 = $(ls data/stu_course/$sid'_'$cid/$hw | wc -l)
        then
            echo "未提交"
        else
            echo "已提交"
        fi
        #步进
        i=i+1
    done
}
