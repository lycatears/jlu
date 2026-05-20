/*

userman.c

管理用户信息

*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "defines.h"
#include "userman.h"
#include "good.h"
#include "public.h"
#include "record.h"
#include "sever_time.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)

extern struct sysconfig sys;
extern int currentUser;
extern HANDLE hout;

void AdminMain(void)
{
	//管理员主函数
	//输入：无
	//输出：无
	struct userinfo* head = CreateChain();
	int judge = 1;
	while (judge)
	{
		int m = ManagementMenu();
		switch (m)
		{
		case 0:      //退出系统
			return;
		case 1:
			UserManageMain();
			break;
		case 2:
			ItemMain();
			break;
		case 3:
			RecordMain();
			break;
		case 4:
			Suggest();//查看意见箱
			break;
		case 5:
			VipSystem(head);//VIP系统
			break;
		case 6:
			Promotion();//促销活动
			break;
		case 7:
			ShowStatus();
			break;
		case 8:
			Setting();
			break;
		case 9:
			BackupMain();
			break;
		}
	}
	return;
}
/*
struct userinfo* ReadUserInfo(void)
{
	//读取客户信息到链表
	//输入：无
	//输出：链表头节点指针
	struct userinfo* head = NULL;
	struct customer temp;
	FILE* plist = fopen("customer.dat", "rb");
	int read_byte = 0;

	if (plist == NULL)
	{
		//此处使用备份文件
	}
	
	head = (struct userinfo*)malloc(sizeof(struct userinfo));
	while (1)
	{
		if (read_byte <= 0)
		{
			break;
		}
		else
		{

		}
	}
}
*/
int ManagementMenu(void)
{
	//管理员总菜单
	//输入：无
	//输出：用户的选择
	int choice = 0;
	system("cls");
	PrintLine(30, '-');
	printf("\t管理员功能菜单\n");
	PrintLine(30, '-');
	printf("请选择功能:\n");
	printf("0:退出系统\n");
	printf("1:用户管理\n");
	printf("2:商品管理\n");
	printf("3:查看交易记录\n");
	printf("4:查看意见箱\n");
	printf("5:VIP系统\n");
	printf("6:促销活动\n");
	printf("7:检查运行情况\n");
	printf("8:设置\n");
	printf("9:备份系统\n");
	//用户购买后自动将购买信息存入文本，不需要管理员单独存储

	InputIntWithLimit(&choice, 9, 0);
	return choice;
}

void FindUser(struct userinfo* head)
{
	//寻找指定编号的客户
	//输入：无
	//输出：无
	int res = 0;
	struct userinfo* qp = head, * op = head;
	if (qp == NULL)
	{
		return;
	}
	while (qp != NULL)
	{
		res++;
		qp = qp->next;
	}
	qp = head;
	printf("请输入您想查询的用户编号：\n");
	fflush(stdin);
	int number, nm = 1;
	while (1)
	{
		int r = scanf("%d", &number);
		if (r != 0)
		{
			break;
		}
		printf("非法输入，请重试！\n");
		ClearBuffer();
	}

	PrintLine(60, '=');
	printf("  编号			名称	累计消费	VIP	密码\n");
	PrintLine(60, '=');
	while (1)
	{
		while (qp->data.id != number && qp != NULL)
		{
			if (qp->next == NULL)
			{
				nm = 0;
			}
			op = qp;
			qp = qp->next;
			if (qp == NULL)
			{
				break;
			}
		}
		if (nm == 1)
			break;
		else
		{
			nm = 1;
			qp = head;
			printf("用户不存在，请重新输入：");
			SafeNumberInput(&number);
		}
	}

	printf("%6d ", qp->data.id);
	printf("%-10s ", qp->data.name);
	printf("%-.2lf ", qp->data.cost);
	printf("%4d ", qp->data.vip);
	printf("%s\n", qp->data.password);

	putchar('\n');
	system("pause");
	return;
}

struct userinfo* CreateChain(void)
{
	//创建用户信息链表
	//输入：无
	//输出：链表头指针
	struct userinfo* head = NULL;
	FILE* p = fopen("user.txt", "r");
	int flag = 1;

	while (flag > 0)
	{
		struct userinfo* tmp = NULL;
		struct userinfo* tp = NULL;
		tp = (struct userinfo*)malloc(sizeof(struct userinfo));
		if (tp == NULL)
		{
			printf("内存不足！");
			return NULL;
		}
		int flag = fscanf(p, "%d", &tp->data.id);
		if (flag < 0)
			break;
		fscanf(p, "%20s ", tp->data.name);
		fscanf(p, "%lf", &tp->data.cost);
		fscanf(p, "%d", &tp->data.vip);
		fscanf(p, "%20s ", tp->data.password);
		if (head == NULL)
		{
			if (flag < 0)
			{
				printf("空文件,读写失败\n");
				exit(0);
			}
			head = tp;
			tmp = head;
			tmp->next = NULL;
		}
		else
		{
			tmp = head;
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}
			tmp->next = tp;
			tmp = tp;
			tmp->next = NULL;
		}
	}
	fclose(p);

	return head;//返回用户链表头结点
}

struct userinfo* AddNewUser(struct userinfo* head)//增加新的用户
{
	//增加新的用户
	//输入：用户信息链表头节点
	//输出：头节点
	int res = 0;
	struct userinfo* qp = head;
	while (qp)
	{
		res++;
		qp = qp->next;
	}
	struct userinfo* mp = NULL;
	mp = (struct userinfo*)malloc(sizeof(struct userinfo));
	if (mp == NULL)
	{
		printf("内存不足！");
		return NULL;
	}
	fflush(stdin);
	printf("请输入用户的姓名：\n");
	scanf("%20s", mp->data.name);
	fflush(stdin);
	printf("请输入用户的总计消费金额：\n");
	InputDoubleWithLimit(&mp->data.cost, 2147483647, 0);
	fflush(stdin);
	printf("请输入用户的贵族等级：\n");
	InputIntWithLimit(&mp->data.vip, 8, 0);
	fflush(stdin);
	printf("请输入用户的密码：\a");
	scanf("%20s", mp->data.password);
	mp->data.id = sys.max_user + 1;
	sys.max_user++;
	struct userinfo* tmp = head;
	if (head == NULL)
	{
		head = mp;
		tmp = head;
		tmp->next = NULL;
	}
	else
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = mp;
		tmp = mp;
		tmp->next = NULL;
	}
	printf("添加成功\n");
	sys.user_count++;
	system("pause");

	return head;
}

void WriteToFile(struct userinfo* head)
{
	//将更改完的用户链表信息写入文件
	//输入：用户信息链表头节点
	//输出：无
	FILE* p = fopen("user.txt", "w");
	struct userinfo* mp = head;

	while (mp)
	{
		fprintf(p, "%-5d ", mp->data.id);
		fprintf(p, "%-20s ", mp->data.name);
		fprintf(p, "%lf ", mp->data.cost);
		fprintf(p, "%-5d ", mp->data.vip);
		fprintf(p, "%-20s\n", mp->data.password);
		mp = mp->next;
	}
	fclose(p);

	return;
}

