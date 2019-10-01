-- 員工

DROP TABLE IF EXISTS `employee`;
CREATE TABLE employee(
	id int(10) unsigned NOT NULL,
	eId VARCHAR(10) NOT NULL,
	eName VARCHAR(20),
	eSex INT,
	eAccount VARCHAR(10),
	ePassword VARCHAR(10),
	eEmail  VARCHAR(40),
	PRIMARY KEY (eId,id)

);
INSERT INTO `employee` (`id`,`eId`, `eName`, `eSex`, `eAccount`, `ePassword`, `eEmail`) VALUES
(1,'emp1', 'hank', 1, 'hank', 'admin', 'hankhank417@gmail.com'),
(2,'emp2', 'howard', 1, 'howard', 'admin', 'howard8701301@yahoo.com.tw'),
(3,'emp3', 'brian', 1, 'yoke', 'admin', 'brian991334@gmail.com'),
(4,'emp4', 'ej', 0, 'ej', 'admin', 'q00480209yijie@gmail.com'),
(5,'emp5', 'vincent', 1, 'vincent', 'admin', 'repk1124@g-mail.nsysu.edu.tw'),
(6,'emp6', 'sae', 1, 'sae', 'admin', 'B054011045@student.nsysu.edu.tw');

-- 供應商

DROP TABLE IF EXISTS `supplier`;
CREATE TABLE supplier(
	id int(10) unsigned NOT NULL,
	sId VARCHAR(10) NOT NULL,
	sName VARCHAR(50),
	sPhone VARCHAR(10),
	sClass VARCHAR(50),
	sAddress VARCHAR(50),
	taxId CHAR(8),
	PRIMARY KEY (sId)
);
INSERT INTO `supplier` (`id`,`sId`, `sName`, `sPhone`, `sClass`, `sAddress`, `taxId`) VALUES
(1,'sup1', 'Howard meat company', '0123456789', 'meat', 'Kaohsiung city NSYSU', '96385527'),
(2,'sup2', 'Hank fruit company', '0159357486', 'fruit', 'Taipei city NTU', '12615801'),
(3,'sup3', 'brian vegetable company', '0987563248', 'vegetable', 'Taipei city NCCU', '84562195'),
(4,'sup4', 'fish seafood company', '0987563248', 'seafood', 'Taipei city NCCU', '84562195'),
(5,'sup5', 'EJ grain company', '0841932547', 'grain', 'Taoyuan city NCU', '95463285');

-- 顧客會員

DROP TABLE IF EXISTS `customer`;
CREATE TABLE customer(
	id int(10) unsigned NOT NULL,
	cId VARCHAR(10) NOT NULL,
	cName VARCHAR(10),
	cPassword VARCHAR(10),
	cPhone VARCHAR(10),
	cSex INT,
	cAddress VARCHAR(50),
	cEMail VARCHAR(30),
	PRIMARY KEY (cId)
);
INSERT INTO `customer` (`id`,`cId`, `cName`, `cPassword`, `cPhone`, `cSex`, `cAddress`, `cEmail`) VALUES
(1,'cus1', 'brian', 'customer', '0988776655', 0, 'Pintung Kenting', 'brian991334@gmail.com'),
(3,'cus2', 'howard', 'customer', '0968463895', 1, 'Yilan beach', 'howard8701301@yahoo.com.tw'),
(4,'cus3', 'hank', 'customer', '0988776655', 1, 'Taipei city NSYSU', 'hankhank417@gmail.com'),
(5,'cus4', 'ej', 'customer', '0926468945', 1, 'Taoyuan 101', 'q00480209yijie@gmail.com'),
(6,'cus5', 'vincent', 'customer', '0926468945', 1, 'Taipei 101', 'repk1124@g-mail.nsysu.edu.tw'),
(7,'cus6', 'sae', 'customer', '0926468945', 1, 'Taipei 101', 'B054011045@student.nsysu.edu.tw');

-- 庫存

