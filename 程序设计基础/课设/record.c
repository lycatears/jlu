#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include "public.h"
#include "defines.h"
#include "sever_time.h"
#include "record.h"

#pragma warning(disable:6031)
#pragma warning(disable:4996)

extern struct sysconfig sys;


void RecordMain(void)
{
	//负责调用其他记录操作的函数
	//输入：无
	//输出：无
	fflush(stdin);
	system("cls");

	int choice = 0;

	while (1)
	{
		PrintLine(30, '-');
		printf("\t交易记录管理\n");
		PrintLine(30, '-');
		printf("0.退出\n");
		printf("1.查看所有记录\n");
		printf("2.按条件查找记录\n");
		//printf("3.查找时间段内记录\n");
		//printf("4.按照金额查找记录\n");
		printf("3.修改记录\n");
		printf("4.删除记录\n");
		printf("请选择功能：");
		InputIntWithLimit(&choice, 4, 0);

		struct deal* head = ReadRecord();
		switch (choice)
		{
		case 0:
			return;
		case 1:
			ShowAllRecord(head);
			break;
		case 2:
			SearchRecord(head);
			break;
		case 3:
			ChangeRecord(head);
			break;
		case 4:
			DeleteRecord(head);
			break;
		}
		fflush(stdin);
		system("cls");
	}

	return;
}

void WriteRecord(int reason, int user, int item_id, int count, double price, double money)
{
	//将一条新的记录写入文件record.dat
	//输入：记录中与交易有关的信息，时间信息由系统自动生成
	//输出：无
	FILE* plist = fopen("record.dat", "ab");
	struct deal* head = ReadRecord();
	struct deal* p = head;
	struct tm* currentTime = GetNormalTime(GetOriginalTime());
	if (plist == NULL)
	{
		plist = fopen("record.dat", "wb");
	}
	struct record temp = { 0 };
	temp.id = GetMaxRecordId(head) + 1;
	temp.count = count;
	temp.day = currentTime->tm_mday;
	temp.hour = currentTime->tm_hour;
	temp.item_id = item_id;
	temp.user_id = user;
	temp.min = currentTime->tm_min;
	temp.month = currentTime->tm_mon;
	temp.year = currentTime->tm_year;
	temp.reason = reason;
	temp.price = price;
	temp.money = money;
	//while (p->next != NULL)
	//{
	//	p = p->next;
	//}
	//p->next = (struct deal*)malloc(sizeof(struct deal*));
	//if (p->next == NULL)
	//{
	//	printf("内存不足！\n");
	//	return;
	//}
	//p = p->next;
	//p->data = temp;
	//p->next = NULL;
	//SaveConfig();
	fwrite(&temp, sizeof(temp), 1, plist);
	fclose(plist);
	ReleaseRecord(head);
	return;
}

int GetMaxRecordId(struct deal* head)
{
	//获取操作记录中数据数量
	//输入：链表头指针
	//输出：数据个数
	int count = 0;
	struct deal* p = head;
	if (head == NULL)
	{
		return 0;
	}

	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}

struct deal* ReadRecord(void)
{
	//读取操作记录到链表中
	//输入：无
	//输出：链表头指针
	FILE* plist = fopen("record.dat", "rb");
	if (plist == NULL)
	{//若文件不存在，则新建
		plist = fopen("record.dat", "wb+");
	}

	struct record temp;
	struct deal* head = (struct deal*)malloc(sizeof(struct deal)), * p = head;
	p = head;
	size_t read_count = 0;

	if (p == NULL)
	{
		printf("内存不足！\n");
		fclose(plist);
		return head;
	}
	read_count = fread(&temp, 1, sizeof(struct record), plist);
	if (read_count < sizeof(struct record))
	{
		head = NULL;
	}
	p->data = temp;
	p->next = (struct deal*)malloc(sizeof(struct deal));
	if (p->next == NULL)
	{
		printf("内存不足！\n");
		fclose(plist);
		return head;
	}
	if (p == NULL)
	{
		printf("内存不足！\n");
		fclose(plist);
		return NULL;
	}
	while (read_count)
	{
		read_count = fread(&temp, sizeof(struct record), 1, plist);
		p->next = (struct deal*)malloc(sizeof(struct deal));
		if (p == NULL || p->next == NULL)
		{
			printf("内存不足！\n");
			return head;
		}
		p->next->data = temp;
		if (read_count <= 0)
		{
			p->next = NULL;
			break;
		}

		if (feof(plist) == 1 /*|| temp.id < 0 || temp.item_id < 0*/)
		{
			p->next = NULL;
			break;
		}
		p = p->next;
		p->next = NULL;
		fflush(plist);
	}

