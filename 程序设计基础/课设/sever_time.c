#include <time.h>
#include <stdio.h>
#include <stdlib.h>

time_t original_time;       //时间原始数据
struct tm* sever_time;      //time.h 提供的结构体，以规范格式保存时间

time_t GetOriginalTime(void)
{
    //获得原始时间数据
    //参数：无
    //返回：时间原始数据
    original_time=time(NULL);
    return original_time;
}

struct tm* GetNormalTime(time_t original_time)
{
    //获得规范格式数据
    //参数：original_time 时间原始数据
    //返回：规范格式的时间数据结构体
    struct tm* normal;
    normal=localtime(&original_time);
    return normal;
}

void TimeOutput(struct tm* normaltime)
{
    //输出时间
    //参数：一个规范格式的时间结构体
    //返回：无，输出时间
    printf("%d-%d-%d %02d:%02d:%02d",
            normaltime->tm_year+1900,
            normaltime->tm_mon,
            normaltime->tm_mday,
            normaltime->tm_hour,
            normaltime->tm_min,
            normaltime->tm_sec);
    return;
}

void DateOutput(struct tm* normaltime)
{
    //在控制台打印日期信息
    //参数：包含日期信息的结构体tm*指针
    //返回：无
    printf("%d-%d-%d",
        normaltime->tm_year + 1900,
        normaltime->tm_mon + 1,
        normaltime->tm_mday);
    return;
}

void ShowTime(void)
{
    //在控制台上打印时间信息
    //输入：无
    //输出：无
    time_t original=GetOriginalTime();
    struct tm* norm=GetNormalTime(original);
    TimeOutput(norm);
    return;
}

void ShowDate(void)
{
    //在控制台上打印日期
    //输入：无
    //输出：无
    time_t original = GetOriginalTime();
    struct tm* norm = GetNormalTime(original);
    DateOutput(norm);
    return;
}