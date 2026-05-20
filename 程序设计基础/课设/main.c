#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>
#include <time.h>
#include "sever_time.h"
#include "defines.h"
#include "userman.h"
#include "good.h"
#include "public.h"
#include "record.h"

#pragma warning(disable:6031)
#pragma warning(disable:4996)

//#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004;      //Windows API，为控制台启用颜色支持

/*全局变量列表*/
HANDLE hout;
int permission = 0;
FILE* sys_config;//系统配置
FILE* customer_info;//客户信息
FILE* item_info;//商品信息
struct sysconfig sys;
int currentUser = 0;


/*函数原型列表*/
void Init(void);
void LoadDefault();
DWORD EnableColorful(void);
int LoginMenu(void);
void AdminMain(void);
int YNChoice(void);
int UserLogin(void);
int AdminLogin(void);
void End(void);

int main(void)
{
    Init();
    LoginMenu();//从登录函数处获得权限信息
    End();
}

void Init(void)
{
    //在启动管理系统时，加载系统配置，打开必需的文件，并检查文件是否有缺失。
    //输入：无
    //输出：无
    //以下为检查文件完整性代码
    sys_config = fopen("config.dat", "rb");
    customer_info = fopen("user.txt", "a+");
    item_info = fopen("good.txt", "a+");

    hout = GetStdHandle(STD_OUTPUT_HANDLE);//使用Windows API 得到窗口句柄
    EnableColorful();//启用转义序列
    if (sys_config == NULL)
    {
        printf(COLOR_ERR"警告：系统配置文件config.dat文件丢失，已使用默认系统配置。"COLOR_CLEAR);
        sys_config = fopen("config.dat", "wb");
        LoadDefault();
        fwrite(&sys, sizeof(struct sysconfig), 1, sys_config);
        Sleep(2000);
    }
    else
    {
        fread(&sys, sizeof(struct sysconfig), 1, sys_config);
    }

    if (customer_info == NULL)
    {
        printf(COLOR_ERR"警告：用户信息文件user.txt文件丢失，已使用默认系统配置。"COLOR_CLEAR);
        customer_info = fopen("user.txt", "w");
        fprintf(customer_info, "1 200 矿泉水 12 39.00 58.50 康师傅 康师傅 500 360");
        fprintf(customer_info, "2 500 啤酒 18 96.00 144.00 啤酒一厂 青岛啤酒有限公司 500 65");
        fclose(customer_info);
        fopen("item.txt", "r");
        Sleep(2000);
    }

    if (item_info == NULL)
    {
        printf(COLOR_ERR"警告：商品信息文件good.txt文件丢失，已使用默认系统配置。"COLOR_CLEAR);
        item_info = fopen("good.txt", "w");
        fprintf(item_info, "1 李四 888.000000 1 123sa\n");
        fprintf(item_info, "2 张三 999.000000 1 456df\n");
        fclose(item_info);
        fopen("good.txt", "r");
        Sleep(2000);
    }

    _fcloseall();
    //以下检查系统状态
    struct userinfo* head = CreateChain();
    sys.user_count=UserCount(head);
    ReleaseList(head);
    struct ItemNode* head1 = CreateLink((ItemNode*)malloc(sizeof(ItemNode)));
    sys.item_count = Max(sys.item_count, ItemCount(head1));
    sys.max_user = Max(sys.max_user, MaxUserId(head));
    sys.max_item = Max(sys.max_item, MaxItemId(head1));
    //以下检查固定支出
    struct deal* record_head = ReadRecord();
    struct deal* p = record_head;
    struct tm* t = GetNormalTime(GetOriginalTime());
    int pay_rent = 0;
    while (p != NULL)
    {
        if (p->data.reason == RENT && p->data.year == t->tm_year && p->data.month == t->tm_mon && p->data.day == t->tm_mday)
        {
            pay_rent = 1;
        }
        p = p->next;
    }
    if (pay_rent == 0)
    {
        sys.asset -= sys.rent;
        WriteRecord(RENT, 0, 0, 0, 0, -sys.rent);
        SaveConfig();
    }

    return;
}

void LoadDefault(void)
{
    //加载默认的系统配置
    //输入：无
    //输出：无
    sys.asset = 1e6;
    sys.backup_status = 1;
    sys.board_status = 1;
    sys.item_count = 0;
    sys.rent = 0;
    sys.user_count = 0;
    sys.max_user = 0;
    sys.max_item = 0;
    sys.max_list = 100;
    sys.promotion = 1.0;
    strcpy(sys.admin_name, "admin");
    strcpy(sys.admin_pwd, "admin");
    for (int i = 0; i < 9; i++)
    {
        sys.vip_require[i] = 1000 * i;
    }
    for (int i = 0; i < 9; i++)
    {
        sys.vip_discount[i] = 1 - 0.02 * i;
    }
    for (int i = 0; i < 9; i++)
    {
        sys.vip_gift[i] = 0;
    }
    sys.gift_need = 200;
    return;
}

DWORD EnableColorful(void)
{
    //为传统控制台启用颜色支持
    //输入：无
    //输出：状态值
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }
    return 0;

}

