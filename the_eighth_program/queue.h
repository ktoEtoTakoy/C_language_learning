#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////

typedef struct
{
    int front;
    int rear;
    void **array;
    int capacity;
    int size;
} queue_t;

queue_t* create_queue(int capacity);

///////////////////////////////////////////////

void delete_queue(queue_t *queue);

///////////////////////////////////////////////

bool push_to_queue(queue_t *queue, void *data);

///////////////////////////////////////////////

void* pop_from_queue(queue_t *queue);

///////////////////////////////////////////////

void* get_from_queue(queue_t *queue, int idx);

///////////////////////////////////////////////

int get_queue_size(queue_t *queue);

///////////////////////////////////////////////

int abs(int number);

#endif // __QUEUE_H__
