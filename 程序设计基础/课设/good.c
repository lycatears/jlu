#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <malloc.h>
#include <time.h>
#include "good.h"
#include "defines.h"
#include "public.h"
#include "record.h"
#include "userman.h"
#include "sever_time.h"

#pragma warning(disable:4996)
#pragma warning(disable:6031)

int count = 0;
double cost = 0;
extern struct sysconfig sys;
extern int currentUser;

int ItemMenu(void)
{
	int select;
	printf("请选择数字进行操作：\n");
	printf("1.显示所有信息\n");
	printf("2.增加新的商品种类\n");
	printf("3.删除某种商品种类\n");
	printf("4.商品进退货\n");
	printf("5.查找某种商品\n");
	printf("6.修改商品信息\n");
	printf("7.商品损耗处理\n");
	printf("8.拆分为零售商品\n");
	printf("0.返回\n");
	while (1)
	{
		fflush(stdin);
		SafeNumberInput(&select);
		if (select < 0 || select>8)
		{
			printf("输入错误,请继续输入：");
		}
		else
		{
			break;
		}
	}
	return select;
}

ItemNode* CreateLink(ItemNode* goods_head)
{
	FILE* fp = fopen("good.txt", "r");
	ItemNode* current = NULL;
	current = goods_head;
	int flag = 1;
	//将文件中的信息存入链表中
	if (fp == NULL)
	{
		printf("文件打开失败!\n");
		return goods_head;
	}
	else
	{
		while (flag)
		{
			ItemNode* mid = NULL;
			mid = (ItemNode*)malloc(sizeof(ItemNode));
			if (mid == NULL)
			{
				return NULL;
			}
			mid->next1 = NULL;
			flag = fscanf(fp, "%d", &mid->thing.id);
			if (flag < 0)
			{
				break;
			}
			fscanf(fp, "%d", &mid->thing.volume);
			fscanf(fp, "%40s", &mid->thing.brand);
			fscanf(fp, "%d", &mid->thing.number);
			fscanf(fp, "%lf", &mid->thing.in_price);
			fscanf(fp, "%lf", &mid->thing.out_price);
			fscanf(fp, "%40s", &mid->thing.zhizaoshang);
			fscanf(fp, "%40s", &mid->thing.gonghuoshang);
			fscanf(fp, "%d", &mid->thing.storage);
			fscanf(fp, "%d", &mid->thing.duration);
			current->next1 = mid;
			current = mid;
			//商品种类加一
			count++;

		}
	}
	fclose(fp);
	return goods_head;
}

ItemNode* AddItem(ItemNode* goods_head)
{
	//定义新的商品的信息
	if (goods_head == NULL)
	{
		goods_head = (ItemNode*)malloc(sizeof(ItemNode));
		goods_head->next1 = NULL;
	}
	ItemNode* p = goods_head->next1;
	ItemNode* mid;
	mid = (ItemNode*)malloc(sizeof(ItemNode));
	mid->next1 = NULL;
	//读取新的商品的信息并存入链表

	mid->thing.id = sys.max_item + 1;

	system("cls");
	printf("\t增加酒水\n");
	PrintLine(20, '=');

	printf("单个饮品的体积：（单位：毫升）");
	fflush(stdin);
	InputIntWithLimit(&mid->thing.volume, 2147483647, 1);

	printf("品名：");
	fflush(stdin);
	getchar();
	fgets(mid->thing.brand, 30, stdin);
	mid->thing.brand[strlen(mid->thing.brand) - 1] = '\0';

	printf("每箱的数量：");
	fflush(stdin);
	InputIntWithLimit(&mid->thing.number, 2147483647, 1);

	printf("进价：");
	fflush(stdin);
	while (1)
	{
		SafeDoubleInput(&mid->thing.in_price);
		if (mid->thing.in_price <= 0)
		{
			printf("非法输入，请重试！");
			continue;
		}
		break;
	}

	printf("售卖价：");
	fflush(stdin);
	while (1)
	{
		SafeDoubleInput(&mid->thing.out_price);
		if (mid->thing.out_price <= 0)
		{
			printf("非法输入，请重试！");
			continue;
		}
		break;
	}

	printf("库存数量：");
	fflush(stdin);
	InputIntWithLimit(&mid->thing.storage, 2147483647, 1);

	printf("制造商：");
	fflush(stdin);
	char temp;
	scanf("%c", &temp);
	fgets(mid->thing.zhizaoshang, 30, stdin);
	mid->thing.zhizaoshang[strlen(mid->thing.zhizaoshang) - 1] = '\0';

	printf("供货商：");
	fflush(stdin);
	fgets(mid->thing.gonghuoshang, 30, stdin);
	mid->thing.gonghuoshang[strlen(mid->thing.gonghuoshang) - 1] = '\0';

	printf("保质期：(以天为单位)");
	fflush(stdin);
	InputIntWithLimit(&mid->thing.duration, 2147483647, 1);

	if (mid->thing.in_price * mid->thing.storage > sys.asset)
	{
		printf("余额不足，添加失败！\n");
		system("pause");
		return 0;
	}

	//进行链表的链接
	if (goods_head == NULL)
	{
		p->next1 = mid;
		goods_head = p;
	}
	else if (p != NULL)
	{
		while (p->next1 != NULL)
			p = p->next1;
		p->next1 = mid;
	}
	StoreItem(goods_head);
	p = goods_head;
	printf("已成功添加商品：%s，货号：%d\n",mid->thing.brand,mid->thing.id);
	//增加商品数量
	count++;
	sys.item_count++;
	sys.max_item++;
	sys.asset -= mid->thing.storage * mid->thing.in_price;
	WriteRecord(STOCK, 0, mid->thing.id, mid->thing.storage, mid->thing.in_price, 
		-mid->thing.in_price * mid->thing.storage);//添加商品视为进货
	SaveConfig();
	system("pause");
	return goods_head;
}

ItemNode* ChangeItem(ItemNode* goods_head)
{
	if (FindItem(goods_head) == 0)
	{
		return NULL;
	}
	int _id;
	PrintLine(20, '-');
	printf("请输入要进退货的商品编号：");
	SafeNumberInput(&_id);
	PrintLine(20, '-');
	int flag = 1;

	//判断商品是否存在，若存在的话则对商品数量进行更改，
	ItemNode* p = goods_head->next1;
	while (p != NULL)
	{
		if (p->thing.id == _id)
		{
			printf("商品%s已找到，目前库存量为：%d\n", p->thing.brand, p->thing.storage);
			int num;
			printf("请输入需要增改的数量，正数代表进货数量，负数代表退货数量：");
			while (1)
			{
				if (SafeNumberInput(&num))
				{
					if (num > 0)
					{
						if (num * p->thing.in_price > sys.asset)
						{
							printf("余额不足，进货失败！\n");
							system("pause");
							return goods_head;
						}
						printf("成功进货%s %d箱，支付了%.2f元\n", p->thing.brand, num, p->thing.in_price * num);
						system("pause");
					}
					if (num < 0)
					{
						if (num > p->thing.storage)
						{
							printf("库存不足，退货失败！\n");
							system("pause");
							return goods_head;
						}
						printf("成功退货%s %d箱，回收了%.2f元\n", p->thing.brand, num, -p->thing.in_price * num);
						system("pause");
					}
					break;
				}
				else
				{
					printf("输入数据有误，请重新输入：");

				}
			}

			p->thing.storage += num;
			if (num > 0)
			{
				WriteRecord(STOCK, 0, p->thing.id, num, p->thing.in_price, -p->thing.in_price * num);
				sys.asset -= p->thing.in_price * num;
			}
			else if (num < 0)
			{
				WriteRecord(BACK, 0, p->thing.id, num, p->thing.in_price, -p->thing.in_price * num);
				sys.asset -= p->thing.in_price * num;
			}
			flag = 0;
			break;
		}
		p = p->next1;
	}
	//若商品不存在重新执行或退出
	if (flag == 1)
	{
		printf("该商品不存在！\n输入1再次查找，其余选项为退出该操作");
		int choice;
		if ((scanf("%d", &choice)) == 1)
		{
			if (choice == 1)
			{
				return ChangeItem(goods_head);
			}
			else
			{
				return goods_head;
			}

		}
		else
			return goods_head;
	}
	return goods_head;

}

