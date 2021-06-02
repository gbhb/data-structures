#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct coordinate
{
    double x, y;
} coordinate;

typedef struct edge
{
    int xy1;
    int xy2;
    double length;
} edge;

int cmp(const edge lhs, const edge rhs)
{
    return lhs.length - rhs.length;
}

void swap(edge *lhs, edge *rhs) //lhs = left hand side
{
    edge tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
}

int find_root(int x, int parent[])
{
    int x_root = x;
    if(parent[x_root] == -1){
        return x_root;
    }
    return find_root(parent[x_root], parent);
}


int main(int argc, char *argv[])
{
    while (1)
    {
        int n = 0;
        double total_cost = 0;
        scanf("%d", &n);
        /*if (n < 0)
        {
            break;
        }*/

        int *p = malloc(sizeof(int) * n);

        coordinate *c = malloc(sizeof(coordinate) * n);
        double a, b;
        edge *e = malloc(sizeof(edge) * ((n * n - n) / 2));
        ;
        for (int i = 0; i < n; i++)
        {
            scanf("%lf %lf", &a, &b);
            c[i].x = a;
            c[i].y = b;
        }
        int k = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                double cmp = 0;
                e[k].xy1 = i;
                e[k].xy2 = j;
                cmp = pow((c[i].x - c[j].x), 2) + pow((c[i].y - c[j].y), 2);
                e[k].length = sqrt(cmp);
                k++;
            }
        
        //bubble sort
        for (int j = 0; j < ((n * n - n) / 2)-1; j++)
        {
            for (int i = 0; i < ((n * n - n) / 2) - j-1; i++)
                if (e[i].length > e[i + 1].length)
                {
                    swap(&e[i], &e[i + 1]);
                }
        }

        //initialize
        for (int i = 0; i < n; i++)
        {
            p[i] = -1;
        }
        for (int i = 0; i < (n * n - n) / 2; i++)
        {   
            int x_root = find_root(e[i].xy1, p);
            int y_root = find_root(e[i].xy2, p);
            if(x_root != y_root){
                p[y_root] = x_root;
                total_cost += e[i].length;
            }

        }
        printf("The shortest distance=%.3lf\n", floor(total_cost*1000)/1000);
    }
        return 0;
}