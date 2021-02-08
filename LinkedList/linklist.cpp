//带头结点的单链表
#include <stdio.h>
#include <malloc.h>
typedef struct LNode{                   //定义单链表结点类型
    ElemType data;              //每个节点存放一个数据元素
    struct LNode *next;         //指针指向下一个节点
}LNode,*LinkList;               /*LNode和*LinkList其实语法作用都是相同的，但是使用在程序中含义不一样，LNode表示的是链表中的结点
                                *LinkList表示的是链表的头指针，代表一个链表*/

bool ListInsert(LinkList &L,int i,ElemType e){          //按位序插入，在第i个位置插入元素e（带头结点）
    if(i<1)
        return false;
    /*利用代码封装的方法，使函数简洁，又利于维护
    这里调用按位查找函数
    LNode *p;                                 //指针p指向当前扫描到的结点
    int j=0;                                    //当前p指向的是第几个结点
    p=L;                                       //L指向头结点，头结点是第0个结点（不存储数据）
    while(p!=NULL && j<i-1){                    //循环找到第i-1个结点
        p=p->next;
        j++;
    }*/
    LNode *p=GetElem(L,i-1);                    //找到第i-1个结点
    /*直接使用后插法函数完成
    if(p==NULL)                                 //i值不合法
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;                                   //将结点s连接到p之后
    return true;*/
    return InsertNextNode(p,e);
}

bool ListInsert(LinkList &L,,int i,ElemType e){         //按位序插入，在第i个位置插入元素饿e（不带头结点）
    if(i<1)
        return false;
    if(i==1){                                       //插入第一个结点的操作与其他结点不同
        LNode *s=(LNode *)malloc(sizeof(LNode));
        s->data=e;
        s->next=L;  
        L=s;                                        //头指针指向新结点
        return true;
    }
    LNode *p;                                       //指针p指向当前扫描到的结点
    int j=1;                                        // 当前p指向的是第几个结点
    p=L;                                            //p指向第1个结点（注意：不是头结点）
    while(p!=NULL && j<i-1){
        p=p->next;
        j++;
    }
    if(p==NULL)
        return false;                               //i值不合法
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return true;                                    //插入成功
}
//由于单链表的链接指针只能往后寻找，如果给定的插入结点p的话，插入后，p往后的结点都是可以知道的，但是p之前的结点就莫法了
bool InsertNextNode(LNode *p,ElemType e){           //后插操作；在p结点之后插入元素e
    if(p==NULL)                                     //考虑到非法情况，提高健壮性
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));
    if(s==NULL)                                     //内存分配失败，考虑到小概率的某些情况下有可能分配失败（如内存空间不足）
        return false;
    s->data=e;                                      //用结点s保存数据元素e
    s->next=p->next;
    p->next=s;                                      //将结点s连接到p之后
    return true;
}

bool InsertPriorNode(LNode *p,ElemType e){             //前插操作：在p结点之前插入元素e,使用头天的方法
    if(p==NULL)
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));
    if(s==NULL)                                     //内存分配失败
        reutrn false;
    s->next=p->next;
    p->next=s;                                      //新结点s连接到p之后
    s->data=p->data;                                //将p中元素复制到s中
    p->data=e;                                      //p中元素覆盖为e
    return true;
}

bool ListDelete(LinkList &L,int i,ElemType &e){         //按位序删除（带头结点）
    if(i<1)
        reutrn false;
    /*调用按位查找函数
    LNode *p;
    int j=0;
    p=L;
    while(p!=NULL && j<i-1){
        p=p->next;
        j++;
    }*/
    LNode *p=GetElem(L,i-1);

    if(p==NULL)                                     //i值不合法
        return false;
    if(p->next==NULL)
        reutrn false;
    LNode *q=p->next;                               //令p指向被删除结点
    e=q->data;                                      //用e返回元素的值
    p->next=q->next;                                //将*q结点从链中断开
    free(q);                                        //释放结点的存储空间
    return true;                                    //删除成功
}
//对单链表的操作，关系到某个结点的前驱结点的时候，我们可以引入头指针，然后经过循环找到这个前驱结点，或者可以使用偷天换日的方法
bool DeleteNode (LNode *p){                         //删除指定结点p，由于p结点的前驱结点是未知的，这里采用和上次使用相同的方法，偷天换日
    if(p==NULL)
        return false;
    LNode *q=p->next;
    p->data=p->next->data;                          //这里有个小bug，如果我们要删除的结点是最后一个结点的话，那这个方法就没法用了。
    p->next=q->next;
    free(q);
    return true;
}

LNode *GetElem(LinkList L,int i){                   //按位查找，返回第i个元素（带头结点）
    if(i<0)
        return NULL;
    LNode *p;
    int j=0;
    p=LL；
    while(p!=NULL && j<i){
        p=p->next;
        j++;
    }
    return p;
}