	fclose(plist);
	return head;
}

void ShowAllRecord(struct deal* head)
{
	//显示所有记录
	//输入：记录链表首节点
	//输出：无
	struct deal* p = head;
	int count = 0;
	if (head == NULL)
	{
		printf("日志为空！\n");
		return;
	}
	PrintLine(100, '=');
	printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
	PrintLine(100, '=');
	while (p != NULL)
	{
		PrintReason(p);
		count++;
		p = p->next;
		if (sys.max_list == 0)
		{
			sys.max_list = 100;
			SaveConfig();
		}
		if (count % sys.max_list == 0)
		{
			system("pause");
		}
	}
	printf("共找到%d条记录\n", count);
	system("pause");
	return;
}

void PrintReason(struct deal* info) 
{
	//打印单条操作记录
	//输入：记录链表首节点
	//输出：无
	printf("%6d  ", info->data.id);
	switch (info->data.reason)
	{
	case SALE:
		printf("商品销售");
		break;
	case STOCK:
		printf("商品进货");
		break;
	case SPILT:
		printf("商品拆分");
		break;
	case RENT:
		printf("工资房租");
		break;
	case REJECT:
		printf("客户退货");
		break;
	case BACK:
		printf("商家退货");
		break;
	case GIFT:
		printf("赠品送出");
		break;
	}
	printf("%6d%6d%10.2lf%14.2lf%6d  %d-%d-%d %02d:%02d\n",
		info->data.item_id,
		info->data.count,
		info->data.price,
		info->data.money,
		info->data.user_id,
		info->data.year + 1900,
		info->data.month + 1,
		info->data.day,
		info->data.hour,
		info->data.min);
	putchar('\n');
	return;
}

void SearchRecord(struct deal* head)
{
	//查找记录的主函数
	//输入：记录链表头指针
	//输出：无
	struct deal* p = head;
	int target = 0;
	if (head == NULL)
	{
		printf("无可用信息！\n");
		return;
	}
	printf("请选择搜索条件:\n");
	printf("1.按照编号查询\n");
	printf("2.按照时间查询\n");
	printf("3.按照金额查询\n");
	printf("4.按照货号查询\n");
	printf("5.按照用户查询\n");
	printf("6.按照类型查询\n");
	printf("0.返回\n请选择：");
	while (1)
	{
		SafeNumberInput(&target);
		if (target <= 6 && target >= 0)
		{
			break;
		}
		else
		{
			printf("非法输入，请重试！\n");
		}
	}
	switch (target)
	{
	case 0:
		return;
	case 1:
		SearchRecordById(head);
		return;
	case 2:
		SearchRecordByTime(head);
		return;
	case 3:
		SearchRecordByMoney(head);
		return;
	case 4:
		SearchRecordByItem(head);
		return;
	case 5:
		SearchRecordByUser(head);
		return;
	case 6:
		SearchRecordByClass(head);
		return;
	}

	return;
}

void SearchRecordById(struct deal* head)
{
	//根据记录编号查询记录
	//输入：记录链表头指针
	//输出：无
	int id = 0;
	struct deal* p = head;
	printf("请输入要查找的记录编号：");
	SafeNumberInput(&id);
	PrintLine(100, '=');
	printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
	PrintLine(100, '=');
	while (p != NULL)
	{
		if (p->data.id == id)
		{
			PrintReason(p);
			printf("已找到编号为%d的记录\n",id);
			system("pause");
			return;
		}
		p = p->next;
		if (p == NULL)
		{
			printf("记录不存在！\n");
			system("pause");
			break;
		}
	}
	return;
}

