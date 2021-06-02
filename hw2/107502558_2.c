#include <stdio.h>
#include <stdlib.h>
int main()
{
    int  card = 0, front =0,rear =0;
    int *quene = (int *)malloc(sizeof(int) * 100);
    
    while (1)
    {
        rear = 0;
        front = 0;
        scanf("%d", &card); 
        if(card ==0){
            break;
        }
        for ( int i=1; i<card+1; ++i){
            quene[rear++] = i;
        }
        printf("Discarded  cards: ");
        for (int i = 0; rear-1 != front;){
            printf("%d", quene[front]);
            front++;
            quene[rear++] = quene[front];
            front++;
            if(rear-1 != front){
                printf(", ");
            }
        }
        printf("\nRemaining card: %d\n",quene[front] );
    }
        
    
    return 0;
}