DROP TABLE IF EXISTS `stock`;
CREATE TABLE stock(
	id int(10) unsigned NOT NULL,
	gId VARCHAR(10) NOT NULL,
	quantity INT,
	gName VARCHAR(50),
	price int(11),
	goodFullName varchar(50),
	clickCount int(255),
	introduce varchar(200),
	PRIMARY KEY (gId)
);
INSERT INTO `stock` (`id`,`gId`, `quantity`, `gName`, `price`, `goodFullName`, `clickCount`, `introduce`) VALUES
(1,'f1', 176, 'apple', 19, 'fruit', 0, '鮮蘋果含水量為85%且含有豐富的的碳水化合物、維生素和微量元素，尤其是維生素A和胡蘿蔔素的含量較高。蘋果中的蘋果酸和檸檬酸能夠提高胃液的分泌，促進消化。'),
(2,'f2', 411, 'banana', 29, 'fruit', 3,'香蕉幾乎含有所有的維生素和礦物質，因此從中可以很容易地攝取各種營養素。香蕉膳食纖維含量豐富，具有很好的通便效果，加上含有果膠成分，能充分潤滑腸道，加速糞便通過的速度，不讓廢物滯留在腸道中，能避免產生致癌物，可有效預防腸癌。'),
(3,'f3', 921, 'guava', 39, 'fruit', 5,'番石榴為低熱量、高纖維、水分高，易有飽足感之水果，是糖尿病和減肥者的最佳選擇之一。因屬熱帶高維他命Ｃ水果，亦為天然美白的聖品，對於牙齦健康也有幫助。也是人體攝取維他命C最重要的來源。同時富含維生素，纖維與抗氧化劑的番石榴更是天然的防老抗癌防癌的水果。'),
(4,'v1', 335, 'cabbaage', 35, 'vegetable', 2,'甘藍營養相當豐富，含有大量維生素C、纖維素、碳水化合物和各種礦物質。甘藍中含有的蘿蔔硫素，則是功能強大的抗氧化物，可以增強體內酵素的解毒能力，也是維生素C和植物纖維的良好來源。'),
(5,'v2', 270, 'bok choy', 49, 'vegetable', 4,'小白菜又叫青菜、雞毛菜、油白菜。 據測定，小白菜是蔬菜中含礦物質和維生素最豐富的菜。'),
(6,'v3', 504, 'carrot', 79, 'vegetable', 6,'胡蘿蔔營養豐富。人們一般食用其肉質根，有時也食用胡蘿蔔葉。胡蘿蔔種子內含有揮發性油。胡蘿蔔素有治療夜盲症、保護呼吸道和促進兒童生長等功能。'),
(7,'v4', 367, 'cauliflower', 39, 'vegetable', 10,'《本草綱目》中記載：花菜性涼，味甘，歸肝、肺經。現代醫學研究認為，白花菜具有爽喉開音、潤肺止咳、抗癌潤腸等功效，可輔助治療咽喉腫痛、乾咳、便秘等症。'),
(8,'s1', 143, 'prawn', 109, 'sea', 5,'蝦中含有豐富的鎂，鎂對心臟活動具有重要的調節作用，能很好的保護心血管系統，它可減少血液中膽固醇含量，防止動脈硬化，同時還能擴張冠狀動脈，有利於預防高血壓及心肌梗死。'),
(9,'s2', 441, 'shark', 237, 'sea', 6,'鯊魚含有豐富維生素A，維生素A可以促進黏膜健康，有助預防呼吸系統的感染，維持皮膚、頭髮、視力健康，還可以有效對抗氧化，具有促進健康、增加抵抗力、預防老化。'),
(10,'s3', 420, 'crab', 249, 'sea', 7,'螃蟹富含優質蛋白質，蟹肉較細膩，肌肉纖維中含有10餘種游離胺基酸，其中穀氨酸、脯氨酸、精氨酸含量較多，對術後、病後、慢性消耗性疾病等需要補充營養的人大有益處。'),
(11,'l1', 987, 'dumpling', 89, 'frozenFood', 9,'一種源自中國的一種以麵皮包餡、形如半月或元寶形的食物，常見於中國和東亞其他地區。餃子也是在農曆新年和冬至等節日的重要食品，也是中國北方省份全年食用的主要食物之一。'),
(12,'g1', 558, 'rice', 89, 'grain', 1,'稻米的營養價值高，其主要營養成分是：蛋白質、糖類、鈣、磷、鐵、葡萄糖、果糖、麥芽糖、維生素B1、維生素B2等。大米的澱粉粒小，粉質最細。稻米的纖維素含量少，因此口感好，又便於人體消化和吸收。'),
(13,'g2', 620, 'cashew', 119, 'grain', 4,'腰果含鈣、鎂、鉀、鐵、維生素A、B1、B2、B6量很高，其中維生素B1的含量僅次於芝麻和花生，有補充體力、消除疲勞的效果，最適合容易疲倦人士食用。'),
(14,'g3', 231, 'adzuki bean', 49, 'grain', 7,'紅豆屬高蛋白質、低脂肪的高營養榖類食品，而且含有蛋白質、醣類、脂肪、膳食纖維、維生素B群、維生素E、鉀、鈣、鐵、磷、鋅等營養素。紅豆有豐富的鐵質，可以使人氣色紅潤，可以補血、促進血液循環、強化體力、增強抵抗力。'),
(15,'g4', 531, 'soy beans', 49, 'grain', 8,'黃豆，具有健脾寬中，潤燥消水、清熱解毒、益氣等功效。大豆含有豐富的蛋白質、胺基酸、鈣、鐵、鋅、維生素B群及大量的膳食纖維，在人體內都參與調節生理的功能。'),
(16,'m1', 395, 'pork', 88, 'meat', 6,'豬肉能夠提供身體所需的蛋白質、脂肪、維生素及礦物質，能幫助修復身體組織、加強免疫力、保護器官功能。所含的磷能製造骨骼與牙齒所需營養、幫助神經功能保持正常。豬肉也可以提供血紅素鐵和促進鐵吸收的半胱胺酸，能改善缺鐵性貧血。'),
(17,'m2', 482, 'beef', 129, 'meat', 8,'食用前因牛肉屬於高蛋白的食品，腎炎的人不宜多吃以免增加腎的負擔；正常食用的情況下牛肉可以提供人體所需的鋅，鋅有強化免疫系統的功能也可以使傷口復元亦是皮膚、骨骼和毛髮的營養來源。'),
(18,'m3', 878, 'mutton', 189, 'meat', 5,'羊肉中有豐富的蛋白質、脂肪、礦物質、及維生素，容易消化，吃了可以增加熱量、促進血液循環，有禦寒暖身的作用，是冬季的最佳補品。另外，所含的維生素B1、維生素B2、維生素E、鐵質，可以預防貧血、改善手腳冰冷。羊骨中含有豐富的鈣質，中老年人食用可預防骨質疏鬆。');

