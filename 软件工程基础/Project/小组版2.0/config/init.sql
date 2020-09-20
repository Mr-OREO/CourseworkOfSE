DROP TABLE user;
CREATE TABLE user(
    account_id VARCHAR(20) NOT NULL PRIMARY KEY,
    username VARCHAR(20),
    identity_id VARCHAR(20),
    phone_number VARCHAR(20),
    address VARCHAR(60),
    email VARCHAR(40)
);

CREATE TABLE goods(
    goods_id VARCHAR(20) NOT NULL PRIMARY KEY,
    goods_name VARCHAR(20) NOT NULL,
    total int NOT NULL,
    description VARCHAR(60) NOT NULL,
    open_date DATETIME,
    end_date DATETIME
);

CREATE TABLE apply(
    goods_id VARCHAR(20) NOT NULL,
    account_id VARCHAR(20) NOT NULL,
    apply_result int(1) NOT NULL,
    receive_date DATETIME
);

insert into goods values(
    '001',
    'KN-95口罩',
    2,
    '主要是用来做职业呼吸性防护,该口罩可阻挡95%的细微颗粒物。',
    '2020-06-06 10:00:00',
    '2020-06-10 10:00:00'
);

insert into goods values(
    '002',
    '75%酒精',
    2,
    '能够有效杀灭大多数细菌与病毒',
    '2020-06-07 10:00:00',
    '2020-06-20 10:00:00'
);

insert into user values(
    '123123',
    '张三',
    '100000200001010001',
    '10010',
    '杭州市西湖区余杭塘路866号浙大紫金港校区',
    '3180102173@zju.edu.cn'
);

insert into user values(
    '234234',
    '李四',
    '100000200001010001',
    '10010',
    '杭州市西湖区余杭塘路866号浙大紫金港校区',
    '3180102173@zju.edu.cn'
);

insert into user values(
    '345345',
    '王五',
    '100000200001010001',
    '10010',
    '杭州市西湖区余杭塘路866号浙大紫金港校区',
    '3180102173@zju.edu.cn'
);

insert into user values(
    '456456',
    '赵六',
    '100000200001010001',
    '10000',
    '杭州市西湖区余杭塘路866号浙大紫金港校区',
    '3180102173@zju.edu.cn'
);

insert into apply values(
    '001',
    '123123',
    -1,
    NULL
);

insert into apply values(
    '001',
    '234234',
    -1,
    NULL
);

insert into apply values(
    '001',
    '345345',
    -1,
    NULL
);

insert into apply values(
    '001',
    '456456',
    -1,
    NULL
);
-- New Insertion
insert into goods values(
    '003',
    '3M护目镜',
    3,
    '可以用做专业医学防护,该护目镜可有效阻挡新冠病毒接触眼周皮肤。',
    '2020-06-06 10:00:00',
    '2020-06-16 10:00:00'
);

insert into apply values(
    '003',
    '123123',
    -1,
    NULL
);

insert into apply values(
    '003',
    '456456',
    -1,
    NULL
);