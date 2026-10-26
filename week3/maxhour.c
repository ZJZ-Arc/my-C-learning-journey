#include <stdio.h>
double calculate_maxnum(double a,double b)
{
    double max;
    max = b;
    if(a>b){
        max = a;
    }
    return max;
}
int main(void)
{
    double a,b = 0.0;
    printf("请输入两个数字。\n");
    scanf("%lf %lf",&a,&b);
    double max = calculate_maxnum(a,b);
    printf("较大数为：%.2lf\n",max);
    return 0;
}