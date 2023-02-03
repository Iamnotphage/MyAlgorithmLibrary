#include<stdio.h>
#include<stdlib.h>
#include "BinHeap.h"
#define MinPQSize 1  //最小堆的大小
#define MinData 0 //必须小于堆中的任何值

struct HeapStruct{
    int Capacity;
    int Size;
    ElementType *Elements;//数组实现
};

int IsEmpty(PriorityQueue H){
    if(H->Size==0){
        return 1;
    }
    return 0;
}

int IsFull(PriorityQueue H){
    if(H->Capacity==H->Size){
        return 1;
    }
    return 0;
}


PriorityQueue Initialize(int MaxElements){
    PriorityQueue H;
    if(MaxElements<MinPQSize){
        printf("Priority queue size is too small");
    }
    H=malloc(sizeof(struct HeapStruct));
    if(H==NULL){
        printf("Out of space");
    }
    H->Elements=malloc((MaxElements+1)*sizeof(ElementType));
    if(H->Elements=NULL){
        printf("Out of space");
    }
    H->Capacity=MaxElements;
    H->Size=0;
    H->Elements[0]=MinData;
    return H;
}

void Insert(ElementType X,PriorityQueue H){
    int i;
    if(isFull(H)){
        printf("Priority queue is full");
        return;
    }
    for(i=++H->Size;H->Elements[i/2]>X;i/=2){
        H->Elements[i]=H->Elements[i/2];
    }
    H->Elements[i]=X;
}

void DeleteMin(PriorityQueue H){
    int i,Child;
    ElementType MinElement,LastElement;
    if(IsEmpty(H)){
        printf("Priority queue is empty");
        return H->Elements[0];
    }
    MinElement=H->Elements[1];
    LastElement=H->Elements[H->Size--];

    for(i=1; i*2<=H->Size ; i=Child){
        Child=i*2;
        if(Child !=H->Size && H->Elements[Child+1] < H->Elements[Child]){
            Child++;//找较小的孩子
        }
        if(LastElement > H->Elements[Child]){
            H->Elements[i]=H->Elements[Child];//H->Elem[i]指的就是空穴
        }else{
            break;
        }
    }
    H->Elements[i]=LastElement;
    return MinElement;
}

