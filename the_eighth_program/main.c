
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "queue.h"
// https://en.wikipedia.org/wiki/Queue_(abstract_data_type)
/*
 * Fronta je datová struktura, u které jsou definovány operace výběru a vložení prvku.
 * Operace výběr z fronty vybere prvek, který jsme vložili do fronty jako první.
 * Při vkládání prvků do fronty se vkládaná položka vloží na jeho konec. (anglicky enqueue/push a dequeue/pop)
 * Tato struktura se také někdy označuje termínem FIFO (first-in first-out).
 *
 *
 *
 * Nejjednodušší implementací fronty v poli je ukládání i-tého prvku ve frontě na i-tou pozici v poli.
 * Přidávání nového prvku je velmi snadné.
 *  Nicméně vyjímání prvků může tvrvat dlouho, protože (abychom zachovali pořadí)
 *        je nutné nejprve vyjmout 1. prvek (z čela) fronty a všechny následující prvky posunout o jednu pozici.
 * Taková implementace je značně neefektivní pro větší fronty, proto se zpravidla nepoužívá a ani v tomto úkolu nevede na správné řešení.
 *
 *
 *
 * When we pop element, a pointer from the first element redirects to the second element
*/


/*
 * Testovací program očekává na standardním vstupu velikost fronty N. Poté jsou na jednotlivých řádcích pokyny pro simulaci práce se frontou:

 * a value - (push) - Alokuje pamět pro jedno číslo typu int,
 *      uloží do něj hodnotu value a ukazatel na toto číslo vloží na konec fronty
  zavoláním funkce push_to_queue().
 * r - (pop) - Zavolá funkci pop_from_queue() a získá tak ukazatel na první element ve frontě, ze které byl zároveň odstraněn. Vypíše hodnotu čísla,
 * na který odkazuje získaný ukazatel a uvolní jeho paměť.
 * g idx - (get) - Zavolá funkci get_from_queue() a získá tak ukazatel na element ve frontě na indexu idx.
 * Element nebyl z fronty odstraněn. Následně vypíše hodnotu čísla, na který odkazuje získaný ukazatel.
 * Na standardním výstupu tento simulátor vypisuje hodnoty pro operace r(pop), g(get). Pokud je dotaz neplatný, vypíše NULL.
*/


/* allocate new integer with value a and add it to the queue */
void add(int a, queue_t *queue);

/* print the int value on pointer p */
void print_int(void *p);

/* pop from the queue, print and free the element */
void pop(queue_t *queue);

/* get i-th element and print it (do not remove them) */
void get(int idx, queue_t *queue);

/*
 * TEST PROGRAM
 * - reads commands from stdin and executes them in the queue
 */

int main(int argc, char *argv[])
{
    int n;
    /* the tested queue */
    queue_t queue;
    // read the size of the queue
    printf("Enter size of an array\n");
    scanf("%d", &n);
    // create queue
    queue = *create_queue(n);
    printf("What do you want to do next:\n\t'a': add an element\n\t'p': pop an element\n\t'g': get the element\n");
    while (true)
    {

        char s[2];
        // read one command
        int ret = scanf("%1s", s);

        if (ret != 1) break;

        // add command
        if (s[0] == 'a')
        {
            int a;
            // read the argument of the command

            ret = scanf("%d", &a);
            if (ret != 1) break;

            add(a, &queue);
            // remove command
        } else if (s[0] == 'p')
        {
            pop(&queue);
            // get command
        } else if (s[0] == 'g')
        {
            int a;
            // read the argument of the command
            ret = scanf("%d", &a);

            if (ret != 1) break;

            get(a, &queue);
        }
    }
    printf("After 1st while \n");

    // remove rest of the elements in the queue
    while (get_queue_size(&queue))
    {
        void *p = pop_from_queue(&queue);
        free(p);
    }
    printf("After 2nd while \n");
    // free memory
    delete_queue(&queue);
    printf("After delete queue \n");

    // return 0 on succes
    return 0;
}

void add(int a, queue_t *queue)
{
    int *p = (int*)malloc(sizeof(int));
    *p = a;
    bool ret = push_to_queue(queue, (void*)p);
    if (!ret) free(p);
}

void print_int(void *p)
{
    if(p != NULL)  printf("%d\n", *((int*)p));
    else           printf("NULL\n");
}

void pop(queue_t *queue)
{
    void *p = pop_from_queue(queue);
    print_int(p);
    free(p);
}

void get(int idx, queue_t *queue)
{
    print_int(get_from_queue(queue, idx));
}
