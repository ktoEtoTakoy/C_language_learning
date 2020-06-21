#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 110

int find_the_key(char* crypted, char* encrypted_w_error)
{
    int key;
    char ch1;
    char ch2;
    int array[SIZE];

    for (int i = 0; crypted[i] != '\0'; ++i)
    {
        ch1 = encrypted_w_error[i];// забираем i-тый char
        //посмотеть , на сколько передвинут i = тый char
        ch2 = crypted[i];
        array[i]=ch2-ch1; // ищем повторяшки в этом массиве! 12 24 12 47 38 12 45
    }

    int i = k = 0;
    for(k; array[k] != '\0'; k++) // проходим всеми элементами
    {
        i = k+1;
        do// для k того элемента смотрим все и от 1 до последнего
        {
            // 1 2 1 4 4 1
            if (array[k] == array[i])
            {
                printf("%i",array[i]);
            }

            ++i;
        }
        while(array[k] != '\0');
    }

    return key;
}

void function_encrypt(char* string, int key) // takes an array of chars, key is cipher movement
{
    char value;
    char good_letter;
    char ch;

    if (key>26){ key %= 26; }else if (key<0) { key += 26; }

    for (int i = 0; string[i] != '\0'; ++i) // проходим каждый символ строки
    {
		ch = string[i]; // в i-той итерации ch является i-тым символом

		if (ch >= 'a' && ch <= 'z') // если символ является символом маленького алфавита
        {
			ch += key; // подвигаем символ на длину key


            /* если мы подвинули так сильно, что вышли за алфавит, то ch -= 26;
             z - 122 элемент. ch например 123, а 123 это а, но а это 97. 123 - 26 = 97, поэтому 26*/
			if (ch > 'z') ch -= 26;

            string[i] = ch;
		}

		else if (ch >= 'A' && ch <= 'Z')
        {
			ch += key;


			if (ch > 'Z') ch -= 26;

			string[i] = ch;
		}
        printf("%c",string[i] );
	}
}

void print_string(char* string)
{
    for (int i = 0; string[i] != '\0'; ++i)
    {
        printf("%c", string[i]);
    }
}

int main()
{
    char crypt[SIZE];   // chagne to dynamic array
    char encrypt[SIZE]; // chagne to dynamic array

    fgets(crypt, sizeof(crypt), stdin);

    printf("\n");

    //print_string(crypt);
    printf("\n");
    find_the_key(crypt, encrypt);
    function_encrypt(crypt, find_the_key);

    return 0;
}
