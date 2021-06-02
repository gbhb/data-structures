#include"stdio.h"
#include"stdlib.h"
#include"math.h"
typedef struct htree *ptree;
struct htree{
    int lab;
    int fre;
    ptree left;
    ptree right;
    ptree slink;
};
void sort(ptree *f){
    int count=0;
    ptree p=*f;
    while(p){
        count++;
        p=p->slink;
    }

    int i;
    for(i=1;i<=count;++i){
        p=*f;
        int j;
        for(j=1;j<=count-i;++j){
            if((p->fre > p->slink->fre) || ((p->fre==p->slink->fre) && (p->lab > p->slink->lab))){
                ptree after=p->slink;
                int temp1;
                temp1=p->fre;
                p->fre=after->fre;
                after->fre=temp1;
                temp1=p->lab;
                p->lab=after->lab;
                after->lab=temp1;
                ptree temp2;
                temp2=p->left;
                p->left=after->left;
                after->left=temp2;
                temp2=p->right;
                p->right=after->right;
                after->right=temp2;
            }
                p=p->slink;

        }
    }
}
typedef struct table *ptable;
struct table{
    int key;
    int label;
    int count;
    int fre;
    ptable link;
};
void msort(ptable *f){
    int count=0;
    ptable p=*f;
    while(p){
        count++;
        p=p->link;
    }

    int i;
    for(i=1;i<=count;++i){
        p=*f;
        ptable pre=*f;
        int j;
        for(j=1;j<=count-i;++j){
            if(p->label > p->link->label){
                ptable after=p->link;
                if(pre==p){
                    p->link=after->link;
                    pre=after;
                    after->link=p;
                    *f=after;
                }else{
                    p->link=after->link;
                    pre->link=after;
                    after->link=p;
                    pre=pre->link;
                }
            }else{
                if(pre==p){
                    p=p->link;
                }else{
                    p=p->link;
                    pre=pre->link;
                }
            }
        }
    }
}
void print(ptable p){
    while(p){
        if(p->label==' '){
            printf("Space: ");
        }else{
            printf("%c: ",p->label);
        }
        int n=p->key;
        int i;
        for(i=p->count-1;i>=0;--i){
            printf("%d",n/(int)pow(2,i));
            n=n%(int)pow(2,i);
        }
        printf("\n");
        p=p->link;
    }
}

/*void tprint(ptree r){
    if(r){
        tprint(r->left);
        printf("%d\t%c\n",r->fre,r->lab);
        tprint(r->right);
    }
}*/
void searchleaf(ptree r,ptable *t,int v,int c){
    if(r->left==NULL && r->right==NULL){
        ptable temp;
        temp=(ptable)malloc(sizeof(struct table));
        temp->key=v;
        temp->count=c;
        temp->fre=r->fre;
        temp->label=r->lab;
        if(*t==NULL){
            *t=temp;
        }else{
            ptable temp2=*t;
            while(temp2->link!=NULL)
                temp2=temp2->link;
            temp2->link=temp;
        }
        return;
    }
    searchleaf(r->left,t,v*2+0,c+1);

    searchleaf(r->right,t,v*2+1,c+1);
}
int main(){
    char c;
    ptree first=NULL;
    while(scanf("%c",&c) && c!='\n'){

        if(c==' ' || (c>='A' && c<='Z') || (c>='a' && c<='z')){
            if(first==NULL){
                first=(ptree)malloc(sizeof(*first));
                first->slink=NULL;
                first->left=NULL;
                first->right=NULL;
                first->fre=1;
                first->lab=(int)c;
            }else{
                ptree btemp=first;
                while(btemp!=NULL){
                    if(btemp->lab==c){
                        btemp->fre++;
                        break;
                    }else {
                        btemp=btemp->slink;
                    }
                }
                if(btemp==NULL){
                    btemp=first;
                    while(btemp->slink!=NULL){
                        btemp=btemp->slink;
                    }
                    ptree temp=NULL;
                    temp=(ptree)malloc(sizeof(*temp));
                    temp->slink=NULL;
                    temp->left=NULL;
                    temp->right=NULL;
                    temp->fre=1;
                    temp->lab=(int)c;
                    btemp->slink=temp;
                }
            }
        }
    }

    sort(&first);

    ptree root=NULL;
    while(1){
        ptree temp;
        temp=(ptree)malloc(sizeof(*temp));
        temp->left=first;
        temp->right=first->slink;
        temp->fre=first->slink->fre+first->fre;
        temp->lab=(int)first->lab;
        first=first->slink->slink;
        if(first==NULL){
            root=temp;
            break;
        }
        temp->slink=first;
        first=temp;
        sort(&first);
    }
    //tprint(root);
    ptable map=NULL;
    searchleaf(root,&map,0,0);

    //print(map);
    msort(&map);
    printf("Huffman code:\n");
    print(map);

    ptable pmap=map;
    int sum=0,cfre=0;
    while(pmap){
        cfre=cfre+pmap->fre;
        sum=sum+pmap->fre*pmap->count;
        pmap=pmap->link;
    }
    printf("Minimum weighted external path length: %d\n",sum);
    printf("Compression ratio: %d/%d\n\nPlease input the code: ",cfre*8-sum,cfre*8);

    sum=0;
    int cnum=0;
    while(scanf("%c",&c) && c!='\n'){
        sum=sum*2+c-'0';
        cnum++;
        pmap=map;
        while(pmap){
            if(sum==pmap->key && cnum==pmap->count){
                printf("%c",pmap->label);
                sum=0;
                cnum=0;
                break;
            }
            pmap=pmap->link;
        }
    }
    printf("\n");
    return 0;
}
//Baby, baby, baby oh Like baby, baby, baby no Like baby, baby, baby ooh
//010011100001001110000100101110111
