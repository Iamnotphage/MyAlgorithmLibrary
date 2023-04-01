#define TElemType int
typedef struct BiTNode{
    TElemType data;
    struct BiTNode* lchild,*rchild;
}BiTNode,*BiTree;

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