//实现循环双链表各种基本运算算法（李春葆代码）
//实现双链表各种功能，李春葆代码
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct DNode{
    ElemType data;
    struct DNode *prior;                    //指向前驱结点
    struct DNode *next;                     //指向后继结点
}DLinkNode;                                 //声明双链表结点类型

void CreateListF(DLinkNode *&L,ElemType a[],int n){         //头插法建立双链表
    DLinkNode *s;
    L=(DLinkNode *)malloc(sizeof(DLinkNode));               //创建头结点
    L->next=NULL;
    for(int i=0;i<n;i++){
        s=(DLinkNode *)malloc(sizeof(DLinkNode));           //创建新结点
        s->data=a[i];
        s->next=L->next;                                    //将结点s插在原开始结点之前，头结点之后
        if(L->next!=NULL)   
            L->next->prior=s;
        L->next=s;
        s->prior=L;
    }
    s=L->next;
    while(s->next!=NULL)                                    //找到尾结点，由s指向它
        s=s->next;
    s->next=L;                                              //尾结点next域指向头结点
    L->prior=s;                                             //头结点的prior域指向尾结点
}

void CreateListR(DLinkNode *&L,ElemType a[],int n){         //尾插法建立双链表
    DLinkNode *s,*r;
    L=(DLinkNode*)malloc(sizeof(DLinkNode));                //创建头结点
    L->next=NULL;
    r=L;                                                    //r始终指向尾结点，开始时指向头结点
    for(int i=0;i<n;i++){
        s=(DLinkNode*)malloc(sizeof(DLinkNode));            //创建新结点
        s->data=a[i];
        r->next=s;                          
        s->prior=r;                                         //将结点s插入结点r之后
        r=s;                
    }
    r->next=L;                                           //尾结点next域指向头结点
    L->prior=r;                                          //头结点的prior域指向尾结点
}

void InitList(DLinkNode *&L){                               //初始化双链表
    L=(DLinkNode*)malloc(sizeof(DLinkNode));                //创建头结点
    L->prior=L->next=L;
}

void DestroyList(DLinkNode *&L){                            //销毁线性表
    DLinkNode *pre=L,*p=pre->next;
    while(p!=L){
        free(pre);                                          //pre,p同步后移一个结点
        pre=p;
        p=pre->next;
    }
    free(pre);                                              //此时p=L,pre指向尾结点，释放它
}

bool ListEmpty(DLinkNode *L){                               //判断双链表是否为空表
    return(L->next==L);
}

int ListLength(DLinkNode *L){                               //求线性表的长度
    DLinkNode *p=L;
    int i=0;                                                
    while(p->next!=L){                                  
        i++;                                                
        p=p->next;
    }
    return(i);                                              //循环结束，p指向尾结点，其序号i为结点个数
}

void DispList(DLinkNode *L){                                //输出双链表
    DLinkNode *p=L->next;
    while(p!=L){
        printf("%c",p->data);
        p=p->next;
    }
    printf("\n");
}

bool GetElem(DLinkNode *L,int i,ElemType &e){               //求线性表中第i个元素值
    int j=1;
    DLinkNode *p=L->next;
    if(i<=0 || L->next==L)
        return false;                                       //i错误或者L为空表返回假
    if(i==1){                                               //i=1作为特殊情况处理
        e=L->next->data;
        return true;
    }
    else{                                                   //i不为1时
        while(j<i-1 && p!=L){                               //查找第i个结点                          
            j++;
            p=p->next;
        }
        if(p==NULL)                                             //没有找到第i个结点，返回假
        return false;
        else{                                                   //找到第i个结点，返回真
            e=p->data;
            return true;
        }
    }
}

int LocateElem(DLinkNode *L,ElemType e){                    //查找第一个值域为e的元素序号
    int i=1;
    DLinkNode *p=L->next;
    while(p!=NULL && p->data!=e){
        i++;
        p=p->next;
    }
    if(p==NULL)                                              //没有找到返回0
        return 0;   
    else                                                    //找到就返回其序号
        return(i);
}

