#include <stdio.h>
void set_zero( int *value){
    
}



int main(void)
{
    int spare = 1;
    int *p=&spare;
    *p = 5;
    printf("%d\n",*p);
    printf("%d\n",spare);
    printf("%p\n",(void*)p);
    printf("%p\n",(void*)&spare);
    return 0;
}