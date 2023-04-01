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

//KMP算法,求模式串T的next值 (改进后的)
void Better_GetNext(char* T,int* next,int Tlength){
    int i=1,j=0;
    next[1]=0;
    while(i<Tlength){
        if(j==0 || T[i]==T[j]){
            ++i;
            ++j;
            if(T[i]!=T[j]){
                next[i]=j;
            }else{
                next[i]=next[j];
            }
        }else{
            j=next[j];
        }
    }
}