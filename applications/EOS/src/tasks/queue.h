#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../debug/debug.h"
#include "../utils/string/strings.h"
#include "hal/time/time.h"

typedef struct TaskArguments {
  int length;
  const char* elements;
} TaskArguments;
typedef struct TaskTimer {
  bool (*func)(TaskArguments args); //boolean is if the task completed. Functions should always return false if it is an infinite task
  TaskArguments args; //Argument to pass to callback
  int id; //ID of the task
  unsigned long start; //Time started
  unsigned long delay; //Delay between calling and start
  unsigned long interval; //Delay between runs
  unsigned long lastrun; //Last run time. 0 means never ran before
  unsigned long timeout; //Time until it gives up. Set to 0 to disable
} TaskTimer;

//TaskArguments NULL_ARGS = (TaskArguments) {.length=0,.elements=NULL}; //Null struct for referencing


void queueFunction(bool (*func)(TaskArguments args), TaskArguments args, long delay, unsigned long interval, unsigned long timeout);
void shrinkTaskList(int i);
void runQueue(void);


#endif