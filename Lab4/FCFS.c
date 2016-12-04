#include "tools.h"

/*
* 先来先服务 FCFS
*/
void FCFS(pro process[],int n)
{
    pro tempPro[Num];
	copy(process, tempPro, n);
	int sort[Num];
	sortOfPro(process,sort, n);
	sortByArrTime(tempPro, n);//按达到时间排序，排序后依次执行
	int currTime = 0;
	for (int i = 0; i<n; i++) {
		currTime += tempPro[i].serTime;
		process[sort[i]].finTime = currTime;
		process[sort[i]].cycTime = process[sort[i]].finTime - process[sort[i]].arrTime;
		process[sort[i]].resRation = process[sort[i]].cycTime * 1.0 / process[sort[i]].serTime;
	}

	printf("\n------ FCFS -------\n");
	printResult(process, n);//打印运行结果
}
