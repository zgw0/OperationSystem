#include "tools.h"
#include<stdio.h>
/*
* 最短剩余时间
*/

void SRT(pro process[], int n)
{
    int sort[Num];
    sortOfPro(process, sort, n);
    pro tempPro[Num];
    copy(process, tempPro, n);
    int currTime = 0;
    int minK, minSerTime;
    int k = 0;
    int next = 0;
    int ready[Num];
    int m;
    while (k<n) {

        if (next < (n-1)) {
            while (currTime >= process[sort[next]].arrTime) {//如果下一个进程已经到达，则将其加入到队列中来
                next++;
            }
        }

        m = 0;
        for (int i = 0; i<n; i++) {
            if (tempPro[sort[i]].serTime > 0) {
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

        //m==0说明当前无可执行进程,更新当前时间
        if (m == 0) {
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

            int interval = tempPro[sort[next]].arrTime - currTime;
            //如果当前时间与即将到来的进程的时间间隔小于最短剩余时间，则只执行间隔时间
            if (interval>0 && interval < minSerTime) {
                minSerTime = interval;
            }

            tempPro[minK].serTime -= minSerTime;
            currTime += minSerTime;
            if (tempPro[minK].serTime == 0) {
                k++;
                process[minK].finTime = currTime;
                process[minK].cycTime = process[minK].finTime - process[minK].arrTime;
                process[minK].resRation = process[minK].cycTime * 1.0 / process[minK].serTime;
            }
        }
    }

    printf("\n------ SRT -------\n");
    printResult(process, n);
}