-- 購物車

DROP TABLE IF EXISTS `cart`;
CREATE TABLE cart(
	bId int(10) unsigned NOT NULL,
	peopleId VARCHAR(10) NOT NULL,
	gId VARCHAR(10) NOT NULL,
	gName VARCHAR(50),
	quantity INT,
	price int(11),
	goodFullName varchar(50),
	PRIMARY KEY (bId)
);
INSERT INTO `cart` (`bId`, `peopleId`,`gId`, `gName`, `quantity`, `price`, `goodFullName`) VALUES
	(1, 'cus4','f1', 'apple', 2, 67, 'fruit'),
	(2, 'cus4','v2', 'bok choy', 5, 49, 'vegetable'),
	(3, 'cus4','g4', 'soy beans', 1, 44, 'grain');

-- 圖片庫

DROP TABLE IF EXISTS `imageList`;
CREATE TABLE imageList (
	name varchar(30) NOT NULL,
	dir varchar(50) NOT NULL,
	PRIMARY KEY(name)
);
INSERT INTO `imageList` (`name`,`dir`) VALUES
('apple', 'list/apple.jpg'),
('banana', 'list/banana.jpg'),
('guava', 'list/guava.jpg'),
('cabbaage', 'list/cabbaage.jpg'),
('bok choy', 'list/bok choy.jpg'),
('carrot', 'list/carrot.jpg'),
('cauliflower', 'list/cauliflower.jpg'),
('prawn', 'list/prawn.jpg'),
('shark', 'list/shark.jpg'),
('crab', 'list/crab.jpg'),
('dumpling', 'list/dumpling.jpg'),
('pork', 'list/pork.jpg'),
('beef', 'list/beef.jpg'),
('mutton', 'list/mutton.jpg'),
('rice', 'list/rice.jpg'),
('cashew', 'list/cashew.jpg'),
('adzuki bean', 'list/adzuki bean.jpg'),
('soy beans', 'list/soy beans.jpg');

