#文件名:adm.sh
#作者:王子腾 3180102173
#创建日期:2020-07-25
#最后修改:2020-07-28
#! /bin/bash

#入口文件
admin()
{
    login_adm       #管理员登陆
    operation_adm   #操作界面
    exit 1          #错误返回
}

#管理员登陆
login_adm()
{
    #获取密码
    passwd=$(cat data/passwd | grep "^a" | awk '{print $2}')
    #五次试错机会
    for((i=0;i<5;i++))
    do
        echo -n "管理员密码-> "
        read input
        #检测输入值与密码是否匹配
        if test $passwd = $input
        then
            echo "欢迎admin登入"
            echo "";
            #成功匹配
            return 0;
        else
            #回显错误次数
            j=$((4-$i));
            echo "密码错误! 您还有 $j 次机会"
        fi
    done
    #密码错误退出,错误码 2
    exit 2
}

#管理员初始菜单
operation_adm()
{
    #操作提示
    echo "请选择操作:"
    echo "1 管理教师信息"
    echo "2 管理课程信息"
    echo "q 退出系统"

    #获取输入序号
    read type
    case $type in
        1)  manage_teach;;
        2)  manage_course;;
        q)  exit 0;;
        #其他输入,错误
        *)  echo "错误输入!"
            operation_adm;;
    esac
    #未知异常
    exit 1
}

#管理教师信息
manage_teach()
{
    #操作提示
    echo ""
    echo "请选择具体操作:"
    echo "1 增加教师信息"
    echo "2 删除教师信息"
    echo "3 修改教师信息"
    echo "4 查询教师信息"
    echo "r 返回上一层"
    echo "q 退出系统"

    #获取输入序号
    read op
    case $op in
        1)  add_teach;;
        2)  del_teach;;
        3)  mod_teach;;
        4)  que_teach;;
        r)  operation_adm;;
        q)  exit 0;;
        #其他输入,错误
        *)  echo "错误输入!"
            manage_teach;;
    esac
    #未知异常
    exit 1
}

#添加教师账户,以工号为主键primary key
add_teach()
{
    #操作提示
    echo ""
    echo -n "请输入教师工号-> "
    #获取工号
    read id
    #检查已有账户,工号是否重复
    if test 0 != $(cat data/info/teacher | awk '{print $1}' | grep -c "$id")
    then
        #重复,返回上一界面
        echo "工号已存在"
        manage_teach
        exit 1
    fi
    #不重复,进一步添加
    echo -n "请输入教师姓名-> "
    read name
    #将账户输入账户文件
    echo $id $name >> data/info/teacher
    echo -n "请输入新账户密码-> "
    read passwd
    #将账户密码输入密码文件
    echo "t"$id $passwd >> data/passwd
    
    echo "添加成功! 新教师账户为$id $name"
    #返回上一级
    manage_teach
    #异常退出
    exit 1
}

#删除教师账户
del_teach()
{
    #操作提示
    echo ""
    echo -n "请输入教师工号-> "
    read id
    #检查是否存在该工号
    if test 0 != $(cat data/info/teacher | awk '{print $1}' | grep -c "$id")
    then
        #存在,删除账户信息和密码信息
        sed -i '/'"$id"'/d' data/info/teacher
        sed -i '/'"$id"'/d' data/passwd
        echo "删除成功!"
        #返回上一级
        manage_teach
        #未知错误,退出错误码 1
        exit 1
    else
        echo "工号不存在!"
        #返回上一级
        manage_teach
        #未知错误,退出错误码 1
        exit 1
    fi
}

mod_teach()
{
    #操作提示
    echo ""
    echo -n "请输入教师工号-> "
    read id
    #检查是否存在该工号
    if test 0 != $(cat data/info/teacher | awk '{print $1}' | grep -c "$id")
    then
        #存在,执行修改操作
        #获取修改后账户信息
        echo -n "请输入修改后教师工号-> "
        read newid
        echo -n "请输入修改后教师姓名-> "
        read name
        echo -n "请输入修改后账户密码-> "
        read newpswd
        #删除原账户信息和密码信息
        sed -i '/'"$id"'/d' data/info/teacher
        sed -i '/'"$id"'/d' data/passwd
        #添加新账户信息和密码信息
        echo $newid $name >> data/info/teacher
	    echo "t"$newid $newpswd >> data/passwd
        echo "修改成功! 新账户为:$newid $name"
        #返回上一级
        manage_teach
        #未知错误,退出错误码 1
        exit 1
    else
        echo "工号不存在!"
        #返回上一级
        manage_teach
        #未知错误,退出错误码 1
        exit 1
    fi
}

que_teach()
{
    #操作提示
    echo ""
    echo "请选择查询方式:"
    echo "1 按教师工号查询"
    echo "2 按教师姓名查询"
    echo "3 列举所有教师"
    echo "r 返回上一层"
    read type
    case $type in
        1)  que_teach_id;;
        2)  que_teach_name;;
        3)  que_teach_list;;
        r)  manage_teach;;
        #其他输入,不合法
        *)  echo "输入错误!"
            que_teach;;
    esac
    #未知错误,退出错误码 1
    exit 1
}

