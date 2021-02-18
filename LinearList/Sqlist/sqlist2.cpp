/*
    <1>引用：
    在c++里，除了c语言的功能之外，还代表“引用”只能在创建变量的时候使用，格式是：类型 &变量名=另一个变量。如：
　　int a=0,&b=a,c;声明三个变量a、b、c，b和a等价，c是独立的变量。
    注意：类型标识符是指目标变量（等于号右边）的类型。
        声明引用时，必须同时对其进行初始化，不能让他指向其他变量。
        引用的声明符放置在变量名的前面，和*操作符的用法一样。
        引用声明完毕后，相当于目标变量名有两个名称，即该目标原名称和引用名，且不能再把该引用名作为其他变量名的别名。
        声明一个引用，不是新定义了一个变量，它只表示该引用名是目标变量名的一个别名，它本身不是一种数据类型，因此引用本身不占存储单元，系统也不给引用分配存储单元。
        
    <2>函数间调用，参数三种传递方式：
    1.值传递：将实参变量所占的内存单元的内容全部传递给形参。在函数调用期间建立的形参（当然形参和实参的类型要相同）也要占用内存单元。
            （是与主函数中变量存储的区域不一样的另一块区域，调用完函数后就都被释放了。所以不能返回影响主函数中的变量，是单向传递）
            这种传递方式相互间传递的是整个变量的内容，在空间和实践上开销较大，如果传递的是结构体，结构体的规模很大时，开销是很客观的。因此一般较少使用这种方法。 
 
    2.指针传递：这种方式虽然也是值传递的方式，但是这次传递的值却是指针。通过改变指针指向的变量的值，可以间接改变实参的值。
              （相同的，传递数组名的方式也是异曲同工）这样双向影响的传递为双向传递。  
                并且，在调用函数期间，仅仅建立了一个指针变量，相对于变量本身大大的减小了系统的开销。 
    
    3.引用传递：实参是变量，形参是对应的变量类型的引用，传递的是地址（和指针变量是异曲同工，只不过看起来更加直观易懂）
                定义引用时，程序把引用和它的初始值绑定（bind）在一起，而不是将初始值拷贝给引用。一旦初始化完成，引用将和它的初始值对象一直绑定在一起。
                因为引用本身不是一个对象，所以不能定义引用的引用。一旦定义了引用，就无法令其再绑定到另外的对象，之后每次使用这个引用都是访问它最初绑定的那个对象。
                而且在实际编译运行操作中，打印引用的地址结果与变量的地址一样。
                得到结论：引用类型的变量会占用内存空间，占用的内存空间的大小和指针类型的大小是相同的。从反编译的汇编代码可以看出，虽然引用是一个对象的别名，但是在
                汇编层面，和指针是一样的。因而，和指针变量一样提高效率，而且保持程序良好的可读性。
                        **/

/*静态分配顺序表：
#include <stdio.h>
#define MaxSize 10
typedef struct{//定义顺序表类型
    int data[MaxSize];
    int length;
}SqList;

void InitList(SqList &L){//顺序表初始化
    L.length=0;
}*/

//动态分配顺序表
#include <stdio.h>
#include <stdlib.h>
#define InitSize 15         //默认的最大值
typedef int ElemType;
typedef struct{
    ElemType *data;//存放顺序表的元素
    int length; 
    int MaxSize;            //存放顺序便的长度
}SqList;//声明顺序表的类型



void CreateList(SqList &L,ElemType a[],int n){//整体建立内容为连续十个数的顺序表
    L.data=(ElemType *)malloc(n*sizeof(ElemType));
    for(int i=0;i<n;i++)
        L.data[i]=a[i];
    L.length=n;
}


void InitList(SqList &L){//顺序表初始化
    L.data=(int *)malloc(InitSize*sizeof(int));
    L.length=0;
    L.MaxSize=InitSize;
}

void DestroyList(SqList &L){//销毁顺序表
    free(L.data);
}

bool ListEmpty(SqList L){//判断顺序表是否为空
    return(L.length==0);
}

bool ListFull(SqList L){//判断顺序表是否已装满
    return(L.length==L.MaxSize);
}