ItemNode* DeleteItem(ItemNode* goods_head)
{
	if (FindItem(goods_head) == 0)
	{
		return NULL;
	}
	printf("请输入要删除商品的编号：");
	int _id2;
	int flag = 1;
	SafeNumberInput(&_id2);
	ItemNode* current = goods_head->next1;
	ItemNode* pre = goods_head;
	while (current != NULL)
	{
		if (current->thing.id == _id2)
		{
			pre->next1 = current->next1;
			free(current);
			flag = 0;
			count--;
			break;
		}
		current = current->next1;
		pre = pre->next1;


	}
	if (flag == 1)
	{
		printf("删除商品不存在!");
	}
	else
	{
		printf("删除成功！\n");
	}
	system("pause");
	sys.item_count--;
	return goods_head;

}

int FindItem(ItemNode* goods_head)
{
	if (goods_head == NULL)
	{
		printf("无可用信息！\n");
		system("pause");
		return 0;
	}
	int select = 0;
	int flag = 1;
	printf("\n操作前请通过搜索确认信息\n");
	PrintLine(30, '-');
	printf("若按照商品编号查找，请输入1：");
	printf("\n若按照规格查找，请输入2：");
	printf("\n若按照一箱数量查找，请输入3：\n若按照名称查找，请输入4：\n输入其他数字以退出");
	SafeNumberInput(&select);
	if (select > 4 || select <= 0)
	{
		return 0;
	}
	if (select == 1)
	{
		printf("请输入要查找的商品编号：");
		int _id3;
		SafeNumberInput(&_id3);

		ItemNode* p = goods_head->next1;
		while (p != NULL)
		{

			if (p->thing.id == _id3)
			{
				printf("商品编号：%d\t", p->thing.id);
				printf("名称：%s\n", p->thing.brand);
				printf("体积：%d\t", p->thing.volume);
				printf("每箱数量：%d\t", p->thing.number);
				printf("进价：%.2f\t", p->thing.in_price);
				printf("售价：%.2f\n", p->thing.out_price);
				printf("制造商：%s\t", p->thing.zhizaoshang);
				printf("供货商：%s\n", p->thing.gonghuoshang);
				printf("库存：%d\t", p->thing.storage);
				printf("保质期（单位：天）：%d\n", p->thing.duration);
				putchar('\n');
				flag = 0;
				break;
			}
			p = p->next1;
		}
		if (flag == 1)
		{
			printf("该商品不存在!");
		}
		system("pause");
		return 1;

	}
	if (select == 2)
	{
		fflush(stdin);
		printf("请输入规格大小：");
		int v = 0;
		SafeNumberInput(&v);
		ItemNode* pp = goods_head->next1;
		int flag2 = 1;
		while (pp != NULL)
		{
			if (pp->thing.volume == v)
			{
				printf("商品编号：%d\t", pp->thing.id);
				printf("名称：%s\n", pp->thing.brand);
				printf("体积：%d\t", pp->thing.volume);
				printf("每箱数量：%d\t", pp->thing.number);
				printf("进价：%.2f\t", pp->thing.in_price);
				printf("售价：%.2f\n", pp->thing.out_price);
				printf("制造商：%s\t", pp->thing.zhizaoshang);
				printf("供货商：%s\n", pp->thing.gonghuoshang);
				printf("库存：%d\t", pp->thing.storage);
				printf("保质期（单位：天）：%d\n\n", pp->thing.duration);
				flag2 = 0;
			}
			pp = pp->next1;
		}
		if (flag2 == 1)
		{
			printf("该类商品不存在！");
		}
		system("pause");
		return 1;
	}
	if (select == 3)
	{
		fflush(stdin);
		printf("请输入一箱数量的大小：");
		int num;
		SafeNumberInput(&num);
		ItemNode* ppp = goods_head->next1;
		int flag3 = 1;
		while (ppp != NULL)
		{
			if (ppp->thing.number == num)
			{
				printf("商品编号：%d\t", ppp->thing.id);
				printf("名称：%s\n", ppp->thing.brand);
				printf("体积：%d\t", ppp->thing.volume);
				printf("数量：%d\t", ppp->thing.number);
				printf("进价：%.2f\t", ppp->thing.in_price);
				printf("售价：%.2f\n", ppp->thing.out_price);
				printf("制造商：%s\t", ppp->thing.zhizaoshang);
				printf("供货商：%s\n", ppp->thing.gonghuoshang);
				printf("库存：%d\t", ppp->thing.storage);
				printf("保质期（单位：天）：%d\n\n", ppp->thing.duration);
				flag3 = 0;
			}
			ppp = ppp->next1;
		}
		if (flag3 == 1)
		{
			printf("该类商品不存在！");
		}
		system("pause");
		return 1;
	}
	if (select == 4)
	{
		printf("请输入要查找的关键字：");
		char keyword[20] = { 0 };
		scanf_s("%s", keyword, 20);

		ItemNode* p = goods_head->next1;
		while (p != NULL)
		{

			if (IsSameNode(keyword, p->thing.brand) == 1 || IsSameNode(keyword, p->thing.gonghuoshang) == 1 || IsSameNode(keyword, p->thing.zhizaoshang) == 1)
			{
				printf("商品编号：%d\t", p->thing.id);
				printf("名称：%s\n", p->thing.brand);
				printf("体积：%d\t", p->thing.volume);
				printf("每箱数量：%d\t", p->thing.number);
				printf("进价：%.2f\t", p->thing.in_price);
				printf("售价：%.2f\n", p->thing.out_price);
				printf("制造商：%s\t", p->thing.zhizaoshang);
				printf("供货商：%s\n", p->thing.gonghuoshang);
				printf("库存：%d\t", p->thing.storage);
				printf("保质期（单位：天）：%d\n\n", p->thing.duration);
				flag = 0;
				// break;
			}
			p = p->next1;
		}
		if (flag == 1)
		{
			printf("该商品不存在!");
		}
		system("pause");
		return 1;

	}
	return 1;
}

