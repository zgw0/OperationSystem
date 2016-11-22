#define RPN 5 //虚拟存储大小
#define PAGESNUM 50 //页面执行序列的最大长度
void testError(int err, int total);
int iInResidentPages(int residentPages[], int RPN1, int page, int * errNum);
void print(int pages[], int n);
void randomPages(int pages[], int n);
void init(int ResidentPages[], int RPN1);

