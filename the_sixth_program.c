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

int factorial(int number);

void swap(int *a, int *b);

void permutation(int *arr, int start, int end, int** arrays_with_p);

Arrays matrix_declaration();

Arrays arithmetic_action(Arrays A, Arrays B, int action);

Arrays multiplication(Arrays A, Arrays B);

int det(Arrays result);

int** true_perm2(int size);

char* err_msg_100 = "Error: Wrong input.";
char* err_msg_101 = "Error: Incorrect size of matrixes.";
int arrays_with_perm[40320][8];
int jjj = 0;

int POSITION;

//////////////////////////////////

int main()
{
    int increased = INCREASE;
    char action = '0';
    int matrix_position = 0;
    Arrays *array_with_matrixes = (Arrays *) malloc(100 * sizeof(int*));
    char *array_with_actions = (char *) malloc(100 * sizeof(char));
    int determinant;

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

    if (action == 'd')
    {
        determinant = det(array_with_matrixes[0]);
        printf("Determinant is: %d\n", determinant);
        return 0;
    }


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

    determinant = det(array_with_matrixes[0]);
    printf("Determinant is: %d\n", determinant);
    return 0;


}

///////////////////////////////////

int det(Arrays matrix)
{

    if (matrix.rows != matrix.cols )
    {
        fprintf(stderr, "Determinant can be evaluated only"
         "for matrices with the same number of rows and collums\n" );
        exit(EXIT_FAILURE);
    }
    else if (matrix.cols == 1)
    {
        return matrix.matrix[0][0];
    } else if(matrix.cols > 1)
    {
        int determinant = 0;
// here is the determinant determinaton

        int factorial_of_size = factorial(matrix.cols);
        int size = matrix.cols;
        //int** permutations = (int**)malloc(factorial_of_size* sizeof(int*));

        int** permutations = true_perm2(size);


        int* arr = (int*) malloc(size*sizeof(int));
        for (int i = 0; i < size; i++)
            arr[i] = i; //[0 1 2 ]


        int multipl;
        for (int i = 0; i < factorial_of_size; i++ )//[ [] [] [] [] [] [] ]
        {
            multipl = 1;

            for (int j = 0; j < size; j++)
            {
                multipl *= matrix.matrix[arr[j]][permutations[i][j]];//[0 1 2]
                                                                    //[ 2 1 0]
            }
            if (i % 2 != 0 ) {determinant -= multipl;}
            else            {determinant += multipl;}
        }


        return determinant;
    }
}

///////////////////////////////////

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

void permutation(int *arr, int start, int end, int** arrays_with_p)
{

    int i;
    if(start==end)
    {
        arrays_with_p[jjj] = arr;
        for(int i=0; i <= end; i++)
        {
            //printf("%d\t",arr[i]);

            printf("%d ",arrays_with_p[jjj][i]);
            arrays_with_perm[jjj][i] = arrays_with_p[jjj][i];
        }
        printf("\n");
        jjj++;

    }

    for(i=start; i<=end; i++)
    {
        swap((arr+i), (arr+start));
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        permutation(arr, start+1, end, arrays_with_p);
        swap((arr+i), (arr+start));
    }

}


void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int factorial(int number)
{
    if ( number <= 1)
        {return 1;}
    else number = number * factorial(number-1);

    return number;
}

int** true_perm2(int size)
{

    int factorial_of_size = factorial(size);

    int** arrays_with_p = (int**)malloc(factorial_of_size * sizeof(int*));

    int* arr = (int*) malloc(size*sizeof(int));

    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }


    permutation(arr, 0, size-1, arrays_with_p);


    int** true_perm2 =(int**)malloc(factorial_of_size* sizeof(int*));// 4
    for (size_t i = 0; i < factorial_of_size; i++)
        true_perm2[i] = (int*)malloc(size* sizeof(int*));


    for (int r = 0; r < factorial_of_size; r++)
        for (int k = 0; k < size; k++)
            true_perm2[r][k] = arrays_with_perm[r][k];


    // for (int i = 0; i <factorial_of_size; i++)
    // {
    //     free(arrays_with_p[i]);
    // }
    // free(arrays_with_p);

    return true_perm2;
}
