/*
define MaxSize 10
typedef struct{
    ElemType data;
    int next;
}SLinkList[MaxSize];
等价于：
#define MaxSize 10
struct Node{
    ElemType data;
    int next;
};
typedef struct Node SLinkList[MaxSize];//可以用SLinkList定义"一个长度为MaxSize 的Node型数组"
如下：
void test{
    SLinkList a;
    //....
}*/
//测试代码如下：
#include <stdio.h>
#define MaxSize 10
struct Node{
    int data;
    int next;
};
typedef struct{
    int data;
    int next;
}SLinkList[MaxSize];

void testSLinkList(){
    struct Node x;
    printf("sizeX=%d\n",sizeof(x));

    struct Node a[MaxSize];
    printf("sizeA=%d\n",sizeof(a));

    SLinkList b;
    printf("sizeB=%d\n",sizeof(b));
}

int main(){
    testSLinkList();
    return 0;
}

/*输出结果为：
sizeX=8
sizeA=80
sizeB=80
证明结论正确
*/