bool ListInsert(SqList &L,int i,ElemType e){//插入第i个元素
    if(i<1||i>L.length+1)
        return false;
    if(L.length>=L.MaxSize)
        return false;
                                
    for(int j=L.length;j>i;j--)                //将data[i]及后面元素都后移动一个位置
        L.data[j]=L.data[j-1];
    L.data[i-1]=e;                          //将顺序表位序转换为数组data的下标
    L.length++;
    return true;
}

bool ListInserts(SqList &L,int i,ElemType a[]){//从某位序开始连续插入10个元素
    if(i<1||i>L.length+1)
        return false;
    if(L.length>(L.MaxSize-10))
        return false;
    int j;                        
    for(j=L.length;j>i;j--)                //将data[i]及后面元素都后移动一个位置
        L.data[j]=L.data[j-10];
    
    for(j=0;i<10;j++)
        L.data[i-1]=a[j];                         //将顺序表位序转换为数组data的下标
    L.length+=10;
    return true;
}


bool ListDelete(SqList &L,int i,ElemType &e){//删除第i个元素
    if(i<1||i>L.length)
        return false;
    e=L.data[i-1];
    for(int j=i;j<L.length-1;j++)              //将data[i]之后的每个元素都前移一个位置
        L.data[j-1]=L.data[j];
    L.length--;
    return true;
}

void ListDeleteAll(SqList &L,int x){//删除值为x的所有位序
    int k=0;
    for(int i=0;i<L.length;i++)
        if(L.data[i]!=x){
            L.data[k]=L.data[i];
            k++;
        }
    L.length=k;
}

/*删除值为x的所有位序方法二：
void delete(Sqlist &L,int x){
    int k=0;
    for(int i=0;i<L.length;i++){
        if(L.data[i]==x)
            k++;
        else
            L.data[i-k]=L.data[i];
    }
    L.length=L.length-k;
}
*/
bool ListDeleteSorted(Sqlist &L,int s,int t){
    int i,k=0;
    if(L.lenght==0)
}
void DispList(SqList L){//输出顺序表
    for(int i=0;i<L.length;i++)
        printf("%d\t",L.data[i]);
    printf("\n");
}

int ListLenth(SqList L){//求顺序表长度
    return(L.length);
}

int ListMaxSize(SqList L){
    return(L.MaxSize);
}
void IncreaseSize(SqList &L,int len){                     //增加动态数组的长度
    ElemType *p=L.data;
    L.data=(ElemType *)malloc((L.MaxSize+len)*sizeof(ElemType));
    for(int i=0;i<L.length;i++){
        L.data[i]=p[i];
    }
    L.MaxSize=L.MaxSize+len;
    free(p);
}

bool GetElem(SqList &L,int i,ElemType &e){//求线性表中的第i个元素值
    if(i<1||i>L.length)    
       return false;
    e=L.data[i-1];
    return true;
}

int LocateElem(SqList &L,ElemType e){//查找第一个值域为e的元素编号
    for(int i=0;i<L.length;i++)
        if(L.data[i]==e)
            return i+1;

    return 0;
}