struct userinfo* DeleteUserById(struct userinfo* head)//删除所输入的用户
{
	//删除指定id的用户
	//输入：链表头指针
	//输出：修改后的链表的头指针
	fflush(stdin);
	ClearBuffer();
	if (head == NULL)
	{
		printf("无可用数据，请检查后重试！");
		return NULL;
	}
	struct userinfo* p = head, * q = head;
	int target = 0;
	q = head;

	fflush(stdin);
	printf("请输入您想删除的用户编号：\n");
	while (1)
	{
		if (scanf("%d", &target) != 0)
		{
			break;
		}
		else
		{
			ClearBuffer();
			printf("非法输入，请重试！\n");
		}
	}
	q = head;
	while (p != NULL)
	{
		if (p->data.id == target)
		{
			if (p == head)
			{
				p = p->next;
				if (q != NULL)
				{
					free(q);
				}
				continue;
			}
			else
			{
				struct userinfo* tmp = p;
				q->next = p->next;
				p = p->next;
				free(tmp);
				printf("成功删除了编号为%d的用户。\n", target);
				sys.user_count--;
				SaveConfig();
				system("pause");
				return head;
			}
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	if (p == NULL)
	{
		printf("用户不存在！\n");
	}
	else
	{
		printf("删除成功！\n");
	}
	system("pause");
	return head;

	/*struct userinfo* qp = head, * op = head;
	fflush(stdin);
	printf("请输入您想删除的用户编号：\n");
	int number, nm = 1;
	scanf("%d", &number);
	while (1)
	{
		while (qp->data.id != number && qp != NULL)
		{
			if (qp->next == NULL)
			{
				nm = 0;
			}
			op = qp;
			if (qp->next != NULL)
			{
				qp = qp->next;
			}
		}
		if (nm == 0)
		{
			break;
		}
		else
		{
			nm = 1;
			qp = head;
			printf("用户不存在，请重新输入：");
			scanf("%d", &number);
		}
	}
	op->next = qp->next;
	printf("删除成功！\n");
	return head;*/
}

struct userinfo* ChangeUser(struct userinfo* head)//改变所选用户的信息
{
	//改变指定id用户的信息
	//输入：链表头指针
	//输出：修改后的链表的头指针
	ClearBuffer();
	struct userinfo* mp = head;
	printf("请输入您想更改的用户编号：\n");
	int number, nm = 1;
	fflush(stdin);
	while (1)
	{
		int r = SafeNumberInput(&number);
		if (number > sys.max_user || number <= 0)
		{
			printf("用户不存在！\n");
			system("pause");
		}
		if (r != 0)
		{
			break;
		}
		//else
		//{
		//	ClearBuffer();
		//	printf("非法输入，请重试！\n");
		//}
	}
	while (1)
	{
		if (mp == NULL)
		{
			return NULL;
		}
		while (mp->data.id != number && mp != NULL)
		{
			if (mp->next == NULL)
			{
				nm = 0;
			}
			mp = mp->next;
			if (mp == NULL)
			{
				printf("用户不存在！\n");
				system("pause");
				return head;
			}
		}
		if (nm == 1)
		{
			break;
		}
		else
		{
			nm = 1;
			mp = head;
			printf("用户不存在，请重新输入：");
			fflush(stdin);
			SafeNumberInput(&number);
		}
	}
	int mm, judge = 1;
	while (judge)
	{
		fflush(stdin);
		printf("现有信息：用户编号%d，名称%s，消费金额%.2f，VIP%d，密码%s\n",
			mp->data.id,mp->data.name,mp->data.cost,mp->data.vip,mp->data.password);
		printf("请输入您要更改的属性\n");
		printf(" 1:用户姓名 2:用户总消费金额 3:用户贵族等级 4:用户密码 \n输入其他数字以退出");
		SafeNumberInput(&mm);
		switch (mm)
		{
		case 1:
			printf("请输入新的用户姓名:\n");
			scanf("%20s", mp->data.name);
			break;
		case 2:
			printf("请输入新的用户总消费金额:\n");
			SafeDoubleInput(&mp->data.cost);
			break;
		case 3:
			printf("请输入新的用户贵族等级:\n");
			SafeNumberInput(&mp->data.vip);
			break;
		case 4:
			printf("请输入新的用户密码:\n");
			scanf("%16s", mp->data.password);
			break;
		default:
			return head;
		}
		printf("是否要继续更改信息（是1否0）\n");
		SafeNumberInput(&judge);
	}
	printf("修改信息成功！\n");
	system("pause");
	return head;
}

struct suggestlian* ReadSuggestions(void)//将意见箱文件中的信息存入意见箱链表
{
	//将意见箱文件中的信息存入意见箱链表
	//输入：无
	//输出：意见链表头指针
	struct suggestlian* head2 = NULL;
	FILE* p2 = fopen("suggest.txt", "r");
	int flag2 = 1;
	while (flag2 > 0)
	{
		struct suggestlian* tmp = NULL;
		struct suggestlian* mp = NULL;
		mp = (struct suggestlian*)malloc(sizeof(struct suggest));
		if (mp == NULL)
		{
			return NULL;
		}
		flag2 = fscanf(p2, "%d", &mp->cell.num);
		if (flag2 < 0)
			break;
		fscanf(p2, "%s ", mp->cell.propose);
		if (head2 == NULL)
		{
			if (flag2 < 0)
			{
				printf("空文件,读写失败");
				exit(0);
			}
			head2 = mp;
			tmp = head2;
			tmp->next = NULL;
		}
		else
		{
			tmp = head2;
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}
			tmp->next = mp;
			tmp = mp;
			tmp->next = NULL;
		}
	}
	return head2;
	fclose(p2);
	/*struct suggestlian* head = (struct suggestlian*)malloc(sizeof(struct suggestlian));
	if (head == NULL)
	{
		printf("内存不足！\n");
		return NULL;
	}
	FILE* plist = fopen("suggest.txt", "r");
	struct suggestlian* p = head, * q = head;
	head->next = q;
	
	if (plist == NULL)
	{
		fopen("suggest.txt", "w");
		printf("意见箱为空！\n");
		free(head);
		return NULL;
	}

	while (1)
	{
		int readCount = fscanf(plist, "%d", &p->cell.num);
		if (readCount < 0)
		{
			break;
		}
		fscanf(plist, "%100s", p->cell.propose);
		q->next = p;
		p->next = NULL;
	}

	return head;*/
}

void Suggest(void)//调用这些意见箱函数的“主函数”（在主菜单的意见箱栏只需调用这一个函数）
{
	fflush(stdin);
	struct suggestlian* head2 = ReadSuggestions();
	int m, judge2 = 1;

	while (1)
	{
		system("cls");
		PrintLine(30, '-');
		printf("\t意见箱系统\n");
		PrintLine(30, '-');
		printf("请输入您想选择的功能：\n");
		printf("0:退出意见箱系统\n");
		//printf("1:增加意见\n");
		printf("1:查看所有意见\n");
		printf("2:删除所有意见\n");
		ReleaseSuggestions(head2);
		head2 = ReadSuggestions();
		InputIntWithLimit(&m, 2, 0);
		switch (m)
		{
		case 0:      //退出意见箱系统
			return;
		//case 1:
		//	head2 = AddSuggest(head2);//增加意见
		//	WriteSuggestToFile(head2);
		//	system("pause");
		//	break;
		case 1:
			ShowSuggestions(head2);//查看所有意见
			//judge2=0;
			system("pause");
			break;
		case 2:
			DeleteAllSuggestion();
			system("pause");
			break;
		default:
			printf("您输入的格式不正确，请重新输入：\n");
			SafeNumberInput(&m);
		}
	}
}

struct suggestlian* AddSuggest(struct suggestlian* head2)//增加新的意见
{
	//增加新的意见
	//输入：意见箱链表头指针
	//输出：修改后的链表的头指针
	ClearBuffer();
	struct suggestlian* tp = head2, * mp = head2;
	int res = 1;
	while (tp != NULL && tp->next != NULL)
	{
		res++;
		tp = tp->next;
	}
	int number = res + 1;
	mp = (struct suggestlian*)malloc(sizeof(struct suggestlian));
	if (tp == NULL && mp != NULL)
	{
		tp = mp;
		mp->cell.num = 1;
		printf("请输入您对本店的意见：\n");
		fflush(stdin);
		scanf_s("%s", mp->cell.propose, 100);
		printf("添加成功！\n");
		FILE* plist = fopen("suggest.txt", "w");
		fprintf(plist, "%d %s", mp->cell.num, mp->cell.propose);
		return NULL;
	}
	if (mp == NULL)
	{
		printf("内存不足！");
		return NULL;
	}
	mp->cell.num = number;
	printf("请输入您对本店的意见：\n");
	fflush(stdin);
	scanf_s("%s", mp->cell.propose, 100);
	tp->next = mp;
	mp->next = NULL;
	printf("添加成功！\n");

