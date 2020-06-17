#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* The main program */
int main()
{
    int value1 = 0;
    int value2 = 0;
    float podil_prumer = 0.0f;
    bool variable=false;
    printf("Napiste dve cisla\n");
    while (variable==false)
    {
        scanf ("%i %i", &value1, &value2);

        if ( (10000 >= value1 && value1 >= -10000 ) && ( 10000 >= value2 && value2 >= -10000) )
        {
            variable = true;
            printf("Desitkova soustava: %d %d\n", value1,value2);
            printf("Sestnactkova soustava: %x %x\n", value1,value2);
            printf("Soucet: %d + %d = %d\n", value1,value2, value1+value2);
            printf("Rozdil: %d - %d = %d\n", value1,value2, value1-value2);
            printf("Soucin: %d * %d = %d\n", value1,value2, value1*value2);

            if (value2 && true)
                printf("Podil: %d / %d = %1.2f\n", value1,value2, podil_prumer = ((float)value1/value2));
            else
                printf("Nedefinovany vysledek!\n");

            printf("Prumer: (%d + %d)/2 = %1.2f\n",value1, value2, podil_prumer = ((float)value1+value2)/2.0);

        } else
            printf("Vstup je mimo interval!\n");
    }

    printf("Program was completed!");
    return 0;
}


    /*
           24
      16   +   8
    1*16^1 + 8*16^0
    */
