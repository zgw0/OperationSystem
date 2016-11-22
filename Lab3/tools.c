#include<stdio.h>
#include<time.h>
#include<stdlib.h>

/*
* 初始化内存空间
*/
void init(int arr[], int n)
{
	for (int i = 0; i<n; i++) {
		arr[i] = 0;
	}
}




/*
* 随机产生执行执行序列
*/
void randomPages(int pages[], int n)
{
	srand(time(NULL));
	for (int i = 0; i<n; i++) {
		pages[i] = rand() % 9 + 1;
	}
}


/*
* 打印执行序列
*/
void print(int pages[], int n)
{
	for (int i = 0; i<n; i++) {
		printf("%d ", pages[i]);
	}
	printf("\n");
}


/*
* 判断是否该页是否已经在内存中
* 如果在则返回下标
* 如果不在，且空间已满则返回-1，未满则存入且返回下表
*/
int iInResidentPages(int residentPages[], int RPN1, int page, int * errNum)
{
	for (int i = 0; i<RPN1; i++) {
		if (residentPages[i] == 0) {
			(*errNum)++;
			printf("-%d-", page);
			residentPages[i] = page;
			return i;
		}
		else if (residentPages[i] == page) {
			return i;
		}
	}
	(*errNum)++;//printf("\n---()-------%d\n",*errNum);
	return -1;
}


/*
* 计算并输出缺页数、缺页率和命中率
*/
void testError(int err, int total)
{
	float errPct = 1.0*err / total;
	printf("\n缺页数：%d\n", err);
	printf("缺页率：%f\n", errPct);
	printf("命中率： %f\n", 1 - errPct);
}
