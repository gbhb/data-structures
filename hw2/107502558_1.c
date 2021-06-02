#include <stdio.h>
#include <stdlib.h>
int main()
{
    int  tl = 0, stop = 0, trainnum = 0, b = 0,q,i,a=1 ; //stop = stack top ,b=need break ,q is in stack number
    int *stack = (int *)malloc(sizeof(int) * 100);
    while (1)
    {
        if(b==0)
        {
            b=1;
            scanf("%d", &tl);//train length
            if(tl==0)
            {
                a=0;
                break;
            }
        }
        for (i = 0, stop = 0,q=1; i < tl; --stop)
        {
            scanf("%d", &trainnum);
            if(trainnum==0)
            {
                b=0;
                break;
            }
            ++i;
            while (stop == 0 || (trainnum != stack[stop-1] && stop < tl))
            {
                stack[stop++] = q++;
            }
        }
        if (b == 1)
        {
            if (stop == 0)
            {
                printf("Possible output result: true\n");
            }
            else
            {
                printf("Possible output result: false\n");
            }
        }
    }
    return 0;
}
