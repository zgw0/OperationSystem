#include<stdio.h>
#include "exchange.h"
#include "tools.h"
//RPN:Resident Pages Number

int main()
{

	int ResidentPages[RPN];
	int pages[PAGESNUM];

	randomPages(pages, PAGESNUM);//随机产生页面执行序列

	printf("随机产生页面执行序列：\n");
	print(pages, PAGESNUM);//打印页面执行序列
	
	printf("\n页面执行序列长度：%d\n内存分配大小：%d\n",PAGESNUM,RPN);

	printf("\n------\nOPT\n");
	init(ResidentPages, RPN);
	OPT(ResidentPages, RPN, pages, PAGESNUM);//OPT算法

	printf("\n------\nFIFO\n");
	init(ResidentPages, RPN);
	FIFO(ResidentPages, RPN, pages, PAGESNUM);//FIFO算法

	printf("\n------\nLRU\n");
	init(ResidentPages, RPN);
	LRU(ResidentPages, RPN, pages, PAGESNUM);//LRU算法
	return 0;
}
