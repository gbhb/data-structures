#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    int next;
    int cost;
} edge;

struct min_heap
{
    edge stack[1024];
    int tail;
};

int compare(const edge lhs, const edge rhs)
{
    if (lhs.cost == rhs.cost)
        return lhs.next - rhs.next;
    return lhs.cost - rhs.cost;
}

void swap(edge *lhs, edge *rhs) //lhs = left hand side
{
    edge temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

int choose_left_right(const struct min_heap *h, const unsigned int father)
{
    int left = father * 2 + 1, right = left + 1;
    if (right > h->tail) // if  father have one or no child
        return left > h->tail ? 0 : left;
    return compare(h->stack[left], h->stack[right]) <= 0 ? left : right;
}

void pop(struct min_heap *h)
{
    if (h->tail < 0) //tail ==-1 is empty heap
        return;
    edge *t = h->stack;
    swap(&t[0], &t[h->tail--]);                                                                                     // h-> tail ; tail--
    for (int next, index = 0; (next = choose_left_right(h, index)) && compare(t[next], t[index]) < 0; index = next) // rebulid min heap ,first compare left amd right child then compare father and smaller child
        swap(&t[index], &t[next]);
}

edge get_min(const struct min_heap *h)
{
    return (h->tail >= 0) ? h->stack[0] : (edge){0, 0}; // p
}

void push(struct min_heap *h, edge lenght)
{
    if (h->tail >= 1023)
        return;
    edge *t = h->stack;
    t[++(h->tail)] = lenght;
    for (int index = h->tail; (index) && compare(t[index], t[(index - 1) / 2]) < 0; index = (index - 1) / 2)
        swap(&t[index], &t[(index - 1) / 2]);
}

void filter_edges(struct min_heap *h, int edges[], int n) //edges[] = ptr of array
{
    for (int i = 0; i < n; i++)
        if (edges[i])                     // edges[i] = vertex[ ][i]
            push(h, (edge){i, edges[i]}); //i = next ,edges[i] = cost
}

int main(int argc, char *argv[])
{
    while (1)
    {
        int n;
        scanf("%d", &n);
        if (n == -1)
        {
            break;
        }
        struct min_heap h = {.stack = {}, .tail = -1}; // initialize the heap { {},-1 }

        int vertex[26][26] = {0}, connected[26] = {[0] = 1};

        int total_cost = 0, have_connected_num = 1;

        for (int i = 0, temp; i < n; i++) //read the matrix
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &temp);
                vertex[i][j] = temp;
            }

        filter_edges(&h, vertex[0], n); //filter 0 cost and add first row

        for (; h.tail >= 0; pop(&h))
        {
            int next_vertex = get_min(&h).next;
            if (!connected[next_vertex])
            {
                filter_edges(&h, vertex[next_vertex], n);
                total_cost += get_min(&h).cost;
                connected[next_vertex] = 1;
                have_connected_num++;
            }
        }
        if (have_connected_num != n)
        {
            printf("NO connected\n");
        }
        else
        {
            printf("Minimum cost:%d\n", total_cost);
        }
    }

    return 0;
}