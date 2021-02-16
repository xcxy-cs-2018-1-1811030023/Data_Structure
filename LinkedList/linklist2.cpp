//实现单链表各种基本运算的算法（李春葆）
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LinkNode;                          

void CreateListF(LinkNode *&L,ElemType a[],int n){//头插法建立单链表
    LinkNode *s;
    L=(LinkNode *)malloc(sizeof(LinkNode));         //创建头结点
    L->next=NULL;
    for(int i=0;i<n;i++){
        s=(LinkNode *)malloc(sizeof(LinkNode));      //建立新的结点
        s->data=a[i];
        s->next=L->next;                            //将结点s插在原开始结点之前，头结点之后
        L->next=s;
    }
}

void CreateListR(LinkNode *&L,ElemType a[],int n){//尾插法建立单链表
    LinkNode *s,*r;
    L=(LinkNode *)malloc(sizeof(LinkNode));         //创建头结点
    L->next=NULL;   
    r=L;                                            //r始终指向尾结点，开始时指向头结点
    for(int i=0;i<n;i++){
        s=(LinkNode *)malloc(sizeof(LinkNode));     //创建新结点s
        s->data=a[i];
        r->next=s;                                  //将结点s插入r结点之后
        r=s;
    }
    r->next=NULL;                                   //尾结点next域设置为NULL
}

void InitList(LinkNode *&L){                        //初始化链表
    L=(LinkNode *)malloc(sizeof(LinkNode));         //创建头结点
    L->next=NULL;                                   //将单链表设置为空表
}

void DestroyList(LinkNode *&L){                     //销毁单链表
    LinkNode *pre=L,*p=pre->next;
    while(p!=NULL){
        free(pre);
        pre=p;                                      //pre,p同步后移一个结点
        p=pre->next;
    }
    free(pre);                                      //此时p为NULL，pre指向尾结点，释放它
}

bool ListEmpty(LinkNode *L){                       //判断单链表是否为空
    return(L->next==NULL);
}

int ListLength(LinkNode *L){                        //求单链表的长度
    int i=0;
    LinkNode *p=L;                                  //P指向头结点，i设置为0(即头结点的序号为0)
    while(p->next!=NULL){
        i++;
        p=p->next;
    }
    return(i);                                      //循环结束，p指向尾结点，其序号i为结点个数
}

void DispList(LinkNode *L){                         //输出单链表
    LinkNode *p=L->next;                            //p指向首结点
    while(p!=NULL){                                 //p不为NULL，输出p结点的data域
        printf("%c",p->data);
        p=p->next;                                  //p移向下一个结点
    }
    printf("\n");
}

bool GetElem(LinkNode *L,int i,ElemType &e){         //求线性表中第i个元素值
    int j=0;
    LinkNode *p=L;                                  //p指向头结点，j设置为0(即头结点的序号为0)
    if(i<0) return false;                           //i错误返回假
    while(j<i && p!=NULL){                          //找第i个结点P
        j++;
        p=p->next;
    }
    if(p==NULL)                                     //不存在第i个数据结点，返回false
        return false;
    else{                                           //存在第i个数据结点,返回true
        e=p->data;  
        return true;
    }
}

int LocateElem(LinkNode *L,ElemType e){                 //查找第一个值域为e的元素序号
    int i=1;
    LinkNode *p=L->next;                                //p指向首结点，i设置为1（即首结点的序号为1）
    while(p!=NULL && p->data!=e){                       //查找data值为e的结点，其序号为1
        p=p->next;
        i++;
    }
    if(p==NULL)
        return(0);                                      //不存在值为e的结点，返回0
    else
        return(i);                                      //存在值为e的结点，返回其逻辑序号i
}

bool ListInsert(LinkNode *&L,int i,ElemType e){         //插入第i个元素
    int j=0;
    LinkNode *p=L,*s;                                   //p指向头结点，j设置为0（即头结点的序号为0）
    if(i<=0) return false;                              //i错误返回假
    while(j<i-1 && p!=NULL){                            //查找第i-1个结点p
        j++;
        p=p->next;
    }
    if(p==NULL)                                         //未找到第i-1个结点，返回false
        return false;
    else{                                               //找到第i-1个结点p,插入新结点并返回true
        s=(LinkNode *)malloc(sizeof(LinkNode));
        s->data=e;                                      //创建新结点s,其data域值设置为e
        s->next=p->next;                                //将结点s插入到结点p之后
        p->next=s;
        return true;
    }
}

bool ListDelete(LinkNode *&L,int i,ElemType &e){        //删除第i个元素
    int j=0;
    LinkNode *p=L,*q;                                   //p指向头结点，j设置为0(即头结点的序号为0)
    if(i<=0) return false;                              //i错误返回假
    while(j<i-1 && p!=NULL){                            //查找第i-1个结点
        j++;
        p=p->next;
    }
    if(p==NULL)                                        //未找到第i-1个结点，返回false
        return false;
    else{                                               //找到第i-1个结点p
        q=p->next;                                      //q指向第i个结点
        if(q==NULL)                                     //若不存在第i个结点，返回false
            return false;
        e=q->data;
        p->next=q->next;                                //从单链表中删除q结点
        free(q);                                        //释放q结点
        return true;                                    //返回true表示成功删除第i个结点
    }
}

int main(){
    LinkNode *h;
    ElemType e;
    printf("单链表的基本运算如下：\n");
    printf("    (1)初始化单链表h\n");
    InitList(h);
    printf("    (2)依次采用尾插法插入a,b,c,d,e元素\n");
    ListInsert(h,1,'a');
    ListInsert(h,2,'b');
    ListInsert(h,3,'c');
    ListInsert(h,4,'d');
    ListInsert(h,5,'e');
    printf("    (3)输出单链表h:");DispList(h);
    printf("    (4)单链表的长度：%d\n",ListLength(h));
    printf("    (5)单链表h为%s\n",(ListEmpty(h)?"空":"非空"));
    GetElem(h,3,e);
    printf("    (6)单链表h的第3个元素：%c\n",e);
    printf("    (7)元素a的位置:%d\n",LocateElem(h,'a'));
    printf("    (8)在第4个元素位置上插入f元素\n");
    ListInsert(h,4,'f');
    printf("    (9)输出单链表h:");DispList(h);
    printf("    (10)删除h的第3个元素\n");
    ListDelete(h,3,e);
    printf("    (11)输出单链表h:");DispList(h);
    printf("    (12)释放单链表h\n");
    DestroyList(h);
    return 1;
}