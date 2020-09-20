#文件名:teach.sh
#作者:王子腾 3180102173
#创建日期:2020-07-26
#最后修改:2020-07-28

#!bin/bash

#教师功能入口
teacher()
{
    echo -n "请输入教师工号-> "
    read tid
    #检查该工号是否存在
    if test 0 = $(cat data/info/teacher | grep $tid | wc -l)
    then
        echo "用户不存在"
        teacher
        #函数错误返回,退出错误码 1
        exit 1
    fi

    #进入登陆模块
    login_teacher
    echo "欢迎老师登陆!"

    #操作菜单
    operation_teacher
    #函数错误返回,退出错误码 1
    exit 1
}

#登录验证功能
login_teacher()
{
    #获取该账号密码
    passwd=$(cat data/passwd | grep "^t$tid" | awk '{print $2}')
    #提供5次试错机会
    for((i=0; i<5; i++))
    do
        echo -n "登录密码-> "
        read input
        #比较输入是否与密码匹配
        if test $passwd = $input
        then
            #验证成功,返回
            return 0
        else
            #计算剩余次数
            j=$((4-$i));
            echo "密码错误! 您还有 $j 次机会"
        fi
    done
    #密码验证失败,退出码 2
    exit 2
}

#教师操作主界面
operation_teacher()
{
    #声明数学整数变量
    declare -i i=1
    declare -i option
    #操作提示
    echo ""
    echo "请选择课程:"
    #打印出所有课程信息,带序号
    for course in $(ls data/bind/$tid* | grep -o "[[:alnum:]]*$" | sort)
    do
        echo -e $i $course $(cat data/info/course | grep "^$course" | awk '{print $2}')
        i=i+1
    done

    #获取输入选择
    read option
    #输入是否合法(在给出序号范围内)
    if test $option -le $(ls data/bind/$tid* | grep -c "[[:alnum:]]*$")
    then
        #获取课程id
        cid=$(ls data/bind/$tid* | grep -o "[[:alnum:]]*$" | sort | sed -n $option"p")
        #获取课程名
        name=$(cat data/info/course | grep "^$cid" | awk '{print $2}')
        manage
        #函数错误返回,退出错误码 1
        exit 1
    else
        echo "输入错误!"
        #重新尝试
        operation_teacher
        #函数错误返回,退出错误码 1
        exit 1
    fi
}

#管理该课程相关信息
manage()
{
    #操作提示信息
    echo ""
    echo "请选择进一步操作"
    echo "1 管理学生信息"
    echo "2 管理课程信息"
    echo "3 管理作业实验"
    echo "r 返回上一级"
    echo "q 退出"
    read op
    #根据输入选择功能入口
    case $op in
        1)  manage_student;;
        2)  manage_course;;
        3)  manage_homework;;
        r)  operation_teacher;;
        q)  exit 0;;
        #其他输入,非法
        *)  echo "错误输入!"
            operation_teacher;;
    esac
    #函数错误返回,退出错误码 1
    exit 1
}

#管理学生账户
manage_student()
{
    #操作提示信息
    echo ""
    echo "请选择具体操作"
    echo "1 创建学生账户"
    echo "2 修改学生账户"
    echo "3 删除学生账户"
    echo "4 查找选课学生"
    echo "r 返回上一级"
    echo "q 退出"
    read op
    #根据输入选择功能入口
    case $op in
        1)  add_stu;;
        2)  mod_stu;;
        3)  del_stu;;
        4)  que_stu;;
        r)  operation_teacher;;
        q)  exit 0;;
        #其他输入,非法
        *)  echo "输入错误!"
            exit 1;;
    esac
    #函数错误返回,退出错误码 1
    exit 1
}

