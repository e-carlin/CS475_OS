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
sem_t* doneBrowsingArt;

#endif /* GLOBALS_H_ */
