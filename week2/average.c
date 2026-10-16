#include <stdio.h>
int main()
{ 
    double a=0.0,b=0.0,c=0.0;
    printf("输入三科成绩。\n");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {   /* 一个 scanf，带检查 */
        printf("输入无效，需要三个数字。\n");
        return 1;
}
    printf("平均成绩为：%.2f\n",(a+b+c)/3);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    printf("按回车键退出...");
    getchar();
    return 0;
}
  