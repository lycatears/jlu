#pragma once

#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#endif 

//日志中事件定义
#define SALE	1//出售
#define STOCK	2//进货
#define SPILT	3//商品拆分
#define RENT	4//房租水电等固定支出
#define REJECT	5//客户退货
#define BACK	6//商店退货
#define GIFT	7//赠品送出

//账户日志定义

//配置信息定义
#define DISABLE 0//禁用
#define ENABLE	1//启用

#define COLOR_ERR "\033[1;31m"                          //错误信息以红色输出
#define COLOR_WARN "\033[1;35m"                         //警告信息以紫色输出
#define COLOR_NOTE "\033[1;36m"                         //提示信息以蓝色输出
#define COLOR_CLEAR "\033[0m"                           //恢复控制台白色字体

struct sysconfig
{//系统配置结构体
	double	asset;			//现有资产
	int		user_count;		//注册客户数量
	int		item_count;		//现有商品数量
	int		backup_status;	//是否开启自动备份
	int		rent;			//房租等固定开支
	int		board_status;	//是否开启意见箱
	int		max_user;		//最大用户编号
	int		max_item;		//最大商品编号
	int		max_list;		//每一页最多显示的记录条数
	char	admin_name[16];	//管理员用户名
	char	admin_pwd[16];	//管理员密码
	double	vip_require[9];	//以下分别为vip0-8级的门槛和折扣
	double	vip_discount[9];
	double	promotion;		//临时开展促销活动的折扣
	int		vip_gift[9];	//各会员等级收到的赠品
	double	gift_need;		//每消费多少元能够领取赠品
};

