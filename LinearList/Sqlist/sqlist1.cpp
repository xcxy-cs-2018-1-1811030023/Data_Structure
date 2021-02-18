/*李春葆的代码，全程使用的是指针，用指针指向根据声明的顺序表类型动态开辟的空间。优点：代码空间复杂度小，效率高。
缺点：代码看起来没有王道的"建立一个变量，然后引用变量的方法简便",而且最大的问题在于李春葆的代码是没有实际的声明变量
并创建变量的，只是根据变量类型的大小，动态分配的内存空间。空间复杂度是小，但是如果我们遇到问题是要改变顺序表的大小的时候，
就没法了，因为我们没有建立变量，就谈不上利用算法去改变结构体中变量的值了，就无法改变结构体中data[MaxSize]的大小。
*/
/*
    SqList *&L,表示的是类型为SqList *的指针变量的引用类型变量L。不能简单理解为取值和取址，不然就等同于事发生过了
    在最初主函数中，李春葆的代码不是王道那样直接建立结构体变量L,而是建立起结构变量L的指针变量。如果函数间要求是双向
    传递的话，王道直接用引用是更加简便的，但是如果是单向传递的话，王道的就只能是值传递了（对于结构体空间开销太大了）
    而李春葆的，全局都使用的都是指针类型的变量，传递的只是指针的地址。无论是双向还是单向都是可以的。
*/
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50         //默认的最大值
typedef char ElemType;
typedef struct{
    ElemType data[MaxSize];//存放顺序表的元素
    int length;            //存放顺序表的长度
}SqList;//声明顺序表的类型

void CreateList(SqList *&L,ElemType a[],int n){//整体建立顺序表
    L=(SqList *)malloc(sizeof(SqList));
    for(int i=0;i<n;i++)
        L->data[i]=a[i];
    L->length=n;
}

void InitList(SqList *&L){//初始化顺序表
    L=(SqList *)malloc(sizeof(SqList));
    L->length=0;
}


void DestroyList(SqList *&L){//销毁顺序表
    free(L);
}

bool ListEmpty(SqList *L){//判断顺序表是否为空
    return(L->length==0);
}

int ListLenth(SqList *L){//求顺序表长度
    return(L->length);
}

void DispList(SqList *L){//输出顺序表
    for(int i=0;i<L->length;i++)
        printf("%c\t",L->data[i]);
    printf("\n");
}

bool GetElem(SqList *L,int i,ElemType &e){//求线性表中的第i个元素值
    if(i<1||i>L->length)    
       return false;
    e=L->data[i-1];
    return true;
}

int LocateElem(SqList *L,ElemType e){//查找第一个值域为e的元素编号
    int i=0;
    while(i<L->length && L->data[i]!=e)
       i++;
    if(i>=L->length)
        return 0;
    else
        return i+1;
}

bool ListInsert(SqList *&L,int i,ElemType e){//插入第i个元素
    int j;
    if(i<1||i>L->length+1)
        return false;
    if(L->length>=MaxSize)
        return false;
    i--;                                    //将顺序表位序转换为数组data的下标
    for(j=L->length;j>i;j--)                //将data[i]及后面元素都后移动一个位置
        L->data[j]=L->data[j-1];
    L->data[i]=e;
    L->length++;
    return true;
}

bool ListDelete(SqList *&L,int i,ElemType &e){//删除第i个元素
    int j;
    if(i<1||i>L->length)
        return false;
    i--;
    e=L->data[i];
    for(j=i;j<L->length-1;j++)              //将data[i]之后的每个元素都前移一个位置
        L->data[j]=L->data[j+1];
    L->length--;
    return true;
}


int main(){
    SqList *L;
    ElemType e;
    printf("对顺序表依次插入a,b,c,d,e元素\n");
    InitList(L);
    ListInsert(L,1,'a');
    ListInsert(L,2,'b');
    ListInsert(L,3,'c');
    ListInsert(L,4,'d');
    ListInsert(L,5,'e');
    printf("此顺序表内容为：");DispList(L);
    printf("顺序表L为%s\n",(ListEmpty(L)?"空":"非空"));
    printf("此顺序表的长度为%d\n",ListLenth(L));
    GetElem(L,3,e);printf("顺序表的第3个元素为:%c\n",e);
    printf("元素a的位置为：%d\n",LocateElem(L,'a'));
    printf("在第4个元素位置上插入f元素\n"); ListInsert(L,4,'f');
    printf("此顺序表的内容为；");DispList(L);
    printf("删除元素的第三个元素\n");ListDelete(L,3,e);
    printf("此顺序表的内容为；");DispList(L);
    printf("释放顺序表...\n");DestroyList(L);
    return 1;
}

