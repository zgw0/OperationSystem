#include "tools.h"
#include<stdio.h>
/*
* 最短进程优先
*/

void SPN(pro process[], int n)
{
    int sort[Num];
    sortOfPro(process, sort, n);
    pro tempPro[Num];
    copy(process, tempPro, n);
    int currTime = 0;
    int minK, minSerTime;
    int k = 0;
    int ready[Num];
    int m;
    while (k<n) {
        m = 0;
        for (int i = 0; i<n; i++) {
            if (tempPro[sort[i]].serTime>0) {
                if (m==0) {
                    minK = sort[i];
                    minSerTime = tempPro[minK].serTime;
                }
                if (tempPro[sort[i]].arrTime <= currTime) {
                    ready[m++] = sort[i];
                }
                else {
                    break;
                }
            }
        }

        if (m == 0) {//如果ready数组为空，说明当前无可运行进程，将当前时间只为下一个可执行进程的到达时间
            currTime = process[minK].arrTime;
        }
        else {

            //找出最短进程
            for (int j = 1; j<m; j++) {
                if (tempPro[ready[j]].serTime < minSerTime) {
                    minK = ready[j];
                    minSerTime = tempPro[minK].serTime;
                }
            }

            k++;
            currTime += minSerTime;
            process[minK].finTime = currTime;
            process[minK].cycTime = process[minK].finTime - process[minK].arrTime;
            process[minK].resRation = process[minK].cycTime * 1.0 / process[minK].serTime;
            tempPro[minK].serTime = 0;
        }
    }

    printf("\n------ SPN -------\n");
    printResult(process, n);
}
