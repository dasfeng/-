#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//定义多个进程和资源
#define MAX_PROCESS_NUM 10
#define MAX_RESOURCE_NUM 10

//创建结构体包含可利用资源向量Available，最大需求矩阵Max，已分配矩阵Allocation，需求矩阵Need，进程请求量Request，进程数和资源数
typedef struct{
    int Available[10];
    int Max[10][10];
    int Allocation[10][10];
    int Need[10][10];
    int Request[10][10];
    int Work[10];
}Resources;

//输入进程个数
void InputProcessNum(int *process_num){
    printf("Input the process number:\n");
    scanf("%d",process_num);
}

//输入资源个数
void InputResourceNum(int *resource_num){
    printf("Input the resource number:\n");
    scanf("%d",resource_num);
}

//输入可利用资源向量Available
void InputAvailable(int *available,int resource_num){
    printf("Input the available vector:\n");
    for(int i=0;i<resource_num;i++){
        scanf("%d",&available[i]);
    }
}

//输入最大需求矩阵Max
void InputMax(Resources *res,int process_num,int resource_num){
    int i,j;
    printf("Input the Max matrix:\n");
    for(i=0;i<process_num;i++){
        for(j=0;j<resource_num;j++){
            scanf("%d",&res->Max[i][j]);
        }
    }
}

//输入已分配矩阵Allocation
void InputAllocation(Resources *res,int process_num,int resource_num){
    int i,j;
    printf("Input the Allocation matrix:\n");
    for(i=0;i<process_num;i++){
        for(j=0;j<resource_num;j++){
            scanf("%d",&res->Allocation[i][j]);
        }
    }
}

//计算需求矩阵Need
void CalculateNeed(Resources *res,int process_num,int resource_num){
    int i,j;
    for(i=0;i<process_num;i++){
        for(j=0;j<resource_num;j++){
            res->Need[i][j]=res->Max[i][j]-res->Allocation[i][j];
        }
    }
}

//输入进程请求量Request,检测并分配资源
void InputRequest(Resources *res,int process_num,int resource_num){
    int i,j;
    printf("Input the first few processes:\n");
    scanf("%d",&i);
    printf("Input the Request vector:\n");
    for(j=0;j<resource_num;j++){
        scanf("%d",&res->Request[i][j]);
    }
    //判断请求量是否大于需求量
    for (int j=0;j<resource_num;j++){
        if(res->Request[i][j]>res->Need[i][j]){
            printf("The Request vector is too large!\n");
            exit(0);
        }
    }
    //判断请求量是否大于可利用资源向量
    for (int j=0;j<resource_num;j++){
        if(res->Request[i][j]>res->Available[j]){
            printf("The Request vector is too large!\n");
            exit(0);
        }
    }
    //将资源分配给进程
    for (int j=0;j<resource_num;j++){
        res->Available[j]-=res->Request[i][j];
        res->Allocation[i][j]+=res->Request[i][j];
        res->Need[i][j]-=res->Request[i][j];
    }

    for (int k=0;k<resource_num;k++){
        res->Work[k]=res->Available[k];
    }

    //安全性算法
    int ready[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int re[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int finish=0;
    int l=0;
    int s=0;
    int a=0;
    int h=0;
    //printf("The number of safe sequence is %d\n",s);

    while(finish == 0){  
        //判断是否有进程可以分配资源
        for(i=0;i<process_num ;i++){
            if (re[i]!=0){
                for(j=0;j<resource_num;j++){
                    if(res->Need[i][j]<=res->Work[j]){
                       h++;
                    }
                    else{
                        h=0;
                        break;
                    }
                }
                if(h == resource_num){
                    h=0;
                    re[i]=0;
                    ready[l]=i;
                    for(j=0;j<resource_num;j++){
                        res->Work[j]+=res->Allocation[i][j];
                    }
                    l++;
                    s++;
                }
                a++;
            }
            
        }
        if(a == 400){
            finish=1;
        }
        if (s==process_num){
            finish=1;
        }


    }
    //输出s
    printf("The number of safe sequence is %d\n",s);

    if (ready[process_num-1] == -1){
        printf("The system is unsafe!\n");
    }
    else{
        printf("The system is safe!\n");
        printf("The safe sequence is:\n");
        for (int d=0;d<process_num;d++){
            printf("P%d\t",ready[d]);
        }
    }
    

}

int main (){
    int process_num,resource_num,num;
    Resources res;
    InputProcessNum(&process_num);
    InputResourceNum(&resource_num);
    InputAvailable(res.Available,resource_num);
    InputMax(&res,process_num,resource_num);
    InputAllocation(&res,process_num,resource_num);
    CalculateNeed(&res,process_num,resource_num);
    InputRequest(&res,process_num,resource_num);
    return 0;
}



