#include "tools.h"
/*
* 最高响应比优先
*/

void HRRN(pro process[],int n)
{
    int sort[Num];//进程的对应的顺序
    sortOfPro(process, sort, n);
    pro tempPro[Num];//拷贝进程数组，防止该表进程数组，影响其他算法的结果
    copy(process, tempPro, n);

    int currTime = 0;
    int maxK, maxResRation;//maxK、maxResRation分别记录最高相应比的对应的进程下标和大小
    int k = 0;
    int ready[Num];
    int m;
    while (k<n) {
        m = 0;

        for (int i = 0; i<n; i++) {
            if (tempPro[sort[i]].serTime>0) {
                if (m==0) {
                    maxK = sort[i];
                    maxResRation = tempPro[maxK].resRation;
                }
                if (tempPro[sort[i]].arrTime <= currTime) {
                    tempPro[sort[i]].resRation = (currTime - tempPro[sort[i]].arrTime)*1.0 / tempPro[sort[i]].serTime;
                    ready[m++] = sort[i];
                }
                else {
                    break;
                }
            }
        }

        //若m=0，说明当前无可运行进程，更新当前时间
        if (m == 0) {
            currTime = process[maxK].arrTime;
        }
        else {     
            for (int j = 0; j<m; j++) {
                if (tempPro[ready[j]].resRation > maxResRation) {
                    maxK = ready[j];
                    maxResRation = tempPro[maxK].resRation;
                }
            }

            k++;
            currTime += process[maxK].serTime;
            //记录完成时间、周转时间、响应比
            process[maxK].finTime = currTime;
            process[maxK].cycTime = process[maxK].finTime - process[maxK].arrTime;
            process[maxK].resRation = process[maxK].cycTime * 1.0 / process[maxK].serTime;
            tempPro[maxK].serTime = 0;
        }
    }

    printf("\n------ HRRN -------\n");
    printResult(process, n);
}
