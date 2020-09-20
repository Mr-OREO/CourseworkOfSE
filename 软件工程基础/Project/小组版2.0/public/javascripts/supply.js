/**
 * supply.js
 * G05 物资管理子系统 功能模块
 *
 * 目前实现功能：
 *  1. 连接数据库
 *  2. 筛选中签名单
 *  3. 自动发送邮件
 *  4. 导出excel格式的中签名单和详细信息
 *
 * 日期：2020-06-07
 * Copyright@ 2020 软件工程基础-张引-G05
 */

// 创建对象
var Supply = new Object();
// MySQL
var mysql = require('mysql');
var connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'wzt123',
    database: 'se05'
});
connection.connect();
// Email
var nodemailer = require('nodemailer');
var transporter = nodemailer.createTransport({
    service: 'qq',
    auth: {
        user: '1065363303@qq.com',
        pass: 'ijrrjxvysgrqbbhd' //授权码,通过QQ获取
    }
});
// Excel
var excel = require('exceljs');
var async = require('async');
var db = require("../../config/db");

/**
 * randomNum()
 * 产生[minNum, maxNum]之间的随机数
 * @param minNum 下限
 * @param maxNum 上限
 */
Supply.randomNum = function(minNum, maxNum) {
    switch (arguments.length) { // 参数个数
        case 1:
            return parseInt(Math.random() * minNum + 1, 10);
        case 2:
            return parseInt(Math.random() * (maxNum - minNum + 1) + minNum, 10);
        default:
            return 0;
    }
}

/**
 * check()
 * 检查当前是否有需要筛选的物资，若有则调用select()
 */
Supply.check = function() {
    var curdate = new Date();
    curdate.setDate(curdate.getDate());

    // 查询已结束申请的物资id
    var chksql1 = "select goods_id from goods where end_date < ? and goods_id in (select goods_id from apply where apply_result = -1)";
    var res = new Array;
    connection.query(chksql1, curdate, function(err, result) {
        if (err)
            console.log('[SELECT ERROR] - ', err.message);
        else{
            res = result;
            console.log(res);
            console.log(res.length);
        }
    });

    setTimeout(function(){
        console.log(res.length);
        for (var i = 0; i < res.length; i++){
            console.log(res[i].goods_id);
            Supply.select(res[i].goods_id);
        }
        // 查询已结束申请但未筛选过的物资id
        // for (var i = 0; i < res.length; i++) {
        //     var chksql2 = "select goods_id from apply where goods_id = ? and apply_result = -1";
        //     connection.query(chksql2, res[i].goods_id, function(err, res) {
        //         if (err)
        //             console.log('[SELECT ERROR] - ', err.message);
        //         for (var i = 0; i < res.length; i++){
        //             console.log(res[i].goods_id);
        //             Supply.select(res[i].goods_id);
        //         }
        //     })
        // }
    }, 300);
    

}

/**
 * select()
 * 对需要筛选的申请记录进行筛选，并更新数据库apply中的apply_result，调用邮件函数mail()
 * @param id 需要筛选的物资的id (goods ---> goods_id)
 */
Supply.select = function(id) {
    var total; // 库存
    var current; // 申请人数
    // 获取total和current情况
    var cur_sql = 'select count(account_id) as cnt from apply where goods_id=?';
    connection.query(cur_sql, id, function(err, result) {
        if (err) {
            console.log('[SELECT ERROR] - ', err.message);
        }
        //result process
        current = result[0].cnt;
        console.log(current);
    });

    var tot_sql = 'select total from goods where goods_id= ?'
    connection.query(tot_sql, id, function(err, result) {
        if (err) {
            console.log('[SELECT ERROR] - ', err.message);
            return callback(err);
        }
        //result process
        total = result[0].total;
        console.log(total);
    });


    setTimeout(function(){
        // 物资更多，无需筛选
        if (current < total) {
            var updtsql = "update apply set apply_result = 1 where goods_id = ?"
            connection.query(updtsql, id, function(err, res) {
                if (err) {
                    console.log('[UPDATE ERROR] - ', err.message);
                }
                console.log("物资更多，无需筛选，已更新");
            })
            return;
        }

        // 申请者更多，需要筛选
        var account = new Array;
        // var selected = 0;
        var chk_sql = 'select account_id from apply where goods_id = ? order by rand()';
        connection.query(chk_sql, id, function(err, res) {
            if (err) {
                console.log('[SELECT ERROR] - ', err.message);
            }
            console.log("人更多，需筛选");
            account = res;
        })

        setTimeout(function(){
            // var branch;
            // while(中签者<物资数)
            new Promise(async resolve => {
                let branch = await db.query("select apply_result from apply where goods_id = '"+id+"'");
                for (var i = 0; i < total; i++)
                    await db.query("update apply set apply_result = 1 where account_id = '"+account[i].account_id+"' and goods_id = '"+id+"'");
                for(var i = total; i < current; i++)
                    await db.query("update apply set apply_result = 0 where account_id = '"+account[i].account_id+"' and goods_id = '"+id+"'");
            });
            setTimeout(function(){
                console.log("筛选完成，已更新");
                Supply.mail(id);
            },1000);
        }, 100);
    }, 100);
}

