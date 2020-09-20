## README

> ##### 2020-张引-软件工程基础-第五组（G5）
>
> ##### 配置与开发文档

#### 文件层次

- ##### ./config

  存储数据库配置及操作文件，其中包含db.js并新建了一个query函数，使用Promise异步编程对象

- ##### ./db

  第一组用户管理数据库配置接口

- ##### ./public/wz

  存储所需静态资源，其中javascripts里面包含的**supply.js**是物资管理后台模块，**index_helper.js**是交互模块，包含数据渲染函数；

  **assets/demo/datatables-demo.js**中，定义了主界面数据渲染方式，采用datatable对象和AJAX异步编程

- ##### ./routes/G05物资申领

  默认子系统url标识符为**/wz**，简便起见此处略去

  - index.js 定义了所有页面的中转路由

    | API    | 方式 | 说明                                                        |
    | ------ | ---- | ----------------------------------------------------------- |
    | /      | GET  | 主界面，普通用户权限。<br>ejs脚本中定义了渲染数据参数 adm=0 |
    | /admin | GET  | 管理员主界面，管理权限。渲染参数adm=1                       |
    | /sxwz  | GET  | 上线物资界面，管理员权限                                    |
    | /grxx  | GET  | 个人信息填写及查看，默认渲染已有data，可修改                |
    | /wzsl  | GET  | 物资申领界面，渲染对应的个人信息，缓存物资信息              |
    | /dcmd  | GET  | 导出对应货物EXCEL中签名单                                   |
    | /xxxx  | GET  | 物资详细信息，根据物资id渲染                                |

  - user.js 定义所有操作相关的路由

    | API        | 方式 | 说明                                                         |
    | ---------- | ---- | ------------------------------------------------------------ |
    | /grxx      | POST | 在个人信息填写页面提交，创建个人信息                         |
    | /wzsl      | POST | 物资申领接口，<br />获取session中account 和goods_id，插入apply表 |
    | /sxwz      | POST | 上线物资接口，获取物资信息，插入goods表                      |
    | /qxsl      | GET  | 取消申领物资，通过session中account 和goods_id<br />删除apply记录 |
    | /user/wzxx | GET  | 下线物资，删除goods表记录和apply表的记录                     |
    | /apply     | GET  | datatable通过ajax调用该接口，<br />获取并渲染对应权限的主界面表格。 |

- ##### ./views/G05物资申领

  上线物资/个人信息填写/主界面/主界面-admin/查看详细信息/物资申领/

#### 实现功能

已实现需求报告中全部需求

额外增加部分：

- 物资检索、个人信息修改、公告栏功能
- URL隐匿保护、百用户同时响应耗时<0.5s、3000次并发攻击零故障率
- 完整文件头及文中注释

#### 启动/部署

1. 确认本地已安装**node**环境

2. 将**根目录**下的**G05_Init.sql**和**news.sql**在MySQL数据库中运行

3. 修改以下文件中的数据库配置

   - **./config/db.js**
   - **./db/userdb.js**
   - **./public/wz/javascripts/supply.js**

4. 将工程目录在控制台终端打开

5. 依次输入以下代码

   ```
   npm install
   ```

   ```
   npm start
   ```

6. 在浏览器地址栏输入

   ```
   localhost:3000/
   ```

   即可成功运行工程
