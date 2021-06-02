#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define char_span (1 << (sizeof(char) << 3))

typedef struct node
{
    char character;
    int frequency;
    struct node *left, *right;
} node;

void free_tree(node *tree)
{
    if (!tree)
        return;
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
    tree = NULL;
}

int find_node(char *encode, node *tree, char key)
{
    if (!tree->left && tree->character == key)
        return 1;
    if (!tree->left)
        return 0;
    if (find_node(encode, tree->left, key))
    {
        strcat(encode, "0");
        return 1; //return last find_node 1
    }
    else if (find_node(encode, tree->right, key))
    {
        strcat(encode, "1");
        return 1;
    }
    return 0;
}
node *merge(node *left, node *right)
{
    if (!left || !right)
        return NULL;
    node *parent = (node *)malloc(sizeof(struct node));
    parent->left = left;
    parent->right = right;
    parent->character = left->character;
    parent->frequency = left->frequency + right->frequency;
    return parent;
}

int comp(const void *lhs, const void *rhs)
{ //lhs = left hand side
    if ((*(const node **)lhs)->frequency == (*(const node **)rhs)->frequency)
        return (*(const node **)lhs)->character - (*(const node **)rhs)->character; //to allow dictionary sequential
    return (*(const node **)lhs)->frequency - (*(const node **)rhs)->frequency;
}

int main(int argc, char *argv[])
{
    char input[1024] = {};
    fgets(input, 1024, stdin);

    int frequency_map[char_span] = {};
    for (char *it = input; *it; it++) //it is pointer
        if (isalnum(*it) || *it == ' ')
            frequency_map[*it]++; // *it is ascii code

    int countnum = 0;
    node *arr[char_span] = {};
    for (int i = 0; i < char_span; i++)
    {
        if (frequency_map[i])
        {
            arr[countnum] = (node *)calloc(1, sizeof(struct node)); //size = 4+4+8+8
            arr[countnum]->frequency = frequency_map[i];
            arr[countnum]->character = i;
            countnum++;
        }
    } // creat all leaves

    // sort array small to big
    qsort(arr, countnum, sizeof(node *), comp);

    int offset;
    for (offset = 0; offset < countnum - 1; offset++)
    {
        // pick the first two smallest nodes and merge them together
        // then put the merged node back into array to resort
        arr[offset + 1] = merge(arr[offset], arr[offset + 1]);
        // bubble sort
        for (int j = offset + 1; j < countnum - 1 && comp(&arr[j], &arr[j + 1]) > 0; j++)
        { //comp(&arr[j], &arr[j + 1]) > 0 when after merge the arr[offset+1] big then next one resort to small to big array
            node *tmp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = tmp;
        }
    }
    node *huffman_tree = arr[offset]; //root = last array element
    int total_length = 0;
    for (int i = 0; i < char_span; i++)
    {
        if (frequency_map[i])
        {
            if (i == ' ')
                printf("Space: ");
            else
                printf("%c: ", i);

            char encode[256] = {};
            if (find_node(encode, huffman_tree, i))
                printf("%s", strrev(encode));
            printf("\n");
            total_length += frequency_map[i] * strlen(encode); //calculate total length
        }
    }
    printf("Minimum weighted external encode length: %d\n", total_length);
    printf("Compression ratio: %d/%d\n\n", huffman_tree->frequency * 8 - total_length, huffman_tree->frequency * 8);
    printf("Please input the code: ");
    char buf[1024] = {}, output[1024] = {};
    fgets(buf, 1024, stdin);
    // step-down until we reach the leaf
    node *search_node = huffman_tree;
    for (char *it = buf; *it; ++it)
    {
        if (*it == '0')
            search_node = search_node->left;
        else if (*it == '1')
            search_node = search_node->right;
        if (!search_node->left)
        { // reach the end, left = null
            printf("%c", search_node->character);
            search_node = huffman_tree; //return the root
        }
    }
    printf("\n");

    free_tree(huffman_tree);
    return 0;
}
