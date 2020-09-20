var express = require('express');
var router = express.Router();
var db = require('../config/db');
var supply = require('../public/javascripts/supply');

//主界面
router.get('/', function(req, res, next) {
  supply.check();
  res.render('主界面',{id:req.query.uid})
});

//管理员页面
router.get('/admin', function(req, res, next) {
  supply.check();
  res.render('主界面-admin');
});

// 上线物资界面
router.get('/sxwz',function(req,res,next){
  res.render('上线物资')
});

// 个人信息填写
router.get('/grxx', function (req, res, next) {
  var sql = "select * from user where account_id="+req.query.uid+"";
  console.log(req.query.uid);
  var sqlArr = [];
  var callBack = (err,result)=>{
  if(err){
    console.log("在这里",'[SELECT ERROR] - ', err)
  }else{
    var dataString = JSON.stringify(result);
    var data = JSON.parse(dataString);
    console.log(data)
    if(data.length>0)
      res.redirect('/?uid='+req.query.uid+'');
    else{
      res.render('个人信息填写', {account_id:req.query.uid});
    }
  }
}
db.sqlConnect(sql,sqlArr,callBack)
})

//物资申领界面
router.get('/wzsl', function (req, res, next) {
  var uid = req.query.uid;
  var mid = req.query.mid;
  var sql = "select * from user where account_id= ?;";
  var sqlArr = [uid];
  var callBack = (err,result)=>{
    if(err){
      console.log('SELECT ERROR] - ', err)
    }else{
      var dataString = JSON.stringify(result);
      var data = JSON.parse(dataString);
      console.log(data);
      data[0]["goods_id"] = mid;
      res.render('物资申领',{data:data, id:req.query.uid})
    }
  };
  db.sqlConnect(sql,sqlArr,callBack)
});

//物资详细信息
router.get('/xxxx',function(req,res,next){
  var mid = req.query.mid;
  var sql = "select * from goods where goods_id=?";
  var sqlArr = [mid];
  var callBack = (err,result)=>{
    if(err){
      console.log('[SELECT ERROR] - ', err)
    }else{
      // var dataString = JSON.stringify(result);
      // var data = JSON.parse(dataString);
      console.log(result);
      res.render('查看详细信息',{data:result, admin:req.query.adm, ret:req.query.uid})
    }
  };
  db.sqlConnect(sql,sqlArr,callBack)
});

router.get('/dcmd', function(req, res, next){
  supply.excel(req.query.mid);
  res.render('主界面-admin');
})

module.exports = router;
