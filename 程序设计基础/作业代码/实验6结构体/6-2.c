/*
【计2016级期末试题】构造一个表示教师的结构体（包含3个字段：姓名、性别、年龄），编写函数，读入n个教师的信息，存入一个结构体数组中（如下图所示）。最后输出第n/2个教师的信息。
例如：一个教师的信息为zhangsan、false、50，另一个教师的信息为lisi、false、37。
输入：依次输入一个正整数n及n个教师的姓名、性别、年龄。（说明：n不大于10；姓名长度不超过20个英文字符；性别输入0/1表示女/男）。
输出：数组下标为n/2的教师信息。（说明：n/2直接截取整数，不进行四舍五入；性别输出Female/Male表示女/男；每个数据后均有1个空格）。
样例1：
输入：1 zhangsan 0 50
输出：zhangsan Female 50
样例2：
输入：4 zhangsan 0 50 lisi 1 28 wangwu 0 30 zhaoliu 1 34
输出：wangwu Female 30
样例3：
输入：5 zhangsan 0 50 lisi 1 28 wumei 0 30 zhaoliu 1 34 wangermazi 1 18
输出：wumei Female 30
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char name[20];
    int sex;
    int age;
} teacher;
int n, i;
teacher a[10];
int main(void)
{
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%s", &a[i].name);
        scanf("%d", &a[i].sex);
        scanf("%d", &a[i].age);
    }
    printf("%s ", a[n / 2].name);
    if (a[n / 2].sex == 0)
    {
        printf("Female ");
    }
    if (a[n / 2].sex == 1)
    {
        printf("Male ");
    }
    printf("%d", a[n / 2].age);
}
