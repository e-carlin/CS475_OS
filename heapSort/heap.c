/*
 * heapsort.c
 *
 *  Created on: Jul 1, 2013
 *      Author: 
 */
#include <stdio.h>
#include <stdlib.h>
#include "employee.h"
#include "heap.h"

//Helper prototypes
static int getIndexLeftChild(int);
static int getIndexRightChild(int);

/**
 * Sorts a list of n employees in descending order
 *
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the list
 */
void heapSort(struct Employee *A, int n)
{
	//BuildHeap on the list
	buildHeap(A, n);

	while(n>0){
		//A[0] is the smallest element due to min-heap property so put it at n-1 and it is now sorted 
		swap(&A[n-1], &A[0]);
		//No longer need to worry about it so decrement n
		n--;
		//Find the next smalles element after running heapify() it will be at A[0]
		heapify(A, 0, n);
	}
}


/**
 * Given an array A[], we want to get A[] into min-heap property
 * We only need to run heapify() on internal nodes (there are floor(n/2) of them)
 * and we need to run it bottom up (top-down cannot build a heap)
 *
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the list
 */
void buildHeap(struct Employee *A, int n)
{
	int i;
	for(i=n/2; i>-1; i--){
		heapify(A, i, n);
	}
}


/**
 * We want to start with A[i] and trickle it downward
 * if it is greater than either left or right child.
 *
 * @param	*A	Pointer to the list of employees
 * @param	i	Index of current element to heapify
 * @param	n	Size of the list
 */
 void heapify(struct Employee *A, int i, int n)
 {
 	//Left child of i
 	int leftChild = getIndexLeftChild(i);
 	//right child of i
 	int rightChild = getIndexRightChild(i);

 	//If leftChild < n then there are still elements we might want to swap with
 	if(leftChild < n){

 		//If rightChild < n then we need to find the child with smalles salary
 		if(rightChild < n){
 			//Find child with smallest salary
 			int smallerChild = A[leftChild].salary < A[rightChild].salary ? leftChild : rightChild;
 			//If i's salary is > than the child with the smallest salary then swap and recurse
 			if( A[i].salary > A[smallerChild].salary){
 				//Swap
 				swap(&A[i], &A[smallerChild]);
 				//recurse on child
 				heapify(A, smallerChild, n);
 			}
 	}
 	//rightChild is out of bounds so we can only swap with left
 	else{
 		//If i's salary is > leftChild's salary then swap and recurse
 		if(A[i].salary > A[leftChild].salary){
 			swap(&A[i], &A[leftChild]);
 			heapify(A, leftChild, n);
 		}
 	}	 
 	}
 }

/**
 * Gets the minimally paid employee. Assumes the given list is a min-heap.
 *
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the list
 */
struct Employee *getMinPaidEmployee(struct Employee *A, int n)
{
	return &A[0];
}


/**
 * Swaps the locations of two Employees
 * @param *e1 An Employee
 * @param *e2 Another Employee to swap with
 */
void swap(struct Employee *e1, struct Employee *e2)
{
	struct Employee temp = *e1;
	*e1 = *e2;
	*e2 = temp;
}

/**
 * Outputs an array of Employees
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the list
 */
void printList(struct Employee *A, int n)
{
	int i;
	printf("[ ");
	for(i=0; i<n-1; i++){
		printf("id= %s sal= %d, ", A[i].name, A[i].salary);
	}
	printf("id= %s sal= %d ]\n", A[n-1].name, A[n-1].salary);
}


//************** static helpers ******************
/**
* Get the index of the left child of node with index i
* @param i Index of the element we want to find the left child of
* @return the index of the left child
*/
static int getIndexLeftChild(int i){
	return 2 * (i+1) -1;
}

/**
* Get the index of the right child of a noded at index i
* @param i Index of the element we want to find the right child of
* @return Index of the left child
*/
static int getIndexRightChild(int i){
	return 2 * (i+1);
}