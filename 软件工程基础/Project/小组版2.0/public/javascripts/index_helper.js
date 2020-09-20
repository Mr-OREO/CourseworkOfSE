var db = require("../../config/db");
var moment = require("moment");


var get_index_record = function get_index_record(uid, adm) {
    var now = moment().format('YYYY-MM-DD HH:MM'); // 未申领且截至日期大于现在且数量大于0的
    if (adm) {
        return new Promise(async resolve => {
            var sql = "select goods.goods_id,goods.goods_name,goods.total,DATE_FORMAT(goods.end_date,'%Y-%m-%d %h:%m') as end_date,DATE_FORMAT(goods.open_date,'%Y-%m-%d %h:%m') as open_date from goods";
            let data = await db.query(sql);
            for (var i = 0; i < data.length; i++) {

                if (data[i]["end_date"] < now) { // 过期 导出名单
                    data[i].apply_result = 0;
                } else if (data[i]["open_date"] > now) { // 还未上线
                    data[i].apply_result = -1;
                } else if (data[i]["open_date"] < now && data[i]["end_date"] > now) { // 在线 可以物资下线
                    data[i].apply_result = 1;
                }
            }
            resolve(data)
        })
    } else {
        return new Promise(async resolve => {
            //已经申领的包括 申领成功和待分配的
            var sql = "select goods.goods_id,goods.goods_name,goods.total,DATE_FORMAT(goods.end_date,'%Y-%m-%d %h:%m') as end_date,apply.apply_result " +
                "from goods right join apply on goods.goods_id=apply.goods_id where apply.account_id = '" + uid + "'";
            let data = await db.query(sql);
            var result = [];
            for (var j = 0; j < data.length; j++) {
                // console.log(data[j]);
                result.push(data[j])
            }
            //没有申领过的 已经open的
            sql = "select goods.goods_id,goods.goods_name,DATE_FORMAT(goods.end_date,'%Y-%m-%d %h:%m') as end_date,goods.total from goods " +
                "where goods_id not in (select apply.goods_id from apply where account_id = '" + uid + "') and goods.end_date > '" + now + "' and goods.open_date < '" + now + "' and goods.total != 0";
            let data2 = await db.query(sql);
            for (var i = 0; i < data2.length; i++) {
                data2[i]["apply_result"] = 2; //未申领的为2
                // console.log(data2[i]);
                result.push(data2[i]);
            }
            resolve(result);
        })
    }
};

exports.get_index_record = get_index_record;