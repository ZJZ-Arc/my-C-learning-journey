#include <stdio.h>
int main()
{
    int num ,a,b,c;
    printf("请输入三位数字\n");
    scanf("%d",&num);
    a = num  / 100;
    b = (num % 100 )/10;
    c = num % 10;
    printf("各位数字之和为%d\n",a + b + c);
    return 0;
}