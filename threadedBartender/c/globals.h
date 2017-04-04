/*
 * globals.h
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

int num_threads;	// number of customer threads
int nowServing;	// customer's ID who is being served

//Semaphores
sem_t* customerHere;
sem_t* roomToEnterBar;
sem_t* orderPlaced;
sem_t* orderReady;
sem_t* paidForDrink;
sem_t* paymentReceived;
sem_t* customerGone;

/*
* Sleeps for a random period of time between min and max
* @param min the minimum amount of sleep time
* @param max the maximum amount of sleep time
*/
static inline void msSleep(int min, int max){
	struct timespec slptm;
	long randSleep = rand() % (max-min); //Random sleep time between min and max
	slptm.tv_sec = 0;
	slptm.tv_nsec = (min + randSleep) * 1000000;
	nanosleep(&slptm, NULL);
}

#endif /* GLOBALS_H_ */
