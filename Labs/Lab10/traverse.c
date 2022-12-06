/*
 * CSCI 315 Operating Systems Design
 * Original developed by CSCI 315 staff
 * Modified by: L. Felipe Perrone
 * Date: 2011-4-21
 * Copyright (c) 2011 Bucknell University
 *
 * Permission is hereby granted, free of charge, to any individual or
 * institution obtaining a copy of this software and associated
 * documentation files (the "Software"), to use, copy, modify, and
 * distribute without restriction, provided that this copyright and
 * permission notice is maintained, intact, in all copies and supporting
 * documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "read_dir.h"

// function prototypes
void process(char *name);
void enqueue(char *name, que_t *q);
void dequeue(que_t *q);
void peek_front(char *name,que_t q);
bool queue_empty(que_t q);
void initq(que_t *q);

// main function
int main(int argc,char *argv[]) {

  if (2 != argc) {
    printf(" usage: %s dirpath\n", argv[0]);
    exit(-1);
  }
  else {
    // pass in the starting directory
    process(argv[1]);       
  }
  
  return 0;
}

// traverse a directory tree applying a function when a file is found
void process(char *root)
{
  int numOfFiles = 0;
  que_t nameq;
  char dname[MAXLENGTH];
  char cname[MAXLENGTH];
  char prefix[MAXLENGTH];

  struct dirent *dp;
  DIR *dirp;
  int small = INT_MAX;
  int large = 0;
  double sum = 0.0;
  int numReg = 0;
  int numDir = 0;
  struct stat file_info;
  time_t recentlyMod = 0;
  time_t leastRecent = INT_MAX;

  char modname[MAXLENGTH] = "";
  char rmodname[MAXLENGTH] = "";
  
  initq(&nameq);
  enqueue(root,&nameq);

  while (true != queue_empty(nameq)) {
	peek_front(dname,nameq); 
	dequeue(&nameq);
    
	dirp = opendir(dname);
	if (dirp != NULL) { // it is a directory
	  
	  printf("directory : %s\n",dname);
	  strncpy(prefix, dname, MAXLENGTH);
	  strncat(prefix,"/", MAXLENGTH);
	  
	  for (dp = readdir(dirp); NULL != dp; dp = readdir(dirp)) {
		if ((strcmp(dp->d_name,"..") != 0) && 
			(strcmp(dp->d_name,".") != 0)) {
		  
		  // prevent from infinite loop
		  strncpy(cname, prefix, MAXLENGTH);
		  
		  // concatenate the prefix
		  strncat(cname, dp->d_name, MAXLENGTH);  
		  enqueue(cname,&nameq);
		}
	  }
	  numDir++;
	  closedir (dirp);
	} else { 
	  // test if it is a regular file and not a device or link -- TO-DO
	  // if this is a regular file, then process it -- TO-DO
	  printf(" processing file: %s\n", dname);
	  struct stat buf;
	  lstat(dname, &buf);
	  if (S_ISLNK(buf.st_mode)) {
		printf(" link detected [name: %s]\n", dname);
		continue;
	  }

	  int fd = open(dname, O_RDONLY);
	  if (fd == -1) {
		perror(" failed to open file\n");
		exit(-1);
	  }
	  fstat(fd, &file_info);
	  if (file_info.st_size < small) {
		small = file_info.st_size;
	  }
	  if (file_info.st_size > large) {
		large = file_info.st_size;
	  }
	  sum += file_info.st_size;

	  switch(file_info.st_mode & S_IFMT) {
	  case S_IFREG:
		numReg++;
		break;
	  case S_IFDIR:
		numDir++;
		break;
	  default:
		break;
	  }

	  if (file_info.st_mtime < leastRecent) {
		leastRecent = file_info.st_mtime;
		strcpy(modname, dname);
	  }
	  else if (file_info.st_mtime > recentlyMod) {
		recentlyMod = file_info.st_mtime;
		strcpy(rmodname, dname);
	  }
	  numOfFiles++;
	  close(fd);
	}      
  } // while
  
  printf(" a total of %d files were counted\n", numOfFiles);
  printf(" smallest file size: %d\n", small);
  printf(" largest file size: %d\n", large);
  printf(" average file size: %0.2f\n", sum/(double)numOfFiles);
  printf(" a total of %d directories were counted\n", numDir);
  printf(" a total of %d regular files were counted\n", numReg);
  printf(" file most recently modified: %s\n", rmodname);
  printf(" file least recently modified: %s\n", modname);
}

// initialize queue data structure
void initq(que_t *q) {
  q->head = q->tail = NULL;
}

// test whether queue data structure is empty
bool queue_empty(que_t q) {
  if (NULL == q.head) {
	return true;
  } else {
    return false;
  }
}

// add an element to queue
void enqueue(char *name, que_t *q) {
  item_t *temp;
  
  temp = (item_t *)malloc(sizeof(item_t));
  strncpy(temp->name,name,MAXLENGTH);
  temp->next = NULL;
  
  if (true == queue_empty(*q)) {
    q->head = temp;
    q->tail = temp;
  } else {
    q->tail->next = temp;
    q->tail = q->tail->next;
  }
}

// remove an element from the front of the queue
void dequeue(que_t *q) {
  item_t *temp;
  
  if (true == queue_empty(*q)) {
    printf(" error in dequeue \n");
    exit(-1);
  } else {
    temp = q->head;
    q->head = q->head->next;
    free(temp);
  }
}

// find element at front of queue without removing
void peek_front(char *name, que_t q) {
  if (true == queue_empty(q)) {
    printf(" error in dequeue \n");
     exit(-1);
  } else {
    strncpy(name, q.head->name, MAXLENGTH);
  }
} 
