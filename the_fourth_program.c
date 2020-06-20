#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
    int number = 0;
    int k =0;

    int count = 0;
    char error_msg_100[] = "Error, this input is not allowed!";

    int input = scanf("%d", &number);

    while (input == 1)
    {
        if (number == 0) break;

        if (number < 0)
        {
            fprintf(stderr, "Error: Bad input!\n");
            return 100;
        }

        if (number == 1)
        {
            printf("Prime factorization of %d is:\n%d\n", number, number);
        }

        if (number != 1)
        {
            count = 0;
            k = 0;

            printf("Prime factorization %d is:\n", number);

            for (int j = 2; j < number; j++)
            {
                if (number % j == 0)
                    count++; // считаем количество делителей напр 30: 2,3,5,6,10,15
            }

            for (int i = 2; i*i <= number; i++) // идем до 5
            {
                if (number%i == 0) // если делитель то выполняем, например для 2, 3, 5
                {
                    if (i >=3 && k>=1)
                    {
                        printf(" * %d", i);
                    }else
                        printf("%d", i);

                    for (k = 0; number%i == 0; k++) // если i является множителем, то выполняется это до тех пор, пока является таковым. k же
                    { // в свож очередь являетсятся счетчком степени
                        number /= i;
                    }

                    if (k >= 2) // пишет степень, тк в предыдыщем цыкле k увеличивались столько раз, сколько есть делителей
                        printf("^%d", k);

                    if (number == 1)
                        printf("\n");
                }
            }

            if (number>1) // выписывает остаток
            {
                if (count == 0)
                    printf("%d\n", number);
                else
                    printf(" * %d\n", number);
            }
        }
        input = scanf("%d", &number);
    }

    if (input == 0)
    {
        fprintf(stderr, "%s", error_msg_100);
        return 100;
    }

    printf("\n");
    return 0;
}