	return head2;
}

void WriteSuggestToFile(struct suggestlian* head2)//将更改后的意见链表写入文件保存
{
	//将修改后的意见箱链表写入文件
	//输入：意见箱链表头指针
	//输出：无
	FILE* p2 = fopen("suggest.txt", "w");
	struct suggestlian* mp = head2;
	mp = head2;
	while (mp != NULL)
	{
		fprintf(p2, "%-d ", mp->cell.num);
		fprintf(p2, "%-s\n", mp->cell.propose);
		mp = mp->next;
	}
	fclose(p2);
}

void ShowSuggestions(struct suggestlian* head2)//展示所有意见
{
	struct suggestlian* mp = head2;
	if (mp == NULL)
	{
		printf("意见箱为空！\n");
		return;
	}
	while (mp)
	{
		printf("%d ", mp->cell.num);
		printf("%s\n", mp->cell.propose);
		mp = mp->next;
	}
	return;
}

void DeleteAllSuggestion(void)//删除所有意见箱文件内的内容（读完之后不得删嘛）
{
	int choice;
	FILE* p;

	printf("您确定要删除所有用户反馈吗？(是1否0)");
	scanf("%d", &choice);
	if (choice == 1)
	{
		p = fopen("suggest.txt", "w");
		fclose(p);
	}
	return;
}

void VipSystem(struct userinfo* head)//调用vip系统的这些函数（相当于vip系统的“主函数”，主菜单中只需调用这一个函数）
{
	while(1)
	{
		system("cls");
		fflush(stdin);
		PrintLine(30, '-');
		printf("\tVIP管理\n");
		PrintLine(30, '-');
		printf("请输入您想选择的功能：\n");
		printf("0:退出VIP系统\n");
		printf("1:查看当前VIP标准\n");
		printf("2:更改VIP标准\n");
		printf("3:按照VIP查找用户\n");
		printf("4:查看赠品\n");
		printf("5:修改赠品\n");
		int m, judge3 = 1;
		int firstrun = 1;
		InputIntWithLimit(&m, 5, 0);
		switch (m)
		{
		case 0:
			return;
		case 1:
			ShowVip();
			break;
		case 2:
			ChangeVip();
			break;
		case 3:
			SearchUserByVip(head);
			break;
		case 4:
			ShowVipGift();
			break;
		case 5:
			ChangeVipGift();
			break;
		}
	}
	return;
}

void ShowVip(void)
{
	printf("当前VIP设置如下：\n");
	for (int i = 0; i < 9; i++)
	{
		printf("VIP等级%d 折扣%.2lf 最低消费金额%.2f\n\n",
			i, sys.vip_discount[i], sys.vip_require[i]);
	}
	system("pause");
	return;
}

void ChangeVip(void)
{
	int target_vip = 0;
	int choice = 0;
	printf("请输入要修改的VIP等级：");
	InputIntWithLimit(&target_vip, 8, 0);
	printf("当前%d等级设置为：折扣%.2f，最低消费%.2f\n",
		target_vip,sys.vip_discount[target_vip],sys.vip_require[target_vip]);
	printf("输入1改变折扣，输入2改变最低消费金额，其他数字为退出：");
	SafeNumberInput(&choice);
	if (choice == 0)
	{
		return;
	}
	if (choice == 1)
	{
		printf("请输入修改后的折扣：");
		while (1)
		{
			InputDoubleWithLimit(&sys.vip_discount[target_vip], 2147483647, 0.01);
			if (sys.vip_discount[target_vip] > 1)
			{
				printf("打折不能高于原价，请重新输入！");
				continue;
			}
			SaveConfig();
			printf("修改成功！");
			system("pause");
			break;
		}
	}
	if (choice == 2)
	{
		printf("请输入修改后的最低消费：");
		InputDoubleWithLimit(&sys.vip_require[target_vip], 2147483647, 0);
		SaveConfig();
		printf("修改成功！\n");
		system("pause");
	}
	return;
}

void SearchUserByVip(struct userinfo* head)
{
	struct userinfo* p = head;
	int target_vip = 0;
	if (p == NULL)
	{
		printf("无可用信息！\n");
		system("pause");
		return;
	}
	printf("请输入您要查看的VIP等级：");
	InputIntWithLimit(&target_vip, 8, 0);
	PrintLine(60, '=');
	printf("  编号     名称		累计消费	VIP		密码\n");
	PrintLine(60, '=');
	while (p != NULL)
	{
		if (p->data.vip == target_vip)
		{
			printf("%6d", p->data.id);
			printf("%20s", p->data.name);
			printf("%10.2lf", p->data.cost);
			printf("%4d", p->data.vip);
			printf("%16s", p->data.password);
			putchar('\n');
			PrintLine(60, '-');
		}
		p = p->next;
	}
	system("pause");
	return;
}

void Promotion(void)
{
	int choice = 0;
	while (1)
	{
		system("cls");
		PrintLine(30, '-');
		printf("\t促销管理\n");
		PrintLine(30, '-');
		printf("1.显示当前促销优惠\n");
		printf("2.设置当前促销优惠\n");
		printf("3.清除促销活动\n");
		printf("4.改变赠品标准\n");
		printf("0.退出\n");
		printf("请选择：");
		InputIntWithLimit(&choice, 4, 0);
		switch (choice)
		{
		case 0:
			return;
		case 1:
			printf("当前折扣：%.2f\n", sys.promotion);
			break;
		case 2:
			printf("输入您的促销折扣：(0到1之间的小数)");
			double temp = 0;
			while (1)
			{
				SafeDoubleInput(&temp);
				if (temp <= 1 && temp>0)
				{
					sys.promotion = temp;
					break;
				}
				else
				{
					printf(COLOR_ERR"非法输入，请重试！\n"COLOR_CLEAR);
				}
			}
			printf("设置成功！用户的购买价格将为原价的%d%%\n", (int)(sys.promotion * 100));
			break;
		case 3:
			sys.promotion = 1;
			SaveConfig();
			printf("清除成功！\n");
			break;
		case 4:
			printf("输入新的赠品标准：(当前为%.2lf)", sys.gift_need);
			InputDoubleWithLimit(&sys.gift_need, 2147483647, 0.01);
			printf("设置成功！用户每消费%.2f元，将收到一个赠品。\n", sys.gift_need);
			break;
		}
		system("pause");
	}
	SaveConfig();
	return;
}

void UserManageMain(void)
{
	//用户管理菜单
	//输入：无
	//输出：无
	int IsFirstRun = 1;
	struct userinfo* head = CreateChain();
	int judge = 1, select = 0;

	while (1)
	{
		system("cls");
		fflush(stdin);
		if (IsFirstRun == 0)
		{
			ClearBuffer();
		}
		PrintLine(30, '-');
		printf("\t用户管理\n");
		PrintLine(30, '-');
		printf("1:查看所有用户\n");
		printf("2:按照ID查询用户信息\n");
		printf("3:增加新的用户\n");
		printf("4:删除用户\n");
		printf("5:更改用户信息\n");
		printf("6:按照姓名查询用户信息(支持模糊搜索)\n");
		printf("7:查找指定范围消费金额的用户\n");
		printf("0:返回\n");

		SafeNumberInput(&select);
		switch (select)
		{
		case 0:
			return;
		case 1:
			ReadAllUser(head);
			break;
		case 2:
			FindUser(head);
			break;
		case 3:
			head = AddNewUser(head);//增加新的用户
			WriteToFile(head);
			break;
		case 4:
			head = DeleteUserById(head);//删除用户
			WriteToFile(head);
			break;
		case 5:
			head = ChangeUser(head);//更改用户信息
			WriteToFile(head);
			break;
		case 6:
			SearchUserByName(head);
			break;
		case 7:
			SearchForUserCost(head);
			break;
		default:
			ClearBuffer();
		}
	}
	return;
	//switch (select)
	//{
	//case 1:
	//	ReadAllUser(head);
	//	break;
	//case 2:
	//	FindUser(head);
	//	break;
	//case 3:
	//	head = AddNewUser(head);//增加新的用户
	//	WriteToFile(head);
	//	break;
	//case 4:
	//	head = DeleteUserById(head);//删除用户
	//	WriteToFile(head);
	//	break;
	//case 5:
	//	head = ChangeUser(head);//更改用户信息
	//	WriteToFile(head);
	//	break;
	//case 6:
	//	SearchUserByName(head);
	//	break;
	//case 7:
	//	SearchForUserCost(head);
	//	break;
	//}

	return;
}

struct userinfo* ReadAllUser(struct userinfo* head)
{
	//读取所有用户信息
	//输入：用户链表头指针
	//输出：用户链表头指针
	struct userinfo* tmp = head;
	if (tmp == NULL)
	{//若文件为空，报错提示
		printf("没有可用的用户信息，请检查后重试！");
		Sleep(1000);
		return NULL;
	}