void SearchRecordByTime(struct deal* head)
{
	//根据交易时间查询记录
	//输入：记录链表头指针
	//输出：无
	struct tm* t = GetNormalTime(GetOriginalTime());
	int currentday = t->tm_year * 365 + (t->tm_mon + 1) * 30 + t->tm_mday;
	int pday = 0;
	struct deal* p = head;
	int choice = 0, maxyear = 0, maxmonth = 0, maxday = 0;
	int minyear = 0, minmonth = 0, minday = 0, count = 0;
	printf("1-查看近一个月内的记录\n2-查看一周内的记录\n3-按照日期精确查找\n请选择：");
	while (1)
	{
		SafeNumberInput(&choice);
		if (choice <= 3 && choice >= 1)
		{
			break;
		}
		else
		{
			printf("非法输入，请重试！\n");
		}
	}


	if (choice == 1)
	{//一个月内的查找
		PrintLine(100, '=');
		printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
		PrintLine(100, '=');
		while (p != NULL)
		{
			pday = p->data.year * 365 + p->data.month * 30 + p->data.day + 30;
			if ((pday) >= (currentday - 30))
			{
				count++;
				PrintReason(p);
			}
			p = p->next;
		}
		printf("找到%d条记录\n",count);
		system("pause");
		return;
	}

	if (choice == 2)
	{//一周内的查找
		PrintLine(100, '=');
		printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
		PrintLine(100, '=');
		while (p != NULL)
		{
			pday = p->data.year * 365 + p->data.month * 30 + p->data.day + 30;
			if ((pday) >= (currentday - 7))
			{
				count++;
				PrintReason(p);
			}
			p = p->next;
		}
		printf("找到%d条记录\n", count);
		system("pause");
		return;
	}

	if (choice == 3)
	{//精确查找
		int pmax = 0, pmin = 0;
		printf("请输入最远时间的年份：");
		InputIntWithLimit(&minyear, 9999, 1900);
		printf("请输入最远时间的月份：");
		InputIntWithLimit(&minmonth, 12, 1);
		printf("请输入最远时间的日期：");
		if (minmonth == 2 && (minyear % 100 != 0 && minyear % 4 == 0 || minyear % 400 == 0))
		{
			InputIntWithLimit(&minday, 29, 1);
		}
		if (minmonth == 2 && (minyear % 4 != 0 || minyear % 100 == 0 && minyear % 400 != 0))
		{
			InputIntWithLimit(&minday, 28, 1);
		}
		if (minmonth == 4 || minmonth == 6 || minmonth == 9 || minmonth == 11)
		{
			InputIntWithLimit(&minday, 30, 1);
		}
		if (minmonth == 1 || minmonth == 3 || minmonth == 5 || minmonth == 7 || minmonth == 8 || minmonth == 10 || minmonth == 12)
		{
			InputIntWithLimit(&minday, 31, 1);
		}
		printf("请输入最近时间的年份：");
		InputIntWithLimit(&maxyear, 9999, 1900);
		printf("请输入最近时间的月份：");
		InputIntWithLimit(&maxmonth, 12, 1);
		printf("请输入最近时间的日期：");
		if (maxmonth == 2 && (maxyear % 100 != 0 && maxyear % 4 == 0 || maxyear % 400 == 0))
		{
			InputIntWithLimit(&maxday, 29, 1);
		}
		if (maxmonth == 2 && (maxyear % 4 != 0 || maxyear % 100 == 0 && maxyear % 400 != 0))
		{
			InputIntWithLimit(&maxday, 28, 1);
		}
		if (maxmonth == 4 || maxmonth == 6 || maxmonth == 9 || maxmonth == 11)
		{
			InputIntWithLimit(&maxday, 30, 1);
		}
		if (maxmonth == 1 || maxmonth == 3 || maxmonth == 5 || maxmonth == 7 || maxmonth == 8 || maxmonth == 10 || maxmonth == 12)
		{
			InputIntWithLimit(&maxday, 31, 1);
		}
		pmin = 365 * (minyear - 1900) + 30 * minmonth + minday;
		pmax = 365 * (maxyear - 1900) + 30 * maxmonth + maxday;

		PrintLine(100, '=');
		printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
		PrintLine(100, '=');
		while (p != NULL)
		{
			pday = p->data.year * 365 + p->data.month * 30 + p->data.day + 30;
			if (pday >= pmin && pmax >= pday)
			{
				count++;
				PrintReason(p);
			}
			p = p->next;
		}
		printf("找到%d条记录\n", count);
		system("pause");
		return;
	}
}

void SearchRecordByMoney(struct deal* head)
{
	//根据交易额大小查询记录
	//输入：记录链表头指针
	//输出：无
	double max_money = 0, min_money = 0;
	int count = 0;
	struct deal* p = head;
	if (p == NULL)
	{
		printf("记录为空！\n");
		return;
	}
	while (1)
	{
		printf("请输入最小金额：");
		SafeDoubleInput(&min_money);
		printf("请输入最大金额：");
		SafeDoubleInput(&max_money);
		if (min_money >= 0 && max_money >= 0 && min_money <= max_money)
		{
			break;
		}
		else
		{
			printf("非法输入，请重试！");
		}
	}
	PrintLine(100, '=');
	printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
	PrintLine(100, '=');
	while (p != NULL)
	{
		if (fabs(p->data.money) >= min_money && fabs(p->data.money) <= max_money)
		{
			PrintReason(p);
			count++;
		}
		p = p->next;
	}
	printf("找到%d条记录\n",count);
	system("pause");
	return;
}

