////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      mySigHandler.c
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
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <ctype.h>



void send_sig_int(int pid){
	//check kill return value.
	if((kill(pid, SIGINT) < 0)){
		printf("Error: cannot send SIGINT\n");
		exit(1);
	}
}

void send_sig_siguser1(int pid){
	////check kill return value.
        if((kill(pid, SIGUSR1) < 0)){
                printf("Error: cannot send SIGUSR1\n");
                exit(1);
        }
}

int main(int argc, char *argv[]){
	//check if the number of arguments are correct.
	if(argc != 3){
		printf("Usage: sendsig <signal type> <pid>\n");
		exit(1);
	}

	char *pid = argv[2];
	int i = 0;
	while(pid[i] > 0){
		//loop through the pid input to check if they are all digits
		if(!isdigit(pid[i])){
			//if it is not a digit, exit.
	       		printf("Usage: sendsig <signal type> <pid>\n");
               		exit(1);
	       	}
	       i++;
	}	       


	//receieve the signal.
	//at this point it is -i or -u.
	char *sig_with_dash = argv[1];

	//get rid of the dash and get only the char part.
	char signal_char = sig_with_dash[1];

	//if u, then call the siguser1 handler.
	if(signal_char == 'u'){
		send_sig_siguser1(atoi(pid));
	}
	//if i, call INT handler.
	else if(signal_char == 'i'){
		send_sig_int(atoi(pid));
	}
	//if it is neither i or u then the input is invalid.
	else{
		printf("Usage: sendsig <signal type> <pid>\n");
                exit(1);
	}
}


