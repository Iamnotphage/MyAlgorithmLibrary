# My-Algorithm-Library

    Collect the DS & Algorithms I have learned.

- [My-Algorithm-Library](#my-algorithm-library)
- [前言](#前言)
- [表、栈和队列](#表栈和队列)
- [树](#树)
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

# 树



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