void StoreItem(ItemNode* goods_head)
{
	if (goods_head == NULL)
	{
		return;
	}
	ItemNode* p = goods_head->next1;
	FILE* fp;
	if ((fp = fopen("good.txt", "w")) == NULL)
	{
		printf("文件打开失败！\n");
		return;
	}
	else
	{
		while (p != NULL)
		{
			fprintf(fp, "%d\t", p->thing.id);
			fprintf(fp, "%d\t", p->thing.volume);
			fwrite(&p->thing.brand, strlen(p->thing.brand), 1, fp);
			fprintf(fp, "\t\t\t");
			fprintf(fp, "%d\t", p->thing.number);
			fprintf(fp, "%.2f\t", p->thing.in_price);
			fprintf(fp, "%.2f\t", p->thing.out_price);
			fwrite(&p->thing.zhizaoshang, strlen(p->thing.zhizaoshang), 1, fp);
			fprintf(fp, "\t\t\t");
			fwrite(&p->thing.gonghuoshang, strlen(p->thing.gonghuoshang), 1, fp);
			fprintf(fp, "\t\t\t");
			fprintf(fp, "%d\t", p->thing.storage);
			fprintf(fp, "%d", p->thing.duration);
			fprintf(fp, "\n");
			p = p->next1;
		}
	}
	fclose(fp);
	return;
}

void DisplayItem(ItemNode* goods_head)
{
	ItemNode* p = goods_head->next1;
	while (p != NULL)
	{
		printf("商品编号：%-6d\t", p->thing.id);
		printf("体积：%-6d\t", p->thing.volume);
		printf("名称：%-20s\n", p->thing.brand);
		printf("数量：%-6d\t", p->thing.number);
		printf("进价：%-14.2f\t", p->thing.in_price);
		printf("售价：%-14.2f\n", p->thing.out_price);
		printf("制造商：%-20s\t", p->thing.zhizaoshang);
		printf("供货商：%-20s\n", p->thing.gonghuoshang);
		printf("库存：%-6d\t", p->thing.storage);
		printf("保质期（单位：天）：%-6d\n", p->thing.duration);
		putchar('\n');
		p = p->next1;
	}
	system("pause");
	return;
}

void FindItem2(ItemNode* goods_head)
{
	if (goods_head == NULL)
	{
		printf("无可用信息！\n");
		system("pause");
		return;
	}
	int select;
	int flag = 1;
	printf("若查看商品编号，请输入1：");
	printf("\n若查看所有相同规格的商品，请输入2：");
	printf("\n若查看一箱数量相同的商品，请输入3：\n若要根据关键词查找，请输入4：\n输入其他数字以退出");
	SafeNumberInput(&select);
	if (select > 4 || select <= 0)
	{
		return;
	}
	if (select == 1)
	{
		printf("请输入要查找的商品编号：");
		int _id3;
		int flag = 1;
		SafeNumberInput(&_id3);

		ItemNode* p = goods_head->next1;
		while (p != NULL)
		{
			if (p->thing.id == _id3)
			{
				printf("商品编号：%d\t", p->thing.id);
				printf("体积：%d\t", p->thing.volume);
				printf("名称：%s\n", p->thing.brand);
				printf("数量：%d\t", p->thing.number);
				printf("进价：%.2f\t", p->thing.in_price);
				printf("售价：%.2f\t", p->thing.out_price);
				printf("制造商：%s\t", p->thing.zhizaoshang);
				printf("供货商：%s\n", p->thing.gonghuoshang);
				printf("库存：%d\t", p->thing.storage);
				printf("保质期（单位：天）：%d\n\n", p->thing.duration); 
				flag = 0;
				break;
			}
			p = p->next1;
		}
		if (flag == 0)
		{
			int choice = 0;
			printf("查找成功，如需再次查找请输入1：");
			SafeNumberInput(&choice);
			if (choice == 1)
			{
				FindItem2(goods_head);
				return;
			}
			else
			{
				system("pause");
				return;
			}
		}
		if (flag == 1)
		{
			printf("该商品不存在!");
			system("pause");
			return;
		}
	}
	if (select == 2)
	{
		printf("请输入所要查看的规格大小：");
		int v = 0;
		SafeNumberInput(&v);
		ItemNode* pp = goods_head->next1;
		int flag2 = 1;
		while (pp != NULL)
		{
			if (pp->thing.volume == v)
			{
				printf("商品编号：%d\t", pp->thing.id);
				printf("体积：%d\t", pp->thing.volume);
				printf("名称：%s\n", pp->thing.brand);
				printf("数量：%d\t", pp->thing.number);
				printf("进价：%.2f\t", pp->thing.in_price);
				printf("售价：%.2f\t", pp->thing.out_price);
				printf("制造商：%s\t", pp->thing.zhizaoshang);
				printf("供货商：%s\n", pp->thing.gonghuoshang);
				printf("库存：%d\t", pp->thing.storage);
				printf("保质期（单位：天）：%d\n\n", pp->thing.duration); 
				flag2 = 0;
			}
			pp = pp->next1;
		}
		if (flag2 == 0)
		{
			int choice;
			printf("查找成功，如需再次查找请输入1：");
			SafeNumberInput(&choice);
			if (choice == 1)
			{
				FindItem2(goods_head);
				return; 
			}
			else
			{
				system("pause");
				return;
			};
		}
		if (flag2 == 1)
		{
			printf("该类商品不存在！");
		}
		return;
	}
	if (select == 3)
	{
		printf("请输入要查找的一箱数量的数量：");
		int num = 0;
		SafeNumberInput(&num);
		ItemNode* ppp = goods_head->next1;
		int flag3 = 1;
		while (ppp != NULL)
		{
			if (ppp->thing.number == num)
			{
				printf("商品编号：%d\t", ppp->thing.id);
				printf("体积：%d\t", ppp->thing.volume);
				printf("名称：%s\n", ppp->thing.brand);
				printf("数量：%d\t", ppp->thing.number);
				printf("进价：%.2f\t", ppp->thing.in_price);
				printf("售价：%.2f\t", ppp->thing.out_price);
				printf("制造商：%s\t", ppp->thing.zhizaoshang);
				printf("供货商：%s\n", ppp->thing.gonghuoshang);
				printf("库存：%d\t", ppp->thing.storage);
				printf("保质期（单位：天）：%d\n\n", ppp->thing.duration); 
				flag3 = 0;
			}
			ppp = ppp->next1;
		}
		system("pause");
		if (flag3 == 0)
		{
			int choice;
			printf("查找成功，如需再次查找请输入1：");
			SafeNumberInput(&choice);
			if (choice == 1)
			{
				FindItem2(goods_head);
				return;
			}
			else return;
		}
		if (flag3 == 1)
		{
			printf("该类商品不存在！");
		}
		return;
	}
	if (select == 4)
	{
		printf("请输入要查找的关键字：");
		char keyword[20] = { 0 };
		scanf_s("%s", keyword, 20);

		ItemNode* p = goods_head->next1;
		while (p != NULL)
		{

			if (IsSameNode(keyword, p->thing.brand) == 1 || IsSameNode(keyword, p->thing.gonghuoshang) == 1 || IsSameNode(keyword, p->thing.zhizaoshang) == 1)
			{
				printf("商品编号：%d\t", p->thing.id);
				printf("名称：%s\n", p->thing.brand);
				printf("体积：%d\t", p->thing.volume);
				printf("每箱数量：%d\t", p->thing.number);
				printf("进价：%.2f\t", p->thing.in_price);
				printf("售价：%.2f\n", p->thing.out_price);
				printf("制造商：%s\t", p->thing.zhizaoshang);
				printf("供货商：%s\n", p->thing.gonghuoshang);
				printf("库存：%d\t", p->thing.storage);
				printf("保质期（单位：天）：%d\n\n", p->thing.duration);
				flag = 0;
				//break;
			}
			p = p->next1;
		}
		if (flag == 1)
		{
			printf("该商品不存在!");
		}
		system("pause");
		return;

	}
}