	PrintLine(60, '=');
	printf("  编号     名称		累计消费	VIP		密码\n");
	PrintLine(60, '=');
	while (tmp != NULL)
	{
		printf("%6d", tmp->data.id);
		printf("%20s", tmp->data.name);
		printf("%12.2lf", tmp->data.cost);
		printf("%4d", tmp->data.vip);
		printf("%16s", tmp->data.password);
		putchar('\n');
		tmp = tmp->next;
		PrintLine(60, '-');
	}
	printf("共找到%d条信息\n", sys.user_count);
	system("pause");

	return head;
}

int UserCount(struct userinfo* head)
{
	//用户计数
	//输入：用户信息链表头指针
	//输出：无
	int count = 0;
	struct userinfo* tmp = head;

	if (head == NULL)
	{
		printf("无可用信息！");
		Sleep(1000);
		return 0;
	}
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}

	return count;
}

void ReleaseList(struct userinfo* head)
{
	//释放用户信息链表空间
	//输入：链表头指针
	//输出：无
	struct userinfo* p=NULL, *q=head;
	while (p != NULL)
	{
		p = q;
		q = q->next;
		free(p);
	}
	return;
}

void ShowStatus(void)
{
	//显示目前的运行状况
	//输入：无
	//输出：无。全部信息基于sys结构体
	InitNew();
	PrintLine(20, '-');
	printf("\t系统状态:\n");
	PrintLine(20, '-');
	printf("目前余额：%.2lf\n用户人数：%d\n商品种数：%d\n", sys.asset,sys.user_count,sys.item_count);
	printf("当前促销折扣：%.2f\n\n", sys.promotion);
	PrintLine(20, '-');
	printf("\t管理员信息：\n");
	PrintLine(20, '-');
	printf("管理员账号：%s\n", sys.admin_name);
	printf("管理员密码：%s\n\n", sys.admin_pwd);
	PrintLine(20, '-');
	printf("\t经营建议：\n");
	PrintLine(20, '-');
	BestGood();
	BestSale();
	WorstSale();
	CheckDuration();
	system("pause");
	return;
}

void SearchUserByName(struct userinfo* head)
{
	//通过姓名查找客户
	//输入：用户链表头指针
	//输出：无，仅打印符合要求的数据
	if (head == NULL)
	{
		printf("无可用信息！\n");
		return;
	}

	int count = 0;
	char target[100] = { '\0' };
	struct userinfo* p = head;

	fflush(stdin);
	ClearBuffer();
	printf("请输入要查找的用户名称：");
	scanf("%100s", target);
	PrintLine(60, '=');
	printf("  编号     名称		累计消费	VIP\n");
	PrintLine(60, '=');
	while (p != NULL)
	{
		if (strcmp(target, p->data.name) == 0 || IsSameNode(target, p->data.name) == 1)
		{
			printf("%6d ", p->data.id);
			printf("%-20s ", p->data.name);
			printf("%10.2lf ", p->data.cost);
			printf("%4d\n", p->data.vip);
			count++;
			PrintLine(60, '-');
		}
		p = p->next;
	}
	if (count > 0)
	{
		printf("共找到%d条信息\n", count);
	}
	else
	{
		printf("未找到用户%s\n", target);
	}
	system("pause");
	return;
}