-- 進貨單

DROP TABLE IF EXISTS `purchaseOrder`;
CREATE TABLE purchaseOrder(
	id int(10) unsigned NOT NULL,
	pId VARCHAR(10) NOT NULL,
	eId VARCHAR(10) NOT NULL,
	sId VARCHAR(10) NOT NULL,
	pDate DATETIME,
	PRIMARY KEY(pId),
	FOREIGN KEY (eId) REFERENCES employee(eId) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (sId) REFERENCES supplier(sId) ON DELETE CASCADE ON UPDATE CASCADE
);
INSERT INTO `purchaseOrder` (`id`, `pId`,`eId`, `sId`, `pDate`) VALUES
(1, 'pOrder1', 'emp1', 'sup5', '2017-11-22'),
(2, 'pOrder2', 'emp3', 'sup2', '2017-12-14'),
(3, 'pOrder3', 'emp5', 'sup3', '2018-01-04'),
(4, 'pOrder4', 'emp2', 'sup4', '2018-02-21'),
(5, 'pOrder5', 'emp1', 'sup1', '2018-03-19'),
(6, 'pOrder6', 'emp4', 'sup5', '2018-04-11'),
(7, 'pOrder7', 'emp2', 'sup4', '2018-05-06'),
(8, 'pOrder8', 'emp3', 'sup1', '2018-05-24'),
(9, 'pOrder9', 'emp4', 'sup2', '2018-06-03'),
(10, 'pOrder10', 'emp1', 'sup3', '2018-06-16');

-- 進貨商品

DROP TABLE IF EXISTS `purchaseProduct`;
CREATE TABLE purchaseProduct(
	id int(10) unsigned NOT NULL,
	pId VARCHAR(10) NOT NULL,
	gId VARCHAR(10) NOT NULL,
	costPrice INT,
	purchaseQuantity INT,
	PRIMARY KEY (pId,gId),
	FOREIGN KEY (pId) REFERENCES purchaseOrder(pId) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (gId) REFERENCES stock(gId) ON DELETE CASCADE ON UPDATE CASCADE
);
INSERT INTO `purchaseProduct` (`id`,`pId`, `gId`, `costPrice`, `purchaseQuantity`) VALUES
(1,'pOrder1', 'g1', 150, 6),
(2,'pOrder1', 'g2', 199, 5),
(3,'pOrder1', 'g3', 112, 8),
(4,'pOrder1', 'g4', 236, 11),
(5,'pOrder2', 'f1', 80, 15),
(6,'pOrder3', 'v1', 164, 6),
(7,'pOrder3', 'v3', 688, 9),
(8,'pOrder3', 'v4', 183, 13),
(9,'pOrder4', 's1', 253, 7),
(10,'pOrder4', 's2', 234, 15),
(11,'pOrder5', 'm1', 562, 5),
(12,'pOrder5', 'm2', 357, 7),
(13,'pOrder5', 'm3', 765, 4),
(14,'pOrder6', 'g1', 264, 6),
(15,'pOrder6', 'g2', 346, 9),
(16,'pOrder6', 'g3', 135, 9),
(17,'pOrder6', 'g4', 346, 14),
(18,'pOrder7', 's1', 293, 10),
(19,'pOrder7', 's2', 193, 6),
(20,'pOrder8', 'm1', 469, 11),
(21,'pOrder8', 'm2', 346, 6),
(22,'pOrder8', 'm3', 623, 9),
(23,'pOrder9', 'f1', 113, 5),
(24,'pOrder9', 'f2', 222, 13),
(25,'pOrder9', 'f3', 692, 8),
(26,'pOrder10', 'v1', 167, 5),
(27,'pOrder10', 'v2', 130, 6),
(28,'pOrder10', 'v3', 730, 8),
(29,'pOrder10', 'v4', 194, 4);