int ItemMain(void)
{
	//创建头节点和链表
	ItemNode* goods_head = NULL;
	goods_head = (ItemNode*)malloc(sizeof(ItemNode));
	
	goods_head = CreateLink(goods_head);
	//菜单选择
	int flag = 1;
	while (flag == 1)
	{
		system("cls");
		PrintLine(30, '-');
		printf("\t商品管理\n");
		PrintLine(30, '-');
		int select = ItemMenu();
		switch (select)
		{
		case 0:
			return 0;
		case 1:
			DisplayItem(goods_head); 
			break;//展示商品信息
		case 2:
			AddItem(goods_head); 
			StoreItem(goods_head); 
			break;//增加新的商品种类
		case 3: 
			DeleteItem(goods_head); 
			StoreItem(goods_head); 
			break;//改变商品库存
		case 4: 
			ChangeItem(goods_head); 
			StoreItem(goods_head);
			break;//删除某一种商品
		case 5:
			FindItem2(goods_head);
			break;//查找某一种商品的信息
		case 6:
			ChangeItemInfo(goods_head);
			break;
		case 7:
			LossProcess(goods_head);
			break;
		case 8:
			SpiltItem(goods_head);
			break;
		default:
			break;
		}
	}
	return 0;
}

int ItemCount(ItemNode* head)
{
	//计算商品总数
	//输入：商品链表头指针
	//输出：商品数量
	int count = 0;
	struct ItemNode* p = NULL;
	struct ItemNode* q = NULL;
	q = head;
	if (head == NULL)
	{
		return 0;
	}
	while (q != NULL)
	{
		p = q;
		q = q->next1;
		count++;
	}
	return count;
}

int MaxItemId(ItemNode* head)
{
	//查找最大商品id
	//输入：商品链表头指针
	//输出：最大的id
	int count = 0;
	ItemNode* p = head;
	if (head == NULL)
	{
		return 0;
	}
	while (p != NULL)
	{
		if (p->thing.id > count)
		{
			count = p->thing.id;
		}
		p = p->next1;
	}
	return count;
}

void Buy(void)
{
	// 所有商品信息链表的建立
	ItemNode* allgoods = NULL;
	allgoods = (ItemNode*)malloc(sizeof(ItemNode));
	struct deal* allrecord = ReadRecord();
	struct userinfo* alluser = CreateChain();
	if (allgoods == NULL)
	{
		printf("内存不足！\n");
		return;
	}
	allgoods->next1 = NULL;
	allgoods = CreateLink(allgoods);

	// 购物车商品链表的建立
	List* goods_head = NULL;
	goods_head = (List*)malloc(sizeof(List));
	if (goods_head == NULL)
	{
		printf("内存不足！\n");
		return;
	}
	goods_head->next = NULL;

	// 菜单的选择
	while (1)
	{
		system("cls");
		int select = BuyMenu();
		switch (select)
		{
		case 0:
			return;
		case 1:
			DisplayItemForUser(allgoods);
			break; // 展示商品信息
		case 2:
			goods_head = AddToCart(allgoods, goods_head);
			break; // 增加新的商品种类
		case 3:
			goods_head = DeleteCart(goods_head);
			break; // 改变商品库存
		case 4:
			goods_head = ChangeCart(goods_head, allgoods);
			break; // 删除某一种商品
		case 5:
			FindCart(goods_head);
			break; // 查找某一种商品的信息
		case 6:
			ShowCart(goods_head);
			break; // 显示购物车
		case 7:
			FindItemForUser(allgoods);
			break; // 按照商品属性显示商品
		case 8:
			Settle(allgoods, goods_head, allrecord, alluser);
			return;
		default:
			break;
		}
	}
	return;
}

List* AddToCart(ItemNode* allgoods, List* goods_head)
{
	int flag = 1;
	while (flag == 1)
	{
		List* p2 = goods_head;
		List* p3 = goods_head;
		if (goods_head == NULL)
		{
		    printf("无可用信息！\n");
		    return NULL;
		}
		int id_buy;
		printf("请输入要购买的商品编号：");
		if (SafeNumberInput(&id_buy) > 0)
		{
			ItemNode* p = allgoods->next1;
			int flag1 = 1;
			int flag2 = 1;
			int number_buy = 0;
			// 先查看购物车是否存在该商品
			ItemNode* info = FindItemPos(allgoods, id_buy);
			if (info == NULL)
			{
				printf("商品不存在！\n");
				system("pause");
				return goods_head;;
			}
			printf("您选择的编号%d商品信息如下：\n", id_buy);
			printf("品名：%s，单价%.2lf\n", info->thing.brand, info->thing.out_price);
			while (p3 != NULL)
			{
				if (p3->data.goods_id == id_buy && p3->data.num != 0)
				{
					flag2 = 0;
					printf(COLOR_NOTE"提示：购物车中已存在该商品\n"COLOR_CLEAR);
					while (p != NULL)
					{
						if (p->thing.id == p3->data.goods_id)
						{
							printf("该商品现有库存%d箱，请选择购买数量\n", p->thing.storage);
							SafeNumberInput(&number_buy);
							while (number_buy > p->thing.storage)
							{
								printf(COLOR_ERR"库存不足！请重新选择购买数量："COLOR_CLEAR);
								SafeNumberInput(&number_buy);
							}
							// 对商品数量的计算
							p3->data.num += number_buy;
							strcpy(p3->data.goods_brand, p->thing.brand);
							p3->data.goods_volume = p->thing.volume;
							p3->data.goods_number = p->thing.number;
							p->thing.storage -= number_buy;
							// 价钱计算
							cost += (double)number_buy * p3->data.goods_price;

							return goods_head;
						}
						p = p->next1;
					}
				}
				p3 = p3->next;
			}

			p = allgoods->next1;
			// 输入的商品编号原本不存在
			if (flag2 == 1)
			{
				// 链表节点的移动
				if (goods_head == NULL)
				{
					p2 = goods_head;
				}
				else
				{
					while (p2->next != NULL)
					{
						p2 = p2->next;
					}
				}

				while (p != NULL)
				{
					if (p->thing.id == id_buy)
					{
						// 标志商品已经找到
						flag1 = 0;
						// 创建链表的节点
						List* mid;
						mid = (List*)malloc(sizeof(struct buyitem));
						if (mid == NULL)
						{
							printf("内存不足！\n");
							return NULL;
						}
						mid->next = NULL;

						// 对链表信息的存入
						mid->data.goods_id = p->thing.id;
						strcpy(mid->data.goods_brand, p->thing.brand);
						mid->data.goods_price = p->thing.out_price;
						mid->data.goods_volume = p->thing.volume;
						mid->data.goods_number = p->thing.number;

						printf("该商品现有库存%d箱，请选择购买数量\n", p->thing.storage);
						SafeNumberInput(&number_buy);
						while (number_buy > p->thing.storage)
						{
							printf(COLOR_ERR"库存不足！请重新选择购买数量："COLOR_CLEAR);
							SafeNumberInput(&number_buy);
						}
						mid->data.num = number_buy;

						// 对于原库存内的商品数量改变
						p->thing.storage -= mid->data.num;

						// 价钱的计算
						cost += (double)number_buy * p->thing.out_price;

						// 链表的链接
						p2->next = mid;
						p2 = mid;

						// 跳出循环
						break;
					}
					p = p->next1;
				}
				if (flag1 == 1)
				{
					printf("商品不存在！");
				}
			}
		}
		else
			printf("输入错误\n");
		printf("若要继续购买请输入1，其他数字为退出\n");
		SafeNumberInput(&flag);
	}
	return goods_head;
}

