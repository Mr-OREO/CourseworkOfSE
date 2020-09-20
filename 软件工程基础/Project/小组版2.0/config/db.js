const mysql = require('mysql');


module.exports = {
    //数据库配置
    config:{
        host     : 'localhost',
        port     : '3306',
        user     : 'root',
        password : 'wzt123',
        database : 'se05'
    },
    //数据库连接
    sqlConnect : function(sql,sqlArr,callBack){
        var pool = mysql.createPool(this.config);
        pool.getConnection((err,conn)=>{
            console.log('success');
            if(err){
                console.log('数据库连接失败');
                return;
            }
            conn.query(sql,sqlArr,callBack);
            conn.release;
        })
    },

    create: function () {
        const me = this;
        // 没有pool的才创建
        if (!me.pool) {
            me.pool = mysql.createPool(this.config);
        }
    },
    query: function (sql) {
        console.log(sql)
        return new Promise((resolve, reject) => {
            const me = this;
            me.create();
            me.pool.getConnection((err, conn) => {
                if (err) {
                    console.log('mysql pool getConnections err:' + err);
                    reject(err)
                } else {
                    conn.query(sql, (err, result) => {
                        if(!err){
                            resolve(result)
                        }else{
                            reject(err)
                        }
                        // 释放连接到连接池
                        conn.release();

                    });
                }
            });
        })
    }
}
