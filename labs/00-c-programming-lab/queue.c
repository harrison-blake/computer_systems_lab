/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/

int input_count(char *s) 
{
    int input_length = 0;
    while(s[input_length] != '\0')
    {
        input_length++;
    }

    return input_length;
}

queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    if(!q)
        return NULL;

    q->head = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if(q)
    {
        list_ele_t *curr = q->head;
        list_ele_t *next;

        while(curr)
        {
            next = curr->next;
            free(curr->value);
            free(curr);
            curr = next;
        }
        
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    // if q is null return false
    if(!q)
        return false;

    // if malloc fails to allocate space return false
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if(!newh)
        return false;

    unsigned int input_length = input_count(s);

    // allocate list element value memory and copy string into it
    // add 1 to malloc and copy for ending string character
    // return false if malloc fails
    newh->value = malloc(input_length+1);
    if(!newh->value)
    {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, input_length+1);

    newh->next = q->head;

    if(q->size == 0)
        q->tail = newh;

    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{   
    if(!q)
        return false;

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));

    if(!newt)
        return false;

    unsigned int input_length = input_count(s);

    newt->value = malloc(input_length+1);
    if(!newt->value)
    {
        free(newt);
        return false;
    }

    strncpy(newt->value, s, input_length+1);

    // if queue is empty set new tail to be queue's head and tail
    // if queue is not empty keep track of queue's current tail
    if(q->size == 0)
        q->head = newt;
    else
    {
        list_ele_t *curt;
        curt = q->tail;
        curt->next = newt; 
    }
    
    newt->next = NULL;
    q->tail = newt;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if(!q || !q->head)
        return false;

    list_ele_t *curr = q->head;
    q->head = curr->next;

    int input_length = input_count(curr->value);

    if(!sp){}
    else if(bufsize-1 >= input_length)
    {
        strncpy(sp, curr->value, bufsize-1);
        sp[input_length] = '\0';  
    }
    else
    {
        for(int i=0; i<bufsize-1; i++)
        {
            sp[i] = curr->value[i];
        }
        sp[bufsize-1] = '\0';
    }

    free(curr->value);
    free(curr);
    q->size--;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if(!q)
        return 0;
    else
        return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty or size = 1
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    // only do something if q != NULL or q is greater than 1 element
    if(q && q->size > 1)
    {
        list_ele_t *prev = NULL, *curr = q->head, *next = NULL;
        list_ele_t *oldh = q->head, *oldt = q->tail;

        while(curr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        q->head = oldt;
        q->tail = oldh;
    }
}