int BuyMenu(void)
{
	int select = 0;
	int flag = 1;
	PrintLine(30, '-');
	printf("\t购买/退货系统\n");
	PrintLine(30, '-');
	printf("请选择数字进行操作：\n");
	printf("1.显示所有商品信息\n");
	printf("2.增加购买或退货的商品\n");
	printf("3.删除购物车中的商品\n");
	printf("4.修改购物车中商品数量\n");
	printf("5.查找购物车中的商品\n");
	printf("6.显示购物车的全部商品\n");
	printf("7.按照商品属性查找商品信息\n");
	printf("8.结算订单\n");
	printf("0.退出\n");
	InputIntWithLimit(&select, 8, 0);
	return select;
}

List* ChangeCart(List* goods_head, ItemNode* head)
{
	List* p = goods_head->next;
	printf("请输入你所需要改变商品数量的编码：");
	int id_change;
	int flag = 1;
	SafeNumberInput(&id_change);
	ItemNode* q = FindItemPos(head, id_change);
	while (p != NULL)
	{
		if (p->data.goods_id == id_change)
		{
			flag = 0;
			printf("查找成功，请输入您需要更改的数量，正数表示增加，负数表示减少：");
			int number;
			SafeNumberInput(&number);
			if ((number + p->data.num) < 0)
			{
				printf(COLOR_ERR"减少的商品数量少于您购物车中的数量，修改失败！\n"COLOR_CLEAR);
				system("pause");
				return goods_head;
			}
			if (number + p->data.num > q->thing.storage)
			{
				printf(COLOR_ERR"库存不足，修改失败！\n"COLOR_CLEAR);
				system("pause");
				return goods_head;
			}
			p->data.num += number;
			q->thing.storage -= number;
			// 价钱的计算
			cost += (double)(p->data.goods_price) * number;
			printf("修改成功！\n");
		}
		p = p->next;
	}
	if (flag == 1)
	{
		printf(COLOR_ERR"购物车中不含此商品！\n"COLOR_CLEAR);
	}
	return goods_head;
}

void FindCart(List* goods_head)
{
	List* p = goods_head->next;
	printf("请输入您要查找的商品编号：");
	int id_find;
	int flag = 1;
	SafeNumberInput(&id_find);

	while (p != NULL)
	{
		if (p->data.goods_id == id_find)
		{
			flag = 0;
			printf("已找到该商品，信息如下：\n");
			printf("编号：%d\t名称：%s\t价格：%14.2lf\t数量：%d\n", 
				p->data.goods_id, p->data.goods_brand, p->data.goods_price, p->data.num);
		}
		p = p->next;
	}
	if (flag == 1)
	{
		printf("该商品不存在\n");
	}
	system("pause");
	return;
}

void ShowCart(List* goods_head)
{
	List* p = goods_head->next;
	if (p == NULL)
	{
		printf("购物车为空！\n");
		system("pause");
		return;
	}
	PrintLine(100, '=');
	printf("您当前的购物车信息如下：(正数代表购买，负数代表退货)\n");
	PrintLine(100, '=');
	while (p != NULL)
	{
		if (p->data.num != 0)
		{
			printf("编号：%-6d\t", p->data.goods_id);
			printf("名称：%-30s\t", p->data.goods_brand);
			printf("单价：%-14.2lf\t", p->data.goods_price);
			printf("数量：%-6d\n", p->data.num);
		}
		p = p->next;
	}
	PrintLine(100,'-');
	printf("消费总额：%14.2lf\n", cost);
	system("pause");
	return;
}

void SearchCart(ItemNode* goods_head)
{
	int select = 0;
	int flag = 1;
	printf("若按照商品编号查找，请输入1：");
	printf("\n若按照规格查找，请输入2：");
	printf("\n若按照一箱数量查找，请输入3：\n");
	SafeNumberInput(&select);
	if (select == 1)
	{
		printf("请输入要查找的商品编号：");
		int _id3;
		int flag = 1;
		while (1)
		{
			int flag = scanf("%d", &_id3);
			if (flag == 1)
				break;
			else
			{
				fflush(stdin);
				printf("输入错误，请重新输入:");
			}
		}

		ItemNode* p = goods_head->next1;
		while (p != NULL)
		{

			if (p->thing.id == _id3)
			{
				printf("编号：%d\t规格：%dml\t品名：%s\t箱内瓶数：%d\t售价：%14.2lf\t库存：%d\n", 
					p->thing.id, p->thing.volume, p->thing.brand, p->thing.number,
					p->thing.out_price, p->thing.storage);
				flag = 0;
				break;
			}
			p = p->next1;
		}
		if (flag == 1)
		{
			printf("该商品不存在!");
		}
		system("pause");
		return;
	}
	if (select == 2)
	{
		printf("请输入规格大小：");
		int v;
		SafeNumberInput(&v);
		ItemNode* pp = goods_head->next1;
		int flag2 = 1;
		while (pp != NULL)
		{
			if (pp->thing.volume == v)
			{
				printf("编号：%d\t规格：%dml\t品名：%s\t箱内瓶数：%d\t售价：%14.2lf\t库存：%d\n", 
					pp->thing.id, pp->thing.volume, pp->thing.brand, pp->thing.number, pp->thing.out_price, 
					pp->thing.storage);
				flag2 = 0;
			}
			pp = pp->next1;
		}
		if (flag2 == 1)
		{
			printf("该类商品不存在！");
		}
		system("pause");
		return;
	}
	if (select == 3)
	{
		printf("请输入一箱数量的大小：");
		int num;
		SafeNumberInput(&num);
		ItemNode* ppp = goods_head->next1;
		int flag3 = 1;
		while (ppp != NULL)
		{
			if (ppp->thing.volume == num)
			{
				printf("编号：%d\t规格：%dml\t品名：%s\t箱内瓶数：%d\t售价：%14.2lf\t库存：%d\n",
					ppp->thing.id, ppp->thing.volume, ppp->thing.brand, ppp->thing.number,
					ppp->thing.out_price, ppp->thing.storage);
				flag3 = 0;
			}
			ppp = ppp->next1;
		}
		if (flag3 == 1)
		{
			printf("该类商品不存在！");
		}
		system("pause");
		return;
	}
}

List* DeleteCart(List* goods_head)
{
	int flag = 1;
	List* pre = goods_head;
	if (pre == NULL || pre->next == NULL)
	{
		printf("购物车为空！\n");
		return NULL;
	}
	List* cur = goods_head->next;
	printf("请输入您要删除的商品编号：");
	int id_cancel;
	SafeNumberInput(&id_cancel);
	if (goods_head->next->data.goods_id == id_cancel)
	{
		cost -= (float)(cur->data.goods_price) * (cur->data.num);
		return cur;
	}
	while (cur != NULL)
	{
		if (cur->data.goods_id == id_cancel)
		{
			pre->next = cur->next;
			flag = 0;

			// 价钱的处理
			cost -= (float)(cur->data.goods_price) * (cur->data.num);
			break;
		}
		cur = cur->next;
		pre = pre->next;
	}
	if (flag == 1)
	{
		printf("该商品不存在！");
		system("pause");
	}
	return goods_head;
}

