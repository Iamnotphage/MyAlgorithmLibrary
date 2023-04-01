# My-Algorithm-Library

    Collect the DS & Algorithms I have learned.

- [My-Algorithm-Library](#my-algorithm-library)
- [前言](#前言)
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


# 前言

忙碌一阵后，终于想起自己在这里挖了个坑:D

本文内容主要是自己所学所见闻的数据结构与算法的收录。

主体结构按照黑皮书**Data Structures and Algorithm Analysis in C**的目录。

    谨以此库当作我人脑的外存。

23年3月补档，数据结构期末总评100（当然考核肯定水一些，只能说出的题刚好都会）

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



