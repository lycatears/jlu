#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include "defines.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)

extern struct sysconfig sys;
extern HANDLE hout;

void ClearBuffer(void)
{
    //清空缓冲区，防止死循环。用于异常处理
    //输入：无
    //输出：无
    char b = 0;

    do
    {
        scanf("%c", &b);

    } while (b != '\n');

    return;
}

void InitNew(void)
{
    //刷新界面
    //输入：无
    //输出：无
    _flushall();
    ClearBuffer();
    system("cls");

    return;
}

void PrintLine(int n, char c)
{
    //打印指定数量的字符
    //输入：字符数量，字符
    //输出：无

    int i = 0;
    for (i = 0; i < n; i++)
    {
        putchar(c);
    }
    putchar('\n');
    return;
}

int SafeNumberInput(int* target)
{
    //安全输入整数
    //输入：整型变量指针
    //输出：整型变量的值
    double temp = 0;
    fflush(stdin);
    while (1)
    {
        int r = scanf_s("%lf", &temp);
        if (r != 0)
        {
            *target = (int)temp;
            fflush(stdin);
            _flushall();
            return *target;
        }
        else
        {
            printf(COLOR_ERR"非法输入，请重试！\n"COLOR_CLEAR);
            ClearBuffer();
            fflush(stdin);
        }
    }
    ClearBuffer();
}

double SafeDoubleInput(double* target)
{
    //安全输入浮点数
    //输入：双精度浮点型变量指针
    //输出：双精度变量的值
    int r = 0;
    fflush(stdin);
    while (1)
    {
        r = scanf_s("%lf", target);
        if (r != 0)
        {
            return *target;
        }
        else
        {
            printf(COLOR_ERR"非法输入，请重试！\n"COLOR_CLEAR);
            ClearBuffer();
        }
    }
}

int Max(int x, int y)
{
    if (x >= y)
    {
        return x;
    }
    return y;
}

int Min(int x, int y)
{
    if (x <= y)
    {
        return x;
    }
    return y;
}

void SaveConfig(void)
{
    //保存系统配置
    //输入：无
    //输出：无
    FILE* sys_config = fopen("config.dat", "wb");
    fwrite(&sys, sizeof(sys), 1, sys_config);
    fclose(sys_config);
    return;
}

int InputIntWithLimit(int* target, int max, int min)
{
    //有最大值、最小值限制输入整数
    //输入：存放整数的指针，最大值，最小值
    //输出：按要求输入的整数
    while (1)
    {
        SafeNumberInput(target);
        if (*target <= max && *target >= min)
        {
            fflush(stdin);
            return *target;
        }
        else
        {
            printf(COLOR_ERR"非法输入，请重试！\n"COLOR_CLEAR);
            ClearBuffer();
        }
    }
}

int TimeCheck(int year, int month, int day, int hour, int minute)
{
    //检查时间数据是否合法
    //输入：年月日时分五个时间数据
    //输出：若合法输出1，不合法输出0
    if (hour >= 24 || hour < 0 || minute >= 60 || minute < 0)
    {
        return 0;
    }
    if (day > 31 || day <= 0)
    {
        return 0;
    }
    if (month > 12 || month < 1)
    {
        return 0;
    }
    if (year > 9999 || year < 1900)
    {
        return 0;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30 || day < 1)
        {
            return 0;
        }
    }
    if (month == 2)
    {
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        {
            if (day > 29)
            {
                return 0;
            }
        }
        else
        {
            if (day > 28)
            {
                return 0;
            }
        }
    }
    return 1;
}

int VerifyCode(void)
{
    //在用户登陆时生成并要求验证码
    //输入：无
    //输出：若正确输入，返回1；若不正确，返回0
    int a = 0, b = 0, result = 0;
    srand((UINT)time(0));
    a = rand() % 20;
    b = ((int)(sin(a) * 100)) % 10;
    b = abs(b);
    if (a % 2 == 1)
    {
        printf("请输入验证码：（计算以下算式结果）");
        printf("%d+%d=", a, b);
        SafeNumberInput(&result);
        if (result == (a + b))
        {
            return 1;
        }
        else
        {
            printf("验证码错误！\n");
            system("pause");
            return 0;
        }
    }
    if (a % 2 == 0)
    {
        printf("请输入验证码：（计算以下算式结果）");
        if (a >= b)
        {
            printf("%d-%d=", a, b);
        }
        else
        {
            printf("%d-%d=", b, a);
        }
        SafeNumberInput(&result);
        if (result == abs(a - b))
        {
            return 1;
        }
        else
        {
            printf("验证码错误！\n");
            system("pause");
            return 0;

        }
    }
    return 0;
}

void HiddenPassword(char password[])
{
    //输入密码专用函数，在控制台上显示星号
    //输入：密码字符串指针
    //输出：无
    int i = 0, flag = 0;
    char input;
    while (i<17)//可以控制while循环次数，但这里写成了只能通过回车结束函数使用。
    {
        if ((input = getch()) != '\r')//结束条件
        {
            if (input != '\b')
            {
                *(password + i++) = input;//通过指针给数组赋值
                printf("*");//回显*号
                fflush(stdin);
                flag++;
            }
            if (input == '\b' && flag != 0)//为了不让\b \b也删除掉输入密码前的提示文字即判断flag是否为0
            {
                flag--;//如果用户想要backspace，那么flag自减
                i--;//使指针向前移动一格
                printf("\b \b");
            }
        }
        else
        {
            *(password + i) = '\0';//\0不能忘记
            fflush(stdin);
            printf("\n");
            return;//函数调用结束

        }
    }
}

void Gotoxy(HANDLE hout, int x, int y)
{
    //将控制台光标移动到指定位置
    //输入：控制台窗口句柄，指定的坐标
    //输出：无

    COORD pos = { 0,0 };
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hout, pos);//调用了Windows API 移动控制台光标
    return;
}

void PrintToxy(char* text, int x, int y)
{
    //在指定位置输出字符串
    //输入：字符串内容，指定的坐标
    //输出：无
    Gotoxy(hout, x, y);
    printf("%s", text);

    return;
}//备注：换行需要调用时自行输入

double InputDoubleWithLimit(double* target, double max, double min)
{
    //有最大值、最小值限制输入整数
    //输入：存放整数的指针，最大值，最小值
    //输出：按要求输入的整数
    while (1)
    {
        SafeDoubleInput(target);
        if (*target <= max && *target >= min)
        {
            return *target;
        }
        else
        {
            printf(COLOR_ERR"非法输入，请重试！\n"COLOR_CLEAR);
        }
    }
}