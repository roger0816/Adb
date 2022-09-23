BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "Settings" (
	"key"	TEXT NOT NULL,
	"value"	TEXT,
	PRIMARY KEY("key")
);
CREATE TABLE IF NOT EXISTS "UserData" (
	"Sid"	INTEGER,
	"Id"	TEXT NOT NULL,
	"Password"	TEXT NOT NULL,
	"Name"	TEXT,
	"Cid"	TEXT,
	"Lv"	INTEGER DEFAULT 0,
	"ParentId"	TEXT,
	"StartDay"	TEXT,
	"BirthDay"	TEXT,
	"Tel"	TEXT,
	"Email"	TEXT,
	"Note1"	TEXT,
	"Note2"	TEXT,
	"Note3"	TEXT,
	"CreateTime"	TEXT,
	"UpdateTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "GameList" (
	"Sid"	INTEGER,
	"Id"	TEXT NOT NULL,
	"Name"	TEXT NOT NULL,
	"Enable"	INTEGER NOT NULL,
	"UpdateTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "Bulletin" (
	"Sid"	INTEGER,
	"UserSid"	INTEGER,
	"Top"	INTEGER,
	"UpdateTime"	TEXT,
	"EndTime"	TEXT,
	"Title"	TEXT,
	"Content"	TEXT,
	"Note"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "CustomerClass" (
	"Sid"	INTEGER,
	"Id"	TEXT NOT NULL,
	"Name"	TEXT NOT NULL,
	"UpdateTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "CustomerData" (
	"Sid"	INTEGER,
	"Id"	TEXT NOT NULL,
	"Class"	TEXT NOT NULL,
	"Name"	TEXT,
	"Money"	INTEGER DEFAULT 0,
	"Currency"	TEXT,
	"PayType"	TEXT,
	"PayInfo"	TEXT,
	"UpdateTime"	TEXT,
	"UserSid"	TEXT,
	"Note1"	TEXT,
	"Note2"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "CustomerGameInfo" (
	"Sid"	INTEGER,
	"CustomerId"	TEXT,
	"GameSid"	TEXT,
	"LoginType"	TEXT,
	"LoginAccount"	TEXT,
	"ServerName"	TEXT,
	"Character"	TEXT,
	"LastTime"	TEXT,
	"UpdateTime"	TEXT,
	"Note1"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "FactoryClass" (
	"Sid"	INTEGER,
	"Id"	TEXT NOT NULL,
	"Name"	TEXT NOT NULL,
	"Currency"	TEXT,
	"PayTypeSid"	TEXT NOT NULL,
	"CostRate"	TEXT NOT NULL,
	"UpdateTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "CustomerCost" (
	"Sid"	INTEGER,
	"CustomerSid"	TEXT,
	"OrderId"	TEXT,
	"Currency"	TEXT,
	"Rate"	TEXT,
	"AddRate"	TEXT,
	"Type"	TEXT,
	"Change"	TEXT,
	"Value"	TEXT,
	"UserSid"	TEXT,
	"UpdateTime"	TEXT,
	"OrderTime"	TEXT,
	"Note1"	TEXT,
	"Note2"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "ExchangeRate" (
	"Sid"	INTEGER,
	"Id"	TEXT,
	"Name"	TEXT,
	"UpdateTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "PrimeCostRate" (
	"Sid"	INTEGER,
	"Id"	TEXT,
	"Name"	TEXT,
	"UpdateTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "UserBonus" (
	"Sid"	INTEGER,
	"UserSid"	TEXT,
	"OrderSid"	TEXT,
	"Bonus"	TEXT,
	"Pay"	TEXT,
	"AddBonus"	TEXT,
	"AddPay"	TEXT,
	"UpdateTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "GameItem" (
	"Sid"	INTEGER,
	"GameSid"	INTEGER,
	"Enable"	INTEGER DEFAULT 1,
	"Name"	TEXT,
	"OrderNTD"	TEXT,
	"Bonus"	TEXT,
	"NTD"	TEXT,
	"EnableCost"	INTEGER DEFAULT 0,
	"Cost"	TEXT,
	"AddValueTypeSid"	TEXT,
	"Note1"	TEXT,
	"Note2"	TEXT,
	"UpdateTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "PayType" (
	"Sid"	INTEGER,
	"Name"	TEXT,
	"Id"	TEXT,
	"UpdateTime"	TEXT,
	"Value"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "OrderData" (
	"Sid"	INTEGER,
	"Id"	TEXT,
	"Name"	TEXT,
	"UiRecord"	TEXT,
	"CustomerSid"	TEXT,
	"Step"	TEXT,
	"StepTime"	INTEGER,
	"User"	TEXT,
	"Owner"	TEXT,
	"PaddingUser"	TEXT,
	"Item"	TEXT,
	"Cost"	TEXT,
	"Bouns"	TEXT,
	"ExRateSid"	TEXT,
	"PrimeRateSid"	TEXT,
	"PayType"	TEXT,
	"CanSelectPayType"	TEXT,
	"Money"	TEXT,
	"Note0"	TEXT,
	"Note1"	TEXT,
	"Note2"	TEXT,
	"Note3"	TEXT,
	"Note4"	TEXT,
	"Note5"	TEXT,
	"UpdateTime"	TEXT,
	"OrderDate"	TEXT,
	"OrderTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "ScheduleData" (
	"Sid"	INTEGER,
	"Id"	TEXT,
	"Cost"	TEXT,
	"Check"	TEXT,
	"Note"	TEXT,
	"UpdateTime"	TEXT,
	PRIMARY KEY('Sid' AUTOINCREMENT)
);
INSERT INTO "UserData" ("Sid","Id","Password","Name","Cid","Lv","ParentId","StartDay","BirthDay","Tel","Email","Note1","Note2","Note3","CreateTime","UpdateTime") VALUES (1,'root','1234','Test001','R01',99,NULL,'20220618',NULL,NULL,NULL,NULL,NULL,NULL,'20220618124009','20220618124009');
INSERT INTO "UserData" ("Sid","Id","Password","Name","Cid","Lv","ParentId","StartDay","BirthDay","Tel","Email","Note1","Note2","Note3","CreateTime","UpdateTime") VALUES (6,'AAAA02','111111','會計02','A02',4,NULL,'20220828','20000101','','','',NULL,NULL,'20220828224253','20220828224606');
INSERT INTO "UserData" ("Sid","Id","Password","Name","Cid","Lv","ParentId","StartDay","BirthDay","Tel","Email","Note1","Note2","Note3","CreateTime","UpdateTime") VALUES (7,'AAAA01','111111','會計01','A01',4,NULL,'20220828','20000101','','','',NULL,NULL,'20220828224402','20220828224611');
INSERT INTO "UserData" ("Sid","Id","Password","Name","Cid","Lv","ParentId","StartDay","BirthDay","Tel","Email","Note1","Note2","Note3","CreateTime","UpdateTime") VALUES (8,'BBBB01','111111','主管01','B01',3,NULL,'20220828','20000101','','','',NULL,NULL,'20220828224437','20220828224616');
INSERT INTO "UserData" ("Sid","Id","Password","Name","Cid","Lv","ParentId","StartDay","BirthDay","Tel","Email","Note1","Note2","Note3","CreateTime","UpdateTime") VALUES (9,'BBBB02','111111','主管02','B02',3,NULL,'20220828','20000101','','','',NULL,NULL,'20220828224445','20220828224622');
INSERT INTO "UserData" ("Sid","Id","Password","Name","Cid","Lv","ParentId","StartDay","BirthDay","Tel","Email","Note1","Note2","Note3","CreateTime","UpdateTime") VALUES (10,'CCCC01','111111','儲值01','C01',2,NULL,'20220828','20000101','','','',NULL,NULL,'20220828224531','20220828224629');
INSERT INTO "UserData" ("Sid","Id","Password","Name","Cid","Lv","ParentId","StartDay","BirthDay","Tel","Email","Note1","Note2","Note3","CreateTime","UpdateTime") VALUES (11,'CCCC02','111111','儲值02','C02',2,NULL,'20220828',NULL,NULL,NULL,NULL,NULL,NULL,'20220828224640','20220828224640');
INSERT INTO "UserData" ("Sid","Id","Password","Name","Cid","Lv","ParentId","StartDay","BirthDay","Tel","Email","Note1","Note2","Note3","CreateTime","UpdateTime") VALUES (12,'DDDD01','111111','客服01','D01',1,NULL,'20220828',NULL,NULL,NULL,NULL,NULL,NULL,'20220828224700','20220828224700');
INSERT INTO "UserData" ("Sid","Id","Password","Name","Cid","Lv","ParentId","StartDay","BirthDay","Tel","Email","Note1","Note2","Note3","CreateTime","UpdateTime") VALUES (13,'DDDD02','111111','客服02','D02',1,NULL,'20220828',NULL,NULL,NULL,NULL,NULL,NULL,'20220828224708','20220828224708');
INSERT INTO "GameList" ("Sid","Id","Name","Enable","UpdateTime") VALUES (1,'NSAN','新三國志',1,'20220618054449');
INSERT INTO "CustomerClass" ("Sid","Id","Name","UpdateTime") VALUES (1,'A','艾比','20220618054833');
INSERT INTO "CustomerClass" ("Sid","Id","Name","UpdateTime") VALUES (2,'V','VIP','20220907182505');
INSERT INTO "CustomerClass" ("Sid","Id","Name","UpdateTime") VALUES (3,'S','晴子','20220907182513');
INSERT INTO "CustomerData" ("Sid","Id","Class","Name","Money","Currency","PayType","PayInfo","UpdateTime","UserSid","Note1","Note2") VALUES (13,'A-A001','1','aa01user',217.9,'美金(USD)','玉山','123','20220827205045','1','',NULL);
INSERT INTO "CustomerGameInfo" ("Sid","CustomerId","GameSid","LoginType","LoginAccount","ServerName","Character","LastTime","UpdateTime","Note1") VALUES (3,'A-A002','1','gggg','aaa','bbb','ccc',NULL,'20220827130547',NULL);
INSERT INTO "CustomerGameInfo" ("Sid","CustomerId","GameSid","LoginType","LoginAccount","ServerName","Character","LastTime","UpdateTime","Note1") VALUES (13,'A-A001','1','google','account1','server1','cha1',NULL,'20220827205045',NULL);
INSERT INTO "FactoryClass" ("Sid","Id","Name","Currency","PayTypeSid","CostRate","UpdateTime") VALUES (1,'self1','自營1',NULL,'1;;2;;3','2.00','20220826203549');
INSERT INTO "CustomerCost" ("Sid","CustomerSid","OrderId","Currency","Rate","AddRate","Type","Change","Value","UserSid","UpdateTime","OrderTime","Note1","Note2") VALUES (2,'13','-1','新台幣(NTD)','5','0.00','玉山','100.00','100.00','1','20220827205724','20220827205423','',NULL);
INSERT INTO "CustomerCost" ("Sid","CustomerSid","OrderId","Currency","Rate","AddRate","Type","Change","Value","UserSid","UpdateTime","OrderTime","Note1","Note2") VALUES (3,'13','-1','新台幣(NTD)','5','0.00','中信','11.00','111.00','1','20220827205724','20220827205815','',NULL);
INSERT INTO "CustomerCost" ("Sid","CustomerSid","OrderId","Currency","Rate","AddRate","Type","Change","Value","UserSid","UpdateTime","OrderTime","Note1","Note2") VALUES (4,'13','-1','美金(USD)','1','0.00','','3.45','114.45','1','20220827205724','20220828062552','',NULL);
INSERT INTO "CustomerCost" ("Sid","CustomerSid","OrderId","Currency","Rate","AddRate","Type","Change","Value","UserSid","UpdateTime","OrderTime","Note1","Note2") VALUES (5,'13','-1','美金(USD)','1','0.00','','103.45','217.90','1','20220827205724','20220828152203','',NULL);
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (1,NULL,'新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828024602');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (2,NULL,'新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828182146');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (3,NULL,'新台幣(NTD),,1;;美金(USD),,32;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828182207');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (4,NULL,'新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828183959');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (5,NULL,'新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828184034');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (6,NULL,'新台幣(NTD),,1;;美金(USD),,35;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828184138');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (7,NULL,'新台幣(NTD),,1;;美金(USD),,32;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828184554');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (8,NULL,'新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828184712');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (9,NULL,'新台幣(NTD),,1;;美金(USD),,29;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828184721');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (10,NULL,'新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828184741');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (11,NULL,'新台幣(NTD),,1;;美金(USD),,32;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828185255');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (12,NULL,'新台幣(NTD),,1;;美金(USD),,34;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828185538');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (13,NULL,'新台幣(NTD),,1;;美金(USD),,39;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828185758');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (14,NULL,'新台幣(NTD),,1;;美金(USD),,33;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828191344');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (15,NULL,'新台幣(NTD),,1;;美金(USD),,36;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828191545');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (16,NULL,'新台幣(NTD),,1;;美金(USD),,39;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220828191557');
INSERT INTO "ExchangeRate" ("Sid","Id","Name","UpdateTime") VALUES (17,NULL,'新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220829075302');
INSERT INTO "PrimeCostRate" ("Sid","Id","Name","UpdateTime") VALUES (1,NULL,'新台幣(NTD),,1;;美金(USD),,29;;港幣(HKD),,3.9;;人民幣(RMB),,4.9;;林吉特(MYR),,5.9;;新加元(SGD),,6.9','20220828024640');
INSERT INTO "PrimeCostRate" ("Sid","Id","Name","UpdateTime") VALUES (2,NULL,'新台幣(NTD),,1;;美金(USD),,29;;港幣(HKD),,3.9;;人民幣(RMB),,4.8;;林吉特(MYR),,5.7;;新加元(SGD),,6.6','20220828024841');
INSERT INTO "PrimeCostRate" ("Sid","Id","Name","UpdateTime") VALUES (3,NULL,'新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220829075319');
INSERT INTO "PrimeCostRate" ("Sid","Id","Name","UpdateTime") VALUES (4,NULL,'新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4.2;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7','20220829075917');
INSERT INTO "UserBonus" ("Sid","UserSid","OrderSid","Bonus","Pay","AddBonus","AddPay","UpdateTime") VALUES (1,'1',NULL,X'00342e3030',NULL,'4.00',NULL,'20220829082757');
INSERT INTO "GameItem" ("Sid","GameSid","Enable","Name","OrderNTD","Bonus","NTD","EnableCost","Cost","AddValueTypeSid","Note1","Note2","UpdateTime") VALUES (1,1,1,'卡包三百','300.0','30.0','250.0',0,NULL,'1,,25.00;;2,,25.00',NULL,NULL,'20220829014210');
INSERT INTO "GameItem" ("Sid","GameSid","Enable","Name","OrderNTD","Bonus","NTD","EnableCost","Cost","AddValueTypeSid","Note1","Note2","UpdateTime") VALUES (2,1,1,'卡包六百','600.0','60.0','500.0',0,NULL,'1,,50.00;;4,,50.00',NULL,NULL,'20220829040527');
INSERT INTO "GameItem" ("Sid","GameSid","Enable","Name","OrderNTD","Bonus","NTD","EnableCost","Cost","AddValueTypeSid","Note1","Note2","UpdateTime") VALUES (3,1,1,'卡包一百','100.0','10.0','80.0',0,NULL,'5,,10.00',NULL,NULL,'20220829044013');
INSERT INTO "GameItem" ("Sid","GameSid","Enable","Name","OrderNTD","Bonus","NTD","EnableCost","Cost","AddValueTypeSid","Note1","Note2","UpdateTime") VALUES (4,1,1,'卡包45','45.0','4.0','40.0',0,NULL,'3,,10.00',NULL,NULL,'20220829075428');
INSERT INTO "PayType" ("Sid","Name","Id","UpdateTime","Value") VALUES (1,'國際谷哥-小虎1',NULL,'20220618135555','1;2;1;1;1;1;1;14.500;美金(USD)');
INSERT INTO "PayType" ("Sid","Name","Id","UpdateTime","Value") VALUES (2,'港幣刷卡',NULL,'20220618135803','10;10;1;1;1;1;1;129.000;美金(USD)');
INSERT INTO "PayType" ("Sid","Name","Id","UpdateTime","Value") VALUES (3,'現金-港幣',NULL,'20220828161116','1;1;1;1;1;1;1;4.000;港幣(HKD)');
INSERT INTO "PayType" ("Sid","Name","Id","UpdateTime","Value") VALUES (4,'現金台幣',NULL,'20220828161136','1;1;1;1;1;1;1;1.000;新台幣(NTD)');
INSERT INTO "PayType" ("Sid","Name","Id","UpdateTime","Value") VALUES (5,'現金人民幣',NULL,'20220828161202','1;1;1;1;1;1;1;4.800;人民幣(RMB)');
INSERT INTO "OrderData" ("Sid","Id","Name","UiRecord","CustomerSid","Step","StepTime","User","Owner","PaddingUser","Item","Cost","Bouns","ExRateSid","PrimeRateSid","PayType","CanSelectPayType","Money","Note0","Note1","Note2","Note3","Note4","Note5","UpdateTime","OrderDate","OrderTime") VALUES (1,'220829-A001','自營11','0,0,0,0','13','5',',20220829081430,,,','1,1,1,1,1','自營1','','1,,1;;2,,1','25.00','90.00','17','4','1','1','775;4650;-3875','',NULL,NULL,NULL,NULL,NULL,'20220829081426','20220829','081417');
INSERT INTO "OrderData" ("Sid","Id","Name","UiRecord","CustomerSid","Step","StepTime","User","Owner","PaddingUser","Item","Cost","Bouns","ExRateSid","PrimeRateSid","PayType","CanSelectPayType","Money","Note0","Note1","Note2","Note3","Note4","Note5","UpdateTime","OrderDate","OrderTime") VALUES (2,'220829-A002','自營12','0,0,0,0','13','5',',20220829082726,,,','1,1,1,1,1','自營1','','4,,1','1.33','4.00','17','4','3','3','41.230000000000004;42;-0.769999999999996','',NULL,NULL,NULL,NULL,NULL,'20220829082721','20220829','082713');
COMMIT;
