/*
题目编号：Exp09-Basic04
题目名称：单链表交换两结点
题目描述：请填写缺失代码完成程序，实现如下功能：
首先根据键盘随机输入，以0结束的若干非零整数建立单链表；
然后根据输入的两个索引位置交换链表上的两个结点（链表首元素索引为1,且要交换的两个索引位置不相邻）；
最后链表各结点值输出，相邻数字间以一个西文空格间隔，最后一个数字后无任何字符。
若是空链表，则输出NULL。
例如，
输入:1 2 3 4 5 6 0 1 5
输出：5 2 3 4 1 6
输入:0 1 2 3 4 5 6 0 1 5
输出：NULL
***注意***：
提交答案时，需粘贴完整的源代码，仅粘贴填空处的代码将被判错。
*/
#include <stdio.h>
#include <malloc.h>
struct cell // 单链表结点结构体定义
{
    int x;
    struct cell *next;
};
struct cell *build(void) // 新建单链表，并将建好的单链表首结点地址返回
{
    struct cell *head, *tmp, *p;
    head = tmp = p = NULL;
    head = (struct cell *)malloc(sizeof(struct cell));
    scanf("%d", &head->x);
    tmp = head;
    tmp->next = NULL;
    if (head->x == 0)
    {
        head = NULL;
    }
    else
    {
        do
        {
            p = (struct cell *)malloc(sizeof(struct cell));
            scanf("%d", &p->x);
            if (p->x == 0)
            {
                break;
            }
            tmp->next = p;
            tmp = p;
            tmp->next = NULL;
        } while (p->x != 0);
    }
    return head; // 返回单链表头
}
struct cell *swap(struct cell *head, int m, int n) // 交换索引为m和n的两个结点，head是单链表首结点指针
{
    if (head == NULL)
        return NULL;
    struct cell *pm = head, *pn = head;
    struct cell *pm0 = NULL, *pn0 = NULL;
    struct cell *tmp;
    int i;
    for (i = 1; i < m && pm != NULL; i++) /// 使得pm指针指向索引为m处
    {
        pm0 = pm;
        pm = pm->next;
    }
    for (i = 1; i < n && pn != NULL; i++) /// 使得pn指针指向索引为n处
    {
        pn0 = pn;
        pn = pn->next;
    }
    if (pm != NULL && pn != NULL && m != n) // 索引为m,n的结点位于链表中间
    {
        if (pm0 != NULL && pn0 != NULL)
        {
            tmp = pm->next;
            pm->next = pn->next;
            pn->next = tmp;
            pm0->next = pn;
            pn0->next = pm;
            pm = pm0->next;
            pn = pn0->next;
        }
        if (pm0 == NULL && pn0 != NULL)
        {
            head = pn;
            tmp = pn->next;
            pn->next = pm->next;
            pn0->next = pm;
            pm->next = tmp;
        }
        if (pm0 != NULL && pn0 == NULL)
        {
            head = pm;
            tmp = pm->next;
            pm->next = pn->next;
            pm0->next = pn;
            pn->next = tmp;
        }
    }
    return head;
}
void print(struct cell *head) // 打印整个单链表,head是单链表首结点指针
{
    struct cell *p = head->next;
    printf("%d", head->x);
    while (p->x != 0 && p != NULL)
    {
        printf(" %d", p->x);
        p = p->next;
        if (p == NULL)
        {
            break;
        }
    }
}
void release(struct cell *head) // 释放单链表空间,head是单链表首结点指针
{
    struct cell *p = NULL, *q = NULL;
    p = head;
    q = p;
    if (head != NULL)
    {
        do
        {
            q = p;
            p = p->next;
            free(q);
        } while (p != NULL);
    }
}
int main(void)
{
    struct cell *head;
    int m, n;
    head = build();
    scanf("%d%d", &m, &n);
    head = swap(head, m, n);
    if (head != NULL)
        print(head);
    else
        printf("NULL");
    release(head);
    return 0;
}