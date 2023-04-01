#define TElemType int
typedef struct BiTNode{
    TElemType data;
    struct BiTNode* lchild,*rchild;
}BiTNode,*BiTree;

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
