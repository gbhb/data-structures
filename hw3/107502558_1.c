#include <stdio.h>
#include <stdlib.h>
struct binary_search_tree_node
{
    int data;
    struct binary_search_tree_node *left;
    struct binary_search_tree_node *right;
};
typedef struct binary_search_tree_node BSTNode;

void print_inorder(BSTNode *ptr);
void print_preorder(BSTNode *ptr);
void print_postorder(BSTNode *ptr);
BSTNode *insert_node(BSTNode *root, int value);

int main()
{
    int num, in;

    while (1)
    {
        BSTNode *head = 0;// in the beginning root is null
        scanf("%d", &num);
        if (num == -1)
        {
            break;
        }
        for (int i = 0;i < num; i++)
        {
            scanf("%d", &in);
            head = insert_node(head, in);
        }
        printf("Preorder: ");
        print_preorder(head);
        printf("\n");
        printf("Inorder: ");
        print_inorder(head);
        printf("\n");
        printf("Postorder: ");
        print_postorder(head);
        printf("\n");
        printf("\n");
    }

    return 0;
}
BSTNode *insert_node(BSTNode *root, int value)
{
    BSTNode *new_node;
    BSTNode *current;
    BSTNode *parent;

    // 建立節點
    new_node = (BSTNode *)malloc(sizeof(BSTNode));
    new_node->data = value;
    new_node->left = 0;
    new_node->right = 0;
    if (root == 0) // 目前無資料
    {
        return new_node;
    }
    else
    {
        current = root; // 從頭找要新節點之插入點
        while (current != 0)
        {
            parent = current; // 找新節點之父節點
            if (current->data > value)
                current = current->left; // 往左找
            else
                current = current->right; // 往右找
        }
        if (parent->data > value)    // 插入此父節點左邊或右邊
            parent->left = new_node; // 小左
        else
            parent->right = new_node; //大於等於右
    }
    return root; // 回傳此樹
}
void print_inorder(BSTNode *ptr)
{
    if (ptr != 0)
    {
        print_inorder(ptr->left);  // 走左子樹
        printf("%d ", ptr->data);  // 印出節點內容
        print_inorder(ptr->right); // 走右子樹
    }
}
void print_postorder(BSTNode *ptr)
{
    if (ptr != 0)
    {
        print_postorder(ptr->left);  // 走左子樹
        print_postorder(ptr->right); // 走右子樹
        printf("%d ", ptr->data);    // 印出節點內容
    }
}
void print_preorder(BSTNode *ptr)
{
    if (ptr != 0)
    {
        printf("%d ", ptr->data);   // 印出節點內容
        print_preorder(ptr->left);  // 走左子樹
        print_preorder(ptr->right); // 走右子樹
    }
}