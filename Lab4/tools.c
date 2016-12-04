#include<stdio.h>
#include<string.h>
#define Num 100

typedef struct pro
{
    char name[20]; //进程名称
    int arrTime; //到达时间
    int serTime; //服务时间
    int finTime; //结束时间
    int cycTime; //周转时间
    float  resRation; //响应比
}pro;

void print(pro process)
{
    printf("进程：%s\n", process.name);
    printf("\t到达时间：%d\n", process.arrTime);
    printf("\t服务时间：%d\n", process.serTime);
    printf("\t结束时间：%d\n", process.finTime);
    printf("\t周转时间：%d\n", process.cycTime);
}

void printResult(pro process[], int n)
{
    for (int i = 0; i<n; i++) {
        printf("进程 %s:\n", process[i].name);
        //printf("\t到达时间：%d\n", process[i].arrTime);
        //printf("\t服务时间：%d\n", process[i].serTime);
        printf("\t完成时间：%d\n", process[i].finTime);
        printf("\t周转时间：%d\n", process[i].cycTime);
        printf("\t响应比： %.2f\n", process[i].resRation);
    }
}

void copy(pro process[], pro tempPro[], int n)
{
    for (int i = 0; i<n; i++) {
        tempPro[i] = process[i];
        //print(tempPro[i]);
    }
}

void sortByArrTime(pro process[], int n)
{
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n - i - 1; j++) {
            if (process[j].arrTime>process[j + 1].arrTime) {
                pro temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

void sortOfPro(pro process[], int sort[],int n)
{
    pro tempPro[Num];
    copy(process, tempPro, n);
    
    int hasSort[Num] = { 0 };
    sortByArrTime(tempPro, n);
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (hasSort[j]) {
                continue;
            }
            if (strcmp(process[j].name, tempPro[i].name) == 0) {
                sort[j] = i;
                break;
            }
        }
    }
}

int isFinish(pro process[], int n)
{
    for (int i = 0; i<n; i++) {
        if (process[i].serTime>0) {
            return 0;
        }
    }
    return 1;
}