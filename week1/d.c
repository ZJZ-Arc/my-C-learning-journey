#include <stdio.h>

int main()
{
    printf("%d\n", 372%72);    // 少了参数会打印出垃圾值，\n 别忘
    printf("按回车键继续...");    // getchar() 等的是回车，不是"任意键"
    getchar();
    return 0;
}