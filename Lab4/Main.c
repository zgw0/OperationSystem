#include "tools.h"
#include "dispatch.h"

/*
* 定义进程数据结构
*/

int main()
{
    pro myPro[5] = {{"A",0,3},{"B",2,6},{"C",4,4},{"D",6,5},{"E",8,2}}; 

    for(int i=0;i<n;i++){
        print(myPro[i]);//打印进程
    }

    FCFS(myPro,5);//先来先服务
    RR(myPro,5);//乱转，q=1
    SPN(myPro,5);//最短进程优先
    SRT(myPro,5);//最短剩余时间
    HRRN(myPro,5);//最高响应比

    return 0;
}
