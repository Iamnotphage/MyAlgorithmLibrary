# My-Algorithm-Library

    Collect the DS & Algorithms I have learned.

- [My-Algorithm-Library](#my-algorithm-library)
- [前言](#前言)
- [数学](#数学)
- [表、栈和队列](#表栈和队列)
- [串](#串)
  - [BruteForce算法（暴力匹配）](#bruteforce算法暴力匹配)
  - [KMP算法](#kmp算法)
- [树](#树)
  - [二叉树](#二叉树)
  - [二叉排序树](#二叉排序树)
- [散列](#散列)
- [优先队列（堆）](#优先队列堆)
- [排序](#排序)
  - [冒泡排序](#冒泡排序)
  - [选择排序](#选择排序)
  - [插入排序](#插入排序)
  - [希尔排序](#希尔排序)
  - [归并排序](#归并排序)
  - [快速排序](#快速排序)
  - [堆排序](#堆排序)
  - [计数排序](#计数排序)
  - [桶排序](#桶排序)
  - [基数排序](#基数排序)
- [不相交集ADT](#不相交集adt)
- [图论算法](#图论算法)
  - [DFS和BFS](#dfs和bfs)
  - [Prim](#prim)
  - [Kruskal](#kruskal)
  - [TopologicalSort](#topologicalsort)
  - [Dijkstra](#dijkstra)
  - [Floyd](#floyd)


# 前言

忙碌一阵后，终于想起自己在这里挖了个坑:D

本文内容主要是自己所学所见闻的数据结构与算法的收录。

主体结构按照黑皮书**Data Structures and Algorithm Analysis in C**的目录。

    谨以此库当作我人脑的外存。

23年3月补档，数据结构期末总评100（当然考核肯定水一些，只能说出的题刚好都会）

# 数学

MIT6.828里面学到一个多线程素数筛:

```CPP
//primes.c
#include "kernel/types.h"
#include "user/user.h"

void prime_sieve(int* fd){
    int buf[1];
    close(fd[1]);
    if(read(fd[0],buf,4)!=0){
        //0 stands for nothing to read.
        int p=buf[0];
        fprintf(2,"prime %d\n",p);

        int fd2[2];//to the right neighbor
        pipe(fd2);
        int pid2=fork();//the new process shared that pipe

        if(pid2==0){
            prime_sieve(fd2);
        }else{
            //current(parent) process write to RIGHT
            int n=p;
            while(read(fd[0],buf,4)!=0){
                //n = get a number from left neighbor
                n=buf[0];

                if(n%p!=0){
                    close(fd2[0]);
                    write(fd2[1],buf,4);//send n to right neighbor
                }
            }
            close(fd2[1]);
            wait(0);
        }
    }
    exit(0);
}

int main(){
    int fd[2];
    int p,n;
    int buf[1];
    pipe(fd);
    int pid=fork();
    if(pid==0){
        //in child process
        //read frome left, write into right
        prime_sieve(fd);
    }else{
        //in parent process
        p=2;
        fprintf(2,"prime %d\n",p);
        n=p;
        while(n<35){
            buf[0]=++n;
            if(buf[0]%p!=0){
                close(fd[0]);
                write(fd[1],buf,4);//int has 4B
            }
        }
        close(fd[1]);
        wait(0);//wait for child process
    }
    exit(0);
}
```


# 表、栈和队列

# 串

我只知道模式匹配。

## BruteForce算法（暴力匹配）

```C
//下面的内容中 串S[0] T[0]表长度 next[0]无内容

//模式匹配 暴力匹配 也就是BruteForce算法
//返回子串T在主串S中第pos个字符之后的位置，若不存在返回0
int BruteForce(char* S,char* T,int pos){
    // 1<=pos<=S.length 
    int i=pos,j=1;
    while(i<=S[0] && j<=T[0]){
        if(S[i]==T[j]){
            ++i;
            ++j;
        }else{//匹配失败
            i=i-j+2;//i倒退 因为串是从1数，所以i=i-j+2;
            j=1;//j从串T的第一个字符开始
        }
    }
    if(j>T[0]){
        return i-T[0];
    }else{
        return 0;//表示匹配失败
    }
}
```

## KMP算法

核心是求Next[j]

```C
//KMP算法,求模式串T的next值
//求最长前后缀长度 然后加1就是next_j的值
void GetNext(char* T,int* next,int Tlength){
    int i=1,j=0;
    next[1]=0;
    while(i<Tlength){
        if(j==0 || T[i]==T[j]){
            ++i;
            ++j;
            next[i]=j;
        }else{
            j=next[j];
        }
    }
}

//KMP
int KMP(char* S,char* T,int pos,int* next){
    //利用模式串T的next函数求T在主串S中第pos个字符之后位置的KMP算法
    //T非空 1<= pos <= S.length() S[0]和T[0]都是长度
    int i=pos,j=1;
    while(i<=S[0] && j<=T[0]){
        if(j==0 || S[i]==T[j]){//继续比较后继字符
            ++i;
            ++j;
        }else{
            j=next[j];//模式串向后移动
        }
    }
    if(j>T[0]){
        return i-T[0];//匹配成功
    }else{
        return 0;
    }
}
```

# 树

主要是二叉树，二叉排序树(二叉查找树)。

首先是二叉树链表形式的数据结构：

```C
#define TElemType int
typedef struct BiTNode{
    TElemType data;
    struct BiTNode* lchild,*rchild;
}BiTNode,*BiTree;
```
## 二叉树

```C
//递归版本前序遍历,自己写的,比较垃圾,LDR,LRD同理
void PreOrder(BiTree T){
    if(T==nullptr){
        return;
    }else{
        cout<<T->data;//Visit();
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

//递归版本中序遍历，自己写的
void InOrder(BiTree T){
    if(T==nullptr){
        return;
    }else{
        InOrder(T->lchild);
        cout<<T->data;//Visit();
        InOrder(T->rchild);
    }
}

//递归版本后序遍历，自己写的
void PostOrder(BiTree T){
    if(T==nullptr){
        return;
    }else{
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        cout<<T->data;
    }
}

//非递归版本的二叉树遍历(利用栈),以及一个层次遍历(利用队列)//
/*
    非递归版本的二叉树遍历
前序遍历(DLR)：循环中，刷新p，入栈右子树，入栈左子树
*/
//非递归版本前序遍历
int PreOrderTraverseNonR(BiTree T,int(*Visit)(TElemType e)){
    //DLR
    stack<BiTree>S;
    auto p=T;
    while(p || !S.empty()){
        if(p){
            if(!Visit(p->data)){
                return 0;
            }//一整坨 Visit()
            S.push(p);
            p=p->lchild;
        }else{
            p=S.top();
            S.pop();
            p=p->rchild;
        }
    }
    return 1;//OK
}

//非递归版本中序遍历
int InOrderTraverseNonR(BiTree T,int(*Visit)(TElemType e)){
    //LDR,先入左子树，再右子树
    stack<BiTree>S;
    auto p=T;
    while(p || !S.empty()){
        if(p){//根指针进栈，遍历左子树
            S.push(p);
            p=p->lchild;
        }else{
            //根指针退栈，访问根节点，遍历右子树
            p=S.top();
            S.pop();
            if(!Visit(p->data)){
                return 0;//ERROR
            }
            p=p->rchild;
        }
    }
    return 1;//OK
}

//非递归版本后序遍历
int PostOrderTraverseNonR(BiTree T,int(*Visit)(TElemType e)){
    //LRD
    BiTree p;
    stack<BiTree>S;
    S.push(T);//根结点先入栈
    BiTree pre=nullptr;
    while(!S.empty()){//栈不空
        p=S.top();
        if((p->lchild==nullptr && p->rchild==nullptr) || (pre!=nullptr && (pre==p->lchild || pre==p->rchild)) ){
            //子树空或者子树都以及被访问过
            if(!Visit(p->data)){
                return 0;
            }
            S.pop();
            pre=p;
        }else{
            if(p->rchild!=nullptr){
                S.push(p->rchild);//先右子树入栈
            }
            if(p->lchild!=nullptr){
                S.push(p->lchild);//后左子树入栈
            }
        }
    }
    return 1;
}

//非递归层次遍历
int LevelTraverseNonR(BiTree T,int(*Visit)(TElemType e)){
    //队列实现 queue 总体是先入队，p=Q的头并访问，p左子树入队，p右子树入队，再循环
    BiTree p;
    queue<BiTree>Q;
    Q.push(T);
    while(!Q.empty()){
        p=Q.front();
        if(!Visit(p->data)){
            return 0;//ERROR
        }
        Q.pop();
        if(p->lchild!=nullptr){
            Q.push(p->lchild);
        }
        if(p->rchild!=nullptr){
            Q.push(p->rchild);
        }
    }
    return 1;//OK
}

//先序次序创建二叉树
BiTree CreateBiTree(){
    char ch;
    BiTree T;
    scanf("%c",&ch);
    if(ch==' '){//用空格表示空树
        T=NULL;
    }else{
        if(!(T=(BiTree)malloc(sizeof(BiTNode)))){
            exit(0);
        }
        T->data=ch;//生成根结点
        T->lchild=CreateBiTree();
        T->rchild=CreateBiTree();
    }
    return T;
}

//求二叉树的深度
int BiTreeDepth(BiTree T){
    int lchilddep=0,rchilddep=0;
    if(T==nullptr){
        return 0;
    }else{
        lchilddep=BiTreeDepth(T->lchild);
        rchilddep=BiTreeDepth(T->rchild);
        return (lchilddep>rchilddep)?(lchilddep+1):(rchilddep+1);
    }
}

//判定俩二叉树是否相似
int Like(BiTree T1,BiTree T2){
    //T1和T2俩颗二叉树是否相似，是1，否0
    int like1,like2;
    if(T1==nullptr && T2==nullptr){
        return 1;
    }else if(T1==nullptr || T2==nullptr){
        return 0;
    }else{
        like1 = Like(T1->lchild,T2->lchild);
        like2 = Like(T1->rchild,T2->rchild);
        return(like1 && like2);
    }
}
```

## 二叉排序树

```C
//BinarySearchTree,结点结构体定义与二叉树相同
//定义：左子树所有结点小于根，右子树所有结点大于根，子树仍符合上述定义(递归)

//MakeEmpty,初始化
BiTree MakeEmpty(BiTree T){
    if(T!=nullptr){
        MakeEmpty(T->lchild);
        MakeEmpty(T->rchild);
        free(T);
    }
    return nullptr;
}

//Find查找 递归的方法
BiTree Find(TElemType x,BiTree T){
    if(T==nullptr){
        return nullptr;
    }
    if(x < T->data){
        return Find(x,T->lchild);
    }else if(x > T->data){
        return Find(x,T->rchild);
    }else{
        return T;
    }
}

//FindMin查找最小值 递归版本
BiTree FindMin(BiTree T){
    if(T==nullptr){//先写终止条件
        return nullptr;
    }else if(T->lchild==nullptr){
        return T;
    }else{
        return FindMin(T->lchild);
    }
}

//FindMax查找最大值 非递归版本
BiTree FindMax(BiTree T){
    if(T!=nullptr){
        while(T->rchild!=nullptr){
            T=T->rchild;
        }
    }
    return T;
}

//在二叉查找树中插入x结点
BiTree Insert(TElemType x,BiTree T){
    if(T=nullptr){
        //创建一个树
        T=(BiTree)malloc(sizeof(BiTNode));
        if(T==nullptr){
            printf("Out of Space");//溢出
        }else{
            T->data=x;
            T->lchild=nullptr;
            T->rchild=nullptr;
        }
    }else{
        if(x < T->data){
            T->lchild=Insert(x,T->lchild);//这里已经实现插入了
        }else if(x > T->data){
            T->rchild=Insert(x,T->rchild);//这里已经实现插入了
        }
    }
    return T;//这一行非常重要
}

//Delete删除操作 递归 lazy deletion
BiTree Delete(TElemType x,BiTree T){
    BiTree TmpCell;
    if(T==nullptr){
        printf("ERROR: Element not found");
    }else if(x < T->data){
        T->lchild=Delete(x, T->lchild);
    }else if(x > T->data){
        T->rchild=Delete(x, T->rchild);
    }else if(T->lchild && T->rchild){//找到要删除的元素了,不过是有俩个子树的情况
        //找右子树中的最小值   或者左子树的最大值也行
        TmpCell=FindMin(T->rchild);
        T->data=TmpCell->data;
        T->rchild=Delete(T->data,T->rchild);//此时T->data已经赋值成右子树的最小值了，接下来需要在右子树删除这个结点(因为多余了)
    }else{
        //0个子树，或者1个子树
        TmpCell = T;
        if(T->lchild==nullptr){//这里同时也处理了0个子树的情况
            T=T->rchild;
        }else if(T->rchild==nullptr){
            T=T->lchild;
        }
        free(TmpCell);
    }
    return T;
}
```

# 散列

# 优先队列（堆）
堆的定义不用多说，递归定义，大顶堆父结点最大，小顶堆父结点最小，完全二叉树。

主要是数据结构吗，因为是完全二叉树，所以常用数组。

BinHeap.h文件内容如下:

定义数据结构，操作主要有判断是否为空、是否满、初始化堆、删除、插入、查找最小元素。

```C
//BinHeap.h
#ifndef _BinHeap_H

#define ElementType int

struct HeapSturct;
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(ElementType X,PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);

#endif
```

具体实现的code clip：
```C
#define MinPQSize 1  //最小堆的大小
#define MinData 0 //必须小于堆中的任何值

struct HeapStruct{
    int Capacity;
    int Size;
    ElementType *Elements;//数组实现
};

```


# 排序

经典的十大排序，主要是C的实现

先来个swap()
```C
//swap()
void swap(int* a,int* b){
    int t=*a;
    *a=*b;
    *b=t;
}
```


## 冒泡排序

```CPP
//冒泡排序BubbleSort 稳定 O(n^2)
void BubbleSort(int* a,int len){
    int i,j,isSorted;
    for(i=0;i<len-1;++i){
        isSorted=1;
        for(j=0;j<len-i-1;++j){
            if(a[j]>a[j+1]){
                swap(&a[j],&a[j+1]);
                isSorted=0;//false
            }
        }
        if(isSorted){
            break;
        }
    }
}
```

## 选择排序

```CPP
//选择排序SelctionSort 不稳定 O(n^2)
void SelectionSort(int* a,int len){
    int i,j,min;
    for(i=0;i<len-1;++i){
        min=i;
        for(j=i+1;j<len;++j){
            if(a[j]<a[min]){
                min=j;
            }
        }
        swap(&a[min],&a[i]);
    }
}
```


## 插入排序

```CPP
//插入排序InsertionSort 稳定 O(n^2)
void InsertionSort(int* a,int len){
    int i,j,tmp;
    for(i=1;i<len;++i){
        tmp=a[i];
        j=i-1;
        while( (j>=0) && (tmp<a[j])){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=tmp;
    }
}
```

## 希尔排序

```CPP
//希尔排序ShellSort 不稳定 O(n logn logn )
//gap序列不同可能导致复杂度的不同
void ShellSort(int* a,int len){
    int gap,i,j;
    int tmp;
    for(gap=len>>1;gap>0;gap>>=1){
        for(i=gap;i<len;++i){
            //InsertionSort
            tmp=a[i];
            for(j=i-gap;j>=0 && tmp<a[j];j-=gap){
                a[j+gap]=a[j];
            }
            a[j+gap]=tmp;
        }
    }
}
```

## 归并排序

```CPP
//归并排序MergeSort 稳定 O(nlogn)
void MergeSort(int* arr,int len){
    int *a=arr;
    int *b=(int *)malloc(len * sizeof(int));
    int seg,start;
    for(seg=1;seg<len;seg+=seg){
        for(start=0;start<len;start+=seg*2){
            int low=start,mid=min(start+seg,len),high=min(start+seg*2,len);
            int k=low;
            int start1=low,end1=mid;
            int start2=mid,end2=high;
            while(start1<end1 && start2<end2){
                b[k++]=a[start1]<a[start2]?a[start1++]:a[start2++];
            }
            while(start1<end1){
                b[k++]=a[start1++];
            }
            while(start2<end2){
                b[k++]=a[start2++];
            }
        }
        int *tmp=a;
        a=b;
        b=tmp;
    }
    if(a!=arr){
        int i;
        for(i=0;i<len;++i){
            b[i]=a[i];
        }
        b=a;
    }
    free(b);
}
//归并排序递归版本
void MergeSortRecursive(int* arr,int* reg,int start,int end){
    if(start>=end){
        return;
    }
    int len=end-start,mid=(len>>1)+start;
    int start1=start,end1=mid;
    int start2=mid+1,end2=end;
    MergeSortRecursive(arr,reg,start1,end1);
    MergeSortRecursive(arr,reg,start2,end2);
    int k=start;
    while(start1<=end1 && start2<=end2){
        reg[k++]=arr[start1]<arr[start2]?arr[start1++]:arr[start2++];
    }
    while(start1<=end1){
        reg[k++]=arr[start1++];
    }
    while(start2<=end2){
        reg[k++]=arr[start2++];
    }
    for(k=start;k<=end;k++){
        arr[k]=reg[k];
    }
}
//调用时， int reg[len]; MergeSortRecursive(arr,reg,0,len-1);

```

## 快速排序

```CPP
//快速排序QuickSort 不稳定 O(nlogn)
void QuickSort(int* a,int start,int end){
    if(start>=end){
        return;
    }
    int pivot=a[start];
    int left=start,right=end;
    while(left<right){
        while(a[right]>=pivot && left<right){
            right--;
        }
        if(left<right){
            a[left++]=a[right];
        }
        while(a[left]<=pivot && left<right){
            left++;
        }
        if(left<right){
            a[right--]=a[left];
        }
    }
    a[left]=pivot;
    QuickSort(a,start,left-1);
    QuickSort(a,left+1,end);
}
```

## 堆排序

## 计数排序

## 桶排序

## 基数排序

# 不相交集ADT

# 图论算法

主要用邻接矩阵存储。算法除了DFS和BFS都挺复杂的，让我手搓我也不会。

先来数据结构:

```CPP
//邻接矩阵
#define INFINITY INT_MAX//设INT_MAX是无穷大 表示俩者不邻接(俩点可达存边权，不可达存infinity) 有时候0表示不邻接，这个一般是可达矩阵(要么存0要么存1)
#define MAX_VERTEX_NUM 20//最大顶点个数

typedef struct MatrixGraph{
    char vexs[MAX_VERTEX_NUM];//顶点向量，如果顶点名字是字符就改成char,这只做参考
    int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//核心，邻接矩阵
    int vexnum,arcnum;//顶点数和边数，并非必要的
}MGraph;
```

## DFS和BFS

```CPP
//DepthFirstSearch 图的深度优先搜索DFS
//类似树的DLR先序遍历
//全局变量visited

//注意：下面DFS是以MatrixGraph的存储方式进行的 (0，1表示不可达，可达)

bool visited[MAX_VERTEX_NUM];//true表示访问过，false表示未访问
//在利用dfs判断有向图是否有环时，可以利用三种状态-1 0 1分别表示 正在访问，未访问，已经访问；
//正在访问也就是正在程序栈中 即在dfs递归的过程中重新遇到正在访问的结点说明有环。

//DFS递归版本 以邻接矩阵为例 顺便求一下连通分量omega
void DFS(MGraph G, int v){
    //从第v个结点出发DFS遍历图G
    visited[v]=true;
    printf("%c ",G.AdjMatrix[v]);//这里的访问就用输出替代

    for(int w=0;w<G.vexnum;++w){
        if(!visited[w] && G.AdjMatrix[v][w]==1){
            DFS(G,w);
        }
    }
}
void DFSTraverse(MGraph G,int & omega){//omega为连通分量(并非一定要求)
    omega=0;
    for(int i=0;i<G.vexnum;++i){
        visited[i]=false;//初始化为false
    }
    for(int i=0;i<G.vexnum;++i){
        if(!visited[i]){
            DFS(G,i);
            omega++;//在这里计算omega
        }
    }
}

//DFS非递归版本 以邻接矩阵为例
void DepthFirstSearch(MGraph G){
    stack<int> S;//visit stack 存储访问过的结点
    S.push(0);
    visited[0]=1;
    int lineNo=S.top();
    cout<<"visit: "<<lineNo;
    while(!S.empty()){
        lineNo=S.top();
        int colNo=0;
        for(colNo=0;colNo<G.vexnum;++colNo){
            if(G.AdjMatrix[lineNo][colNo] && !visited[colNo]){
                S.push(colNo);
                visited[colNo]=true;
                cout<<"visit: "<<colNo;
                break;
            }
        }
        if(colNo==G.vexnum){
            S.pop();
        }
    }
}

//BFS 图的广度优先搜索 以邻接矩阵为例子 类似树的层次遍历
void BFSTraverse(MGraph G){
    for(int i=0;i<G.vexnum;++i){
        visited[i]=false;//初始化visited数组
    }
    queue<int> Q;//辅助队列Q
    for(int v=0;v<G.vexnum;++v){
        if(!visited[v]){
            visited[v]=true;
            cout<<v+1<<" ";// Visite()的一种示例
            Q.push(v);//i入队列
            while(!Q.empty()){
                int u=Q.front();
                Q.pop();//u赋值为队列的头然后出队
                for(int w=0;w<G.vexnum;++w){//从小到大找与u邻接的结点w
                    if(!visited[w] && G.AdjMatrix[u][w]){
                        visited[w]=true;
                        cout<<w+1<<" ";// Visite()的一种示例
                        Q.push(w);
                    }//if
                }//for
            }//while
        }//if
    }//for
}//BFS
```

## Prim

```CPP
//最小生成树/Minimum Cost Spanning Tree

//Prim算法 MGraph图的邻接矩阵存储的是边和边的权重
//权重(一般为正) 下面的例子中 G.adj[i][j]权重INT_MAX表示infinity 其余是边权值
//无向图G没有自回路 所以一般i=j的边直接赋值0
//Prim算法对于稠密图的情况会好用一点/ 边数多 O(n^2)
void Prim(MGraph G){
    //用Prim算法从第u个结点出发构造G的最小生成树T，输出T的各条边
    int min,i,j,k;
    //min表示当前结点最小的边权 ij做临时变量 k是最小边权的另外一个结点

    int adjvex[MAX_VERTEX_NUM];//存储相关顶点的下标(也就是索引)
    int lowcost[MAX_VERTEX_NUM];//存储最小代价/权值 0表示已经访问过

    //Part1 初始化lowcost数组和adjvex数组
    lowcost[0]=0;//初始化第一个权值为0 表示第一个结点已经访问
    adjvex[0]=0;//下标为0
    for(i=1;i<G.vexnum;++i){
        lowcost[i]=G.AdjMatrix[0][i];//lowcost存储 与v0结点相关的所有权值
        adjvex[i]=0;//初始化都为v0的下标
    }

    //Part2 
    for(i=1;i<G.vexnum;++i){
        min=INT_MAX;//INT_MAX在<climits>或<limits.h>中有定义
        j=1;
        k=0;
        //Part2 找当前结点 边的最小值 从lowcost中找最小值(不为0)
        while(j<G.vexnum){
            if(lowcost[j]!=0 && lowcost[j]<min){//到j结点可达 且 最小值需要刷新
                min=lowcost[j];//刷新最小值
                k=j;//下标赋值给k
            }
            ++j;
        }
        printf("(%d,%d)\n",adjvex[k],k);//输出当前顶点中权值最小的边 (v1,v2)俩节点表示边
        //Part3 以k为"当前结点” 重新刷新lowcost和adjvex
        lowcost[k]=0;//置零表示该顶点已经完成查找最小边
        for(j=1;j<G.vexnum;++j){
            if(lowcost[j]!=0 && G.AdjMatrix[k][j]<lowcost[j]){//j结点没访问过
                lowcost[j]=G.AdjMatrix[k][j];
                adjvex[j]=k;
            }
        }
    }
}
```

## Kruskal

## TopologicalSort

```CPP
//TopologicalSort/有向图的拓扑排序/邻接矩阵存储为例

int indegree[MAX_VERTEX_NUM];//各个结点的入度值

//先对各顶点求入度
void FindInDegree(MGraph G,int indegree[]){
    for(int i=0;i<G.vexnum;++i){
        for(int j=0;j<G.vexnum;++j){
            if(G.AdjMatrix[i][j]!=0){
                indegree[j]++;
            }
        }
    }
}

bool TopologicalSort(MGraph G,int indegree[]){
    FindInDegree(G,indegree);//对各顶点求入度
    stack<int> S;//这里的容器改成queue也可以实现TopoSort
    for(int i=0;i<G.vexnum;++i){
        if(indegree[i]==0){
            S.push(i);//入度为0，进入S
        }
    }
    int count=0;//对输出顶点计数
    while(!S.empty()){
        int u=S.top();
        S.pop();
        for(int w=0;w<G.vexnum;++w){
            if(G.AdjMatrix[u][w]!=0){
                indegree[w]--;
                if(indegree[w]==0){
                    S.push(w);
                }
            }
        }
        count++;
    }
    if(count<G.vexnum){
        return false;//TopoSort失败 有环
    }else{
        return true;//TopoSort成功
    }
}
```

## Dijkstra

## Floyd