void DisplayItemForUser(ItemNode* goods_head)
{
	ItemNode* p = goods_head->next1;
	while (p != NULL)
	{
		printf("商品编号：%-6d\t", p->thing.id);
		printf("体积：%-6d\t", p->thing.volume);
		printf("名称：%-30s\n", p->thing.brand);
		printf("每箱数量：%-6d\t", p->thing.number);
		printf("售价：%-.2f\t", p->thing.out_price);
		printf("库存：%-6d\t", p->thing.storage);
		printf("保质期（单位：天）：%-6d\n", p->thing.duration);
		putchar('\n');
		p = p->next1;
	}
	system("pause");
	return;
}

ItemNode* FindItemPos(ItemNode* head, int item_id)
{
	ItemNode* p = head;
	while (p != NULL)
	{
		if (p->thing.id == item_id)
		{
			return p;
		}
		p = p->next1;
	}
	return NULL;
}

void Settle(ItemNode* goods_head, List* cart_head, struct deal* record_head, struct userinfo* user_head)
{
	ItemNode* pItem = goods_head;
	List* pCart = cart_head->next;
	struct userinfo* pUser = user_head;
	pUser = FindUserPosById(pUser, currentUser);
	double promotion = sys.promotion;
	if (sys.promotion == 0)
	{
		sys.promotion = 1;
	}

	promotion = min(sys.promotion, sys.vip_discount[pUser->data.vip]);
	StoreItem(pItem);
	fflush(stdin);
	while (pCart != NULL)
	{
		if (pCart->data.num > 0)
		{
			WriteRecord(SALE, currentUser, pCart->data.goods_id,
				-pCart->data.num, pCart->data.goods_price,
				pCart->data.num * pCart->data.goods_price * promotion);
		}
		if (pCart->data.num < 0)
		{
			WriteRecord(REJECT, currentUser, pCart->data.goods_id,
				-pCart->data.num, pCart->data.goods_price,
				-pCart->data.num * pCart->data.goods_price * promotion);
		}
		pCart = pCart->next;
	}
	cost *= promotion;
	pUser->data.cost += cost;
	sys.asset += cost;
	SendGift(goods_head, pUser);
	UpdateVip(pUser);
	WriteToFile(user_head);
	SaveConfig();

	printf("结算成功！您本次共计消费%.2f元，欢迎下次光临！\n", cost);
	system("pause");
	cost = 0;
	return;
}

void UpdateVip(struct userinfo* info)
{
	for (int i = info->data.vip; i < 9; i++)
	{
		if (info->data.cost >= sys.vip_require[i])
		{
			info->data.vip = i;
		}
	}
	return;
}

void CheckDuration(void)
{
	ItemNode* head_item = CreateLink((ItemNode*)malloc(sizeof(ItemNode)));
	if (head_item == NULL)
	{
		return;
	}
	ItemNode* pItem = head_item->next1;
	struct deal* head_record = ReadRecord();
	struct deal* pRecord = head_record;
	if (head_item == NULL || head_record == NULL)
	{
		printf("内存不足！\n");
		system("pause");
		return;
	}
	while (pItem != NULL)
	{
		if (pItem->thing.storage == 0)
		{//库存为空则跳过检查
			pItem = pItem->next1;
			continue;
		}
		pRecord = head_record;
		struct tm* t = GetNormalTime(GetOriginalTime());
		int currentDay = t->tm_year * 365 + t->tm_mon * 30 + 30 + t->tm_mday;//当前日期
		int lastStock = 2147483647;//最后一次进货时间
		while (pRecord != NULL)
		{//扫描最后进货时间
			if (pRecord->data.reason == STOCK && pItem->thing.id == pRecord->data.item_id ||
				pRecord->data.reason == SPILT && pItem->thing.id == pRecord->data.item_id && pItem->thing.number == 1)
			{
				lastStock = pRecord->data.year * 365 + pRecord->data.month * 30 + 30 + pRecord->data.day;
			}
			pRecord = pRecord->next;
		}
		if (currentDay - lastStock > pItem->thing.duration)
		{
			printf("商品%s有%d件已经过期，请注意处理！\n", pItem->thing.brand, pItem->thing.storage);
		}
		else if (currentDay + 15 - lastStock >= pItem->thing.duration)
		{
			printf("商品%s(编号%d)有%d件即将过期，请注意处理！\n",
				pItem->thing.brand, pItem->thing.id, pItem->thing.storage);
		}
		pItem = pItem->next1;
	}
	return;
}

void ChangeItemInfo(ItemNode* goods_head)
{
	if (goods_head == NULL)
	{
		return;
	}
	ItemNode* p = goods_head->next1;
	ItemNode* q = p;
	int target_id = 0;
	int choice = 1;
	char temp[200] = { 0 };

	if (p == NULL)
	{
		printf("无可用信息！\n");
		return;
	}
	printf("请输入要更改商品信息的商品编号：");
	SafeNumberInput(&target_id);
	p = FindItemPos(p, target_id);
	if (p == NULL)
	{
		printf("商品不存在！\n");
		system("pause");
		return;
	}
	while (choice)
	{
		printf("当前信息：\n");
		printf("商品编号：%-6d\t", p->thing.id);
		printf("体积：%-6d\t", p->thing.volume);
		printf("名称：%-20s\n", p->thing.brand);
		printf("数量：%-6d\t", p->thing.number);
		printf("进价：%-14.2f\t", p->thing.in_price);
		printf("售价：%-14.2f\n", p->thing.out_price);
		printf("制造商：%-20s\t", p->thing.zhizaoshang);
		printf("供货商：%-20s\n", p->thing.gonghuoshang);
		printf("库存：%-6d\t", p->thing.storage);
		printf("保质期（单位：天）：%-6d\n", p->thing.duration);
		PrintLine(50, '-');
		printf("1-更改商品名称 2-更改每一箱的数量 3-更改体积\n4-更改进价 5-更改售价 6-更改保质期\n7-更改制造商 8-更改供货商\n");
		printf("输入以上数字以更改信息，或者输入0退出：\n");
		InputIntWithLimit(&choice, 8, 0);
		switch (choice)
		{
		case 0:
			return;
		case 1:
			printf("输入新的商品名称：");
			scanf_s("%s", temp, 100);
			while (q != NULL)
			{
				if (strcmp(temp, p->thing.brand) == 0 && p != q)
				{
					printf("商品名称已经存在！\n");
					system("pause");
					return;
				}
			}
			strcpy(p->thing.brand, temp);
			printf("修改成功！\n");
			break;
		case 2:
			printf("输入新的数量：");
			InputIntWithLimit(&p->thing.number, 2147483647, 1);
			printf("修改成功！\n");
			break;
		case 3:
			printf("输入新的体积：");
			InputIntWithLimit(&p->thing.volume, 2147483647, 1);
			printf("修改成功！\n");
			break;
		case 4:
			printf("输入新的进价：");
			InputDoubleWithLimit(&p->thing.in_price, 2147483647, 1);
			printf("修改成功！\n");
			break;
		case 5:
			printf("输入新的售价：");
			InputDoubleWithLimit(&p->thing.out_price, 2147483647, 1);
			printf("修改成功！\n");
			break;
		case 6:
			printf("输入新的保质期：");
			InputIntWithLimit(&p->thing.duration, 2147483647, 1);
			printf("修改成功！\n");
			break;
		case 7:
			printf("输入新的制造商：");
			scanf_s("%s", p->thing.zhizaoshang, 100);
			printf("修改成功！\n");
			break;
		case 8:
			printf("输入新的供货商：");
			scanf_s("%s", p->thing.gonghuoshang, 100);
			printf("修改成功！\n");
			break;
		}
		StoreItem(goods_head);
		printf("是否继续修改？输入0以退出修改程序：");
		SafeNumberInput(&choice);
	}
	return;
}

