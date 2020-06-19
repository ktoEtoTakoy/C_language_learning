#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;

    int height;
    int width;
    int fence_size;

    char error_msg_100[] = "Error: Chybny vstup!\n";
    char error_msg_101[] = "Error: Vstup mimo interval!\n";
    char error_msg_102[] = "Error: Sirka neni sude cislo!\n";
    char error_msg_103[] = "Error: Neplatna velikost plotu!\n";

    int scan_for_input;

    printf("Enter odd width between 3 and 69.\n");
    printf("If height is the same as width enter fence size.\n");
    printf("Fence size mustnt be greater then height.\n");

    scan_for_input = scanf("%d%d", &width, &height);

    if  (scan_for_input !=2)
    {
        fprintf(stderr, "%s\n", error_msg_100);
        return 100;
    }

    if (width == height)
    {
        if (scanf("%d", &fence_size) == 0)
        {
            fprintf(stderr,"%s", error_msg_100);
            return 100;
        }
        if (fence_size <= 0 || fence_size >= height)
        {
            fprintf(stderr, "%s", error_msg_103);
            return 103;
        }
    }else fence_size=0;

    if (width<3 || width>69 || height<3 || height>69)
    {
        fprintf(stderr, "%s\n", error_msg_101);
        return 101;
    }

    if (width%2 == 0)
    {
        fprintf(stderr, "%s\n", error_msg_102);
        return 102;
    }

    for (int i=0; i<width/2; i++)
    {
        for (int j = 0; j<=width*2; j++)
        {
            if(j != (width/2)-i && j != (width/2)+i)
            {
                printf(" ");

            } else printf("X");

        }
        printf("\n");
    }

    start = clock();

    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width+fence_size; j++)
        {
            if(j >= width)
            {
                if (i>=height-fence_size)
                {
                    if (i==height-fence_size || i==height-1)
                    {
                        if (fence_size%2==0)
                        {
                            if (j%2==0)
                            {
                                printf("|");
                            }else printf("-");
                        }
                        else
                        {
                            if (j%2==0)
                            {
                                printf("-");
                            }else printf("|");
                        }
                    }
                    else
                    {
                        if (fence_size%2==0)
                        {
                            if (j%2==0)
                            {
                                printf("|");
                            }else printf(" ");
                        }
                        else
                        {
                            if (j%2==0)
                            {
                                printf(" ");
                            }else printf("|");
                        }
                    }
                }
            }
            else
            {
              if (height==width)
                {
                    if (i==0 || i==width-1)
                    {
                        printf("X");
                    }
                    else
                    {
                        if (j==0 || j==height-1)
                        {
                            printf("X");
                        }
                        else
                        {
                            if (j%2==0 && j>0)
                            {
                                if (i%2==0 && i >0)
                                {
                                    printf("o");

                                } else printf("*");
                            }
                            else
                            {
                                if (i%2==0 && i>0)
                                {
                                    printf("*");

                                } else printf("o");
                            }
                        }
                    }
                }
                else
                {
                  if (i==0 || i==height-1)
                  {
                      printf("X");
                  }
                  else
                  {
                    if (j==0 || j==width-1)
                    {
                      printf("X");
                    }else printf(" ");
                  }
                }
            }
        }
        printf("\n");
    }


    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n");
    printf("Time of operation = %.5f\n",cpu_time_used);
    return 0;
}