int main(){
    SqList L;
    ElemType Element=0,RankOrder,i,num;
    ElemType c[10];
    while(1){
        printf("--------------------------------------------顺序表操作系统--------------------------------------------\n");
        printf("1.创建10元素的顺序表     2.销毁顺序表        3.初始化顺序表     4.判断顺序表是否为空     5.输出顺序表的长度\n");
        printf("6.输出顺序表的内容      7.插入元素*到第*位序  8.删除第*位序的元素   9.增加顺序表的最大长度  10.判断顺序表是否已满\n");
        printf("11.查询第*位序的元素值  12.查询第一个*元素是第几位序    13.删除所有元素值为*的元素          14.连续插入10数\n");
        printf("请输入你要选择的功能：");
        scanf("%d",&num);
        switch(num){
            case 1:     printf("创建一个顺序表，请连续输入10个数字并回车，数字之间用空格隔开：\n");
                        for(i=0;i<10;i++)
                            scanf("%d",&c[i]);
                        CreateList(L,c,10);
                        printf("顺序表的内容为：");
                        DispList(L);
                        break;

            case 2:     printf("释放在内存中创建的顺序表......\n");
                        DestroyList(L);
                        printf("顺序表释放成功！\n");
                        break;
            
            case 3:     printf("初始化一个内存空间......\n");
                        InitList(L);
                        printf("初始化顺序表成功！\n");
                        break;
            
            case 4:     printf("顺序表L为%s\n",(ListEmpty(L)?"空":"非空"));
                        break;      

            case 5:     printf("当前顺序表的长度为%d\n",ListLenth(L));
                        break;

            case 6:     printf("顺序表的内容为：");
                        DispList(L);
                        break;

            case 7:     printf("输入要插入的位序:");
                        scanf("%d",&RankOrder);
                        printf("输入插入位序的元素:");
                        scanf("%d",&Element);
                        ListInsert(L,RankOrder,Element);
                        printf("元素插入成功!\n");
                        break;

            case 8:     printf("输入要删除的位序:");
                        scanf("%d",&RankOrder);
                        ListDelete(L,RankOrder,Element);
                        printf("位序%d已被删除,被删除内容为%d\n",RankOrder,Element);
                        break;
            
            case 9:     printf("请输入你要增加部分的顺序表元素个数：");
                        scanf("%d",&i);
                        IncreaseSize(L,i);
                        printf("当前顺序表的最大长度为%d\n",ListMaxSize(L));
                        break;

            case 10:     printf("顺序表L为%s\n",(ListFull(L)?"已满":"非满"));
                        break;

            case 11:    printf("请输入你要查找元素值的位序:");
                        scanf("%d",&RankOrder);
                        GetElem(L,RankOrder,Element);
                        printf("位序%d的值为%d\n",RankOrder,Element);
                        break;

            case 12:    printf("请输入你要查找所在位序的元素值:");
                        scanf("%d",&Element);
                        printf("第一个元素为%d的位序为%d\n",Element,LocateElem(L,Element));
                        break;
                    
            case 13:    printf("请输入你要全部删除的元素值:");
                        scanf("%d",&Element);
                        ListDeleteAll(L,Element);
                        printf("所有元素为%d的值已被删除！\n");
                        break;

            case 14:    printf("创建一个顺序表，请连续输入10个数字并回车，数字之间用空格隔开：\n");
                        for(i=0;i<10;i++)
                            scanf("%d",&c[i]);
                        printf("请输入你要插入的位序：\n");
                        scanf("%d",&RankOrder);
                        ListInserts(L,RankOrder,c);
                        printf("连续插入10数成功！\n");
                        printf("顺序表的内容为：");
                        DispList(L);
                        break;
        }
    
    }
    return 0;
}

/*
    return表示从被调函数返回到主调函数继续执行，返回时可附带一个返回值，由return后面的参数指定。 如果函数执行不需要返回计算结果，
    也经常需要返回一个状态码来表示函数执行的顺利与否,主调函数可以通过返回值判断被调函数的执行情况。
    1.返回值 int类型 的函数返回:
        return语句用来结束循环，或返回一个函数的值
        return 0：一般用在主函数结束时，按照程序开发的一般惯例，表示成功完成本函数
        return -1：:表示返回一个代数值，一般用在子函数结尾。按照程序开发的一般惯例，表示该函数失败
        以上两个是约定俗成，系统提供的函数绝大部分定义为 int类型 返回值 的 都是这样的。返回值是返回
        给系统用的，给系统看得。一般做 调试 的时候也会用的，当出现错误的时候可以根据返回值来确定问题出在哪一个函数上的。

    2.布尔类型返回:
        return 0：返回假
        return 1：返回真
        一般这样的函数用来实现一个判断是否的逻辑，或检查有无的数据。返回真表示“是”，返回假表示“否”
    
    3.return 关键字 的作用是返回程序流程的控制权！其副作用是返回一个值,例如int main（）{}则必须返回一个值
        return 0 代表函数正常终止
        ruturn 1 代表函数非正常终止
        被调函数 return 1只是给主调函数一个标志，说明它的执行过程遇到异常情况，然后就返回主调函数来处理，继续执行
        这个异常情况是什么？这个异常情况是返回给控制台的，不在你编的程序的控制范围内，是给操作系统识别的，对你的程序无影响
*/