int MaxUserId(struct userinfo* head)
{
	//查找最大的用户编号
	//输入：用户链表头指针
	//输出：最大编号
	int count = 0;
	if (head == NULL)
	{
		printf("无可用信息！\n");
		return 0;
	}
	struct userinfo* p = head;

	while (p != NULL)
	{
		if (p->data.id > count)
		{
			count = p->data.id;
		}
		p = p->next;
	}

	return count;
}

void SearchForUserCost(struct userinfo* head)
{
	//根据消费金额查找用户
	//输入：用户信息链表头指针
	//输出：无
	struct userinfo* p = head;
	ClearBuffer();
	if (head == NULL)
	{
		return;
	}
	int count = 0;
	double max = 0, min = 0;
	while (1)
	{
		fflush(stdin);
		printf("输入您要查找的最小消费金额：(0为无限制)");
		int mincount = scanf("%lf", &min);
		fflush(stdin);
		printf("输入您要查找的最大消费金额：(0为无限制)");
		int maxcount = scanf("%lf", &max);
		if (max == 0)
		{
			max = (int)(pow(2, 31) - 1);
		}
		if (mincount <= 0 || maxcount <= 0 || min < 0 || max<0 || min>max)
		{
			printf(COLOR_ERR"输入非法，请重试。\n"COLOR_CLEAR);
			ClearBuffer();
		}
		else
		{
			break;
		}
	}

	PrintLine(60, '=');
	printf("  编号     名称		累计消费	VIP\n");
	PrintLine(60, '=');
	if (max == 0 && min == 0)
	{
		while (p != NULL)
		{
			printf("%6d", p->data.id);
			printf("%20s", p->data.name);
			printf("%10.2lf", p->data.cost);
			printf("%4d", p->data.vip);
			printf("%16s", p->data.password);
			putchar('\n');
			PrintLine(60, '-');
			count++;
		}
		p = p->next;
	}
	if (max != 0 && min == 0)
	{
		while (p != NULL)
		{
			if (p->data.cost <= max)
			{
				printf("%6d", p->data.id);
				printf("%20s", p->data.name);
				printf("%10.2lf", p->data.cost);
				printf("%4d", p->data.vip);
				printf("%16s", p->data.password);
				putchar('\n');
				PrintLine(60, '-');
				count++;
			}
			p = p->next;
		}
	}
	if (max == 0 && min != 0)
	{
		while (p != NULL)
		{
			if (p->data.cost >= min)
			{
				printf("%6d", p->data.id);
				printf("%20s", p->data.name);
				printf("%10.2lf", p->data.cost);
				printf("%4d", p->data.vip);
				printf("%16s", p->data.password);
				putchar('\n');
				PrintLine(60, '-');
				count++;
			}
			p = p->next;
		}
	}
	if (max != 0 && min != 0)
	{
		while (p != NULL)
		{
			if (p->data.cost >= min && p->data.cost <= max)
			{
				printf("%6d", p->data.id);
				printf("%20s", p->data.name);
				printf("%10.2lf", p->data.cost);
				printf("%4d", p->data.vip);
				printf("%16s", p->data.password);
				putchar('\n');
				PrintLine(60, '-');
				count++;
			}
			p = p->next;
		}
	}
	printf("共找到%d条信息,占客户总数的%.2f%%\n", count, count * 1.0 / sys.user_count * 100);
	system("pause");
	return;
}

void ReleaseSuggestions(struct suggestlian* head)
{
	//释放建议链表内存
	//输入：建议链表头指针
	//输出：无
	struct suggestlian* p = NULL, * q = head;
	while (p != NULL)
	{
		p = q;
		q = q->next;
		free(p);
	}
	return;
}

int IsSameNode(char input[], char asseredname[])
{
	//模糊搜索实现模块
	//输入：关键字，用户名字符串
	//输出：若含有关键字则返回1，否则返回0
	int firstrun = 1;
	char temp[300] = { 0 };
	if (strlen(input) >= 20)
	{
		return 0;
	}
	int length1 = (int)strlen(input);
	int length2 = (int)strlen(asseredname);
	if (length2 % 2 == 1)
	{
		int m = length2;
		int count = 1;
		while (m)
		{
			if (firstrun == 1)
			{
				strncpy(temp, asseredname, length1);
				temp[length1] = '\0';
			}
			firstrun = 0;
			if (strcmp(temp, input) == 0)
				return 1;
			else
			{
				m = m - 1;
				memset(temp, 0, sizeof(temp));
				strncpy(temp, asseredname + count, length1);
				temp[length1] = '\0';
				count++;
			}
		}
		return 0;
	}
	int m = length2;
	int count = 1;
	while (m)
	{
		if (firstrun == 1)
		{
			strncpy(temp, asseredname, length1);
			temp[length1] = '\0';
		}
		firstrun = 0;
		if (strcmp(temp, input) == 0)
			return 1;
		else
		{
			m = m - 2;
			memset(temp, 0, sizeof(temp));
			strncpy(temp, asseredname + count * 2, length1);
			temp[length1] = '\0';
			count++;
		}
	}
	return 0;
}

struct userinfo* FindUserPos(struct userinfo* head, char username[])
{
	//找到指定用户的链表指针位置
	//输入：用户信息链表头指针，用户名字符串头指针
	//输出：找到的用户信息结构体指针，若不存在该用户，则返回空指针
	struct userinfo* p = head;
	if (head == NULL)
	{
		printf("无可用信息！\n");
		return NULL;
	}
	while (p != NULL)
	{
		if (strcmp(username, p->data.name) == 0)
		{
			return p;
		}
		p = p->next;
	}
	printf("用户不存在！\n");
	system("pause");
	return NULL;
}

struct userinfo* FindUserPosById(struct userinfo* head, int target_id)
{
	//找到指定用户的链表指针位置
	//输入：用户信息链表头指针，用户ID
	//输出：找到的用户信息结构体指针，若不存在该用户，则返回空指针
	struct userinfo* p = head;
	if (head == NULL)
	{
		printf("无可用信息！\n");
		return NULL;
	}
	while (p != NULL)
	{
		if (p->data.id == target_id)
		{
			return p;
		}
		p = p->next;
	}
	printf("用户不存在！\n");
	system("pause");
	return NULL;
}

void NewUser(void)
{
	//注册新用户
	//输入：无
	//输出：无
	int IsFirstRun = 1;
	struct customer new_customer = { 0 };
	char new_password_confirm[16] = { 0 };
	FILE* plist = fopen("user.txt", "a");
	struct userinfo* p = CreateChain();

	InitNew();

	PrintLine(60, '=');
	printf("\t注册新用户");

	printf("\n请输入您要使用的用户名：");
	scanf_s("%s", new_customer.name, 20);
	while (p != NULL)
	{
		if (strcmp(new_customer.name, p->data.name) == 0)
		{
			printf("用户名已存在！\n");
			system("pause");
			return;
		}
		p = p->next;
	}
	putchar('\n');
	printf("请输入您的密码：");
	HiddenPassword(new_customer.password);
	putchar('\n');
	printf("请再次输入密码：");
	HiddenPassword(new_password_confirm);
	putchar('\n');
	if (strcmp(new_customer.password, new_password_confirm) != 0)
	{
		printf("两次输入的密码不一致，请重试！\n");
		system("pause");
		return;
	}
	new_customer.cost = 0;
	new_customer.vip = 0;
	new_customer.id = sys.max_user + 1;
	sys.user_count++;
	sys.max_user++;

	fprintf(plist, "%-5d %-20s %lf% -5d %-20s\n",
		new_customer.id, new_customer.name, 0.000000, 0, new_customer.password);
	fclose(plist);

	printf("注册成功！您的用户名：%s，用户id：%d\n", new_customer.name, new_customer.id);
	system("pause");
	return;
}

