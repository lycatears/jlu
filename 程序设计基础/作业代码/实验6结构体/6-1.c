/*
题目编号 ：Exp07-Basic01
题目名称：复数运算
题目描述：复数可以写成A+Bi的常规形式，其中A是实部，B是虚部，i是虚数单位，满足i^2=-1。
编写程序，分别计算两个复数的和、差、积。
输入：在一行中依次给出两个复数的实部和虚部，数字间以一个西文空格分隔。
输出：一行中按照A+Bi的格式输出两虚数的和、差、积，实部和虚部均保留2位小数；
如果B是负数，则应该写成A-|B|i的形式；如果B是零则不输出虚部；结果间以4个西文空格间隔。
样例1：
输入：
2.3 3.5 5.2 0.4
输出：
7.50+3.90i    -2.90+3.10i    10.56+19.12i
样例2：
输入：
3.3 4.5 3.3 -4.5
输出：
6.60    0.00+9.00i    31.14
*/
#include <stdio.h>
typedef struct
{
    float real;
    float imaginary;
} complexnum;
complexnum x, y;
int addc(complexnum x, complexnum y);
int mulc(complexnum x, complexnum y);
int minc(complexnum x, complexnum y);
int print(complexnum p);
int main(void)
{
    scanf("%f %f", &x.real, &x.imaginary);
    scanf("%f %f", &y.real, &y.imaginary);
    addc(x, y);
    minc(x, y);
    mulc(x, y);
    return 0;
}
int addc(complexnum x, complexnum y)
{
    complexnum result;
    result.real = x.real + y.real;
    result.imaginary = x.imaginary + y.imaginary;
    print(result);
    printf("    ");
    return 0;
}
int minc(complexnum x, complexnum y)
{
    complexnum result;
    result.real = x.real - y.real;
    result.imaginary = x.imaginary - y.imaginary;
    print(result);
    printf("    ");
    return 0;
}
int mulc(complexnum x, complexnum y)
{
    complexnum result;
    result.real = x.real * y.real - x.imaginary * y.imaginary;
    result.imaginary = x.real * y.imaginary + x.imaginary * y.real;
    print(result);
    return 0;
}
int print(complexnum p)
{
    printf("%.2f", p.real);
    if (p.imaginary < 0)
        printf("%.2fi", p.imaginary);
    if (p.imaginary > 0)
        printf("+%.2fi", p.imaginary);
    return 0;
}