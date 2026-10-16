#include <stdio.h>
int main()
{
    printf("请输入温度。\n");
    int temp=0;
    scanf("%d", &temp);
    printf("对应华氏摄氏度为%d\n",temp*9/5+32);
    return 0;
}

