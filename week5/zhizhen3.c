#include <stdio.h>
void swap(int *x,int *y){
    int m = *x ;
    *x = *y ;
    *y = m;
}
int main(void)
{
    int a,b;
    printf("输入两个数字。\n");
    scanf("%d %d",&a,&b);
    swap(&a,&b);
    printf("交换为%d和%d\n",a,b);
    return 0;
}