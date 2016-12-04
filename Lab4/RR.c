#include "tools.h"
#include<stdio.h>
/*
* 轮转 (轮转时间片为1)
*/
void RR(pro process[], int n)
{
    
    int sort[Num];
    sortOfPro(process, sort, n);
    pro tempPro[Num];
    copy(process, tempPro, n);
    int currTime = 0;
    int k = 1;
    int stack[Num];
    int m = 1;//堆栈下个运行
    stack[0] = sort[0];
    int p = 0;//堆栈当前指针

    while (1) {
        if (isFinish(tempPro, n)) break;//如果所有的进程都已经执行完毕，则终止执行
        currTime++;
        tempPro[stack[p]].serTime--;
        while (k<n && currTime >= tempPro[sort[k]].arrTime) {//如果下一个进程已经到达，则将其加入到队列中来
            if (sort[k] != stack[m]) {
                stack[m++] = sort[k];
                if (m == n)m = 0;
            }
            k++;
        }
        if (tempPro[stack[p]].serTime == 0) {
            process[stack[p]].finTime = currTime;
            process[stack[p]].cycTime = process[stack[p]].finTime - process[stack[p]].arrTime;
            process[stack[p]].resRation = process[stack[p]].cycTime * 1.0 / process[stack[p]].serTime;
        }
        else {
            stack[m++] = stack[p];
            if (m == n)m = 0;
        }
        p++;
        if (p == n)p = 0;
    }

    printf("\n------ RR -------\n");
    printResult(process, n);//打印相关数据
}