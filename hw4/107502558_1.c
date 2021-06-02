#include<stdio.h>
#include<stdlib.h>
int IsTree(int nPoint);
int IsInSet(int*n,int nPoint,int x); /* Return member ID in array */
int g[10000][10000];
void Trace(int nPoint,int root);
int visit = 0; /*Tree Traversal*/
int main(){
    int a,b;/* input */
    int numberSet[10000],nPoint;/*numberSet and Set size */
    int indexA,indexB; /*member ID of numberSet*/
    int icase,i,j,multiEdge;

    for(icase =1; ;icase++){
        multiEdge = 0;/*Prevent From muti-edge*/
        scanf("%d%d",&a,&b);
        if(a==-1&&b==-1)return 0;
        if(!a&&!b){
            printf("Case %d is a tree.\n",icase);
            continue;
        }

        /* Initialize */
        for(i=0;i<10000;i++)
            for(j=0;j<10000;j++)
                g[i][j]=0;

        /* EnSet(a,b) */
        if(a==b){
            numberSet[0]=a;
            nPoint = 1;
            g[0][0] = 1;
        }
        else{
            numberSet[0]=a;
            numberSet[1]=b;
            nPoint = 2;
            g[1][0] = 1;
        }
        while(1){
            scanf("%d%d",&a,&b);
            if(!a&&!b)break;/*End Of Case */

            indexA = IsInSet(numberSet,nPoint,a);
            if(indexA==-1){/* EnSet(a,b) */
                numberSet[nPoint++]= a; 
                indexA = nPoint-1;
            }

            indexB = IsInSet(numberSet,nPoint,b);
            if(indexB==-1){/* EnSet(a,b) */
                numberSet[nPoint++]= b;
                indexB = nPoint-1 ;
            }


            if(g[indexB][indexA]==0)
                g[indexB][indexA] = 1;
            else {multiEdge = 1;}
        }

        if(multiEdge)printf("Case %d is not a tree.\n",icase);
        else if(IsTree(nPoint))printf("Case %d is a tree.\n",icase);
        else printf("Case %d is not a tree.\n",icase);

    }
return 0;
}
/* g[a][b] is a <- b and a b is sequential number of array */
int IsInSet(int*numberSet,int nPoint,int x){
    int i;
    for(i=0;i<nPoint;i++)
        if(numberSet[i]==x)return i;
    return -1;
}
int IsTree(int nPoint){
    int i,j;
    int checkSum,nRoot,root;
    for(i=0,nRoot=0;i<nPoint;i++){
        if(g[i][i]==1)return 0;/* connect self */
        for(j=0,checkSum=0;j<nPoint;j++){
            checkSum+=g[i][j];  /* count how many b connect a */
            if(checkSum>1) {return 0;} 
        }

        if(!checkSum) {nRoot++;root = i; }/* Record who is Root because no one will point at root */
    }
    if(nRoot!=1){return 0;} /* have only one */
    /* Check Cycle and path :Using DFS*/
    visit = 1;/*From root */
    Trace(nPoint,root);

    if(visit==nPoint) return 1; /*Is visit the points same with total points */
    else return 0;

}
void Trace(int nPoint,int start){
    int i;
    for(i=0;i<nPoint;i++)
        if(g[i][start]){
            visit++;
            Trace(nPoint,i);
        }
    return ;
}