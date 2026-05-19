/*
 Navicat Premium Data Transfer

 Source Server         : 1
 Source Server Type    : MySQL
 Source Server Version : 80034
 Source Host           : localhost:3306
 Source Schema         : qq_users

 Target Server Type    : MySQL
 Target Server Version : 80034
 File Encoding         : 65001

 Date: 19/05/2026 01:12:42
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for qq_group_relationship
-- ----------------------------
DROP TABLE IF EXISTS `qq_group_relationship`;
CREATE TABLE `qq_group_relationship`  (
  `id` int UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '编号',
  `group_id` int UNSIGNED NOT NULL COMMENT '群号',
  `qq_id` int UNSIGNED NOT NULL COMMENT '群员QQ号',
  `is_owner` tinyint UNSIGNED NOT NULL DEFAULT 0 COMMENT '是否是群主',
  `is_admin` tinyint UNSIGNED NOT NULL DEFAULT 0 COMMENT '是否是管理员',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 18 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for qq_groups
-- ----------------------------
DROP TABLE IF EXISTS `qq_groups`;
CREATE TABLE `qq_groups`  (
  `group_id` int UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '群号',
  `group_name` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '群名称',
  `group_owner` int UNSIGNED NOT NULL COMMENT '群主',
  `maingroup` int UNSIGNED NOT NULL DEFAULT 0 COMMENT '若是分群，则填写对应主群群号，否则为0',
  PRIMARY KEY (`group_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 11 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for qq_messages
-- ----------------------------
DROP TABLE IF EXISTS `qq_messages`;
CREATE TABLE `qq_messages`  (
  `messageId` int UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '消息编号',
  `sender` int NOT NULL COMMENT '发送者',
  `reciever` int NOT NULL COMMENT '接收者',
  `isgroup` tinyint NOT NULL COMMENT '是否是群聊消息',
  `message` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '信息内容',
  `year` int UNSIGNED NOT NULL DEFAULT 1970,
  `month` int UNSIGNED NOT NULL DEFAULT 1,
  `day` int UNSIGNED NOT NULL DEFAULT 1,
  `hour` int UNSIGNED NOT NULL DEFAULT 0,
  `minute` int UNSIGNED NOT NULL DEFAULT 0,
  `second` int UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`messageId`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1942 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for qq_relationship
-- ----------------------------
DROP TABLE IF EXISTS `qq_relationship`;
CREATE TABLE `qq_relationship`  (
  `id` int UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '编号，主键',
  `friend1` int UNSIGNED NOT NULL,
  `friend2` int NOT NULL,
  `comment` varchar(16) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '好友备注',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 28 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for user_basic_information
-- ----------------------------
DROP TABLE IF EXISTS `user_basic_information`;
CREATE TABLE `user_basic_information`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '模拟qq账号',
  `nickname` varchar(16) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT 'QQ昵称',
  `password` varchar(16) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `linked_wechat` int NOT NULL DEFAULT 0 COMMENT '绑定的微信账号',
  `birth_year` int NOT NULL,
  `birth_month` int NOT NULL,
  `birth_day` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `Iid_qq`(`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 14 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Procedure structure for proc1
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc1`;
delimiter ;;
CREATE PROCEDURE `proc1`(IN in_name varchar(32),OUT count_of_name int)
BEGIN
	select count(distinct nickname) into count_of_name
	from user_basic_information
	where nickname=in_name;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