void SearchRecordByItem(struct deal* head)
{
	//根据商品编号查询记录
	//输入：记录链表头指针
	//输出：无
	int count = 0;
	int target_id = 0;
	struct deal* p = head;
	if (head == NULL)
	{
		printf("记录为空！\n");
		return;
	}
	printf("请输入要查找的商品货号：");
	SafeNumberInput(&target_id);
	PrintLine(100, '=');
	printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
	PrintLine(100, '=');
	while (p != NULL)
	{
		if (p->data.item_id == target_id)
		{
			PrintReason(p);
			count++;
		}
		p = p->next;
	}
	printf("找到%d条记录\n",count);
	system("pause");
	return;
}

void SearchRecordByUser(struct deal* head)
{
	//根据用户编号查询记录
	//输入：记录链表头指针
	//输出：无
	int count = 0, target_user = 0;
	struct deal* p = head;
	if (head == NULL)
	{
		printf("记录为空！\n");
		return;
	}
	printf("请输入您要查找的用户编号：（输入0为管理员）");
	InputIntWithLimit(&target_user, sys.max_user, 0);
	PrintLine(100, '=');
	printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
	PrintLine(100, '=');
	while (p != NULL)
	{
		if (p->data.user_id == target_user)
		{
			PrintReason(p);
			count++;
		}
		p = p->next;
	}
	printf("找到%d条记录\n",count);
	system("pause");
	return;
}

void SearchRecordByClass(struct deal* head)
{
	//根据记录类别查找记录
	//输入：记录链表头指针
	//输出：无
	int count = 0, target_class = 0;
	struct deal* p = head;
	if (head == NULL)
	{
		printf("记录为空！\n");
		return;
	}
	printf("请输入要查找的记录类型：\n1-商品出售 2-商品进货 3-商品拆分 4-房租支出\n5-客户退货 6-商店退货 7-赠品送出");
	InputIntWithLimit(&target_class, 7, 1);
	PrintLine(100, '=');
	printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
	PrintLine(100, '=');
	while (p != NULL)
	{
		if (p->data.reason == target_class)
		{
			PrintReason(p);
			count++;
		}
		p = p->next;
	}
	printf("找到%d条记录\n",count);
	system("pause");
	return;
}

void ChangeRecord(struct deal* head)
{
	//修改记录内容
	//输入：记录链表的头指针
	//输出：无
	int target_id = 0, choice = 1;
	double temp = 0;//如果需要修改浮点数，作为临时变量
	struct deal* p = NULL;
	if (head == NULL)
	{
		printf("记录为空！");
		return;
	}
	printf("请输入要修改的操作记录编号：");
	SafeNumberInput(&target_id);
	p = FindRecord(head, target_id);
	if (p == NULL)
	{
		printf("该记录不存在！\n");
		system("pause");
		return;
	}
	printf("该编号的记录如下：\n");
	PrintLine(100, '=');
	printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
	PrintLine(100, '=');
	PrintReason(p);
	while (choice)
	{
		printf("请选择要修改的内容：\n");
		printf("1-类型 2-货号 3-数量 4-单价 5-金额 6-用户 7-交易时间 0-退出\n");
		SafeNumberInput(&choice);
		if (choice == 0)
		{
			return;
		}
		switch (choice)
		{
		case 1:
			printf("请选择修改后的类型：\n1-商品出售 2-商品进货 3-工资支出 4-房租支出\n5-客户退货 6-商店退货 7-赠品送出");
			p->data.reason = InputIntWithLimit(&choice, 7, 1);
			break;
		case 2:
			printf("请输入修改后的货号：\n");
			p->data.item_id = SafeNumberInput(&choice);
			break;
		case 3:
			printf("请输入修改后的数量：\n");
			p->data.count = SafeNumberInput(&choice);
			break;
		case 4:
			printf("请输入修改后的单价：\n");
			p->data.price = SafeDoubleInput(&temp);
			break;
		case 5:
			printf("请输入修改后的金额：\n");
			p->data.money = SafeDoubleInput(&temp);
			break;
		case 6:
			printf("请输入修改后的用户ID：\n");
			p->data.user_id = SafeNumberInput(&choice);
			break;
		case 7:
			while (1)
			{
				printf("请输入修改后的年份：\n");
				SafeNumberInput(&choice);
				if (choice > 9999 || choice < 1900)
				{
					printf("非法输入，请重试！\n");
				}
				break;
			}
			p->data.year = choice - 1900;
			while (1)
			{
				printf("请输入修改后的月份：\n");
				p->data.month = SafeNumberInput(&choice) - 1;
				if (choice <= 12 && choice >= 1)
				{
					break;
				}
				printf("非法输入，请重试！\n");
			}
			while (1)
			{
				printf("请输入修改后的日期：\n");
				p->data.day = SafeNumberInput(&choice);
				if (TimeCheck(p->data.year + 1900, p->data.month + 1, p->data.day, 0, 0) == 1)
				{
					break;
				}
				printf("非法输入，请重试！\n");
			}
			while (1)
			{
				printf("请输入修改后的小时：\n");
				p->data.hour = SafeNumberInput(&choice);
				if (choice <= 23 && choice > 0)
				{
					break;
				}
				printf("非法输入，请重试！\n");
			}
			while (1)
			{
				printf("请输入修改后的分钟：\n");
				p->data.min = SafeNumberInput(&choice);
				if (choice >= 0 && choice < 60)
				{
					break;
				}
				printf("非法输入，请重试！\n");
			}
			break;	
		}
		if (TimeCheck(p->data.year + 1900, p->data.month, p->data.day, p->data.hour, p->data.min) == 0)
		{
			printf("时间数据不合法，请重试！\n");
			continue;
		}
		printf("是否继续修改这条记录？输入0以退出，输入其他数字继续。");
		SafeNumberInput(&choice);
	}
	SaveRecord(head);
	return;
}

