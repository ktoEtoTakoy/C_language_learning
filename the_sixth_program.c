#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INCREASE 3

typedef int** MATRIX;

typedef struct
{
    MATRIX matrix;
    int rows;
    int cols;

} Arrays;

//////////////////////////////////

Arrays matrix_declaration();

Arrays arithmetic_action(Arrays A, Arrays B, int action);

Arrays multiplication(Arrays A, Arrays B);

double** ellemenat(Arrays array);

void deter(double* not_change, double* change, int value, int size);

char* err_msg_100 = "Error: Wrong input.";
char* err_msg_101 = "Error: Incorrect size of matrixes.";

int POSITION;

//////////////////////////////////

int main()
{
    int increased = INCREASE;
    char action = '0';
    int matrix_position = 0;
    Arrays *array_with_matrixes = (Arrays *) malloc(100 * sizeof(int*));
    char *array_with_actions = (char *) malloc(100 * sizeof(char));

///////////////////////////////// fix dynamic memory

    do {
        if(matrix_position + 1 >= increased)
        {
            array_with_matrixes = (Arrays *) realloc(array_with_matrixes, (increased * 20) * sizeof(int*));
            array_with_actions = (char *) realloc(array_with_actions, (increased * 20) * sizeof(char));
            increased += INCREASE;
        }

        array_with_matrixes[matrix_position] = matrix_declaration();

        getchar();
        printf("Enter action\n" );
        scanf("%c", &action);

        array_with_actions[matrix_position] = action;

        ++matrix_position;

    } while (action != '=');

//////////////////////////////////

    POSITION = matrix_position;
    Arrays temp_arrays;

    for (int i = POSITION - 1; i > 0; i--)
    {
        if (array_with_actions[i - 1] == '*')
        {
            temp_arrays = multiplication(array_with_matrixes[i], array_with_matrixes[i - 1]);
            array_with_matrixes[i] = temp_arrays;

            for (int j = i; j < matrix_position; j++)
            {
                array_with_matrixes[j - 1] = array_with_matrixes[j];
                array_with_actions[j - 1] = array_with_actions[j];
            }

            matrix_position--;
        }
    }

//////////////////////////////////

    for (int j = 0; j < matrix_position-1; j++)
    {
        switch (array_with_actions[j])
        {
            case '+':
                temp_arrays = arithmetic_action(array_with_matrixes[0], array_with_matrixes[j+1], 1);
                array_with_matrixes[0] = temp_arrays;
                break;

            case '-':
                temp_arrays = arithmetic_action(array_with_matrixes[0], array_with_matrixes[j+1], -1);
                array_with_matrixes[0] = temp_arrays;
                break;

            default:
                printf("You entered the wrong action\n");
                return 0;
        }
    }

    printf("RESULT :\n");
    for (int i = 0; i < array_with_matrixes[0].rows; i++)
    {
        for (int k = 0; k < array_with_matrixes[0].cols; k++)
        {
            printf("%d ", array_with_matrixes[0].matrix[i][k]);
        }

        printf("\n");
    }

    int size_of_ppp = array_with_matrixes[0].rows;
    double** our_array = (double**)malloc(size_of_ppp * sizeof(double*));
    for (size_t i = 0; i < size_of_ppp; i++)
    {
        our_array[i] = (double*)malloc(size_of_ppp * sizeof(double));
    }

    our_array = ellemenat(array_with_matrixes[0]);

    double determinant = 1.0;
    int scet = size_of_ppp - 1;
    for (int k = 0; k < size_of_ppp - 1; k++)
    {
        for (int i = 0; i < scet; i++)
        {
            if (our_array[k+i+1][k] != 0)
                deter(our_array[k], our_array[k+i+1], k, size_of_ppp);
        }
        scet--;
        determinant*=our_array[k][k];
    }

    determinant*=our_array[size_of_ppp - 1][size_of_ppp - 1];

    printf("\nDeterminant = %.2lf", determinant);

    return 0;
}

///////////////////////////////////

void deter(double* not_change, double* change, int value, int size)
{
    double temp = change[value] / not_change[value]; // 2

    for (int i = 0; i < size; i++)
    {
        not_change[i]*=temp;
        change[j]-=not_change[j];
        not_change[k]/=temp;
    } // if program doesnt work, fix that

    // for (int j = 0; j < size; j++)
    // {
    //     change[j]-=not_change[j];
    // }
    //
    // for (int k = 0; k < size; k++)
    // {
    //     not_change[k]/=temp;
    // }
}

double** ellemenat(Arrays array)
{
    double** mas = (double**)malloc(array.cols * sizeof(double*));
    for (size_t i = 0; i < array.cols; i++)
    {
        mas[i] = (double*)malloc(array.cols * sizeof(double));
        for (size_t j = 0; j < array.cols; j++)
        {
            mas[i][j] = (double)array.matrix[i][j] * 1.0;
        }
    }  // if program doesnt work, fix that

    // for (size_t i = 0; i < array.rows; i++)
    // {
    //     for (size_t j = 0; j < array.cols; j++)
    //     {
    //         mas[i][j] = (double)array.matrix[i][j] * 1.0;
    //     }
    // }

    return mas;
}

Arrays matrix_declaration()
{
    Arrays element;
    int rows, cols;
    printf("Enter number of rows and cols: \n");
    int size_is = scanf("%i %i",&rows, &cols);

    if ((size_is != 2) || (rows<0 || cols<0))
    {
        fprintf(stderr, "%s", err_msg_100);
        exit(EXIT_FAILURE);
    }

    element.cols = cols;
    element.rows = rows;

    MATRIX array=(int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
    {
        array[i]=(int*)malloc(cols * sizeof(int));
    }

    printf("Enter elements of matrix: \n");

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &array[i][j]);

    element.matrix = array;

    return element;
}

///////////////////////////////////

Arrays arithmetic_action(Arrays A, Arrays B, int action)
{
    if (A.rows != B.rows || A.cols != B.cols)
    {
        fprintf(stderr, "%s", err_msg_101);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < A.rows; i++)
        for (int j = 0; j < A.cols; j++)
            A.matrix[i][j] = (A.matrix[i][j] + action * B.matrix[i][j]);

    return A;

}

//////////////////////////////////

Arrays multiplication(Arrays B, Arrays A)
{

    Arrays sum;
    sum.rows = A.rows;
    sum.cols = B.cols;

    MATRIX array=(int**)malloc(sum.rows * sizeof(int*));
    for (int i = 0; i < sum.rows; i++)
    {
        array[i]=(int*)malloc(sum.cols * sizeof(int));
    }
    sum.matrix = array;

    for (int i = 0; i < sum.rows; i++)
        for (int j = 0; j < sum.cols; j++)
            sum.matrix[i][j]=0;

    int r1 = 0;
    int r2 = 0;
    int c1 = 0;
    int c2 = 0;

    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < B.cols; j++)
        {
            while (c1 != A.cols && r2 != B.rows)
            {
                sum.matrix[i][j] += (A.matrix[r1][c1] * B.matrix[r2][c2]);
                c1++;
                r2++;
            }
            c2++;
            r2 = 0;
            c1 = 0;
        }
        c2 = 0;
        r1++;
    }

    return sum;
}

///////////////////////////////////
