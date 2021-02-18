//实现循环单链表各种基本功能（李春葆代码）
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LinkNode;                              //声明循环单链表结点类型

void CreateListF(LinkNode *&L,ElemType a[],int n){//头插法建立单链表
    LinkNode *s;
    int i;
    L=(LinkNode *)malloc(sizeof(LinkNode));         //创建头结点
    L->next=NULL;
    for(int i=0;i<n;i++){
        s=(LinkNode *)malloc(sizeof(LinkNode));      //建立新的结点
        s->data=a[i];
        s->next=L->next;                            //将结点s插在原开始结点之前，头结点之后
        L->next=s;
    }
    s=L->next;
    while(s->next!=NULL)                            //查找尾结点，由s指向它
        s=s->next;
    s->next=L;                                      //尾结点next域指向头结点
}