struct deal* FindRecord(struct deal* head, int id)
{
	//查找记录链表中的指定编号的记录，并返回其指针
	//输入：链表头节点，指定的编号
	//输出：若存在这一编号，返回相应的指针；若不存在，则返回空指针
	struct deal* p = head;
	while (p->data.id != id)
	{
		if (p == NULL)
		{
			return NULL;
		}
		p = p->next;
		if (p == NULL)
		{
			return NULL;
		}
	}
	return p;
}

void SaveRecord(struct deal* head)
{
	//保存所有记录到record.dat文件
	//输入：记录链表头指针
	//输出：无
	FILE* plist = fopen("record.dat", "wb");
	struct deal* p = head;
	if (head == NULL)
	{
		printf("记录为空！\n");
		return;
	}
	while (p != NULL)
	{
		fwrite(&p->data, sizeof(struct record), 1, plist);
		p = p->next;
	}
	fclose(plist);
	return;
}

struct deal* DeleteRecord(struct deal* head)
{
	//删除某条记录
	//输入：记录链表的头节点指针
	//输出：修改后链表的头指针
	struct deal* p = head;
	int target_id = 0;
	if (head == NULL)
	{
		printf("记录为空！\n");
		system("pause");
		return NULL;
	}
	printf("请输入要删除的记录编号：");
	SafeNumberInput(&target_id);
	p = FindRecord(head, target_id);
	if (p == NULL)
	{
		printf("该记录不存在！\n");
		system("pause");
		return head;
	}
	if (p == head)
	{
		struct deal* q = head;
		int new_id = 1;
		p = p->next;
		q = p;
		free(head);
		while (q != NULL)
		{
			q->data.id = new_id;
			q = q->next;
			new_id++;
		}
		SaveRecord(p);
		printf("删除成功！\n");
		system("pause");
		return p;
	}
	struct deal* q = FindRecord(head, target_id - 1);
	int new_id = 1;
	q->next = p->next;
	free(p);
	q = head;
	while (q != NULL)
	{
		q->data.id = new_id;
		q = q->next;
		new_id++;
	}
	SaveRecord(head);
	printf("删除成功！\n");
	system("pause");
	return head;
}

void ReleaseRecord(struct deal* head)
{
	//释放记录信息链表空间
	//输入：链表头指针
	//输出：无
	struct deal* p = NULL, * q = head;
	while (p != NULL)
	{
		p = q;
		q = q->next;
		free(p);
	}
	return;
}

void PrintReasonForUser(struct deal* info)
{
	//打印单条操作记录
	//输入：记录链表首节点
	//输出：无
	printf("%6d  ", info->data.id);
	switch (info->data.reason)
	{
	case SALE:
		printf("商品销售");
		break;
	case STOCK:
		printf("商品进货");
		break;
	case SPILT:
		printf("商品拆分");
		break;
	case RENT:
		printf("缴纳租金");
		break;
	case REJECT:
		printf("客户退货");
		break;
	case BACK:
		printf("商家退货");
		break;
	case GIFT:
		printf("赠品送出");
		break;
	}
	printf("%6d%6d%10.2lf%14.2lf%6d  %d-%d-%d %02d:%02d\n",
		info->data.item_id,
		abs(info->data.count),
		info->data.price,
		fabs(info->data.money),
		info->data.user_id,
		info->data.year + 1900,
		info->data.month + 1,
		info->data.day,
		info->data.hour,
		info->data.min);
	putchar('\n');
	return;
}