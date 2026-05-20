/*
题目编号：Exp09-Basic01
题目名称：创建单链表
题目描述：请填写缺失代码完成程序，实现如下功能：
根据从键盘随机输入以0结束的若干非零整数，建立一个单链表；之后将此链表中保存的数字顺次输出，相邻数字间以一个西文空格间隔，最后一个数字后无任何字符；若是空链表，则输出NULL。
例如，
输入:5 4 2 1 3 0
输出:5 4 2 1 3
输入:0 5 4 2 1 3 0
输出:NULL
***注意***：
提交答案时，需粘贴完整的源代码，仅粘贴填空处的代码将被判错。
*/
#include <stdio.h>
#include <malloc.h>
struct cell
{ // 单链表结点结构体定义
    int x;
    struct cell *next;
} cell;
struct cell *build(void)
{ // 新建单链表，并将建好的单链表首结点地址返回
    struct cell *head, *tmp, *p;
    head = tmp = p = NULL;
    head = (struct cell *)malloc(sizeof(cell));
    scanf("%d", &(head->x));
    if (head->x == 0)
    {
        head = NULL;
        return head;
    }
    tmp = head;
    tmp->next = NULL;
    do
    {
        p = (struct cell *)malloc(sizeof(struct cell));
        scanf("%d", &(p->x));
        tmp->next = p;
        tmp = p;
        tmp->next = NULL;
    } while (p->x != 0);
    return head; // 返回单链表头
}
void print(struct cell *head)
{ // 打印整个单链表,head是指向单链表首结点的指针
    struct cell *p;
    printf("%d", head->x);
    p = head->next;
    while (p->x != 0)
    {
        printf(" %d", p->x);
        p = p->next;
    }
}
void release(struct cell *head)
{ // 释放单链表空间,head是指向单链表首结点的指针
    struct cell *p;
    while (head != NULL)
    {
        p = head;
        head = p->next;
        free(p);
    }
}
int main(void)
{
    struct cell *head;
    head = build();
    if (head != NULL)
        print(head);
    else
        printf("NULL");
    release(head);
}
