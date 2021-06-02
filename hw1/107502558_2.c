#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
//改為前序
void toPostfix(char *, char *); // 中序轉後序
int priority(char);             // 運算子優先
double eval(char *);
double calPostfix(char, double, double);

int main(void)
{
    char infix[MAX] = {'\0'};
    while (1)
    {   
        infix[0] = '\0';
        scanf("%s", infix);
       
        if (strcmp(infix, "-1")==0)
        {
            break;
        }
        printf("\n%.0f\n", eval(strrev(infix)));
    }
    return 0;
}

void toPostfix(char *infix, char *postfix)
{
    char stack[MAX] = {'\0'};
    int i, j, top;
    for (i = 0, j = 0, top = 0; infix[i] != '\0'; i++)
        switch (infix[i])
        {
        case ')': // 運算子堆疊  "("最優先輸入
            stack[++top] = infix[i];
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            while (priority(stack[top]) > priority(infix[i]))//postfix is >=
            {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i]; // 存入堆疊
            break;
        case '(':
            while (stack[top] != ')')
            { // 遇 ) 輸出至 (
                postfix[j++] = stack[top--];
            }
            top--; // 不輸出 (
            break;
        default: // 運算元直接輸出
            postfix[j++] = infix[i];
        } 
    while (top > 0)//最後輸出
    {
        postfix[j++] = stack[top--];
    }
}

int priority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

double eval(char *infix)
{
    char postfix[MAX] = {'\0'};
    char operand[2] = {'\0'};
    double stack[MAX] = {0.0};

    toPostfix(infix, postfix);

    int top, i;
    for (top = 0, i = 0; postfix[i] != '\0'; i++)
    {
        printf("%c", postfix[strlen(postfix)-i-1]);
        switch (postfix[i])
        {
        case '+':
        case '-':
        case '*':
        case '/':
            stack[top - 1] = calPostfix(postfix[i], stack[top], stack[top-1]); //postfix is postfix[i], stack[top-1], stack[top]
            top--;
            break;
        default:
            operand[0] = postfix[i];
            stack[++top] = atof(operand); //轉成浮點數
        }
    }
    return stack[top];
}

double calPostfix(char operator, double p1, double p2)
{
    switch (operator)
    {
    case '+':
        return p1 + p2;
    case '-':
        return p1 - p2;
    case '*':
        return p1 * p2;
    case '/':
        return p1 / p2;
    }
}