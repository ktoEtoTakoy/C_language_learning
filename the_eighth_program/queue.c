#include "queue.h"
#include "string.h"

/* creates a new queue with a given size */
queue_t* create_queue(int capacity)
{
    queue_t *queue = malloc(sizeof(queue_t));
    queue->array = malloc(capacity*sizeof(void*));
    queue->capacity = capacity;
    queue->rear = -1;
    queue->front = -1;
    queue->size = 0;
    return queue;
}

int abs(int number){if(number<0){return -number;}return number;}

/* deletes the queue and all allocated memory */
/*if queue is not empty, return an error*/
void delete_queue(queue_t *queue)
{
    if (queue->rear != -1 && queue->front != -1)
    {
        fprintf(stderr, "Queue cannot be deleted.\n");
    }
    else
    {
        printf("Process deleting 1 \n" );
        if(queue->array != NULL)
        {
            printf("Process deleting 2 \n" );
            free(queue->array);
        }
    }
}

/*
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void* data)
{
    if (queue->rear == -1)
    {
        (queue->rear) = (queue->front) = 0;
        (queue->array[queue->rear]) = data;
        (queue->size) = 1;
        return true;
    }
    else if (queue->size == queue->capacity || queue->front == (queue->capacity - 1)) //[ . . . . , ]
    {
        (queue->capacity)*=2;
        queue->array = (void*)realloc(queue->array, queue->capacity*sizeof(void*));
        (queue->size)++;
        (queue->rear)++;
	    queue->array[queue->rear] = data;
        return true;
    }
	else //[ . . . . ]
	{
        (queue->size)++;
        (queue->rear)++;
	    queue->array[queue->rear] = data;
        return true;
	}
    fprintf(stderr, "Something went wrong while pushing...\n" );
    return false;
}

/*
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 * in the case there is only one element in the queue function returns this element, front and rear become -1
 */
void* pop_from_queue(queue_t *queue)
{
    if (queue->front != -1 || queue->size)
    {
        void* elem = queue->array[queue->front];

        if (queue->front == queue->rear)
        {
            int temp = queue->front;
            queue->front = queue->rear = -1;
            (queue->size) = 0;
            if (queue->size <= (int)((double)(queue->capacity) * (2.0/3.0)))
            {
                void* queue_array_new = malloc(queue->size*2/3*sizeof(void*));
                if(queue_array_new==NULL) return false;// esli pizda pamqti
                memcpy((queue_t*)queue_array_new,(queue->array)+(queue->front),((queue->rear)-(queue->front)+1)*sizeof(void*));
                //          куда      ,     откуда                 , докуда
                //          куд       ,     какие элементы, считая по индексам
            }
            return elem;
        }
        else if (queue->front < queue->rear) { (queue->size)--;queue->array[queue->front] = NULL;(queue->front)++;
            if (queue->size <= (int)((double)(queue->capacity) * (2.0/3.0)))
            {

                void* queue_array_new = malloc(queue->size*2/3*sizeof(void*));
                if(queue_array_new==NULL) return false;// esli pizda pamqti
                memcpy((queue_t*)queue_array_new,(queue->array)+(queue->front),((queue->rear)-(queue->front)+1)*sizeof(void*));
                //          куда      ,     откуда                 , докуда
                //          куд       ,     какие элементы, считая по индексам
            } return elem;}

        else return elem; // this statement mustnt be reached
    }
    else return NULL;
}

/*
 * gets idx-th element from the queue
 * returns the element that will be popped after idx calls of the pop_from_queue()
 * returns: the idx-th element on success; NULL otherwise
 */


void* get_from_queue(queue_t *queue, int idx)
{
    //idx--;
    if(queue->rear == -1 || idx < 0 || idx >= queue->capacity) return NULL;

    void* temp = queue->array[idx];

    if (queue->size <= (int)((double)(queue->capacity) * (2.0/3.0)))
    {
        void* queue_array_new = malloc(queue->size*2/3*sizeof(void*));
        if(queue_array_new==NULL) return false;
        memcpy((queue_t*)queue_array_new,(queue->array)+(queue->front),((queue->rear)-(queue->front)+1)*sizeof(void*));

    }
    return temp;
}

/* gets number of stored elements */
int get_queue_size(queue_t *queue)
{
    if(queue != NULL) return queue->size;
    else return 0;
}
