/*
    单链表：无法逆向检索，有时候不太方便，双链表在此基础上增加一个指向前驱结点的指针
    */
typedef struct DNode{
    ElemType data;
    struct DNode *prior,*next;
}DNode,*DLinklist;

//以下都是按带头结点的链表来展开的
bool InitDLinkList(DLinklist &L){
    L=(DNode *)malloc(sizeof(DNode));       //分配一个头结点
    if(L==NULL)                             //内存不足，分配失败
        return false;
    L->prior=NULL;                          //头结点的prior永远指向NULL
    L->next=NULL;                           //头结点之后暂时还没有结点
    return true;
}

bool Empty(DLinklist L){                //判断双链表是否为空
    return(L->next==NULL);
}

bool InsertNextDNode(DNode *p,DNode *s){//在p结点之后插入s结点
    if(p==NULL || s==NULL)              //非法参数
        return false;
    s->next=p->next;
    if(p->next!=NULL)                   //如果p结点有后继结点
        p->next->prior=s;
    s->prior=p;
    p->next=s;
    return true;
}

bool DeleteNextDNode(DNode *p){         //删除p结点的后继结点
    if(p=NULL)
        return false;
    DNode *q=p->next;                   //找到p的后继结点q
    if(q==NULL)
        return false;                   //p没有后继
    p->next=q->next;
    if(q->next!=NULL)                   //q结点不是最后一个结点
        q->next->prior=p;
    free(q);                            //释放结点空间
    return true;
}

void DestoryList(DLinklist &L){         //循环释放各个数据结点
    while(L->next!=NULL)
        DeleteNextDNode(L);
    free(L);                            //释放头结点
    L=NULL;
}

