#pragma once

struct record
{//日志记录结构体
	int			id;				//记录编号
	int			reason;			//事件
	int			item_id;		//商品编号
	int			count;			//交易数量
	double		price;			//单价
	double		money;			//金额
	int			user_id;		//操作者
	int			year;			//年份
	int			month;			//月份
	int			day;			//日期
	int			hour;			//时
	int			min;			//分
};

struct deal
{//日志记录链表结构体
	struct record data;
	struct deal* next;
};

void RecordMain(void);
int GetMaxRecordId(struct deal* head);
struct deal* ReadRecord(void);
void ShowAllRecord(struct deal* head);
void PrintReason(struct deal* info);
void WriteRecord(int reason, int user, int item_id, int count, double price, double money);
void SearchRecord(struct deal* head);
void SearchRecordById(struct deal* head);
void SearchRecordByTime(struct deal* head);
void SearchRecordByMoney(struct deal* head);
void SearchRecordByItem(struct deal* head);
void SearchRecordByUser(struct deal* head);
void SearchRecordByClass(struct deal* head);
void ChangeRecord(struct deal* head);
struct deal* FindRecord(struct deal* head, int id);
void SaveRecord(struct deal* head);
struct deal* DeleteRecord(struct deal* head);
void ReleaseRecord(struct deal* head);
void PrintReasonForUser(struct deal* info);