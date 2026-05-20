/*
求两个给定整数之和。
问题描述：以下程序实现在屏幕上输出两个给定整数之和，请补全如下代码。
提示：
1.请仔细看样例，输出结果33的前后没有空格、换行等字符，程序中不要随意添加哦；
2.提交时需拷贝补全后的完整程序代码，不能只拷贝补充的代码行哦。
#include <stdio.h>
int main(void){
   int data1,data2;//用于存储给定的2个整数
   data1=13;//为data1赋值
   data2=data1+7;//为data2赋值
   printf(                         );//补全括号内的代码，输出两个整数之和
   return 0;
}
输入：无
输出：2个给定整数的和
样例1：
输入：无
输出：33
*/
#include <stdio.h>
int main(void)
{
    int data1, data2;
    data1 = 13;
    data2 = data1 + 7;
    printf("%d", data1 + data2);
    return 0;
}