void UserMain(void)
{
	int choice = 0;
	struct suggestlian* head_suggest = ReadSuggestions();

	InitNew();
	fflush(stdin);
	while (1)
	{
		PrintLine(60, '=');
		Gotoxy(hout, 24, 1);
		printf(COLOR_NOTE"欢迎光临本店\n"COLOR_CLEAR);
		PrintLine(60, '=');
		PrintToxy("[1]购买/退货\n", 24, 3);
		PrintLine(60, '-');
		PrintToxy("[2]查看个人信息\n", 22, 5);
		PrintLine(60, '-');
		PrintToxy("[3]修改个人信息\n", 22, 7);
		PrintLine(60, '-');
		PrintToxy("[4]提出意见\n", 25, 9);
		PrintLine(60, '-');
		PrintToxy("[0]退出\n", 27, 11);
		PrintLine(60, '=');
		for (int i = 1; i <= 11; i += 2)
		{
			PrintToxy("*", 0, i);
			PrintToxy("*", 59, i);
		}
		Gotoxy(hout, 0, 13);
		printf("请选择：");
		InputIntWithLimit(&choice, 4, 0);
		switch (choice)
		{
		case 0:
			return;
		case 1:
			Buy();
			break;
		case 2:
			ShowPersonalInfo();
			break;
		case 3:
			ChangePersonalInfo();
			break;
		case 4:
			if (sys.board_status == 0)
			{
				printf("抱歉，意见箱已被管理员关闭！\n");
				system("pause");
				break;
			}
			AddSuggest(head_suggest);
			WriteSuggestToFile(head_suggest);
			printf("成功添加意见！感谢您的支持！\n");
			system("pause");
			break;
		}
		system("cls");
	}
}

void ShowPersonalInfo(void)
{
	struct userinfo* head = CreateChain();
	struct userinfo* p = FindUserPosById(head, currentUser);
	int choice = 0;
	if (p == NULL)
	{
		return;
	}

	printf("您当前的用户信息如下：\n");
	printf("用户ID：%d\n", p->data.id);
	printf("用户名：%s\n", p->data.name);
	printf("VIP等级：%d，享受%d%%优惠\n", p->data.vip, 100 - (int)(sys.vip_discount[p->data.vip] * 100));
	printf("累计消费：%.2f\n", p->data.cost);
	//printf("密码：%s\n", p->data.password);
	printf("输入1可显示您的消费记录，输入其他数字以返回：");
	SafeNumberInput(&choice);
	if (choice == 1)
	{
		PrintLine(100, '=');
		printf("编号	类型	货号	数量	单价		金额	用户	交易时间\n");
		PrintLine(100, '=');
		struct deal* p = ReadRecord(), *q = p;
		while (p != NULL)
		{
			if (p->data.user_id == currentUser)
			{
				PrintReasonForUser(p);
			}
			p = p->next;
		}
		system("pause");
		ReleaseRecord(q);
	}
	ReleaseList(head);
	return;
}

void ChangePersonalInfo(void)
{
	struct userinfo* head = CreateChain();
	struct userinfo* p = FindUserPosById(head, currentUser);
	int choice = 0;
	if (p == NULL)
	{
		return;
	}

	printf("您当前的用户信息如下：\n");
	printf("用户ID：%d\n", p->data.id);
	printf("用户名：%s\n", p->data.name);
	printf("VIP等级：%d\n", p->data.vip);
	printf("累计消费：%.2f\n", p->data.cost);
	printf("输入1以修改用户名，输入2以修改密码，其他数字为退出：");
	SafeNumberInput(&choice);
	if (choice == 1)
	{
		printf("请输入修改后的用户名：");
		scanf_s("%s", p->data.name, 20);
		printf("修改成功！\n");
		WriteToFile(head);
		system("pause");
		ReleaseList(head);
		return;
	}
	else if (choice == 2)
	{
		char password[16] = { 0 };
		printf("请输入原密码：");
		HiddenPassword(password);
		if (strcmp(password, p->data.password) != 0)
		{
			printf("密码错误！\n");
			system("pause");
			ReleaseList(head);
			return;
		}
		printf("请输入新密码：(16位)");
		HiddenPassword(p->data.password);
		printf("\n请再次输入新密码：(16位)");
		HiddenPassword(password);
		if (strcmp(p->data.password, password) != 0)
		{
			printf("两次输入密码不一致，修改失败！\n");
			system("pause");
			ReleaseList(head);
			return;
		}
		WriteToFile(head);
		printf("修改成功！\n");
		system("pause");
		ReleaseList(head);
		return;
	}
}

void Setting(void)
{
	int choice = 0;
	char pwd1[16] = { 0 };//若修改密码，作为二次验证
	char pwd2[16] = { 0 };
	system("cls");
	PrintLine(30, '-');
	printf("\t系统设置\n");
	PrintLine(30, '-');
	if (sys.backup_status == 1)
	{
		printf("1.关闭自动备份(关闭程序时自动备份)\n");
	}
	else
	{
		printf("1.打开自动备份(关闭程序时自动备份)\n");
	}

	if (sys.board_status == 0)
	{
		printf("2.开启意见箱\n");
	}
	else
	{
		printf("2.关闭意见箱\n");
	}
	printf("3.修改每页最多显示记录的数量\n");
	printf("4.修改工资、房租等固定支出\n");
	printf("5.修改管理员账号\n");
	printf("6.修改管理员密码\n7.修改当前余额\n0.退出\n");
	printf("请选择设置：");
	InputIntWithLimit(&choice, 7, 0);
	switch (choice)
	{
	case 0:
		return;
	case 1:
		if (sys.backup_status == 0)
		{
			sys.backup_status = 1;
		}
		else
		{
			sys.backup_status = 0;
		}
		printf("修改成功！\n");
		system("pause");
		break;
	case 2:
		if (sys.board_status == 0)
		{
			sys.board_status = 1;
		}
		else
		{
			sys.board_status = 0;
		}
		printf("修改成功！\n");
		system("pause");
		break;
	case 3:
		printf("请输入每页最多显示记录的数量：(当前为%d)",sys.max_list);
		InputIntWithLimit(&sys.max_list, 2147483647, 1);
		printf("修改成功！\n");
		system("pause");
		break;
	case 4:
		printf("请输入每日固定支出：");
		InputIntWithLimit(&sys.rent, 2147483647, 0);
		printf("修改成功！\n");
		system("pause");
		break;
	case 5:
		if (VerifyCode())
		{
			printf("请输入新的管理员账号：(16位)");
			scanf_s("%s", sys.admin_name, 16);
			printf("修改成功！\n");
			system("pause");
		}
		break;
	case 6:
		printf("请输入旧密码：");
		HiddenPassword(pwd1);
		if (strcmp(pwd1, sys.admin_pwd) != 0)
		{
			printf("密码错误！\n");
			break;
		}
		printf("请输入新的管理员密码：(16位)");
		HiddenPassword(pwd2);
		printf("请再次输入新密码：");
		HiddenPassword(pwd1);
		if (strcmp(pwd1, pwd2) == 0)
		{
			strcpy(sys.admin_pwd, pwd1);
		}
		else
		{
			printf("两次输入新密码不一致，修改失败！\n");
			system("pause");
			break;
		}
		printf("修改成功！\n");
		system("pause");
		break;
	case 7:
		printf("输入当前商店余额：（当前为%.2lf）", sys.asset);
		SafeDoubleInput(&sys.asset);
		printf("修改成功！\n");
		system("pause");
	}
	SaveConfig();
	return;
}

