#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int ans[4],user[4],i,j,n,A,B;
    int pass;
    char yn;
    srand(time(0));
    do
    {
        for(i=0;i<4;i++)
        {
            ans[i]=rand()%10;
            while(1)//ans 不重複
            {
                pass=0;
                for(j=1;j<=i;j++)
                {
                    if(ans[i]==ans[i-j])
                    {
                        ans[i]=rand()%10;
                        pass=1;
                    }
                    if(pass)
                    {break;}
                }
                if(pass==0)
                {break;}
            }
        }
        for(n=1;n<=10;n++)//game start
        {
            A=0;B=0;
            printf("請輸入四位不重複的數字：");
            for(i=0;i<4;i++)//輸入
            {
                scanf("%d",&user[i]);
            }
            while(1)//檢查重複
            {
                pass=0;
                for(i=0;i<4;i++)//檢查重複
                {
                    for(j=1;j<=i;j++)
                    {
                        if(user[i]==user[i-j])
                        {
                            pass=1;
                        }
                        if(pass)
                        {break;}
                    }
                    if(pass)
                    {break;}
                }
                if(pass)//重新輸入
                {
                    printf("數字重複，請重新輸入：");
                    for(i=0;i<4;i++)
                    {
                        scanf("%d",&user[i]);
                    }
                }
                else{break;}
            }
            for(i=0;i<4;i++)//A
            {
                if(user[i]==ans[i])
                {
                    A+=1;
                }
            }
            for(i=0;i<4;i++)//B
            {
                for(j=0;j<4;j++)
                {
                    if(user[i]==ans[j])
                    {
                        B+=1;
                    }
                }
            }
            B-=A;
            printf("%02d.",n);
            for(i=0;i<4;i++)
            {
                printf(" %d",user[i]);
            }
            printf(" %dA%dB\n",A,B);
            if(A==4)
            {
                break;
            }
        }
        if(A==4)
        {
            printf("恭喜你答對了！答案就是");
        }
        else
        {
            printf("再接再厲！答案是");
        }
        for(i=0;i<4;i++)
        {
            printf(" %d",ans[i]);
        }
        printf("\n\n要在玩一次嗎？(Y/N)");
        scanf(" %c",&yn);
    }while(yn=='Y'||yn=='y');
    return 0;
}
