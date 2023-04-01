//Sorting.c
#include<stdio.h>
#include<stdlib.h>

//i,j等临时变量最好在一开始声明，以防作用域问题

//swap()
void swap(int* a,int* b){
    int t=*a;
    *a=*b;
    *b=t;
}
//min()
int min(int x,int y){
    return x<y?x:y;
}

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

//堆排序HeapSort 不稳定 O(nlogn)
void HeapSort(){

}

//计数排序CountingSort 稳定 O(n+k)
void CountingSort(){

}

//桶排序BucketSort 稳定 O(n+k)
void BucketSort(){

}

//基数排序RadixSort 稳定 O(n*k)
void RadixSort(){

}

int main(){
    int a[6]={10,7,8,9,1,5};
    int len=6;
    QuickSort(a,0,5);
    for(int i=0;i<len;++i){
        printf("%d ",a[i]);
    }
    return 0;
}