#include<stdio.h>
#include "tools.h"

void FIFO(int residentPages[], int RPN1, int pages[], int PAGESNUM1)//先进先出算法（First In First Out）
{
	int errNum = 0;
	int p = 0;//堆栈指针
	printf("缺页号：");
	for (int i = 0; i<PAGESNUM1; i++) {
		if (iInResidentPages(residentPages, RPN1, pages[i], &errNum) == -1) {
			printf("-%d-", pages[i]);
			residentPages[p] = pages[i];
			p++;
			if (p == RPN) {//指针到堆栈尾巴后又回到开头
				p = 0;
			}
		}
	}
	testError(errNum, PAGESNUM);//计算缺页数、缺页率和命中率
}
