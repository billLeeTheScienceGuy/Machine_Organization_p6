////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c  
// This File:        mySigHandler.c
// Other Files:      sendsig.c
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

void signal_handler(int signal_number);

void signal_user_handler(int signal_number);

void signal_int_handler(int signal_number);

int SIGUSR1_number = 0;

int main(){
	//print the program.
	printf("PID and time print every 4 seconds.\nType Ctrl-C to end the program.\n");
	//set up an alarm that will go off every 4 seconds.
	alarm(4);

	//register a signal handler to handle the SIGALRM signal
	struct sigaction sa;
	memset (&sa, 0, sizeof(sa));

	//The kernel will call this function if you properly register it for the desired signal.
	sa.sa_handler = signal_handler;

	//error handling
	if(sigaction(SIGALRM, &sa, NULL) < 0){
		printf("Error: handle failed to create\n");
		exit(1);
	}

	//write signal handler and register it to handle the SIGUSR1 signal using sigaction()
        struct sigaction sig_user;
        memset (&sig_user, 0, sizeof(sig_user));

        //The kernel will call this function if you properly register it for the desired signal.
        sig_user.sa_handler = signal_user_handler;

        //error handling
        if(sigaction(SIGUSR1, &sig_user, NULL) < 0){
                printf("Error: handle failed to create\n");
                exit(1);
        }

	//write signal handler and register it to handle the SIGUSR1 signal using sigaction()
        struct sigaction sig_int;
        memset (&sig_int, 0, sizeof(sig_int));

        //The kernel will call this function if you properly register it for the desired signal.
        sig_int.sa_handler = signal_int_handler;

        //error handling
        if(sigaction(SIGINT, &sig_int, NULL) < 0){
                printf("Error: handle failed to create\n");
                exit(1);
        }
	//infinite loop to receieve signal.
	while (1){
	}
}

void signal_handler(int signal_number){
	//get the pid value.
	pid_t pid = getpid();

	//get the time.
	time_t t;

	if(time(&t) < 0){
		printf("Error: could not create time variable\n");
		exit(1);
	}

	printf("PID: %d | Current time: %s", pid, ctime(&t));

	//register a signal handler to handle the SIGALRM signal
        struct sigaction sa;
        memset (&sa, 0, sizeof(sa));

	//re-arm or restart a new alarm to go off again 4 seconds later
        //The kernel will call this function if you properly register it for the desired signal.
        sa.sa_handler = signal_handler;

        //error handling
        if(sigaction(SIGALRM, &sa, NULL) < 0){
                printf("Error: handle failed to create\n");
                exit(1);
        }

	 alarm(4);
}
void signal_user_handler(int signal_number){
	//notify that a signal was received.
	printf("SIGUSR1 handled and counted!\n");

	//increment the received number count.
	SIGUSR1_number++;

	//re-arm or restart a new alarm to go off again 4 seconds later
	//write signal handler and register it to handle the SIGUSR1 signal using sigaction()
        struct sigaction sig_user;
        memset (&sig_user, 0, sizeof(sig_user));

        //The kernel will call this function if you properly register it for the desired signal.
        sig_user.sa_handler = signal_user_handler;

        //error handling
        if(sigaction(SIGUSR1, &sig_user, NULL) < 0){
                printf("Error: handle failed to create\n");
                exit(1);
        }

}
void signal_int_handler(int signal_number){
	//output the number of handled instances and exit.
	printf("SIGINT handled.\nSIGUSR1 was handled %d times. Exiting now.\n", SIGUSR1_number);
	exit(0);
}



