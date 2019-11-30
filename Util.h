/*
 * Util.h
 *
 *  Created on: Nov 13, 2019
 *      Author: ganga
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <string.h>
#include <time.h>

#define false 0
#define true 1

#define low 0
#define high 1



// This only works for C
 char *  currentTime () {
  time_t rawtime;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime (&rawtime);
  char * thetime = asctime(timeinfo);
  thetime[strlen(thetime)-1] = '\0';
  return thetime;
}

// What is the current time
#define DATE_STRING currentTime ()

#define log_err(M, ...) printf("%s | " M "\n", DATE_STRING)

#define debug(M, ...) printf("       __debug__   \n")

#define check_mem(A) check((A), "Out of memory.")
#endif /* UTIL_H_ */