bool ListInsert(DLinkNode *&L,int i,ElemType e){            //插入第i个元素
    int j=1;
    DLinkNode *p=L,*s;                                      
    if(i<=0)
        return false;                                       //i错误返回假
    if(p->next==L){                                         //原双链表为空表时
        s=(DLinkNode *)malloc(sizeof(DLinkNode));           //创建新结点s
        s->data=e;
        p->next=s;s->next=p;
        p->prior=s;s->prior=p;
        return true;
    }
    else if(i==1){                                           //L不为空，i=1作为特殊情况处理
        s=(DLinkNode *)malloc(sizeof(DLinkNode));           //创建新结点s
        s->data=e;
        s->next=p->next;p->next=s;                          //将结点s插入到结点p之后
        s->next->prior=s;s->prior=p;
        return true;
    }
    else{                                                   //i不为1时
        p=L->next;
        while(j<=i-2 && p!=L){                              //查找第i-1个结点
            j++;
            p=p->next;
        }
        if(p==L)                                            //未找到第i-1个结点
            return false;
        else{                                               //找到第i-1个结点
            s=(DLinkNode *)malloc(sizeof(DLinkNode));         //创建新结点
            s->data=e;
            s->next=p->next;                                //将结点s插入到结点p之后
            if(p->next!=NULL) p->next->prior=s;             
            s->prior=p;
            p->next=s;
            return false;
        }
    }
}

bool ListDelete(DLinkNode *&L,int i,ElemType &e){           //删除第i个元素
    int j=1;
    DLinkNode *p=L,*q;
    if(i<=0 || L->next==L)
        return false;                                       //i错误或者为空表返回假
    if(i==1){                                               //i==1作为特殊情况处理
        q=L->next;                                          //删除第1个结点
        e=q->data;
        L->next=q->next;
        q->next->prior=L;
        free(L);
        return true;
    }
    else{                                                   //i不为1时
        p=L->next;
        while(j<=i-2 && p!=NULL){                           //查找到第i-1个结点
            j++;
            p=p->next;
        }
        if(p==NULL)                                         //未找到第i-1个结点
            return false;
        else{                                              //找到第i-1个结点
            q=p->next;                                      //q指向要删除的结点
            if(q==NULL) return 0;                           //不存在第i个结点
            e=q->data;
            p->next=q->next;                                //从单链表中删除q结点
            if(p->next!=NULL) p->next->prior=p;
            free(q);                                        //释放p结点
            return true;
        }
    }
}

int main(){
    DLinkNode *h;
    ElemType e;
    printf("双链表的基本运算如下：\n");
    printf("    (1)初始化双链表h\n");
    InitList(h);
    printf("    (2)依次采用尾插法插入a,b,c,d,e元素\n");
    ListInsert(h,1,'a');
    ListInsert(h,2,'b');
    ListInsert(h,3,'c');
    ListInsert(h,4,'d');
    ListInsert(h,5,'e');
    printf("    (3)输出双链表h:");DispList(h);
    printf("    (4)双链表h长度：%d\n",ListLength(h));
    printf("    (5)双链表h为%s\n",(ListEmpty(h)?"空":"非空"));
    GetElem(h,3,e);
    printf("    (6)双链表h的第3个元素：%c\n",e);
    printf("    (7)元素a的位置：%d\n",LocateElem(h,'a'));
    printf("    (8)在第4个元素位置上插入f元素\n");
    ListInsert(h,4,'f');
    printf("    (9)输出双链表h:");DispList(h);
    printf("    (10)删除h的第3个元素\n");
    ListDelete(h,3,e);
    printf("    (11)输出双链表h:");DispList(h);
    printf("    (12)释放双链表h\n");
    DestroyList(h);
    return 1;
}

