////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
// Other Files:      NA
// Semester:         CS 354 Lecture 01 Fall 2022
// Instructor:       deppeler
// 
// Author:           Bill Lee
// Email:            blee266@wisc.edu
// CS Login:         billl
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   
//                   
//
// Persons:          NA
//                  
//
// Online sources:  NA
//                  
//                   
//////////////////////////// 80 columns wide ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013,2019-2020
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for Fall 2022
//
////////////////////////////////////////////////////////////////////////////////
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


void signal_user_terminate (int signal_number);

void signal_user_divide_zero (int signal_number);

int total_count = 0; //global variable to keep count of sucessful operations.

int main(){

	//handler for terminate signal (SIGINT)
	struct sigaction sig_terminate;
        memset (&sig_terminate, 0, sizeof(sig_terminate));

        //The kernel will call this function if you properly register it for the desired signal.
        sig_terminate.sa_handler = signal_user_terminate;

        //error handling
        if(sigaction(SIGINT, &sig_terminate, NULL) < 0){
                printf("Error: handle failed to create\n");
                exit(1);
        }

	//handler for SIGFPE, the divide by zero case.
	struct sigaction sig_div_zero;
        memset (&sig_div_zero, 0, sizeof(sig_div_zero));

        //The kernel will call this function if you properly register it for the desired signal.
        sig_div_zero.sa_handler = signal_user_divide_zero;

        //error handling
        if(sigaction(SIGFPE, &sig_div_zero, NULL) < 0){
                printf("Error: handle failed to create\n");
                exit(1);
        }

	//dont check for invalid values like discribed on rubric.
	while(1){

		printf("Enter first integer: ");

		//Use fgets() to read each line of input (use a buffer of 100 bytes).
		char buffer_first [100];
		fgets(buffer_first, 100, stdin);

		//assign the buffer value to an int variable.
		int input_first;
		input_first = atoi(buffer_first);

		//take the second integer in the same way.
		printf("Enter second integer: ");

		char buffer_second [100];
		fgets(buffer_second, 100, stdin);

		int input_second;
		input_second = atoi(buffer_second);

		//the calculation output.
		printf("%i / %i is %i with a remainder of %i\n", input_first, input_second, 
				input_first/input_second, input_first%input_second);

		//operation was sucessful, increment the total count.
		total_count++;
	}
}

void signal_user_terminate (int signal_number){
	//when ctrl c is pressed then return the total count and exit.
	printf("\nTotal number of operations completed successfully: %i\nThe program will be terminated.\n", total_count);
	exit(0);
}

void signal_user_divide_zero (int signal_number){
	//when divided by zero then notify, return the total count and exit.
	printf("Error: a division by 0 operation was attempted.\nTotal number of operations completed successfully: %i\nThe program will be terminated.\n", total_count);
	exit(0);
}