#添加学生选课信息
add_stu()
{
    #操作提示信息
    echo ""
    echo -n "请输入新建学生学号-> "
    read sid
    #检查是否存在该学号
    if test 0 != $(cat data/info/student | awk '{print $1}' | grep -c "$sid")
    then
        #检测文件存在
        if test -d data/stu_course/$sid"_"$cid
        then
            echo "该学生已选课!"
            manage_student
            #函数错误返回,退出错误码 1
            exit 1
        fi
        #建立子目录
        mkdir data/stu_course/$sid"_"$cid
        echo "添加成功!"
        manage_student
        #函数错误返回,退出错误码 1
        exit 1
    fi

    #不存在学号,需新建学生信息
    echo -n "请输入学生姓名-> "
    read sname
    echo -n "请输入账户密码-> "
    read spswd
    #将新信息输入
    echo $sid $sname >> data/info/student
    echo "s"$sid $spswd >> data/passwd
    #建立子目录
    mkdir data/stu_course/$sid"_"$cid
    echo "添加成功!"
    manage_student
    #函数错误返回,退出错误码 1
    exit 1
}

#删除选课信息
del_stu()
{
    #操作提示信息
    echo ""
    echo -n "请输入删除学生学号-> "
    read sid
    #检测是否存在选课信息
    if test -d data/stu_course/$sid"_"$cid
    then
        #将选课目录删除
        rm -r data/stu_course/$sid"_"$cid
        echo "删除成功!"
        manage_student
        #函数错误返回,退出错误码 1
        exit 1
    else
        echo "无该学生选课记录!"
        manage_student
        #函数错误返回,退出错误码 1
        exit 1
    fi
}

#修改学生信息
mod_stu()
{
    #操作提示信息
    echo ""
    echo -n "请输入修改学生学号-> "
    read sid
    #检查是否存在该学号
    if test 0 != $(cat data/info/student | awk '{print $1}' | grep -c "$sid")
    then
        echo -n "请输入修改后学生学号-> "
        read newid
        echo -n "请输入修改后学生姓名-> "
        read name
        #删除原账户信息
        sed -i '/'"$tid"'/d' data/info/student
        #输入新信息
        echo $newid $name >> data/info/student
        echo "修改成功! 新账户为:$newid $name"
        manage_student
        #函数错误返回,退出错误码 1
        exit 1
    else
        echo "学号不存在!"
        manage_student
        #函数错误返回,退出错误码 1
        exit 1
    fi
}

#查询选课学生
que_stu()
{
    #操作提示信息
    echo ""
    echo -n "请输入查询学生学号-> "
    read sid
    #检查是否存在该学号
    if test 0 = $(cat data/info/student | grep -c "^$sid")
    then
        echo "该学生不存在!"
        manage_student
        #函数错误返回,退出错误码 1
        exit 1
    else
    #检查是否存在该学号的选课信息
	if test -d data/stu_course/$sid"_"$cid
	then
        echo "学生信息为:"
        cat data/info/student | grep "^$sid"
        manage_student
        #函数错误返回,退出错误码 1
        exit 1
	else
        echo "该学生未选课!"
        manage_student
        #函数错误返回,退出错误码 1
        exit 1
	fi
    fi
}

#管理课程信息
manage_course()
{
    #操作提示信息
    echo ""
    echo "请选择具体操作"
    echo "1 新建课程信息"
    echo "2 删除课程信息"
    echo "3 编辑课程信息"
    echo "4 显示课程信息"
    echo "r 返回上一级"
    echo "q 退出"
    read op
    #根据选择提供相应入口
    case $op in
        1)  add_info;;
        2)  del_info;;
        3)  mod_info;;
        4)  list_info;;
        r)  operation_teacher;;
        q)  exit 0;;
        #其他输入,非法
        *)  echo "输入错误!"
            manage_course;;
    esac
    #函数错误返回,退出错误码 1
    exit 1
}

#添加课程信息
add_info()
{
    #操作提示信息
    echo ""
    echo -n "请输入课程信息-> "
    read line
    #加入课程信息
    echo $line >> data/bind/$tid"_"$cid
    echo "信息添加成功!"
    manage_course
    #函数错误返回,退出错误码 1
    exit 1
}

#删除课程信息
del_info()
{
    #操作提示信息
    echo "文本内容为:"
    #展示已有课程信息
    cat data/bind/$tid"_"$cid
    echo ""
    echo -n "请输入你要删除的行数-> "
    read num
    #删除该行信息
    sed -i "${num}d" data/bind/$tid"_"$cid
    echo "删除成功!"
    manage_course
    #函数错误返回,退出错误码 1
    exit 1
}

