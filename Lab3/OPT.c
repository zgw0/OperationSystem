#include<stdio.h>
#include "tools.h"

void OPT(int residentPages[], int RPN1, int pages[], int PAGESNUM1)//最佳置换算法（Optimal）
{
	int errNum = 0; 
	int willUse[RPN];
	int pn; 
	
	printf("缺页号：");
	for (int i = 0; i<PAGESNUM1; i++) {
		if (iInResidentPages(residentPages, RPN, pages[i], &errNum) == -1) {

			printf("-%d-", pages[i]);

			
			for (int j = 0; j<RPN1; j++) {
				willUse[j] = 0;
			}

			pn = RPN1;

			//printf("\n---内存中的页面---\n");
			//print(residentPages, RPN1);
			//printf("-------------\n");
			
			//往远查看即将被执行的页面，找出最久最不可能被使用到的页面
			for (int j = i + 1; j<PAGESNUM1; j++) {
				if (pn == 1) {
					break;
				}
				for (int k = 0; k<RPN1; k++) {
					if (residentPages[k] == pages[j]) {
						willUse[k] = 1;
						pn--;
					}
				}
			}

			//替换
			for (int t = 0; t<RPN1; t++) {
				if (willUse[t] == 0) {
					residentPages[t] = pages[i];
					break;
				}
			}
		}
	}
	testError(errNum, PAGESNUM); //计算缺页数、缺页率和命中率
}
