#include <stdio.h>
#include <stdlib.h>
/*
 * Calls function find_prefix, which creates an array with prefixes once
 * reads file line by line, for each line calls function find_pattern, which finds out, if there is a pattern
*/
int read_file(FILE* filename, char* pattern);
/*
 * returns an array with matched prefixes
 *
*/
int* prefix_function(char* pattern, int pattern_size);
/*
 * Using output from prefix_function finds matching
 * It there is a matching, returns 0, otherwise -1
 *
 */
int find_pattern (char* string, char* pattern, int* prefix_arr, int pattern_size); // finds pattern and returns 0 if pattern has been found

int main( int argc, char* argv[])
/*argc - arguments counter, argv - argument value.
 *Получив параметры интероретатор получает параметры, отделенные пробелом
 *
 */
{
    char* error_100 = "Error, wrong number of arguments:\n"
                      "To use this program you have to enter two arguments:\n\tPATTERN which is a string"
                      " you are looking for \n\tFILEPATH: path to a file where you are looking for a string";
    char* error_102 = "Error: you've entered a wrong path";

    char* error_101 = "Error: sorry, not supported yet";
    char* error_103 = "Error: error when reading the file occured";
    char* error_104 = "Error: error when closing the file occured";

    FILE *working_file;

    switch (argc)
    {
        case 3:
            /*
            * открывем файл - 1
            * выписываем содерюимое рядов, номера рядов, где есть наш паттерн
             *
            */
            if ((working_file=fopen(argv[2], "r")) != NULL) // argv[2] is the FILEPATH - 1
            {
                char* pattern = argv[1];
                switch (read_file(working_file, pattern))
                {
                    case 0:
                        printf("Program completed successfully\n");
                        return 0;
                    case 103:
                        fprintf(stderr, "%s\n",error_103);
                        return 103;
                }
                if ( fclose (working_file) == EOF)
                {
                    fprintf(stderr, "%s\n",error_104);
                    return 104;
                }
            }else {fprintf(stderr, "%s\n",error_102 ); return 102;}


        case 4:
            fprintf(stderr, "%s\n", error_101);
            return 101;

        case 5:
            fprintf(stderr, "%s\n", error_101);
            return 101;

        case 6:
            fprintf(stderr, "%s\n", error_101);
            return 101;

        default:
            fprintf(stderr, "%s\n", error_100);
            return 100;
    }

}

int read_file(FILE* filename, char* pattern)
{
    static const int SIZE = 1000;
    char *str = NULL;
    char buf_string[SIZE];

    int string_number = 0;

    static int pattern_size = 0;
    for (int g = 0; pattern[g] != '\0';g++)
    {
        pattern_size++;
    }

    int* d =  prefix_function(pattern, pattern_size);
    //returns array named d with prefixes matching
    // ----------------------------------------------------------------
    // Переменная, в которую поочередно будут помещаться считываемые строки
    //Указатель, в который будет помещен адрес массива, в который считана
    // строка, или NULL если достигнут коней файла или произошла ошибка

    //Чтение (построчно) данных из файла в бесконечном цикле
    while (1)
    {
        string_number++;
        // Чтение одной строки  из файла
        str = fgets(buf_string, SIZE, filename);
        if (str == NULL)
        {
            // Проверяем, что именно произошло: кончился файл
            // или это ошибка чтения
            if ( feof(filename) != 0)
                return 0; // normal return case
            else
                return 103;// undefined error. Must not be reached, but...
        }

        if (find_pattern(buf_string, pattern, d, pattern_size) == 0) // return 0, если pattern в строке имеется
            printf("%d: %s\n", string_number, buf_string);

        //Проверка на конец файла или ошибку чтения
    }
}

int* prefix_function (char* pattern, int pattern_size)
{
    /* s - строка, в которой мы ищем паттерн, то есть n-тая строка нашего файла
     * p - паттерн, то есть как раз та подстрока, которую мы ищем в нашем файле
    */
    int i, j;

    //int d[pattern_size] = {0};
    int *d = (int*) malloc( pattern_size);
    // Вычисление префикс-функции// префикс фция возвр макс значение совпадающих префикса и суфф
    d[0] = 0;// значения префикс фции записываем в массив d
    for(i = 1, j = 0; i < pattern_size; i++)// i, j указыважт на символы, которые мы рассматриваем и сравниваем
    {
        while(j > 0 && pattern[j] != pattern[i]) // esli j = 0, to d[i] = 0, i++. Inache(j!=0) j = d[j-i].Esli pattern[j] = pattern[i], d[i] = j+1; i++, j++///
            //то естъ если у нас сначала гуляет i, a j стоит на месте. Если же pattern[i] = pattern[j], то мы двигаем j и i, чтобы найти самое длинное совпадение
            // длину самого длиннного спвпадения вписытваем в d[i]
            j = d[j-1];
        if(pattern[j] == pattern[i])
            j++;
        d[i] = j;
    }

    return d;
}

int find_pattern(char* str, char* pattern, int* prefix_arr, const int pattern_size)
{
    int i, j;
    int string_len = 0;
    for(i =0; str[i] != '\0';i++)
    {
        string_len ++;
    }

    for(i = 0, j = 0; i < string_len; i++)
    {
        while(j > 0 && (pattern[j] != str[i]))
            j = prefix_arr[j - 1];
        if(pattern[j] == str[i])
            j++;
        if(j == pattern_size)
        {
            return 0;
        }
    }

    return 1;
}