que_teach_id()
{
    #操作提示
    echo ""
    echo -n "请输入教师工号-> "
    read id
    #检查是否存在该工号
    if test 0 != $(cat data/info/teacher | awk '{print $1}' | grep -c "$id")
    then
        #查找到
        echo "查询结果为:"
        cat data/info/teacher | grep "^$id"
        #返回上一级
        que_teach
        #未知错误,退出错误码 1
        exit 1
    else
        echo "工号不存在!"
        #返回上一级
        que_teach
        #未知错误,退出错误码 1
        exit 1
    fi
}

que_teach_name()
{
    #操作提示
    echo ""
    echo -n "请输入教师姓名-> "
    read name
    #检查是否存在该工号
    if test 0 != $(cat data/info/teacher | awk '{print $2}' | grep -c "$name")
    then
        echo "查询结果为:"
        #管道操作,输出目标行信息
        cat data/info/teacher | grep "$name"
        #返回上一级
        que_teach
        #未知错误,退出错误码 1
        exit 1
    else
        echo "姓名不存在!"
        #返回上一级
        que_teach
        #未知错误,退出错误码 1
        exit 1
    fi
}

que_teach_list()
{
    #展示所有教师账户
    cat data/info/teacher | sort
    #返回上一级
    que_teach
    #未知错误,退出错误码 1
    exit 1
}

manage_course()
{
    #操作提示
    echo ""
    echo "请选择具体操作:"
    echo "1 增加课程信息"
    echo "2 删除课程信息"
    echo "3 修改课程信息"
    echo "4 绑定课程信息"
    echo "5 解除课程绑定"
    echo "r 返回上一层"
    echo "q 退出系统"

    #获取操作码
    read type
    case $type in
        1)  add_course;;
        2)  del_course;;
        3)  mod_course;;
        4)  bind_course;;
        5)  unbind_course;;
        r)  operation_adm;;
        q)  exit 0;;
        #其他输入,不合法
        *)  echo "输入错误!"
            manage_course;;
    esac

#未知错误,退出错误码 1
    exit 1
}

add_course()
{
    #操作提示
    echo ""
    echo -n "请输入课程代号-> "
    read id
    #检查是否存在该课程号
    if test 0 != $(cat data/info/course | awk '{print $1}' | grep -c "$id")
    then
        echo "课程代号已存在"
        #返回上一级
        manage_teach
        #未知错误,退出错误码 1
        exit 1
    fi

    echo -n "请输入课程名称-> "
    read name
    #输入课程信息
    echo $id $name >> data/info/course
    
    echo "添加成功! 新课程为$id $name"
    #返回上一级
    manage_course
    #未知错误,退出错误码 1
    exit 1
}

del_course()
{
    #操作提示
    echo ""
    echo -n "请输入课程代号-> "
    read id
    #检查是否存在该课程号
    if test 0 != $(cat data/info/course | awk '{print $1}' | grep -c "$id")
    then
        #删除该课程信息
        sed -i '/'"$id"'/d' data/info/course
        echo "删除成功!"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    else
        echo "课程不存在!"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    fi
}

mod_course()
{
    #操作提示
    echo ""
    echo -n "请输入课程代号-> "
    read id
    #检查是否存在该课程号
    if test 0 != $(cat data/info/course | awk '{print $1}' | grep -c "$id")
    then
        echo -n "请输入修改后课程代号-> "
        read newid
        echo -n "请输入修改后课程名称-> "
        read name
        #删除原有课程信息
        sed -i '/'"$id"'/d' data/info/course
        #输入新信息
        echo $newid $name >> data/info/course
        echo "修改成功! 新课程为:$newid $name"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    else
        echo "课程号不存在!"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    fi
}

bind_course()
{
    #操作提示
    echo ""
    echo -n "请输入课程代号-> "
    read cid
    #检查是否存在该课程号
    if test 0 = $(cat data/info/course | awk '{print $1}' | grep -c "$cid")
    then
        echo "课程号不存在"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    fi

    echo -n "请输入教师工号-> "
    read tid
    #检查是否存在该工号
    if test 0 = $(cat data/info/teacher | awk '{print $1}' | grep -c "$tid")
    then
        echo "工号不存在"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    fi

    #检查是否已经绑定
    if test -f "data/bind/$tid"_"$cid"
    then
        echo "该教师已绑定该课程"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    fi

    #建立新文件
    touch "data/bind/$tid"_"$cid"
    echo "绑定成功! $tid -- $cid"
    #返回上一级
    manage_course
    #未知错误,退出错误码 1
    exit 1
}

unbind_course()
{
    #操作提示
    echo ""
    echo -n "请输入课程代号-> "
    read cid
    #检查是否存在该课程号
    if test 0 = $(cat data/info/course | awk '{print $1}' | grep -c "$cid")
    then
        echo "课程号不存在"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    fi

    echo -n "请输入教师工号-> "
    read tid
    #检查是否存在该工号
    if test 0 = $(cat data/info/teacher | awk '{print $1}' | grep -c "$tid")
    then
        echo "工号不存在"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    fi

    #检查是否已绑定
    if test -f "data/bind/$tid"_"$cid"
    then
        rm "data/bind/$tid"_"$cid"
        echo "解除绑定成功! $tid !- $cid"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    else
        echo "该教师未绑定该课程"
        #返回上一级
        manage_course
        #未知错误,退出错误码 1
        exit 1
    fi
}