-- 進貨

DROP TABLE IF EXISTS `purchase`;
CREATE TABLE purchase(
	id int(10) unsigned NOT NULL,
	pId VARCHAR(10) NOT NULL,
	gId VARCHAR(10) NOT NULL,
	transactionTime DATETIME,
	PRIMARY KEY(pId,gId),
	FOREIGN KEY (pId,gId) REFERENCES purchaseProduct(pId,gId) ON DELETE CASCADE ON UPDATE CASCADE
);
INSERT INTO `purchase` (`id`,`pId`, `gId`, `transactionTime`) VALUES
(1,'pOrder1', 'g1', '2017-11-29'),
(2,'pOrder1', 'g2', '2017-11-29'),
(3,'pOrder1', 'g3', '2017-11-29'),
(4,'pOrder1', 'g4', '2017-11-29'),
(5,'pOrder2', 'f1', '2017-12-22'),
(6,'pOrder3', 'v1', '2018-01-11'),
(7,'pOrder3', 'v3', '2018-01-11'),
(8,'pOrder3', 'v4', '2018-01-11'),
(9,'pOrder4', 's1', '2018-02-29'),
(10,'pOrder4', 's2', '2018-02-29'),
(11,'pOrder5', 'm1', '2018-03-26'),
(12,'pOrder5', 'm2', '2018-03-26'),
(13,'pOrder5', 'm3', '2018-03-26'),
(14,'pOrder6', 'g1', '2018-04-17'),
(15,'pOrder6', 'g2', '2018-04-17'),
(16,'pOrder6', 'g3', '2018-04-17'),
(17,'pOrder6', 'g4', '2018-04-17'),
(18,'pOrder7', 's1', '2008-05-13'),
(19,'pOrder7', 's2', '2008-05-13'),
(20,'pOrder8', 'm1', '2018-05-29'),
(21,'pOrder8', 'm2', '2018-05-29'),
(22,'pOrder8', 'm3', '2018-05-29'),
(23,'pOrder9', 'f1', '2018-06-11'),
(24,'pOrder9', 'f2', '2018-06-11'),
(25,'pOrder9', 'f3', '2018-06-11'),
(26,'pOrder10', 'v1', NOW()),
(27,'pOrder10', 'v2', NOW()),
(28,'pOrder10', 'v3', NOW()),
(29,'pOrder10', 'v4', NOW());

-- 退貨單

DROP TABLE IF EXISTS `returnOrder`;
CREATE TABLE returnOrder (
	id int(10) unsigned NOT NULL,
	rId VARCHAR(10) NOT NULL,
	eId VARCHAR(10) NOT NULL,
	sId VARCHAR(10) NOT NULL,
	rDate DATETIME,
	PRIMARY KEY (rId),
	FOREIGN KEY (eId) REFERENCES employee(eId) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (sId) REFERENCES supplier(sId) ON DELETE CASCADE ON UPDATE CASCADE
);
INSERT INTO `returnOrder` (`id`, `rId`,`eId`, `sId`, `rDate`) VALUES
(1, 'pOrder1', 'emp1', 'sup5', '2017-12-03'),
(2, 'pOrder3', 'emp1', 'sup3', '2018-02-13'),
(3, 'pOrder6', 'emp3', 'sup5', '2018-05-02'),
(4, 'pOrder7', 'emp2', 'sup4', '2018-05-27'),
(5, 'pOrder9', 'emp5', 'sup2', '2018-06-15');

