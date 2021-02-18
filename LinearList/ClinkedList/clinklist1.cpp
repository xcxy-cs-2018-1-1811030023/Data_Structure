/*
    与单链表相比，循环单链表的最后一个结点的next指针是指向了头结点。单链表，从一个结点出发只能找到后续的各个结点
    而循环单链表：从一个结点出发可以找到其他任何一个结点
    */
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

bool InitList(LinkList &L){
    L=(LNode *)malloc(sizeof(LNode));   //分配一个头结点
    if(L==NULL)                         //内存不足，分配失败
        return false;
    L->next=L;                          //头结点的next指针指向头结点
    return true;
}

bool Empty(LinkList L){                 //判断循环单链表是否为空
    return(L->next=L);
}

bool isTail(LinkList L,LNode *p){       //判断结点p是否为循环单链表的表尾结点
    return(p->next==L);
}