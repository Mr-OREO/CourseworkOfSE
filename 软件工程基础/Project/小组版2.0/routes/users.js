var express = require('express');
var router = express.Router();
var db = require('../config/db');
var indexHelper = require("../public/javascripts/index_helper");

//个人信息填写接口
router.post('/grxx', function (req, res, next) {
  console.log("account_id",req.body.account_id);
  var sql = 'INSERT INTO user values(?,?,?,?,?,?)'
  var sqlArr = [req.body.account_id, req.body.username, req.body.identity_id, req.body.phone_number, req.body.address, req.body.email]
  console.log(sqlArr);
  var callBack = (err, data) => {
      if (err) {
          console.log('[INSERT ERROR] - ', err)
      } else {
          console.log('填写成功')
          res.redirect('/grxx?uid='+req.body.account_id)
      }
  }

  db.sqlConnect(sql, sqlArr, callBack)
});

//物资申领接口
router.post('/wzsl', function (req, res, next) {
  var sql = 'INSERT INTO apply values(?,?,?,?)';
  var sqlArr = [req.body.goods_id, req.body.account_id,-1,null];
  var callBack = (err, data) => {
    if (err) {
      console.log('[INSERT ERROR] - ', err)
    } else {
      console.log('申领成功');
      res.redirect('/?uid='+req.body.account_id)
    }
  };
  db.sqlConnect(sql, sqlArr, callBack)
});


//上线物资接口
router.post('/sxwz',function(req,res,next){
  var sql = 'INSERT INTO goods values(?,?,?,?,?,?)';
  var sqlArr = [req.body.id,req.body.name,req.body.total,req.body.description,req.body.open_date,req.body.end_date];
  var callBack = (err,data)=>{
    if(err){
      console.log('[INSERT ERROR] - ', err)
    }else{
      console.log('上线成功');
      res.redirect('/admin')
    }
  }

  db.sqlConnect(sql,sqlArr,callBack)
})


//取消申领接口
router.get('/qxsl',async function (req,res) {
  var uid = req.query.uid;
  var mid = req.query.mid;
  await db.query("delete from apply where account_id = '"+uid+"' and goods_id='"+mid+"';");
  res.redirect("/?uid="+req.query.uid)
});

//物资下线
router.get('/wzxx',async function (req,res) {
  var mid = req.query.mid;
  await db.query("delete from apply where goods_id='"+mid+"';");
  await db.query("delete from goods where goods_id='"+mid+"';");
  res.redirect("/admin")
});

//获取主页数据
router.get('/apply',async function (req,res) {
  var uid = req.query.uid;
  var adm = req.query.adm;
  try{
    if(adm === '0'){
      let data = await indexHelper.get_index_record(uid,false);
      console.log(data)
      res.send({"data":data})
    }else{
      let data = await indexHelper.get_index_record(uid,true);
      res.send({"data":data})
    }

  }catch (e) {
    console.log(e);
    res.send({"data":[]})
  }
});

module.exports = router;
