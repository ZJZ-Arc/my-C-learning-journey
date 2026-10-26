#include <stdio.h>
void print_array(int nums[],int number)
{
    for(int i = 0; i < number ; i++){
        printf("%d\n",*(nums + i));
    }
}
int total_nums(int *nums,int number){
    int total = 0 ;
    for(int i = 0; i < number ; i++){
        total = total +nums[i];
        }
    return total;    
}
void add_five(int *nums,int number){
    for(int i = 0;i < number ; i ++){
        nums[ i ]+= 5;
    }
    for(int i = 0; i < number ; i++){
        printf("%d\n",*(nums + i));
    }
}
int main(void)
{
    int number = 0;
    int total = 0;
    printf("输入数组的模");
    scanf("%d",&number);
    int nums[number];
    for(int i = 0; i < number ; i ++){
        printf("输入第%d个数",i + 1);
        scanf("%d",&*(nums + i));
    }
    print_array(nums,number);
    total = total_nums(nums,number);
    printf("总和为%d\n",total);
    printf("加五后遍历\n");
    add_five(nums,number);
    return 0;
}