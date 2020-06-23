#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 4

/////////////////////////////////////////////

int return_size(char* array, char* deleting_array);
void find_key(char* crypted, char* encrypted_w_error, int loop);
void function_encrypt(char* crypted, int loop, int number);
char * memory(char *str, int capacity);
void delete_arrays(char* array1, char* array2);
void shift(int* array_with_nums, char* crypted, char* encrypted_w_error, int loop);

/////////////////////////////////////////////

int length_of_crypt;
int length_of_encrypt;
int main()
{
    char *crypt = NULL;
    char *encrypt = NULL;
    crypt = memory(crypt, SIZE);
    encrypt = memory(encrypt, SIZE);

    printf("Enter crypted message:                 ");
    int chars_in_crypt = return_size(crypt, encrypt);

    printf("Enter encrypted message with mistakes: ");
    int chars_in_encrypt = return_size(encrypt, crypt);

    if (chars_in_crypt == 0 )
    {
        delete_arrays(crypt, encrypt);
        fprintf(stderr, "Error: chybny vstup\n");
        return 100;
    }else if(chars_in_crypt <= chars_in_encrypt)
    {
        length_of_crypt = chars_in_crypt;
        length_of_encrypt = chars_in_encrypt;
        find_key(crypt, encrypt, length_of_crypt);
    }
    else
    {
        length_of_crypt = chars_in_crypt;
        length_of_encrypt = chars_in_encrypt;
        find_key(crypt, encrypt, length_of_encrypt);
    }

    delete_arrays(crypt, encrypt);
    return 0;
}

/////////////////////////////////////////////

int return_size(char* working_array, char* deleting_array)
{
    int i = 0;
    int increase = SIZE;
    int elements_in_array = 0;
    int stop = 0 ;

    while ((working_array[i] = getchar()) != '\n')
    {
        if (isalpha(working_array[i]) == 0)
        {
            ++stop;
        }

        elements_in_array++;

        if (++i == increase)
        {
            increase = increase + SIZE;
            working_array = memory(working_array, increase);
        }
    }
    if (stop != 0) return 0;

    return elements_in_array;
}

/////////////////////////////////////////////

void find_key(char* crypted, char* encrypted_w_error, int loop)
{
    int arr_w_nums[loop+2];
    int i;
    int varshift = 0;

    for (i = 0; i < loop; i++)
    {

        if ((crypted[i] <=(int)'Z' && crypted[i] >=(int)'A') && (encrypted_w_error[i] > (int)'a' && encrypted_w_error[i] < (int)'z'))
        {
            varshift = encrypted_w_error[i] - crypted[i] - 6;
        }else if ((crypted[i] <=(int)'z' && crypted[i] >=(int)'a') && (encrypted_w_error[i] >= (int)'A' && encrypted_w_error[i]<= (int)'Z'))
        {
            varshift = encrypted_w_error[i] - crypted[i] + 6;
        }else
            varshift = encrypted_w_error[i] - crypted[i];

        if(varshift < 0  ) varshift+=52;
        if(varshift > 52 ) varshift-=52;

        arr_w_nums[i] = varshift;
        printf(" %d ", arr_w_nums[i] );
    }
    printf("\n" );
    shift(arr_w_nums, crypted, encrypted_w_error, loop);
}

void shift(int* array_with_nums, char* crypted, char* encrypted_w_error, int loop1) // function_encrypt(shift(find_key));
{
    int counter_of_keys = 0;
    int i, k;
    int varshift = array_with_nums[0];
    int max_count = 1;
    for (i=0; i < loop1; i++) // для каюдого элемента массива. es
    {
        int count = 1;// обнуляем как сраку путина

        for (k = i+1; k<loop1; k++)
            if (array_with_nums[i] == array_with_nums[k]) ++count;

        if (count > max_count)
        {
            ++counter_of_keys;
            max_count = count;
            varshift = array_with_nums[i];
        }
    }
    function_encrypt(crypted, loop1, varshift);
}

/////////////////////////////////////////////

void function_encrypt(char* crypted, int loop2, int number)
{
    int newchar;
    int i;

    if (length_of_encrypt < length_of_crypt)
    {
        loop2 = length_of_crypt;
    }

    int good[loop2+2];
    for (i = 0; i<loop2 + 2; i++)
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
        good[i] = newchar;
    }

    for (i = 0; i < loop2+2; i++)
    {
        printf("%c", good[i]);
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
}

/////////////////////////////////////////////