int LoginMenu(void)
{
    //显示登录菜单
    //输入：无
    //输出：权限等级
    int isFirstRun = 1;//是否为第一次显示主菜单

    while (1)//主界面显示
    {
        _flushall();
        system("cls");
        PrintLine(60, '=');
        PrintToxy(COLOR_NOTE"欢迎使用酒水管理系统\n"COLOR_CLEAR, 20, 1);
        PrintLine(60, '=');
        PrintToxy("[1] 客户登录\n", 25, 3);
        PrintLine(60, '-');
        PrintToxy("[2] 管理员登录\n", 24, 5);
        PrintLine(60, '-');
        PrintToxy("[3] 退出系统\n", 25, 7);
        PrintLine(60, '-');
        printf(COLOR_NOTE"    当前日期：");
        ShowDate();
        printf(COLOR_CLEAR"\n");
        PrintLine(60, '=');
        for (int i = 1; i <= 9; i += 2)
        {
            PrintToxy("*", 0, i);
            PrintToxy("*", 59, i);
        }
        Gotoxy(hout, 0, 11);
        printf("请您选择登录选项");

        if (isFirstRun == 0)
        {
            ClearBuffer();
            _flushall();
        }
        
        SafeNumberInput(&permission);
        isFirstRun = 0;
        
        switch (permission)
        {
        case 1:
            if (UserLogin())
            {
                return 1;
            }
            else break;
        case 2:
            if (AdminLogin())
            {
                return 2;
            }
            else break;
        case 3:
            return 0;
        default:
            printf(COLOR_ERR"非法输入，请重试。"COLOR_CLEAR);
            Sleep(1000);
        }

    }
}

int UserLogin(void)
{
    //负责用户登录
    //输入：无
    //输出：状态码
    int choice = 0;
    int IsFirstRun = 1;
    char targetUser[30] = { 0 };
    char userPassword[16] = { 0 };
    struct userinfo* head = CreateChain();
    struct userinfo* target = NULL;

    while (1)
    {
        InitNew();

        PrintLine(60, '=');
        PrintToxy(COLOR_NOTE"用户登录\n"COLOR_CLEAR, 26, 1);
        PrintLine(60, '-');
        PrintToxy("[1] 登录账号\n", 24, 3);
        PrintLine(60, '-');
        PrintToxy("[2] 注册新用户\n", 23, 5);
        PrintLine(60, '-');
        PrintToxy("[3] 返回\n", 26, 7);
        PrintLine(60, '=');
        if (sys.promotion < 1)
        {
            printf("全场优惠%d%%！\n", 100 - (int)(sys.promotion * 100));
        }
        for (int i = 1; i <= 7; i += 2)
        {
            PrintToxy("*", 0, i);
            PrintToxy("*", 59, i);
        }

        Gotoxy(hout, 0, 11);
        printf("请选择：");
        InputIntWithLimit(&choice, 3, 1);
        switch (choice)
        {
        case 1:
            printf("请输入用户名：");
            scanf_s("%s", targetUser, 16);
            target = FindUserPos(head, targetUser);
            if (target == NULL)
            {
                return 0;
            }
            printf("请输入密码：");
            HiddenPassword(userPassword);
            //scanf_s("%s", userPassword);
            if (strcmp(userPassword, target->data.password) != 0)
            {
                printf("密码错误！\n");
                system("pause");
                return 0;
            }
            if (VerifyCode() == 1)
            {
                currentUser = target->data.id;//记录当前用户id
                UserMain();
                return 0;
            }
            break;
        case 2:
            NewUser();
            return 0;
        case 3:
            return 0;
        }
    }
}

int AdminLogin(void)
{
    char pwd[16] = { 0 };
    char adm[1000] = { 0 };

    printf("请输入管理员账号：");
    scanf_s("%s", adm, 16);
    adm[16] = 0;
    if (strcmp(adm, sys.admin_name) != 0)
    {
        printf("账号错误！\n");
        system("pause");
        return 0;
    }
    printf("请输入管理员密码：");
    HiddenPassword(pwd);
    if (strcmp(pwd, sys.admin_pwd) != 0)
    {
        printf("密码错误！");
        system("pause");
        return 0;
    }
    if (VerifyCode() == 0)
    {
        return 0;
    }
    AdminMain();
    return 0;
}

int YNChoice(void)
{
    //提供Y/N选择
    //输入：无
    //输出：用户选择Y，返回1；否则返回0
    char choice;
    int isFirstRun = 1;
    
    while (1)
    {
        if (isFirstRun == 0)
        {
            ClearBuffer();
            _flushall();
        }

        scanf_s("%c", &choice, 1);
        isFirstRun = 0;

        switch (choice)
        {
        case 'Y':
        case 'y':
            return 1;
        case 'N':
        case 'n':
            return 0;
        default:
            continue;
        }
    }
    
    return -1;
}

void End(void)
{
    //关闭所有文件并备份，做好关闭系统前的处理。
    //输入：无
    //输出：无
    if (sys.backup_status != 0)
    {
        BackupAll();
    }
    system("attrib +H *.bak");
    _fcloseall();
    return;
}

