#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char ans;
    do
    {
        srand(time(0));
        int i,a,b;
        int number[10]={0,1,2,3,4,5,6,7,8,9},output[10];
        for(i=10;i>=1;i--)
        {
            a=rand()%i;
            output[i-1]=number[a];
            number[a]=number[i-1];
        }
        for(i=9;i>=0;i--)
        {
            printf("%d ",output[i]);
        }
        printf("\nagain ? (Y/N)");
        scanf(" %c",&ans);
        printf("\n");
    }while(ans=='y'||ans=='Y');
    return 0;
}
