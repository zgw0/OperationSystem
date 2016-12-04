#define Num 100

typedef struct pro
{
    char name[20]; //进程名称
    int arrTime; //到达时间
    int serTime; //服务时间
    int finTime; //结束时间
    int cycTime; //周转时间
    float  resRation; //响应比
}pro;

void printResult(pro process[], int n);

void copy(pro process[], pro tempPro[], int n);

void sortByArrTime(pro process[], int n);

void sortOfPro(pro process[], int sort[],int n);

int isFinish(pro process[], int n);

void print(pro process);
