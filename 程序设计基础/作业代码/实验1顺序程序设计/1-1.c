/*
表达式计算。
问题描述：编写程序，计算并输出如下表达式的值：
【作者注，非原题内容】注意，如果您不理解下面这一行的内容，请复制到在线LaTeX编辑器中查看：
y=\dfrac{\sin x}{ax} + \left | \cos \dfrac{\pi x}{2} \right |
其中a,x,y均为float类型，取值为3.1415926。输出结果要求保留小数点后3位。
提示：使用数学函数应括入math.h头文件，正弦、余弦和求绝对值对应的数学函数名分别为sin，cos和fabs。注意区分C语言表达式与数学表达式的差别哦。
输入：依次输入a和x
输出:  y的值
样例1：
输入：3.1 40
输出：1.006
样例2：
输入：1.6 21
输出：0.025
样例3：
输入：-4.2 40
输出：0.996
*/
#include <stdio.h>
#include <math.h>
#define pai 3.1415926
int main(void)
{
    float a, x, y;
    scanf("%f%f", &a, &x);
    y = (sin(x) / (a * x)) + fabs(cos(pai * x / 2));
    printf("%.3f", y);
}