-- 退貨商品

DROP TABLE IF EXISTS `returnProduct`;
CREATE TABLE returnProduct(
	id int(10) unsigned NOT NULL,
	rId VARCHAR(10) NOT NULL,
	gId VARCHAR(10) NOT NULL,
	costPrice INT,
	returnQuantity INT,
	PRIMARY KEY(rId,gId),
	FOREIGN KEY (rId) REFERENCES returnOrder(rId) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (gId) REFERENCES stock(gId) ON DELETE CASCADE ON UPDATE CASCADE
);
INSERT INTO `returnProduct` (`id`,`rId`, `gId`, `costPrice`, `returnQuantity`) VALUES
(1, 'pOrder1', 'g1', 277, 15),
(2, 'pOrder1', 'g3', 90, 3),
(3, 'pOrder3', 'v3', 557, 19),
(4, 'pOrder6', 'g1', 296, 12),
(5, 'pOrder6', 'g3', 122, 2),
(6, 'pOrder6', 'g4', 295, 13),
(7, 'pOrder7', 's2', 134, 9),
(8, 'pOrder9', 'f2', 195, 13),
(9, 'pOrder9', 'f3', 268, 9);

-- 退貨

DROP TABLE IF EXISTS `returnzzz`;
CREATE TABLE returnzzz(
	id int(10) unsigned NOT NULL,
	rId VARCHAR(10) NOT NULL,
	gId VARCHAR(10) NOT NULL,
	rDate DATETIME,
	PRIMARY KEY (rId,gId),
	FOREIGN KEY (rId,gId) REFERENCES returnProduct(rId,gId) ON DELETE CASCADE ON UPDATE CASCADE
);
INSERT INTO `returnzzz` (`id`,`rId`, `gId`,`rDate`) VALUES
(1, 'pOrder1', 'g1', '2017-12-03'),
(2, 'pOrder1', 'g3', '2017-12-03'),
(3, 'pOrder3', 'v3', '2018-02-13'),
(4, 'pOrder6', 'g1', '2018-05-02'),
(5, 'pOrder6', 'g3', '2018-05-02'),
(6, 'pOrder6', 'g4', '2018-05-02'),
(7, 'pOrder7', 's2', '2018-05-27'),
(8, 'pOrder9', 'f2', '2018-06-15'),
(9, 'pOrder9', 'f3', '2018-06-15');

-- 交易明細

DROP TABLE IF EXISTS `transactionDetails`;
CREATE TABLE transactionDetails(
	id int(10) unsigned NOT NULL,
	tId VARCHAR(10) NOT NULL,
	cId VARCHAR(10) NOT NULL,
	eId VARCHAR(10) NOT NULL,
	PRIMARY KEY (tId),
	FOREIGN KEY (cId) REFERENCES customer(cId) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (eId) REFERENCES employee(eId) ON DELETE CASCADE ON UPDATE CASCADE
);
INSERT INTO `transactionDetails` (`id`, `tId` ,`cId`, `eId`) VALUES
(1, 'tran1' ,'cus2' , 'emp3'),
(2, 'tran2' ,'cus5' , 'emp2'),
(3, 'tran3' ,'cus1' , 'emp3'),
(4, 'tran4' ,'cus3' , 'emp2'),
(5, 'tran5' ,'cus4' , 'emp5'),
(6, 'tran6' ,'cus3' , 'emp5'),
(7, 'tran7' ,'cus4' , 'emp1'),
(8, 'tran8' ,'cus5' , 'emp2'),
(9, 'tran9' ,'cus2' , 'emp4'),
(10, 'tran10' ,'cus1' , 'emp3'),
(11, 'tran11' ,'cus3' , 'emp1'),
(12, 'tran12' ,'cus4' , 'emp3');

-- 販賣