void BestGood(void)
{
	ItemNode* head_item = CreateLink((ItemNode*)malloc(sizeof(ItemNode)));
	ItemNode* pItem = NULL;
	struct deal* head_deal = ReadRecord();
	struct deal* p = head_deal;
	int bestgood = 0;
	double bestcost = 0;
	if (p == NULL)
	{
		return;
	}
	for (int i = 1; i <= sys.max_item; i++)
	{
		double count = 0;
		p = head_deal;
		while (p != NULL)
		{
			if (p->data.month - GetNormalTime(GetOriginalTime())->tm_mon >= 4)
			{
				p = p->next;
				continue;
			}
			if (p->data.item_id == i && (p->data.reason == SALE || p->data.reason == REJECT))
			{
				count += p->data.money;
			}
			p = p->next;
		}
		pItem = FindItemPos(head_item, i);
		if (pItem == NULL)
		{
			continue;
		}
		if (bestcost < count && pItem->thing.number != 1)
		{
			bestcost = count;
			bestgood = i;
		}
	}
	pItem = FindItemPos(head_item, bestgood);
	if (pItem != NULL)
	{
		printf("根据近期销售额情况，建议进货：%s，商品编号%d\n", pItem->thing.brand, bestgood);
	}
	return;
}

void BestSale(void)
{
	ItemNode* head_item = CreateLink((ItemNode*)malloc(sizeof(ItemNode)));
	ItemNode* pItem = NULL;
	struct deal* head_deal = ReadRecord();
	struct deal* p = head_deal;
	int bestgood = 0;
	int bestcount = 0;
	if (p == NULL)
	{
		return;
	}
	for (int i = 1; i <= sys.max_item; i++)
	{
		int count = 0;
		p = head_deal;
		while (p != NULL)
		{
			if (p->data.month - GetNormalTime(GetOriginalTime())->tm_mon >= 4)
			{
				p = p->next;
				continue;
			}
			if (p->data.item_id == i && (p->data.reason == SALE || p->data.reason == REJECT))
			{
				count -= p->data.count;
			}
			p = p->next;
		}
		pItem = FindItemPos(head_item, i);
		if (pItem == NULL)
		{
			continue;
		}
		if (bestcount < count && pItem->thing.number != 1)
		{
			bestcount = count;
			bestgood = i;
		}
	}
	pItem = FindItemPos(head_item, bestgood);
	if (pItem != NULL)
	{
		printf("根据近期销量情况，建议进货：%s，商品编号%d\n", pItem->thing.brand, bestgood);
	}
	return;
}

void BackupAll(void)
{
	system("@ attrib -H *.bak");
	FILE* bakConfig = fopen("config.bak", "wb");
	FILE* pConfig = fopen("config.dat", "rb");
	fread(&sys, sizeof(sys), 1, pConfig);
	fwrite(&sys, sizeof(sys), 1, bakConfig);
	fclose(bakConfig);
	fclose(pConfig);

	FILE* pUser = fopen("user.txt", "r");
	FILE* bakUser = fopen("user.bak", "w");
	while (feof(pUser) == 0)
	{
		char c = fgetc(pUser);
		if (feof(pUser))
		{
			break;
		}
		fputc(c, bakUser);
	}
	fclose(pUser);
	fclose(bakUser);

	FILE* pRecord = fopen("record.dat", "rb");
	FILE* bakRecord = fopen("record.bak", "wb");
	while (feof(pRecord) == 0)
	{
		struct record temp = { 0 };
		fread(&temp, sizeof(struct record), 1, pRecord);
		if (feof(pRecord))
		{
			break;
		}
		fwrite(&temp, sizeof(struct record), 1, bakRecord);
	}
	fclose(pRecord);
	fclose(bakRecord);

	FILE* pItem = fopen("good.txt", "r");
	FILE* bakItem = fopen("good.bak", "w");
	while (feof(pItem) == 0)
	{
		char c = fgetc(pItem);
		if (feof(pItem))
		{
			break;
		}
		fputc(c, bakItem);
	}
	fclose(pItem);
	fclose(bakItem);
	system("attrib +H *.bak");
	return;
}

void RecoverAll(void)
{
	system("attrib -H *.bak");
	FILE* bakConfig = fopen("config.bak", "rb");
	if (bakConfig == NULL)
	{
		printf("没有备份的文件！\n");
		return;
	}
	fread(&sys, sizeof(struct sysconfig), 1, bakConfig);
	SaveConfig();
	fclose(bakConfig);

	FILE* pUser = fopen("user.txt", "w");
	FILE* bakUser = fopen("user.bak", "r");
	if (bakUser == NULL)
	{
		printf("没有备份的文件！\n");
		return;
	}
	while (feof(bakUser) == 0)
	{
		char c = fgetc(bakUser);
		if (feof(bakUser))
		{
			break;
		}
		fputc(c, pUser);
	}
	fclose(pUser);
	fclose(bakUser);

	FILE* pRecord = fopen("record.dat", "wb");
	FILE* bakRecord = fopen("record.bak", "rb");
	if (bakRecord == NULL)
	{
		printf("没有备份的文件！\n");
		return;
	}
	while (feof(bakRecord) == 0)
	{
		struct record temp = { 0 };
		fread(&temp, sizeof(struct record), 1, bakRecord);
		if (feof(bakRecord))
		{
			break;
		}
		fwrite(&temp, sizeof(struct record), 1, pRecord);
	}
	fclose(pRecord);
	fclose(bakRecord);

	FILE* pItem = fopen("good.txt", "w");
	FILE* bakItem = fopen("good.bak", "r");
	if (bakItem == NULL)
	{
		printf("没有备份的文件！\n");
		return;
	}
	while (feof(bakItem) == 0)
	{
		char c = fgetc(bakItem);
		if (feof(bakItem))
		{
			break;
		}
		fputc(c, pItem);
	}
	fclose(pItem);
	fclose(bakItem);
	system("attrib +H *.bak");
	return;
}

