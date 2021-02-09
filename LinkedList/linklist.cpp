/*
    单链表分为带头节点的，和不带头结点的两种形式。
    带头结点的单链表：由头指针指向第0个结点（也就是头结点，这个结点不存储数据，其next指针指向第1个结点，也就是从第1个结点开始存储数据）
    不带头结点的单链表：由头指针指向第1个结点，头指针指向的结点就是数据存储的开始结点。
    平常使用中，常用带头结点的单链表，因为此类型操作起来更简单。当然考试，具体还是要看题目要求了。
    **/

#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct LNode{                   //定义单链表结点类型
    ElemType data;              //每个节点存放一个数据元素
    struct LNode *next;         //指针指向下一个节点
}LNode,*LinkList;               /*
                                    LNode和*LinkList其实语法作用都是相同的，但是使用在程序中含义不一样，LNode表示的是链表中的结点
                                    *LinkList表示的是链表的头指针，代表一个链表。这样代码具有易读性。
                                */

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


/*具体是带头结点，还是不带头结点还是要根据题目要求
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
*/


//由于单链表的链接指针只能往后寻找，如果给定的插入结点p的话，插入后，p往后的结点都是可以知道的，但是p之前的结点就莫法了
bool InsertNextNode(LNode *p,ElemType e){           //后插操作；在p结点之后插入元素e
    if(p==NULL)                                     //考虑到非法情况，提高健壮性，因为在其他函数中，可能会调用这个函数，而传入的指针参数可能是空指针NULL
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

LNode *LocateElem(LinkList L,ElemType){//按值查找
    LNode *p=L->next;                   //从第一个结点开始查找数据域为e的结点
    while(p!=NULL && p->data!=e)
        p=p->next;
    return p;
}

int Length(LinkList L){//求表的长度（带头结点）
    int len=0;
    LNode *p=L;
    while(p->next!=NULL){
        p=p->next;
        len++;
    }
    return len;
}

//尾插法建立单链表（带头结点）
LinkList List_TailInsert(LinkList &L){      //正向建立单链表
    int x;                                   //要插入的元素数据域的值
    L=(LinkList)malloc(sizeof(LNode));         //初始化空表（建立头结点）
    L->next=NULL;                               //虽然这里不影响，但是我们要养成好习惯，只要是初始化单链表，都先把头指针指向NULL
    LNode *s,*r=L;                             //r为表尾元素
    scanf("%d",&x);                             //输入结点的值
    while(x!=8888){                             //输入8888表示结束
                                                //在r结点之后插入元素x
        s=(LNode*)malloc(sizeof(LNode));
        s->data=x;
        r->next=s;
        r=s;                                    //r指向新的表尾结点（永远保持r指向最后一个结点
        scanf("%d",&x);
    }
    r->next=NULL;                               //尾结点指针置空
    return L;
}

//头插法建立单链表（头插法的重要应用：链表的逆置
LinkList List_HeadInsert(LinkList &L){//逆向建立单链表
    LNode *s;
    int x;
    L=(LinkList)malloc(sizeof(LNode));//建立头结点
    L->next=NULL;                       //初始为空链表
    scanf("%d",&x);                      //输入结点的值
    while(x!=8888){
        s=(LNode*)malloc(sizeof(LNode));//创建新的结点
        s->data=x;
        s->next=L->next;
        L->next=s;                      //将新结点插入表中，L为头指针
        scanf("%d",&x);
    }
    return L;
}
