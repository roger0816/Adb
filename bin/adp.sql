/*
Navicat MySQL Data Transfer

Source Server         : adp_server
Source Server Version : 80030
Source Host           : 206.189.185.20:3306
Source Database       : adp

Target Server Type    : MYSQL
Target Server Version : 80030
File Encoding         : 65001

Date: 2022-10-16 09:12:28
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for Bulletin
-- ----------------------------
DROP TABLE IF EXISTS `Bulletin`;
CREATE TABLE `Bulletin` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `UserSid` int DEFAULT NULL,
  `Top` int DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  `EndTime` varchar(255) DEFAULT NULL,
  `Title` varchar(255) DEFAULT NULL,
  `Content` varchar(255) DEFAULT NULL,
  `Note` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of Bulletin
-- ----------------------------

-- ----------------------------
-- Table structure for CustomerClass
-- ----------------------------
DROP TABLE IF EXISTS `CustomerClass`;
CREATE TABLE `CustomerClass` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Id` varchar(255) DEFAULT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of CustomerClass
-- ----------------------------
INSERT INTO `CustomerClass` VALUES ('1', 'A', '艾比', '20220618054833');
INSERT INTO `CustomerClass` VALUES ('2', 'V', 'VIP', '20220907182505');
INSERT INTO `CustomerClass` VALUES ('3', 'S', '晴子', '20220907182513');

-- ----------------------------
-- Table structure for CustomerCost
-- ----------------------------
DROP TABLE IF EXISTS `CustomerCost`;
CREATE TABLE `CustomerCost` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `CustomerSid` varchar(255) DEFAULT NULL,
  `OrderId` varchar(255) DEFAULT NULL,
  `Currency` varchar(255) DEFAULT NULL,
  `Rate` varchar(255) DEFAULT NULL,
  `AddRate` varchar(255) DEFAULT NULL,
  `Type` varchar(255) DEFAULT NULL,
  `Change` varchar(255) DEFAULT NULL,
  `Value` varchar(255) DEFAULT NULL,
  `UserSid` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  `OrderTime` varchar(255) DEFAULT NULL,
  `Note1` varchar(255) DEFAULT NULL,
  `Note2` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of CustomerCost
-- ----------------------------
INSERT INTO `CustomerCost` VALUES ('2', '13', '-1', '新台幣(NTD)', '5', '0.00', '玉山', '100.00', '100.00', '1', '20220827205724', '20220827205423', null, null);
INSERT INTO `CustomerCost` VALUES ('3', '13', '-1', '新台幣(NTD)', '5', '0.00', '中信', '11.00', '111.00', '1', '20220827205724', '20220827205815', null, null);
INSERT INTO `CustomerCost` VALUES ('4', '13', '-1', '美金(USD)', '1', '0.00', null, '3.45', '114.45', '1', '20220827205724', '20220828062552', null, null);
INSERT INTO `CustomerCost` VALUES ('5', '13', '-1', '美金(USD)', '1', '0.00', null, '103.45', '217.90', '1', '20220827205724', '20220828152203', null, null);

-- ----------------------------
-- Table structure for CustomerData
-- ----------------------------
DROP TABLE IF EXISTS `CustomerData`;
CREATE TABLE `CustomerData` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Id` varchar(255) DEFAULT NULL,
  `Class` varchar(255) DEFAULT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `Money` double(255,0) unsigned zerofill DEFAULT NULL,
  `Currency` varchar(255) DEFAULT NULL,
  `PayType` varchar(255) DEFAULT NULL,
  `PayInfo` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  `UserSid` varchar(255) DEFAULT NULL,
  `Note1` varchar(255) DEFAULT NULL,
  `Note2` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of CustomerData
-- ----------------------------
INSERT INTO `CustomerData` VALUES ('13', 'A-A001', '1', 'aa01u', '000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000218', '美金(USD)', '玉山a', '123', '20220827205045', '1', '', '');

-- ----------------------------
-- Table structure for CustomerGameInfo
-- ----------------------------
DROP TABLE IF EXISTS `CustomerGameInfo`;
CREATE TABLE `CustomerGameInfo` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `CustomerId` varchar(255) DEFAULT NULL,
  `GameSid` varchar(255) DEFAULT NULL,
  `LoginType` varchar(255) DEFAULT NULL,
  `LoginAccount` varchar(255) DEFAULT NULL,
  `ServerName` varchar(255) DEFAULT NULL,
  `Character` varchar(255) DEFAULT NULL,
  `LastTime` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  `Note1` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of CustomerGameInfo
-- ----------------------------
INSERT INTO `CustomerGameInfo` VALUES ('3', 'A-A002', '1', 'gggg', 'aaa', 'bbb', 'ccc', null, '20220827130547', null);
INSERT INTO `CustomerGameInfo` VALUES ('13', 'A-A001', '1', 'google', 'account1', 'server1', 'cha1', null, '20220827205045', null);

-- ----------------------------
-- Table structure for ExchangeRate
-- ----------------------------
DROP TABLE IF EXISTS `ExchangeRate`;
CREATE TABLE `ExchangeRate` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Id` varchar(255) DEFAULT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of ExchangeRate
-- ----------------------------
INSERT INTO `ExchangeRate` VALUES ('1', null, '新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828024602');
INSERT INTO `ExchangeRate` VALUES ('2', null, '新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828182146');
INSERT INTO `ExchangeRate` VALUES ('3', null, '新台幣(NTD),,1;;美金(USD),,32;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828182207');
INSERT INTO `ExchangeRate` VALUES ('4', null, '新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828183959');
INSERT INTO `ExchangeRate` VALUES ('5', null, '新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828184034');
INSERT INTO `ExchangeRate` VALUES ('6', null, '新台幣(NTD),,1;;美金(USD),,35;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828184138');
INSERT INTO `ExchangeRate` VALUES ('7', null, '新台幣(NTD),,1;;美金(USD),,32;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828184554');
INSERT INTO `ExchangeRate` VALUES ('8', null, '新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828184712');
INSERT INTO `ExchangeRate` VALUES ('9', null, '新台幣(NTD),,1;;美金(USD),,29;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828184721');
INSERT INTO `ExchangeRate` VALUES ('10', null, '新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828184741');
INSERT INTO `ExchangeRate` VALUES ('11', null, '新台幣(NTD),,1;;美金(USD),,32;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828185255');
INSERT INTO `ExchangeRate` VALUES ('12', null, '新台幣(NTD),,1;;美金(USD),,34;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828185538');
INSERT INTO `ExchangeRate` VALUES ('13', null, '新台幣(NTD),,1;;美金(USD),,39;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828185758');
INSERT INTO `ExchangeRate` VALUES ('14', null, '新台幣(NTD),,1;;美金(USD),,33;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828191344');
INSERT INTO `ExchangeRate` VALUES ('15', null, '新台幣(NTD),,1;;美金(USD),,36;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828191545');
INSERT INTO `ExchangeRate` VALUES ('16', null, '新台幣(NTD),,1;;美金(USD),,39;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220828191557');
INSERT INTO `ExchangeRate` VALUES ('17', null, '新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220829075302');
INSERT INTO `ExchangeRate` VALUES ('18', '', '新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220921073451');
INSERT INTO `ExchangeRate` VALUES ('19', '', '新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20221012222922');
INSERT INTO `ExchangeRate` VALUES ('20', '', '新台幣(NTD),,1;;美金(USD),,31.1;;港幣(HKD),,;;人民幣(RMB),,;;林吉特(MYR),,;;新加元(SGD),,', '20221012234948');
INSERT INTO `ExchangeRate` VALUES ('21', '', '新台幣(NTD),,1;;美金(USD),,31.12;;港幣(HKD),,;;人民幣(RMB),,;;林吉特(MYR),,;;新加元(SGD),,', '20221012235007');
INSERT INTO `ExchangeRate` VALUES ('22', '', '新台幣(NTD),,1;;美金(USD),,31.123;;港幣(HKD),,;;人民幣(RMB),,;;林吉特(MYR),,;;新加元(SGD),,', '20221012235024');
INSERT INTO `ExchangeRate` VALUES ('23', '', '新台幣(NTD),,1;;美金(USD),,31.;;港幣(HKD),,;;人民幣(RMB),,;;林吉特(MYR),,;;新加元(SGD),,', '20221012235050');
INSERT INTO `ExchangeRate` VALUES ('24', '', '新台幣(NTD),,1;;美金(USD),,310;;港幣(HKD),,0;;人民幣(RMB),,0;;林吉特(MYR),,0;;新加元(SGD),,0', '20221012235408');
INSERT INTO `ExchangeRate` VALUES ('25', '', '新台幣(NTD),,1;;美金(USD),,310;;港幣(HKD),,10;;人民幣(RMB),,11;;林吉特(MYR),,12;;新加元(SGD),,13', '20221013000318');
INSERT INTO `ExchangeRate` VALUES ('26', '', '新台幣(NTD),,1;;美金(USD),,310;;港幣(HKD),,10.1;;人民幣(RMB),,11.12;;林吉特(MYR),,12.123;;新加元(SGD),,13.0', '20221013000336');

-- ----------------------------
-- Table structure for FactoryClass
-- ----------------------------
DROP TABLE IF EXISTS `FactoryClass`;
CREATE TABLE `FactoryClass` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Id` varchar(255) DEFAULT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `Currency` varchar(255) DEFAULT NULL,
  `PayTypeSid` varchar(255) DEFAULT NULL,
  `CostRate` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of FactoryClass
-- ----------------------------
INSERT INTO `FactoryClass` VALUES ('1', 'self1', '自營1', null, '1;;2;;3', '2.00', '20220826203549');

-- ----------------------------
-- Table structure for GameItem
-- ----------------------------
DROP TABLE IF EXISTS `GameItem`;
CREATE TABLE `GameItem` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `GameSid` int DEFAULT NULL,
  `Enable` int DEFAULT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `OrderNTD` varchar(255) DEFAULT NULL,
  `Bonus` varchar(255) DEFAULT NULL,
  `NTD` varchar(255) DEFAULT NULL,
  `EnableCost` double(255,0) DEFAULT NULL,
  `Cost` varchar(255) DEFAULT NULL,
  `AddValueTypeSid` varchar(255) DEFAULT NULL,
  `Note1` varchar(255) DEFAULT NULL,
  `Note2` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of GameItem
-- ----------------------------
INSERT INTO `GameItem` VALUES ('1', '1', '1', '卡包三百', '301', '31', '310', '0', '', '1,,26.00;;2,,27.00', '', '', '20220829014210');
INSERT INTO `GameItem` VALUES ('2', '1', '1', '卡包六百', '600.0', '60.0', '600', '0', null, '1,,50.00;;4,,50.00', null, null, '20220829040527');
INSERT INTO `GameItem` VALUES ('3', '1', '1', '卡包一百', '100.0', '10.0', '100', '0', null, '5,,10.00', null, null, '20220829044013');
INSERT INTO `GameItem` VALUES ('4', '1', '1', '卡包45', '45.0', '4.0', '40', '0', null, '3,,10.00', null, null, '20220829075428');
INSERT INTO `GameItem` VALUES ('8', '1', '0', 'aa', '10', '30', '300', null, null, '1,,1.00', null, null, '20221013155708');
INSERT INTO `GameItem` VALUES ('9', '1', '1', 'A', '-10', '-10', '-100', null, null, '1,,1.00', null, null, '20221013163400');

-- ----------------------------
-- Table structure for GameList
-- ----------------------------
DROP TABLE IF EXISTS `GameList`;
CREATE TABLE `GameList` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Id` varchar(255) DEFAULT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `GameRate` varchar(255) DEFAULT NULL,
  `Enable` int DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of GameList
-- ----------------------------
INSERT INTO `GameList` VALUES ('1', 'NSAN', '新三國志', '10', '1', '20220618054449');

-- ----------------------------
-- Table structure for OrderData
-- ----------------------------
DROP TABLE IF EXISTS `OrderData`;
CREATE TABLE `OrderData` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Id` varchar(255) DEFAULT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `UiRecord` varchar(255) DEFAULT NULL,
  `CustomerSid` varchar(255) DEFAULT NULL,
  `Step` varchar(255) DEFAULT NULL,
  `StepTime` varchar(255) DEFAULT NULL,
  `User` varchar(255) DEFAULT NULL,
  `Owner` varchar(255) DEFAULT NULL,
  `PaddingUser` varchar(255) DEFAULT NULL,
  `Item` varchar(255) DEFAULT NULL,
  `Cost` varchar(255) DEFAULT NULL,
  `Bouns` varchar(255) DEFAULT NULL,
  `ExRateSid` varchar(255) DEFAULT NULL,
  `PrimeRateSid` varchar(255) DEFAULT NULL,
  `PayType` varchar(255) DEFAULT NULL,
  `CanSelectPayType` varchar(255) DEFAULT NULL,
  `Money` varchar(255) DEFAULT NULL,
  `Note0` varchar(255) DEFAULT NULL,
  `Note1` varchar(255) DEFAULT NULL,
  `Note2` varchar(255) DEFAULT NULL,
  `Note3` varchar(255) DEFAULT NULL,
  `Note4` varchar(255) DEFAULT NULL,
  `Note5` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  `OrderDate` varchar(255) DEFAULT NULL,
  `OrderTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of OrderData
-- ----------------------------
INSERT INTO `OrderData` VALUES ('1', '220829-A001', '自營11', '0,0,0,0', '13', '5', ',20220829081430,,,', '1,1,1,1,1', '自營1', null, '1,,1;;2,,1', '25.00', '90.00', '17', '4', '1', '1', '775;4650;-3875', null, null, null, null, null, null, '20220829081426', '20220829', '081417');
INSERT INTO `OrderData` VALUES ('2', '220829-A002', '自營12', '0,0,0,0', '13', '5', ',20220829082726,,,', '1,1,1,1,1', '自營1', null, '4,,1', '1.33', '4.00', '17', '4', '3', '3', '41.230000000000004;42;-0.769999999999996', null, null, null, null, null, null, '20220829082721', '20220829', '082713');
INSERT INTO `OrderData` VALUES ('3', null, null, '0,0,0,0', '13', '0', ',,,,', '2,,,,', '', null, '1,,1', '1.00', '31.00', '26', '5', null, '1;;2', ';;', '', null, null, null, null, null, '20221014152950', '20221014', '152946');
INSERT INTO `OrderData` VALUES ('4', '221014-A001', '自營11', '0,0,0,0', '13', '5', ',20221014153134,,,', '2,2,2,2,2', '自營1', '', '1,,1;;9,,1', '0.68', '21.00', '26', '5', '1', '1', '21.08;1674.00;-1652.92', '', null, null, null, null, null, '20221014153016', '20221014', '153011');
INSERT INTO `OrderData` VALUES ('5', '221014-A002', '自營12', '0,0,0,0', '13', '5', ',20221014154646,,,', '2,2,2,2,2', '自營1', '', '1,,1', '1.00', '31.00', '26', '5', '1', '1;;2', '31.00;1612.00;-1581.00', '', null, null, null, null, null, '20221014154606', '20221014', '154553');

-- ----------------------------
-- Table structure for PayType
-- ----------------------------
DROP TABLE IF EXISTS `PayType`;
CREATE TABLE `PayType` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) DEFAULT NULL,
  `Id` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  `Value` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of PayType
-- ----------------------------
INSERT INTO `PayType` VALUES ('1', '國際谷哥-小虎1', null, '20220618135555', '1;2;1;1;1;1;1;14.500;美金(USD)');
INSERT INTO `PayType` VALUES ('2', '港幣刷卡', null, '20220618135803', '10;10;1;1;1;1;1;129.000;美金(USD)');
INSERT INTO `PayType` VALUES ('3', '現金-港幣', null, '20220828161116', '1;1;1;1;1;1;1;4.000;港幣(HKD)');
INSERT INTO `PayType` VALUES ('4', '現金台幣', null, '20220828161136', '1;1;1;1;1;1;1;1.000;新台幣(NTD)');
INSERT INTO `PayType` VALUES ('5', '現金人民幣', null, '20220828161202', '1;1;1;1;1;1;1;4.800;人民幣(RMB)');

-- ----------------------------
-- Table structure for PrimeCostRate
-- ----------------------------
DROP TABLE IF EXISTS `PrimeCostRate`;
CREATE TABLE `PrimeCostRate` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Id` varchar(255) DEFAULT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of PrimeCostRate
-- ----------------------------
INSERT INTO `PrimeCostRate` VALUES ('1', null, '新台幣(NTD),,1;;美金(USD),,29;;港幣(HKD),,3.9;;人民幣(RMB),,4.9;;林吉特(MYR),,5.9;;新加元(SGD),,6.9', '20220828024640');
INSERT INTO `PrimeCostRate` VALUES ('2', null, '新台幣(NTD),,1;;美金(USD),,29;;港幣(HKD),,3.9;;人民幣(RMB),,4.8;;林吉特(MYR),,5.7;;新加元(SGD),,6.6', '20220828024841');
INSERT INTO `PrimeCostRate` VALUES ('3', null, '新台幣(NTD),,1;;美金(USD),,30;;港幣(HKD),,4;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220829075319');
INSERT INTO `PrimeCostRate` VALUES ('4', null, '新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4.2;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7', '20220829075917');
INSERT INTO `PrimeCostRate` VALUES ('5', '', '新台幣(NTD),,1;;美金(USD),,31;;港幣(HKD),,4.2;;人民幣(RMB),,5;;林吉特(MYR),,6;;新加元(SGD),,7;;整數,,102;;小數一位,,102.4;;小數二位,,10.13', '20221013000854');

-- ----------------------------
-- Table structure for Schedule
-- ----------------------------
DROP TABLE IF EXISTS `Schedule`;
CREATE TABLE `Schedule` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Id` varchar(255) DEFAULT NULL,
  `Header` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci,
  `Data` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci,
  `UserCheck` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci,
  `Note` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of Schedule
-- ----------------------------
INSERT INTO `Schedule` VALUES ('7', '202210', ',,白領11-19,,白儲11-19,,早班10-18,,早班10-18,,白班11-19,,白班11-19,,白班11-19,,備註,,晚班18-0130,,晚班18-0130,,晚領19-03,,晚班19-02,,夜班20-03,,夜班20-03,,夜班20-03,,備註', ';;會計02::900::事,,::::,,::::,,::::,,::::,,::::,,::::;;會計02::1000::事,,test01::800::事,,test01::800::*,,root::::#,,::::,,::::,,::::;;會計01::::,,::::,,test01::900::,,::::,,::::,,::::,,::::;;會計01::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,', ';;0,,0,,0,,0,,0,,0,,0;;0,,1,,0,,0,,0,,0,,0;;0,,0,,1,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;', null, '20221014052400');
INSERT INTO `Schedule` VALUES ('8', '0', null, '*::AA::1.0+0,,#::AA::1.0+0,,事::事假::1.0+0,,事事::事假::1.0+0', null, null, '20221014052359');
INSERT INTO `Schedule` VALUES ('9', '202210', ',,白領11-19,,白儲11-19,,早班10-18,,早班10-18,,白班11-19,,白班11-19,,白班11-19,,備註,,晚班18-0130,,晚班18-0130,,晚領19-03,,晚班19-02,,夜班20-03,,夜班20-03,,夜班20-03,,備註', ';;會計02::::,,::::,,::::,,::::,,::::,,::::,,::::;;會計02::::,,::::,,::::,,::::,,::::,,::::,,::::;;會計01::::,,::::,,::::,,::::,,::::,,::::,,::::;;會計01::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;::::,,::::,,::::,,::::,,::::,,::::,,::::;;,,,,,,,,,,,,', ';;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;0,,0,,0,,0,,0,,0,,0;;', null, '20221012192809');

-- ----------------------------
-- Table structure for Settings
-- ----------------------------
DROP TABLE IF EXISTS `Settings`;
CREATE TABLE `Settings` (
  `key` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `value` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of Settings
-- ----------------------------

-- ----------------------------
-- Table structure for sqlite_sequence
-- ----------------------------
DROP TABLE IF EXISTS `sqlite_sequence`;
CREATE TABLE `sqlite_sequence` (
  `name` varchar(255) DEFAULT NULL,
  `seq` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of sqlite_sequence
-- ----------------------------
INSERT INTO `sqlite_sequence` VALUES ('GameList', '1');
INSERT INTO `sqlite_sequence` VALUES ('CustomerClass', '3');
INSERT INTO `sqlite_sequence` VALUES ('CustomerGameInfo', '13');
INSERT INTO `sqlite_sequence` VALUES ('CustomerData', '13');
INSERT INTO `sqlite_sequence` VALUES ('UserData', '13');
INSERT INTO `sqlite_sequence` VALUES ('FactoryClass', '1');
INSERT INTO `sqlite_sequence` VALUES ('CustomerCost', '5');
INSERT INTO `sqlite_sequence` VALUES ('ExchangeRate', '17');
INSERT INTO `sqlite_sequence` VALUES ('PrimeCostRate', '4');
INSERT INTO `sqlite_sequence` VALUES ('GameItem', '4');
INSERT INTO `sqlite_sequence` VALUES ('PayType', '5');
INSERT INTO `sqlite_sequence` VALUES ('OrderData', '2');
INSERT INTO `sqlite_sequence` VALUES ('UserBonus', '1');
INSERT INTO `sqlite_sequence` VALUES ('ScheduleData', '1');

-- ----------------------------
-- Table structure for UserBonus
-- ----------------------------
DROP TABLE IF EXISTS `UserBonus`;
CREATE TABLE `UserBonus` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `UserSid` varchar(255) DEFAULT NULL,
  `OrderSid` varchar(255) DEFAULT NULL,
  `Bonus` varchar(255) DEFAULT NULL,
  `Pay` varchar(255) DEFAULT NULL,
  `AddBonus` varchar(255) DEFAULT NULL,
  `AddPay` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of UserBonus
-- ----------------------------
INSERT INTO `UserBonus` VALUES ('1', '1', null, '\04.00', null, '4.00', null, '20220829082757');
INSERT INTO `UserBonus` VALUES ('2', '2', '5', '\031.00', null, '31.00', null, '20221014154756');

-- ----------------------------
-- Table structure for UserData
-- ----------------------------
DROP TABLE IF EXISTS `UserData`;
CREATE TABLE `UserData` (
  `Sid` int NOT NULL AUTO_INCREMENT,
  `Id` varchar(255) DEFAULT NULL,
  `Password` varchar(255) DEFAULT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `Cid` varchar(255) DEFAULT NULL,
  `Lv` int DEFAULT NULL,
  `ParentId` varchar(255) DEFAULT NULL,
  `StartDay` varchar(255) DEFAULT NULL,
  `BirthDay` varchar(255) DEFAULT NULL,
  `Tel` varchar(255) DEFAULT NULL,
  `Email` varchar(255) DEFAULT NULL,
  `Note1` varchar(255) DEFAULT NULL,
  `Note2` varchar(255) DEFAULT NULL,
  `Note3` varchar(255) DEFAULT NULL,
  `CreateTime` varchar(255) DEFAULT NULL,
  `UpdateTime` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Sid`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of UserData
-- ----------------------------
INSERT INTO `UserData` VALUES ('1', 'root', '1234', 'root', 'R01', '99', null, '20220618', null, null, null, null, null, null, '20220618124009', '20220618124009');
INSERT INTO `UserData` VALUES ('2', 'test01', '111111', 'test01', 'B01', '4', null, '20220923', null, null, null, null, null, null, '20220923110033', '20220923110033');
INSERT INTO `UserData` VALUES ('6', 'AAAA02', '111111', '會計02', 'A02', '4', null, '20220828', '20000101', null, null, null, null, null, '20220828224253', '20220828224606');
INSERT INTO `UserData` VALUES ('7', 'AAAA01', '111111', '會計01', 'A01', '4', null, '20220828', '20000101', null, null, null, null, null, '20220828224402', '20220828224611');
INSERT INTO `UserData` VALUES ('8', 'BBBB01', '111111', '主管01', 'B01', '3', null, '20220828', '20000101', null, null, null, null, null, '20220828224437', '20220828224616');
INSERT INTO `UserData` VALUES ('9', 'BBBB02', '111111', '主管02', 'B02', '3', null, '20220828', '20000101', null, null, null, null, null, '20220828224445', '20220828224622');
INSERT INTO `UserData` VALUES ('10', 'CCCC01', '111111', '儲值01', 'C01', '2', null, '20220828', '20000101', null, null, null, null, null, '20220828224531', '20220828224629');
INSERT INTO `UserData` VALUES ('11', 'CCCC02', '111111', '儲值02', 'C02', '2', null, '20220828', null, null, null, null, null, null, '20220828224640', '20220828224640');
INSERT INTO `UserData` VALUES ('12', 'DDDD01', '111111', '客服01', 'D01', '1', null, '20220828', null, null, null, null, null, null, '20220828224700', '20220828224700');
INSERT INTO `UserData` VALUES ('13', 'DDDD02', '111111', '客服02', 'D02', '1', null, '20220828', null, null, null, null, null, null, '20220828224708', '20220828224708');
