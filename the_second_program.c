#include <stdio.h>
#define SIZE 255

int main()
{
    int number;
    int number_of_elements=0;
    int positives=0;
    int negatives=0;
    int summ=0;
    int max;
    int min;
    float  avarage;
    float  percentage_of_positives;
    float  percentage_of_negatives;
    int array[SIZE];

    for (int i = 0; i < 1;)
    {
        while ((scanf("%i", &number)) != EOF )
        {
            array[number_of_elements] = number;

            if (number>0) {positives++;}
            if (number<0) {negatives++;}

	        summ += number;
            number_of_elements++;
        }

        i=1;
    }

	max = array[0];
	min = array[0];

	for(int i = 0; i < number_of_elements; ++i)
	{
		if(array[i] > max)
		{
        	max = array[i];
    	}
        else if(array[i] < min)
		{
			min = array[i];
		}
	}

	if(number_of_elements != 0)
	{
		avarage = summ/(float)number_of_elements;
		percentage_of_positives = (positives) / (number_of_elements/100.0);
		percentage_of_negatives = (negatives) / (number_of_elements/100.0);
	}
    else
	{
		avarage = 0;
		percentage_of_positives = 0;
		percentage_of_negatives=0;
	}

    /*Final output */
    printf("Number of elements:\t %i \nPositive numbers: \t %i \nNegative numbers: \t %i \n",
    number_of_elements, positives, negatives);

    printf("Percentge of positives: \t%.2f%%\n", percentage_of_positives);

    printf("Percentge of negatives: \t%.2f%%\n", percentage_of_negatives);

    printf("Average:\t%.2f\n", avarage);

    printf("Minimum:\t%i\nMaximum:\t%i\n",min, max);
}
