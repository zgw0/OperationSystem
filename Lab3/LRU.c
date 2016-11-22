#include<stdio.h>
#include "tools.h"

void LRU(int residentPages[], int RPN1, int pages[], int PAGESNUM1)//最近最少使用（Least Recently Used)
{
	int errNum = 0; 
	int willUse[RPN];
	int pn;
	
	printf("缺页号：");
	for (int i = 0; i<PAGESNUM1; i++) {
		if (iInResidentPages(residentPages, RPN1, pages[i], &errNum) == -1) {
			printf("-%d-", pages[i]);
			init(willUse, RPN1);

			pn = RPN1;
			//往远查看历史执行页面，找出内存中最久最不可能使用的页面
			for (int j = i - 1; j >= 0; j--) {
				if (pn == 1) {
					break;
				}
				for (int k = 0; k<RPN1; k++) {
					if (residentPages[k] == pages[j]) {
						if (willUse[k] == 0) {
							willUse[k] = 1;
							pn--;
							break;
						}

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

	testError(errNum, PAGESNUM);//计算缺页数、缺页率和命中率
}
