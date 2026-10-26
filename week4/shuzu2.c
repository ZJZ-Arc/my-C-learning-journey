#include <stdio.h>
double calculate_total(double hours[],int day){
    double total = 0.0;
    for(int i = 0 ;i < day; i++) {
        total += hours[i];   
    }
    return total;
}
double calculate_max_hours(double hours[],int day){
    double max_hours = hours[0];
    for(int i = 0;i < day;i++){
        if(max_hours < hours[i]){
        max_hours = hours[i];
        }
    }
    return max_hours;
}
int main(void){
    int day;
    printf("输入记录的天数。\n");
    scanf("%d",&day);
    while(day <= 0 || day > 30){
        printf("错误，重新输入。\n");
        scanf("%d",&day);
    }
    double hours[day];
    double average = 0.0,max_hours = 0.0,total = 0.0;

    for(int a = 0;a < day ;a++){
        printf("输入第%d天的学习时间。\n",a + 1);
        scanf("%lf",&hours[a]);
        while(hours[a] < 0 || hours[a] > 24){
            printf("错误，重新输入。\n");
            scanf("%lf",&hours[a]);
        }
    }
    total = calculate_total(hours,day);
    average = total / day;
    max_hours = calculate_max_hours(hours,day);
    printf("总时长:%.1f\n平均时长%.1f\n最大时长%.1f\n",total,average,max_hours);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    printf("按回车键退出...");
    getchar();
    
    return 0;
}