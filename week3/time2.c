#include <stdio.h>
int main()
{
    int hour1,minute1;
    int hour2,minute2;
    printf("请输入第一时分.\n");
    scanf("%d %d",&hour1,&minute1);
    printf("请输入第二时分.\n");
    scanf("%d %d",&hour2,&minute2);
    int ih,im;
    ih = hour1 -hour2;
    im = minute1 -minute2;
    if(im<0){
        im = im +60;
        ih = ih - 1;
    }
    printf("时间差为%d时%d分.\n",ih,im);
    return 0;
}
   
