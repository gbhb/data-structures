#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    int col, row, counter = 0, error;
    int i = 0, j = 0;
    char line[4096] = "";

    scanf("%d%d", &row, &col);
    int **arr = (int **)malloc((row) * sizeof(int *));
    for (int i = 0; i < row; i++)
        arr[i] = malloc(sizeof(int) * (col));
A:
    i = 0;
    j = 0;
    error = 0;
    counter = 0;
    

    scanf(" ");

    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        if (strcmp(line, "-1") == 0 || strcmp(line, "-1\n") == 0)
        {
            break;
        }

        char *check = strtok(line, " ");
        while (check != NULL)
        {
            if (i < row && j < col)
            {
                arr[i][j] = atoi(check);
                if (arr[i][j] != 0)
                    counter++;
            }
            check = strtok(NULL, " ");
            j++;
        }
        if (j != col)
        {
            error = 1;
        }
        j = 0;
        i++;
    }
    if (i != row)
    {
        error = 1;
    }
    if (error == 1)
    {
        printf("Input matrix has wrong size. Please input again.\n");

        goto A;
    }
    printf("Sparse matrix by triplet form:\n");
    printf("%d %d %d\n", row, col, counter);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (arr[i][j])
            {
                printf("%d %d %d\n", i, j, arr[i][j]);
            }
        }
    }
    printf("Transpose of the sparse matrix:\n");
    printf("%d %d %d\n", col, row, counter);
    for (int i = 0; i < col; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            if (arr[j][i])
            {
                printf("%d %d %d\n", i, j, arr[j][i]); //transpose to print
            }
        }
    }
    return 0;
}
