/*
 * CSCI 315 Operating Systems Design
 * Author: L. Felipe Perrone
 * Date: 2014-09-21
 * Copyright (c) 2014 Bucknell University
 *
 * Permission is hereby granted, free of charge, to any individual
 * or institution obtaining a copy of this software and associated
 * documentation files (the "Software"), to use, copy, modify, and
 * distribute without restriction, provided that this copyright
 * and permission notice is maintained, intact, in all copies and
 * supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wrapper.h"
#include "wrapper.c"


#define BUFFER_SIZE 512
#define TRUE 1
#define FALSE 0

/*------------------------------------------------------------------------
 * Program:   echoreq
 *
 * Purpose:  allocate a socket, connect to a server, transfer requested
 *            file to local host, and print file contents to stdout
 *
 * Usage:    echoreq [ host ] [ port ] [ string ] 
 *
 *		 host  - name of a computer on which server is executing
 *		 port  - protocol port number server is using
 *     string - a string in double quotes
 *     
 *------------------------------------------------------------------------
 */

int
main(int argc, char* argv[]) {

	struct	hostent	 *ptrh;	 // pointer to a host table entry	
	struct	sockaddr_in sad; // structure to hold an IP address	
	struct addrinfo hints, *res, *p;
	
	int	sd;		                 // socket descriptor			
	char *host;                // pointer to host name		
	char  in_msg[BUFFER_SIZE]; // buffer for incoming message

	int ret_val;

	memset((char *)&sad,0,sizeof(sad)); // zero out sockaddr structure	
	sad.sin_family = AF_INET;	          // set family to Internet	

	// verify usage

	if (argc < 3) {
		printf("Usage: %s [ port ] [ string ]\n", argv[0]);
		exit(-1);
	}

	if (atoi(argv[1]) > 0)	
		// test for legal value		
	  sad.sin_port = htons((u_short)atoi(argv[1]));
	else {				
		// print error message and exit	
		printf("ECHOREQ: bad port number %s\n", argv[2]);
		exit(-1);
	}

	// convert host name to equivalent IP address and copy to sad 

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = 0;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	
	int s = getaddrinfo(NULL, argv[1], &hints, &res);
	if (s != 0) {
	  printf("ECHOREQ: getaddrinfo failed\n");
	  exit(-1);
	}
	
	for (p = res; p != NULL; p = p->ai_next) {
	  sd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	  if (sd < 0) {
		continue;
	  }
	  bind(sd, p->ai_addr, p->ai_addrlen);
	  if (Connect(sd, p->ai_addr, p->ai_addrlen) == 0) {
		break;
	  }
	}

	freeaddrinfo(res);
   
	// send message to server

	Write(sd, argv[2], strlen(argv[2]) + 1);
	// receive message echoed back by server

	Read(sd, in_msg, BUFFER_SIZE);
	printf("ECHOREQ: from server= %s\n", in_msg);

	// close the socket   
	close(sd);

	// terminate the client program gracefully 
	return(0);
}