#修改课程信息
mod_info()
{
    #操作提示信息
    echo "文本内容为:"
    #展示已有课程信息
    cat data/bind/$tid"_"$cid
    echo ""
    echo -n "请输入你要修改的行数-> "
    read num
    echo -n "请输入你要修改的内容-> "
    read line
    #更新该行信息
    sed -i "${num}c${line}" data/bind/$tid"_"$cid
    echo "修改成功!"
    manage_course
    #函数错误返回,退出错误码 1
    exit 1
}

#展示已有课程信息
list_info()
{
    echo ""
    #展示已有课程信息
    cat data/bind/$tid"_"$cid
    manage_course
    #函数错误返回,退出错误码 1
    exit 1
}

#管理作业/实验
manage_homework()
{
    #操作提示信息
    echo ""
    echo "请选择具体操作"
    echo "1 新建作业信息"
    echo "2 删除作业信息"
    echo "3 编辑作业信息"
    echo "4 显示作业信息"
    echo "5 查看完成情况"
    echo "r 返回上一级"
    echo "q 退出"
    read op
    #根据输入提供入口
    case $op in
        1)  add_homework;;
        2)  del_homework;;
        3)  mod_homework;;
        4)  list_homework
            manage_homework;;
        5)  check_homework;;
        r)  operation_teacher;;
        q)  exit 0;;
        #其他输入,非法
        *)  echo "输入错误!"
            exit 1;;
    esac
    #函数错误返回,退出错误码 1
    exit 1
}

#添加作业
add_homework()
{
    #操作提示信息
    echo ""
    echo -n "请输入作业名称-> "
    read wname
    #遍历已有选课学生目录
    for d in $(ls -d data/stu_course/*$cid)
    do
        #创建作业目录
        mkdir $d/$wname
    done
    echo "作业创建成功!"
    manage_homework
    #函数错误返回,退出错误码 1
    exit 1
}

#删除作业
del_homework()
{
    #列举所有作业
    list_homework
    echo ""
    echo -n "请输入你要删除的序号-> "
    read num
    #删除目录信息
    del=$(ls $studir | head -n $num)
    #删除作业子目录
    rm -r data/stu_course/*$cid/$del
    echo "作业删除成功!"
    manage_homework
    #函数错误返回,退出错误码 1
    exit 1
}

#修改作业名称
mod_homework()
{
    #操作提示信息
    list_homework
    echo -n "请输入你要修改的序号-> "
    read num
    #获取旧名称
    oldname=$(ls $studir | head -n $num)
    echo -n "请输入新名称-> "
    read newname
    #遍历该作业
    for d in $(ls -d data/stu_course/*$cid/$oldname)
    do
        #重命名
        mv $d $(echo $d | sed 's/'"$oldname"'/'"$newname"'/')
    done
    echo "作业修改成功!"
    manage_homework
    #函数错误返回,退出错误码 1
    exit 1
}

#列举所有作业
list_homework()
{
    #操作提示信息
    echo ""
    studir=$(ls -d data/stu_course/*$cid | head -1)
    echo "所有作业为:"
    declare -i i=1
    #遍历该作业
    for homework in $(ls $studir | sort)
    do
        echo $i $homework
        i=i+1
    done
    return 0
}

#检查作业完成情况
check_homework()
{
    #列举作业信息
    list_homework
    echo ""
    echo -n "请输入你要检查的序号-> "
    read num
    #作业名
    wname=$(ls $studir | head -n $num)
    echo "完成情况如下:"
    #遍历选课学生
    for d in data/stu_course/*$cid/$wname
    do
        #切割学生学号
        sid=$(echo $d | cut -d '/' -f 3 | cut -d '_' -f 1)
        #检测是否提交
        if test 0 != $(ls $d | wc -l)
        then
            echo $sid "已提交"
        else
            echo $sid "未提交"
        fi
    done
    #返回
    manage_homework
    #函数错误返回,退出错误码 1
    exit 1
}
