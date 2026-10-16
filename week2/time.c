#include <stdio.h>
int main()
{
   int hour,second,min,total;
   printf("输入总秒\n");
   scanf("%d",&total);
   hour = total / 3600;
   min = ( total % 3600 ) / 60 ;
   second = ( total % 3600 ) % 60;
   printf("为%d小时%d分钟%d秒",hour,min,second);  /*second=total%60等价的*/

   return 0;
}