/**
 * mail()
 * 根据指定物资的申请结果，向申请者发送结果邮件
 * @param id 需要邮件推送的物资id (goods ---> goods_id)
 */
Supply.mail = function(id) {
    var mailsql = "select email from user, apply where apply.apply_result = 1 and apply.account_id = user.account_id and apply.goods_id = ?";
    var emailto = new Array;
    connection.query(mailsql, id, function(err, res) {
        if (err) {
            console.log('[SELECT ERROR] - ', err.message);
        }
        console.log("进入");
        emailto = res;
    })

    setTimeout(function(){
        // 所有需要发送邮件的账户
        for (var i = 0; i < emailto.length; i++) {
            var mailOptions = {
                from: '1065363303@qq.com', // 发送者
                to: emailto[i].email, // 收件者，若收件者>1，则用逗号隔开
                subject: '物资申领结果', // 主题
                //text: 'Hello world', // 正文
                html: `<h2>恭喜您已中签，请等待物资配送。</h2>`
            };

            transporter.sendMail(mailOptions, function(err, info) {
                if (err) {
                    console.log(err);
                    return;
                }
                console.log('发送成功');
            });
        }
    }, 100);

    var mailsql2 = "select email from user, apply where apply.apply_result = 0 and apply.account_id = user.account_id and apply.goods_id = ?";
    var emailto2 = new Array;
    connection.query(mailsql2, id, function(err, res) {
        if (err) {
            console.log('[SELECT ERROR] - ', err.message);
        }
        emailto2 = res;
    });

    setTimeout(function(){
        for (var i = 0; i < emailto2.length; i++) {
            var mailOptions = {
                from: '1065363303@qq.com', // 发送者
                to: emailto[i].email, // 收件者，若收件者>1，则用逗号隔开
                subject: '物资申领结果', // 主题
                //text: 'Hello world', // 正文
                html: `<h2>很遗憾您未能中签，请您继续关注其他物资。</h2>`
            };

            transporter.sendMail(mailOptions, function(err, info) {
                if (err) {
                    console.log(err);
                    return;
                }
                console.log('发送成功');
            });
        }
    }, 100);
}

/**
 * excel()
 * 导出指定物资的中签者信息，中签情况存储在apply表中，中签者信息在user表中
 * @param id 需要导出中签者信息的物资id (goods ---> goods_id)
 */
Supply.excel = function(id) {
    // 创建workbook
    var workbook = new excel.Workbook();
    // 创建worksheet
    var worksheet = workbook.addWorksheet('result');

    //
    connection.query("select user.account_id, username, identity_id, phone_number, address, email from apply, user where apply.account_id = user.account_id and apply_result = 1 and goods_id = ?", id, function(err, res) {
        if (err) {
            console.log('[SELECT ERROR] - ', err.message);
        }
        // 解析并导出查询结果
        var jsonResult = JSON.parse(JSON.stringify(res));
        console.log(jsonResult);

        // 表头
        worksheet.columns = [
            { header: 'Id', key: 'account_id', width: 10 },
            { header: 'Name', key: 'username', width: 10 },
            { header: 'Identity', key: 'identity_id', width: 20 },
            { header: 'Phone', key: 'phone_number', width: 20 },
            { header: 'Address', key: 'address', width: 30 },
            { header: 'Email', key: 'email', width: 20 },
        ]

        // 添加数据
        worksheet.addRows(jsonResult);

        // 写入Apply.xlsx
        workbook.xlsx.writeFile('Apply' + id + '.xlsx').then(function() {
            console.log("file saved!");
        });

    });
}

// 导出模块
module.exports = Supply;
