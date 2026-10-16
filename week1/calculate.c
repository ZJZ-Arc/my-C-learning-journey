#include  <stdio.h>
int main()
{
    printf("请输入身高的英尺和英寸\n");
    int feet,inches=0;
    scanf("%d %d",&feet,&inches);
    printf("您的身高是%f米\n", ((feet,+inches/12.0)*0.3048));
    return 0;
}        