void BackupMain(void)
{
	int choice = 0;

	system("@ attrib -H *.bak");
	system("cls");
	PrintLine(30, '-');
	printf("\t备份系统\n");
	PrintLine(30, '-');
	printf("0.退出\n");
	printf("1.立即全部备份\n");
	printf("2.立即全部恢复\n");
	printf("3.备份系统配置\n");
	printf("4.恢复系统配置\n");
	printf("5.备份用户信息\n");
	printf("6.恢复用户信息\n");
	printf("7.备份商品信息\n");
	printf("8.恢复商品信息\n");
	printf("9.备份交易记录\n");
	printf("10.恢复交易记录\n");
	printf("请选择：");
	InputIntWithLimit(&choice, 10, 0);
	switch (choice)
	{
	case 0:
		return;
	case 1:
		BackupAll();
		break;
	case 2:
		RecoverAll();
		break;
	case 3:
	{
		FILE* bakConfig = fopen("config.bak", "wb");
		fwrite(&sys, sizeof(struct sysconfig), 1, bakConfig);
		fclose(bakConfig);
		break;
	}
	case 4:
	{
		FILE* bakConfig = fopen("config.bak", "rb");
		if (bakConfig == NULL)
		{
			printf("没有备份的文件！\n");
			return;
		}
		fread(&sys, sizeof(struct sysconfig), 1, bakConfig);
		SaveConfig();
		fclose(bakConfig);
		break;
	}
	case 5:
	{
		FILE* pUser = fopen("user.txt", "r");
		FILE* bakUser = fopen("user.bak", "w");
		while (feof(pUser) == 0)
		{
			char c = fgetc(pUser);
			if (feof(pUser))
			{
				break;
			}
			fputc(c, bakUser);
		}
		fclose(pUser);
		fclose(bakUser);
		break;
	}
	case 6:
	{
		FILE* pUser = fopen("user.txt", "w");
		FILE* bakUser = fopen("user.bak", "r");
		if (bakUser == NULL)
		{
			printf("没有备份的文件！\n");
			return;
		}
		while (feof(bakUser) == 0)
		{
			char c = fgetc(bakUser);
			fputc(c, pUser);
		}
		fclose(pUser);
		fclose(bakUser);
	}
	case 7:
	{
		FILE* pItem = fopen("good.txt", "r");
		FILE* bakItem = fopen("good.bak", "w");
		while (feof(pItem) == 0)
		{
			char c = fgetc(pItem);
			if (feof(pItem))
			{
				break;
			}
			fputc(c, bakItem);
		}
		fclose(pItem);
		fclose(bakItem);
		break;
	}
	case 8:
	{
		FILE* pItem = fopen("good.txt", "w");
		FILE* bakItem = fopen("good.bak", "r");
		if (bakItem == NULL)
		{
			printf("没有备份的文件！\n");
			return;
		}
		while (feof(bakItem) == 0)
		{
			char c = fgetc(bakItem);
			fputc(c, pItem);
		}
		fclose(pItem);
		fclose(bakItem);
	}
	case 9:
	{
		FILE* pRecord = fopen("record.dat", "rb");
		FILE* bakRecord = fopen("record.bak", "wb");
		while (feof(pRecord) == 0)
		{
			struct record temp = { 0 };
			fread(&temp, sizeof(struct record), 1, pRecord);
			if (feof(pRecord))
			{
				break;
			}
			fwrite(&temp, sizeof(struct record), 1, bakRecord);
		}
		fclose(pRecord);
		fclose(bakRecord);
		break;
	}
	case 10:
	{
		FILE* pRecord = fopen("record.dat", "wb");
		FILE* bakRecord = fopen("record.bak", "rb");
		if (bakRecord == NULL)
		{
			printf("没有备份的文件！\n");
			return;
		}
		while (feof(bakRecord) == 0)
		{
			struct record temp = { 0 };
			fread(&temp, sizeof(struct record), 1, bakRecord);
			if (feof(bakRecord))
			{
				break;
			}
			fwrite(&temp, sizeof(struct record), 1, pRecord);
		}
		fclose(pRecord);
		fclose(bakRecord);
		break;
	}

	}
	printf("操作成功！\n");
	system("pause");
	system("attrib +H *.bak");
	return;
}

void WorstSale(void)
{
	ItemNode* head_item = CreateLink((ItemNode*)malloc(sizeof(ItemNode)));
	ItemNode* pItem = head_item->next1;
	struct deal* head_deal = ReadRecord();
	struct deal* p = head_deal;
	int worstgood = 0;
	int worstcount = 2147483647;
	if (p == NULL)
	{
		return;
	}
	for (int i = 1; i <= sys.max_item; i++)
	{
		int count = 0;
		p = head_deal;
		while (p != NULL)
		{
			if (p->data.month - GetNormalTime(GetOriginalTime())->tm_mon >= 4)
			{
				p = p->next;
				continue;
			}
			if (p->data.item_id == i && (p->data.reason == SALE || p->data.reason == REJECT))
			{
				count -= p->data.count;
			}
			p = p->next;
		}
		pItem = FindItemPos(head_item, i);
		if (pItem == NULL)
		{
			continue;
		}
		if (worstcount > count && pItem->thing.number != 1)
		{
			worstcount = count;
			worstgood = i;
		}
	}
	pItem = FindItemPos(head_item, worstgood);
	if (pItem != NULL)
	{
		printf("根据近期销量情况，建议减少进货：%s，商品编号%d\n", pItem->thing.brand, worstgood);
	}
	return;
}

void ShowVipGift(void)
{
	ItemNode* head_item = CreateLink((ItemNode*)malloc(sizeof(ItemNode)));
	ItemNode* p = NULL;

	for (int i = 0; i < 9; i++)
	{
		p = FindItemPos(head_item, sys.vip_gift[i]);
		if (p == NULL)
		{
			printf("VIP%d当前未设置赠品\n", i);
		}
		else
		{
			printf("当前VIP%d的赠品是%s,编号%d\n", i, p->thing.brand, sys.vip_gift[i]);
		}
	}
	system("pause");
	return;
}

void ChangeVipGift(void)
{
	int target_vip = 0, temp = 0;
	ItemNode* head_item = CreateLink((ItemNode*)malloc(sizeof(ItemNode)));
	ItemNode* p = NULL;

	printf("请输入要修改赠品的VIP等级：");
	InputIntWithLimit(&target_vip, 8, 0);
	p = FindItemPos(head_item, sys.vip_gift[target_vip]);
	if (p == NULL)
	{
		printf("VIP%d当前未设置赠品！\n", target_vip);
	}
	else
	{
		printf("当前VIP%d的赠品是%s,编号%d\n", target_vip, p->thing.brand, sys.vip_gift[target_vip]);
	}
	printf("输入您要为该VIP等级设置的赠品编号(0为清除赠品)：\n");
	SafeNumberInput(&temp);
	if (temp != 0 && FindItemPos(head_item, temp) == NULL)
	{
		printf("选择的商品不存在！\n");
		system("pause");
		return;
	}
	sys.vip_gift[target_vip] = temp;
	SaveConfig();
	printf("修改成功！\n");
	system("pause");
	return;
}

/*967584.26*/