#include <stdio.h>
int main()
{
    int a,b;
    printf("输入两个整数");
    scanf("%d %d",&a,&b);
    int max = b;
    if ( a > b ) {
        max = a;
    }
    printf("较大的数是：%d\n", max);
    return 0;
}