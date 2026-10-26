#include <stdio.h>
double calculate_average(double total,int days)
{
    return total / days;
}
double calculate_max_hours(double max_hours,double hours)
{
    if(max_hours>hours){
        return max_hours;
    }else{
        return hours;
    }
    
}
int main(void)
{
    int days;
    double hours;
    double total = 0.0;
    double max_hours = 0.0;
    
    
    printf("请输入记录天数\n");
    scanf("%d",&days);

    if(days <= 0){
        printf("输入错误,天数必须大于0。\n");
        return 1;
    }

    for (int day = 1;day <= days ; day++){
        printf("请输入第%d天的学习时长\n",day);
        scanf("%lf",&hours);
        while(hours < 0 || hours > 24){
            printf("输入错误,请重新输入。\n");
            scanf("%lf",&hours);
        }
        total = total + hours;
        max_hours = calculate_max_hours(max_hours,hours);
    }
    
    double average = calculate_average(total,days);
    printf("总学习时长为：%.1f小时\n",total);
    printf("平均学习时长为：%.1f小时\n",average);
    printf("最长学习时间为：%.1f小时\n",max_hours);
    return 0;
}



    
   
