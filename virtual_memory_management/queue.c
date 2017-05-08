/* queue.c - enqueue, dequeue, isempty, nonempty, et al. */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * Prints out contents of a queue
 * @param q	pointer to a queue
 */
void	printqueue(struct queue *q)
{
	printf("[ ");
	struct qentry *elem = q->head;
	while(elem != NULL){
		printf("(frame=%d)", elem->frame);
		elem = elem->next;

		//Only print a comma if there are more to follow
		if(elem != NULL){
			printf(", ");
		}
	}
	printf("]\n");
}

/**
 * Checks whether queue is empty
 * @param q	Pointer to a queue
 * @return TRUE if true, FALSE otherwise
 */
int	isempty(struct queue *q)
{
	return (q->head == NULL) ? 1 : 0;
}

/**
 * Checks whether queue is nonempty
 * @param q	Pointer to a queue
 * @return TRUE if true, FALSE otherwise
 */
int	nonempty(struct queue *q)
{

	return (q->head != NULL) ? 1 : 0;
}




/**
 * Insert a process at the tail of a queue
 * @param fream frame number to insert
 * @param q	Pointer to the queue to use
 *
 * @return frame on success, -1 otherwise
 */
int enqueue(int frame, struct queue *q)
{

        //Allocate space on heap for a new QEntry
        struct qentry* procToEnqueue = (struct qentry*) malloc(sizeof(struct qentry));

        //Initialize the new QEntry
        procToEnqueue->frame = frame;
        procToEnqueue->prev = q->tail;
        procToEnqueue->next = NULL;

        //Insert as head if q is empty
        if(isempty(q)){
        	q->head = procToEnqueue;
        	q->tail = procToEnqueue;
        }
        else{
        	q->tail->next = procToEnqueue;
        	q->tail = procToEnqueue;
        }
        //Increment q size
        q->size++;
        //Return the frame on success
        return frame;
}


/**
 * Remove and return the first process on a list
 * @param q	Pointer to the queue to use
 * @return frame of the process removed, or -1 if queue is empty
 */
int dequeue(struct queue *q)
{
        //Return EMPTY if queue is empty
		if(isempty(q)){
			return -1;
		}
		else{
        	//Get the head entry of the queue
			struct qentry* head = q->head;
			int frame = head->frame; 

        	//Unlink the head entry from the rest
			q->head = q->head->next;

        	//Free up the space on the heap
			free(head);

			//Decrement q size
			q->size--;
        	//Return the frame on success
			return frame;
		}
}


/**
 * Finds a queue entry given pid
 * @param pid	a process ID
 * @param q	a pointer to a queue
 * @return pointer to the entry if found, NULL otherwise
 */
struct qentry *getbyframe(int frame, struct queue *q)
{
	//Return NULL if queue is empty or if an illegal pid is given
	if(isempty(q)){
		return NULL;
	}
	else{
		//Find the qentry with the given pid
		struct qentry* entry = q->head;
		while(entry != NULL){
			if(entry->frame == frame){
				return entry;
			}
			else{
				entry = entry->next;
			}
		}
		return NULL;
	}
}

/**
 * Remove a qentry from the front of a queue
 * @param q	pointer to a queue
 * @return frame on success, -1 if queue is empty
 */
int	getfirst(struct queue *q)
{
	//Return EMPTY if queue is empty
	if(isempty(q)){
		return -1;
	}
	else{
		//Remove process from head of queue and return its pid
		return dequeue(q);

	}
}

/**
 * Remove a qentry from the end of a queue
 * @param q	Pointer to the queue
 * @return frame on success, -1 otherwise
 */
int	getlast(struct queue *q)
{
	//Return -1 if queue is empty
	if(isempty(q)){
		return -1;
	}
	else{//Remove process from tail of queue and return its pid
		//Get tail
		struct qentry* tail = q->tail;
		//Get the frame
		int frame = tail->frame;
		//free tail
		free(tail);
		//Decrement q size
		q->size--;
		//return frame
		return frame;
	}
}



/**
 * Remove a qentry from an arbitrary point in a queue
 * @param frame	frame # of qentry to remove
 * @param q	Pointer to the queue
 * @return frame on success, -1 if q is empty or frame can't be found
 */
int	remove_entry(int frame, struct queue *q)
{
	//Return -1 if queue is empty
	if(isempty(q)){
		return -1;
	}

	else{ //Remove process identified by pid parameter from the queue and return its pid
		//Get entry
		struct qentry* entryToRemove = getbyframe(frame, q);
		if(entryToRemove != NULL){ //pid exists
			//Update pointers
			if(q->head == entryToRemove){
				return getfirst(q);
			}
			else if(q->tail == entryToRemove){
				return getlast(q);
			}
			else{
				//Adjust neighbor pointers
				entryToRemove->prev->next = entryToRemove->next;
				entryToRemove->next->prev = entryToRemove->prev;
				//Store frame
				int frame = entryToRemove->frame;
				//Free mem
				free(entryToRemove);
				//Decrment q size
				q->size--;
				//Return frame
				return frame;
			}
		}
		else{ //frame can't be found
			return -1;
		}
	}
}