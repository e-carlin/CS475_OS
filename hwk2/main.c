#include <stdio.h>
#include <string.h>
#include "employee.h"
#include "heap.h"

int MAX_EMPLOYEES = 5;

int main()
{
	struct Employee employees[MAX_EMPLOYEES];
	int numEmployees = 0;
	char promptAgain = 'y';

	// Read in user data
	while(promptAgain == 'y' && numEmployees < MAX_EMPLOYEES){
		//The employee struct
		struct Employee emp;

		//Collect and store info from user
		printf("Name: ");
		fgets(emp.name, MAX_NAME_LEN, stdin); //only read in upto MAX_NAME_LEN
		strtok(emp.name, "\n"); //remove trailing \n

		printf("Salary: ");
		scanf("%d", &emp.salary);
		getchar(); //Clear buffer on \n

		//Add this employee to the list
		employees[numEmployees] = emp;
		numEmployees++;

		//break out if we can't take anymore employees
		if(numEmployees == MAX_EMPLOYEES)
			break;
		printf("Enter another user (y/n): ");
		scanf(" %c", &promptAgain);
		getchar(); //clear buffer of \n
		printf("\n");


	}

	//Sort in descending order
	heapSort(employees, numEmployees);
	printList(employees, numEmployees);
	return 0;
}