void FindItemForUser(ItemNode* goods_head)
{
	int select;
	int flag = 1;
	if (goods_head == NULL)
	{
		return;
	}
	printf("若查看商品编号，请输入1：");
	printf("\n若查看所有相同规格的商品，请输入2：");
	printf("\n若查看一箱数量相同的商品，请输入3：\n若要根据关键词查找，请输入4：\n输入其他数字以退出");
	SafeNumberInput(&select);
	PrintLine(40, '-');
	if (select > 4 || select <= 0)
	{
		return;
	}
	if (select == 1)
	{
		printf("请输入要查找的商品编号：");
		int _id3;
		int flag = 1;
		SafeNumberInput(&_id3);

		ItemNode* p = goods_head->next1;
		while (p != NULL)
		{
			if (p->thing.id == _id3)
			{
				printf("商品编号：%d\t", p->thing.id);
				printf("体积：%d\t", p->thing.volume);
				printf("名称：%s\n", p->thing.brand);
				printf("数量：%d\t", p->thing.number);
				//printf("进价：%.2f\t", p->thing.in_price);
				printf("售价：%.2f\t", p->thing.out_price);
				printf("制造商：%s\t", p->thing.zhizaoshang);
				printf("供货商：%s\n", p->thing.gonghuoshang);
				printf("库存：%d\t", p->thing.storage);
				printf("保质期（单位：天）：%d\n\n", p->thing.duration);
				flag = 0;
				break;
			}
			p = p->next1;
		}
		if (flag == 0)
		{
			int choice = 0;
			printf("查找成功，如需再次查找请输入1：");
			SafeNumberInput(&choice);
			if (choice == 1)
			{
				FindItem2(goods_head);
				return;
			}
			else
			{
				system("pause");
				return;
			}
		}
		if (flag == 1)
		{
			printf("该商品不存在!");
			system("pause");
			return;
		}
	}
	if (select == 2)
	{
		printf("请输入所要查看的规格大小：");
		int v = 0;
		SafeNumberInput(&v);
		ItemNode* pp = goods_head->next1;
		int flag2 = 1;
		while (pp != NULL)
		{
			if (pp->thing.volume == v)
			{
				printf("商品编号：%d\t", pp->thing.id);
				printf("体积：%d\t", pp->thing.volume);
				printf("名称：%s\n", pp->thing.brand);
				printf("数量：%d\t", pp->thing.number);
				//printf("进价：%.2f\t", pp->thing.in_price);
				printf("售价：%.2f\t", pp->thing.out_price);
				printf("制造商：%s\t", pp->thing.zhizaoshang);
				printf("供货商：%s\n", pp->thing.gonghuoshang);
				printf("库存：%d\t", pp->thing.storage);
				printf("保质期（单位：天）：%d\n\n", pp->thing.duration);
				flag2 = 0;
			}
			pp = pp->next1;
		}
		if (flag2 == 0)
		{
			int choice;
			printf("查找成功，如需再次查找请输入1：");
			SafeNumberInput(&choice);
			if (choice == 1)
			{
				FindItem2(goods_head);
				return;
			}
			else
			{
				system("pause");
				return;
			};
		}
		if (flag2 == 1)
		{
			printf("该类商品不存在！");
		}
		return;
	}
	if (select == 3)
	{
		printf("请输入要查找的一箱数量的数量：");
		int num = 0;
		SafeNumberInput(&num);
		ItemNode* ppp = goods_head->next1;
		int flag3 = 1;
		while (ppp != NULL)
		{
			if (ppp->thing.number == num)
			{
				printf("商品编号：%d\t", ppp->thing.id);
				printf("体积：%d\t", ppp->thing.volume);
				printf("名称：%s\n", ppp->thing.brand);
				printf("数量：%d\t", ppp->thing.number);
				//printf("进价：%.2f\t", ppp->thing.in_price);
				printf("售价：%.2f\t", ppp->thing.out_price);
				printf("制造商：%s\t", ppp->thing.zhizaoshang);
				printf("供货商：%s\n", ppp->thing.gonghuoshang);
				printf("库存：%d\t", ppp->thing.storage);
				printf("保质期（单位：天）：%d\n\n", ppp->thing.duration);
				flag3 = 0;
			}
			ppp = ppp->next1;
		}
		if (flag3 == 0)
		{
			int choice;
			printf("查找成功，如需再次查找请输入1：");
			SafeNumberInput(&choice);
			if (choice == 1)
			{
				FindItem2(goods_head);
				return;
			}
			else return;
		}
		if (flag3 == 1)
		{
			printf("该类商品不存在！");
		}
		return;
	}
	if (select == 4)
	{
		printf("请输入要查找的关键字：");
		char keyword[20] = { 0 };
		scanf_s("%s", keyword, 20);

		ItemNode* p = goods_head->next1;
		while (p != NULL)
		{

			if (IsSameNode(keyword, p->thing.brand) == 1 || IsSameNode(keyword, p->thing.gonghuoshang) == 1 || IsSameNode(keyword, p->thing.zhizaoshang) == 1)
			{
				printf("商品编号：%d\t", p->thing.id);
				printf("名称：%s\n", p->thing.brand);
				printf("体积：%d\t", p->thing.volume);
				printf("每箱数量：%d\t", p->thing.number);
				//printf("进价：%.2f\t", p->thing.in_price);
				printf("售价：%.2f\n", p->thing.out_price);
				printf("制造商：%s\t", p->thing.zhizaoshang);
				printf("供货商：%s\n", p->thing.gonghuoshang);
				printf("库存：%d\t", p->thing.storage);
				printf("保质期（单位：天）：%d\n\n", p->thing.duration);
				flag = 0;
				//break;
			}
			p = p->next1;
		}
		if (flag == 1)
		{
			printf("该商品不存在!");
		}
		system("pause");
		return;

	}
}

