#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 3

/////////////////////////////////////////////

int return_size(char* array, char* deleting_array);
int find_key(char* crypted, char* encrypted_w_error, int loop);
void function_encrypt(char* crypted, char* encrypted_w_error, int loop, int number);
char * memory(char *str, int capacity);
void delete_arrays(char* array1, char* array2);

/////////////////////////////////////////////

// если ввести frtg-gd то дичь, нужно фиксить, а так норм вроде

int main()
{
    char *crypt = NULL;
    char *encrypt = NULL;
    crypt = memory(crypt, SIZE);
    encrypt = memory(encrypt, SIZE);
    int length = 0;

    printf("Enter crypted message:                 ");
    int chars_in_crypt = return_size(crypt, encrypt);

    printf("Enter encrypted message with mistakes: ");
    int chars_in_encrypt = return_size(encrypt, crypt);

    if (chars_in_crypt != chars_in_encrypt)
    {
        delete_arrays(crypt, encrypt);
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
        return 101;
    }
    else
        length = chars_in_crypt;

    int our_key = find_key(crypt, encrypt, length);

    function_encrypt(crypt, encrypt, length, our_key);
    return 0;
}

/////////////////////////////////////////////

int return_size(char* working_array, char* deleting_array)
{
    int i = 0;
    int numbers_in_string = SIZE;
    int chars_in_array = 0;

    while ((working_array[i] = getchar()) != '\n')
    {
        if (isalpha(working_array[i]) == 0)
        {
            delete_arrays(working_array, deleting_array);
            fprintf(stderr,"Error: Chybny vstup!\n");
            return 100;
        }

        chars_in_array++;

        if (++i == numbers_in_string)
        {
            numbers_in_string = numbers_in_string + SIZE;
            working_array = memory(working_array, numbers_in_string);
        }
    }
    return chars_in_array;
}

/////////////////////////////////////////////

int find_key(char* crypted, char* encrypted_w_error, int loop)
{
    int lalala1 = SIZE + loop;
    int arr_w_nums[lalala1];
    int i, k;

    int counter_of_keys = 0;

    for (i = 0; i < lalala1-1; i++)
    {
        int shift;

        if ((crypted[i] <=(int)'Z' && crypted[i] >=(int)'A') && (encrypted_w_error[i] > (int)'a' && encrypted_w_error[i] < (int)'z'))
        {
            shift = encrypted_w_error[i] - crypted[i] - 6;
        }else if ((crypted[i] <=(int)'z' && crypted[i] >=(int)'a') && (encrypted_w_error[i] >= (int)'A' && encrypted_w_error[i]<= (int)'Z'))
        {
            shift = encrypted_w_error[i] - crypted[i] + 6; // если какая хуйня, то поменять на -
        }else
            shift = encrypted_w_error[i] - crypted[i];

        if(shift < 0  ) shift+=52;
        if(shift > 52 ) shift-=52;

        arr_w_nums[i] = shift;
    }
    printf("\n" );

    // тут смотрим повторяшки, чтобы найти нужное передвижение в массиве. Надо создать массив array, в котором будут отмечены передвижения
   int number = arr_w_nums[0];
   int max_count = 1;
   for (i=0; i < lalala1-1; i++) // для каюдого элемента массива. es
   {
       int count = 1;// обнуляем как сраку путина

       for (k = i+1; k<lalala1; k++)
           if (arr_w_nums[i] == arr_w_nums[k]) ++count;

       if (count > max_count)
       {
           ++counter_of_keys;
           max_count = count;
           number = arr_w_nums[i];
       }
   }
   return number;
}

/////////////////////////////////////////////

void function_encrypt(char* crypted, char* encrypted_w_error, int loop, int number)
{
    int newchar;
    int lalala1 = SIZE + loop;
    int i;
    int arr_w_nums[lalala1];

    for (i = 0; i<lalala1-1; i++)
    {

        if (arr_w_nums[i]!=number) // если -6 != 10
        {
            newchar = (int)crypted[i] + number;

            if (crypted[i] >= 'A' && crypted[i] <= 'Z')
            {
                if (newchar <= (int)'a' && newchar >= (int)'Z')
                    newchar = (newchar - (int)'Z') + (int)'a' - 1;

                if (newchar <= (int)'A')
                    newchar = (int)'z' - (int)'A' + newchar;

            } else if (crypted[i] >= (int)'a' && crypted[i] <= (int)'z')
            {
                if( newchar >= (int)'z' )
                    newchar = ((int)'A' + newchar) - ((int)'z' + 1);

                else if (newchar <= (int)'a')
                    newchar = (int)'Z' + (int)'a' - newchar;
            }
            encrypted_w_error[i] = newchar;
       }
    }

    for (i = -1; i<lalala1; i++)
    {
        printf("%c", encrypted_w_error[i]);
    }

    printf("\n" );
}

/////////////////////////////////////////////

char * memory(char *increase_message, int capacity)
{
    if ((increase_message = (char *)realloc(increase_message, capacity * sizeof(char))) == NULL)
    {
        printf("Error!\n");
        exit(EXIT_FAILURE);
    }
    return increase_message;
}

/////////////////////////////////////////////

void delete_arrays(char* array1, char* array2)
{
    free(array1);
    free(array2);
    array1 = NULL;
    array2 = NULL;
}

/////////////////////////////////////////////
