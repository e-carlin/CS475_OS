/* queue.h */

/* Queue structure declarations, constants, and inline functions	*/



#define	EMPTY	(-1)		/* null value for qnext or qprev index	*/


//Queue's data members
struct queue
{
	struct qentry *head;
	struct qentry *tail;
	int size;
};


//A queue entry's data members
struct qentry
{
	int frame;
	struct qentry *prev;
	struct qentry *next;
};


/* Queue function prototypes (don't touch!) */
void    printqueue(struct queue *q);

int	isempty(struct queue *q);
int	nonempty(struct queue *q);

int	getfirst(struct queue *q);
int	getlast(struct queue *q);
int	remove_entry(int frame, struct queue *q);
int	dequeue(struct queue *q);
int	enqueue(int frame, struct queue *q);

struct queue	*newqueue();
struct qentry	*getbyframe(int frame, struct queue *q);