void LossProcess(ItemNode* goods_head)
{
	int target_item = 0, choice = 0;
	double temp = 0;
	ItemNode* p = NULL;

	printf("请输入您要处理的损耗商品编号：");
	SafeNumberInput(&target_item);
	p = FindItemPos(goods_head, target_item);
	if (p == NULL)
	{
		printf("商品不存在！\n");
		system("pause");
		return;
	}
	printf("当前选择商品%s，库存%d\n", p->thing.brand, p->thing.storage);
	printf("选择处理方式：\n1-退货 2-打折促销 3-拆分为零售\n4-丢弃 0-放弃处理并返回");
	InputIntWithLimit(&choice, 4, 0);
	switch (choice)
	{
	case 0:
		return;
	case 1:
		printf("输入退货数量：");
		InputIntWithLimit(&choice, 2147483647, 0);
		if (p->thing.storage < choice)
		{
			printf("库存不足！操作失败！\n");
			system("pause");
			return;
		}
		p->thing.storage -= choice;
		sys.asset += p->thing.in_price * choice;
		if (choice != 0)
		{
			WriteRecord(BACK, 0, p->thing.id, -choice, p->thing.in_price, p->thing.in_price * choice);
		}
		printf("操作成功！\n");
		system("pause");
		break;
	case 2:
		printf("输入打折处理的商品数量：");
		InputIntWithLimit(&choice, 2147483647, 1);
		printf("输入该种商品的折扣：(0到1之间的小数)");
		InputDoubleWithLimit(&temp, 1, 0);
		CreateSale(goods_head, p, choice, temp);
		printf("操作成功！\n");
		system("pause");
		break;
	case 3:
		printf("请输入要拆分的箱数：(目前库存：%d)", p->thing.storage);
		InputIntWithLimit(&choice, p->thing.storage, 0);
		CreateSingleItem(goods_head, choice, p);
		break;
	case 4:
		printf("请选择丢弃的数量：(目前库存：%d)", p->thing.storage);
		InputIntWithLimit(&choice, p->thing.storage, 0);
		p->thing.storage -= choice;
		printf("操作成功！\n");
		system("pause");
		break;
	}
	StoreItem(goods_head);
	SaveConfig();
	return;
}

void CreateSingleItem(ItemNode* head, int init_storage, ItemNode* original_info)
{
	ItemNode* p = head;
	if (original_info->thing.number == 1)
	{
		printf("零售商品不能拆分！\n");
		system("pause");
		return;
	}
	if (p == NULL)
	{
		return;
	}
	char temp[100] = { 0 };
	strcpy(temp, original_info->thing.brand);

	while (p->next1 != NULL && p != NULL)
	{
		p = p->next1;
	}
	if (p->next1 == NULL)
	{
		p->next1 = (ItemNode*)malloc(sizeof(ItemNode));
		p = p->next1;
		if (p == NULL)
		{
			printf("内存不足，添加失败！\n");
			return;
		}
		p->next1 = NULL;
	}
	if (p == NULL)
	{
		printf("内存不足，添加失败！\n");
		return;
	}
	
	WriteRecord(SPILT, 0, original_info->thing.id, -init_storage, 0, 0);
	original_info->thing.storage -= init_storage;
	p->thing.duration = original_info->thing.duration;
	p->thing.id = MaxItemId(head) + 1;
	p->thing.in_price = original_info->thing.in_price / original_info->thing.number;
	p->thing.number = 1;
	p->thing.out_price = original_info->thing.out_price / original_info->thing.number;
	p->thing.storage = original_info->thing.number * init_storage;
	p->thing.volume = original_info->thing.volume;
	strcpy(p->thing.brand, original_info->thing.brand);
	strcat(p->thing.brand, "（零售）");
	strcpy(p->thing.gonghuoshang, original_info->thing.gonghuoshang);
	strcpy(p->thing.zhizaoshang, original_info->thing.zhizaoshang);
	WriteRecord(SPILT, 0, p->thing.id, init_storage * original_info->thing.number, 0, 0);
	sys.max_item = p->thing.id;

	StoreItem(head);
	return;
}

void SpiltItem(ItemNode* goods_head)
{
	ItemNode* p = NULL;
	int spilt = 0;

	printf("请输入要拆分的商品编号：");
	SafeNumberInput(&spilt);
	p = FindItemPos(goods_head, spilt);
	if (p == NULL)
	{
		printf("商品不存在！\n");
		system("pause");
		return;
	}
	if (p->thing.number == 1)
	{
		printf("零售商品不能拆分！\n");
		system("pause");
		return;
	}
	if (p->thing.storage < 1)
	{
		printf("库存不足！\n");
		return;
	}
	printf("当前商品信息：编号%d，名称%s，库存%d\n", p->thing.id, p->thing.brand, p->thing.storage);
	printf("请输入要拆分的箱数：");
	InputIntWithLimit(&spilt, p->thing.storage, 0);
	if (spilt == 0)
	{
		return;
	}
	CreateSingleItem(goods_head, spilt, p);
	printf("操作成功！\n");
	system("pause");
	return;
}

void SendGift(ItemNode* goods_head, struct userinfo* user)
{
	ItemNode* head = goods_head, * pGift = goods_head;
	pGift = FindItemPos(head, sys.vip_gift[user->data.vip]);
	int gift_count = 0;//理论上应该赠送的赠品数量
	if (pGift == NULL)
	{//若这个等级的vip设置的赠品不存在，直接退出
		return;
	}
	if (sys.gift_need == 0)
	{//防止出现除以0错误
		sys.gift_need = 100;
		SaveConfig();
	}
	gift_count = (int)cost / (int)sys.gift_need;
	if (gift_count < 0)
	{//消费为负数则直接返回
		return;
	}
	if (pGift->thing.storage <= gift_count)
	{//赠品数量不足，则送完为止
		gift_count = pGift->thing.storage;
	}
	pGift->thing.storage -= gift_count;
	StoreItem(goods_head);
	WriteRecord(GIFT, currentUser, pGift->thing.id, gift_count, 0, 0);
	if (pGift->thing.number == 1)
	{
		printf("根据管理员设置，赠送您 %s %d个！\n", pGift->thing.brand, gift_count);
	}
	else
	{
		printf("根据管理员设置，赠送您 %s %d箱！\n", pGift->thing.brand, gift_count);
	}
	return;
}

void CreateSale(ItemNode* head, ItemNode* original_info, int sale_count, double discount)
{
	ItemNode* p = head;
	if (p == NULL)
	{
		return;
	}

	while (p->next1 != NULL && p != NULL)
	{
		p = p->next1;
	}
	if (p->next1 == NULL)
	{
		p->next1 = (ItemNode*)malloc(sizeof(ItemNode));
		p = p->next1;
		if (p == NULL)
		{
			printf("内存不足，添加失败！\n");
			return;
		}
		p->next1 = NULL;
	}
	if (p == NULL)
	{
		printf("内存不足，添加失败！\n");
		return;
	}

	WriteRecord(SPILT, 0, original_info->thing.id, -sale_count, 0, 0);
	original_info->thing.storage -= sale_count;
	p->thing.duration = original_info->thing.duration;
	p->thing.id = MaxItemId(head) + 1;
	p->thing.in_price = original_info->thing.in_price;
	p->thing.number = sale_count;
	p->thing.out_price = original_info->thing.out_price * discount;
	p->thing.storage = original_info->thing.number;
	p->thing.volume = original_info->thing.volume;
	strcpy(p->thing.brand, original_info->thing.brand);
	strcat(p->thing.brand, "（促销）");
	strcpy(p->thing.gonghuoshang, original_info->thing.gonghuoshang);
	strcpy(p->thing.zhizaoshang, original_info->thing.zhizaoshang);
	WriteRecord(SPILT, 0, p->thing.id, sale_count, 0, 0);
	sys.max_item = p->thing.id;
	sys.item_count++;
	SaveConfig();

	StoreItem(head);
	return;
}