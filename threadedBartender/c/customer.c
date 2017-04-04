/*
 * customer.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"

/**
 * This is what the thread will call.
 * Do not touch.
 */
void* customer(void* args){

	unsigned int *custID = (unsigned int*) args;
	custTravelToBar(*custID);
	custArriveAtBar(*custID);
	custPlaceOrder();
	custBrowseArt();
	custAtRegister();
	custLeaveBar();
	return NULL;
}


/**
 * Each customer takes a random amount of time between 20 ms and 5000 ms to travel to the bar.
 */
void custTravelToBar(unsigned int custID){

	printf("Cust %u\t\t\t\t\t\t\t\t\t\t\t|\n", custID);
	sem_post(customerHere);
}


/**
 * If there is already another customer in the bar the current customer has
 * to wait until bar is empty before entering.
 */
void custArriveAtBar(unsigned int custID){

	printf("\t\tCust %u\t\t\t\t\t\t\t\t\t|\n", custID);

	//Wait for space in the bar
	sem_wait(roomToEnterBar);
}


/**
 * The customer in the bar places an order
 */
void custPlaceOrder(){

	printf("\t\t\t\tCust %u\t\t\t\t\t\t\t|\n", nowServing);
	sem_post(orderPlaced);
}


/**
 * The customer in the bar can browse the wall art for a random amount of time between 3ms and 4000ms.
 */
void custBrowseArt(){

	//TODO - synchronize
	printf("\t\t\t\t\t\tCust %u\t\t\t\t\t|\n", nowServing);
}


/**
 * If their drink is not ready by the time they are done admiring the art they must wait
 * until the bartender has finished. When the bartender is finished, the customer pays.
 *
 */
void custAtRegister(){

	//TODO - synchronize
	printf("\t\t\t\t\t\t\t\tCust %u\t\t\t|\n", nowServing);
}


/**
 * The customer in the bar leaves the bar.
 */
void custLeaveBar(){
	
	//TODO - synchronize
	printf("\t\t\t\t\t\t\t\t\t\tCust %u\t|\n", nowServing);
}
