#include <stdio.h>
int main()
{
    int num;
    printf("输入年份。\n");
    scanf("%d",&num);
    if ( (num%4==0 && num%100!=0 )||(num%400==0))
    {
        printf("该年为闰年。\n");
    }else{
        printf("该年为平年。\n");
    }
    return 0;
}    