DROP TABLE IF EXISTS `trade`;
CREATE TABLE trade(
    id int(10) unsigned NOT NULL,
	tId VARCHAR(10) NOT NULL,
	gId VARCHAR(10) NOT NULL,
	quantity int(11),
	tradeTime DATETIME,
	PRIMARY KEY(tId,gId),
	FOREIGN KEY (tId) REFERENCES transactionDetails(tId) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (gId) REFERENCES stock(gId) ON DELETE CASCADE ON UPDATE CASCADE
);
INSERT INTO `trade` (`id`,`tId`, `gId`, `quantity`, `tradeTime`) VALUES
(1, 'tran1', 's3', 14, '2017-12-17'),
(2, 'tran1', 'f2', 16, '2017-12-17'),
(3, 'tran1', 'v2', 21, '2017-12-17'),
(4, 'tran2', 's2', 13, '2018-01-19'),
(5, 'tran2', 'f2', 18, '2018-01-19'),
(6, 'tran3', 'm3', 14, '2018-01-21'),
(7, 'tran4', 'l1', 16, '2018-02-01'),
(8, 'tran4', 'm1', 19, '2018-02-01'),
(9, 'tran4', 's3', 14, '2018-02-01'),
(10, 'tran5', 'g2', 13, '2018-03-12'),
(11, 'tran5', 'm1', 11, '2018-03-12'),
(12, 'tran6', 'g1', 13, '2018-03-19'),
(13, 'tran6', 's1', 15, '2018-03-19'),
(14, 'tran6', 'f3', 17, '2018-03-19'),
(15, 'tran6', 'm3', 19, '2018-03-19'),
(16, 'tran6', 'v4', 16, '2018-03-19'),
(17, 'tran7', 'v3', 14, '2018-04-13'),
(18, 'tran8', 'f2', 15, '2018-04-29'),
(19, 'tran8', 'g1', 13, '2018-04-29'),
(20, 'tran8', 's1', 11, '2018-04-29'),
(21, 'tran8', 'v2', 12, '2018-04-29'),
(22, 'tran9', 'g4', 16, '2018-05-11'),
(23, 'tran10', 'g3', 18, '2018-05-23'),
(24, 'tran10', 'm2', 14, '2018-05-23'),
(25, 'tran10', 's1', 13, '2018-05-23'),
(26, 'tran11', 'm3', 12, '2018-06-03'),
(27, 'tran11', 'g4', 14, '2018-06-03'),
(28, 'tran11', 's2', 16, '2018-06-03'),
(29, 'tran12', 'f3', 4, NOW()),
(30, 'tran12', 'm3', 3, NOW()),
(31, 'tran12', 'v4', 1, NOW()),
(32, 'tran12', 's2', 3, NOW()),
(33, 'tran12', 'g2', 2, NOW());

-- 信箱

DROP TABLE IF EXISTS `contact`;
CREATE TABLE  contact (
  id int(10) unsigned NOT NULL,
  fullname varchar(100) DEFAULT NULL,
  phoneno int(10) DEFAULT NULL,
  email varchar(100),
  cdate date DEFAULT NULL,
  approval varchar(12) DEFAULT NULL,
  PRIMARY KEY(id)
);

INSERT INTO `contact` (`id`, `fullname`, `phoneno`, `email`, `cdate`, `approval`) VALUES
(1, 'Howard', 0912345678, 'howard8701301@gmail.com', '2018-12-03', 'Allowed'),
(2, 'Brian', 0963258415, 'brian991334@gmail.com', '2018-12-03', 'Allowed'),
(3, 'Hank', 0908125489, 'hankhank417@gmail.com', '2018-12-03', 'Allowed'),
(4, 'EJ', 0984515451, 'q00480209yijie@gmail.com', '2018-12-03', 'Allowed'),
(5, 'vincent', 0915632845, 'repk1124@g-mail.nsysu.edu.tw', '2018-12-03', 'Allowed'),
(6, 'sae', 0984265731, 'B054011045@student.nsysu.edu.tw', '2018-12-03', 'Allowed'),
(7, '邱兆民', 098632541, 'cmchiu@mis.nsysu.edu.tw', '2018-12-03', 'Allowed');
ALTER TABLE `contact`
MODIFY `id` int(10) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=31;