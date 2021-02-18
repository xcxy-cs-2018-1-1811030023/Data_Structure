/*
    双链表，表头结点的prior指向NULL,表尾结点的next指向NULL。
    循环双链表，表头结点的prior指向表尾结点，表尾结点的next指向头结点。
    */
typedef struct DNode{
    ElemType data;
    struct DNode *prior,*next;
}DNode,*DLinklist;

bool InitDLinkList(DLinklist &L){       //初始化空的循环双链表
    L=(DNode*)malloc(sizeof(DNode));    //分配一个头结点
    if(L==NULL)                         //内存不足，分配失败
        return false;
    L->prior=L;                         //头结点的prior指向头结点
    L->next=L;                          //头结点的next指向头结点
    return true;
}

bool IsEmpty(DLinklist L){              //初始化空的循环双链表
    return(L->next==L);
}

bool isTail(DLinklist L,DNode *p){      //判断结点p是否为循环双链表的表尾结点
    return(p->next==L);
}

