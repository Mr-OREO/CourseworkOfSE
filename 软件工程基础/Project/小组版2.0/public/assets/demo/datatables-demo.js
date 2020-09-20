// Call the dataTables jQuery plugin

function getTable(uid,adm) {
  $('#dataTable').DataTable({
    "ajax": {
      "url": "/users/apply?uid="+uid+"&adm="+adm,
      "type": "GET",
      "dataType": "json",
      "dataSrc": "data",
    },
    "destroy": "true",
    "columns": [
      {"data": "goods_name"},
      {"data": "end_date"},
      {"data": "total"},
      {"data": function (data) {
          return {"mid":data.goods_id,"rid":data.apply_result}
        },
        "render": function (data) {
          console.log(data);
          if(adm === 0){  //普通用户
            if(data.rid === 0){
              return '<a class="btn btn-primary" href="/xxxx?mid='+data.mid+'&adm=0&uid='+uid+'">查看详细信息</a> <a class="btn btn-secondary" href="#" >申领失败</a>'
            }else if(data.rid === -1){
              return '<a class="btn btn-primary"  href="/xxxx?mid='+data.mid+'&adm=0&uid='+uid+'">查看详细信息</a> <a class="btn btn-danger" href="/users/qxsl?uid='+uid+'&mid='+data.mid+'">取消申领</a>'
            }else if(data.rid === 1){
              return '<a class="btn btn-primary"  href="/xxxx?mid='+data.mid+'&adm=0&uid='+uid+'">查看详细信息</a> <a class="btn btn-secondary" href="#" >申领成功</a>'
            }else if(data.rid === 2){
              return '<a class="btn btn-primary" href="/xxxx?mid='+data.mid+'&adm=0&uid='+uid+'">查看详细信息</a> <a class="btn btn-success" href="/wzsl?uid='+uid+'&mid='+data.mid+'">申领入口</a>'
            }
          }else{
            if(data.rid === 0){ //导出名单<button class="btn btn-success">导出名单</button>
              return '<a class="btn btn-primary" href="/xxxx?mid='+data.mid+'&adm=1&uid='+uid+'">查看详细信息</a> <a class="btn btn-success" href="/dcmd?mid='+data.mid+'">导出名单</a>'
            }else if(data.rid === -1){ // 还未上线
              return '<a class="btn btn-primary"  href="/xxxx?mid='+data.mid+'&adm=1&uid='+uid+'">查看详细信息</a> <a class="btn btn-secondary" href="#">还未上线</a>'
            }else if(data.rid === 1){ // 物资下线
              return '<a class="btn btn-primary"  href="/xxxx?mid='+data.mid+'&adm=1&uid='+uid+'">查看详细信息</a> <a class="btn btn-danger"  href="/users/wzxx?mid='+data.mid+'">物资下线</a>'
            }
          }
        },"class":"text-right"
      },
    ],
  });
}
