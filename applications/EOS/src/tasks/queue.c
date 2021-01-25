#include "queue.h"

TaskTimer* tList;
unsigned int tListLen=0;

void queueFunction(bool (*func)(TaskArguments args), TaskArguments args, long delay, unsigned long interval, unsigned long timeout) {
  tList=(TaskTimer*)realloc(tList,sizeof(TaskTimer)*(++tListLen));
  tList[tListLen-1]=(TaskTimer) {.func=func,.args=args,.id=tListLen-1,.start=millis(),.delay=delay,.interval=interval,.lastrun=0,.timeout=timeout};
}
void shrinkTaskList(int i) {
  if(tListLen==1 || tListLen==0) {
    tList=NULL;
    tListLen=0;
  } else {
    TaskTimer* tList2 = (TaskTimer*)malloc(sizeof(TaskTimer)*(tListLen-1));
    for(int j=0;j<tListLen-1;j++) { //Shrink tasklist stack
      if(j<i) tList2[j]=tList[j];
      else tList2[j]=tList[j+1];
    }
    tList=(TaskTimer*)malloc(sizeof(TaskTimer)*(--tListLen));
    for(int j=0;j<tListLen;j++) {
      tList[j]=tList2[j];
    }
  }
}
void runQueue(void) {
  if(tList==NULL || tListLen==0) {
    if(getDebug()) {
      //logMessage(DEBUG, "Skipping queue because it is empty."); //Spams too much so disabled for now
    }
    return; //If nothing in queue, return.
  }
  for(int i=0;i<tListLen;i++) {
    TaskTimer current = tList[i];

    unsigned long now = millis(); //Log current time for reference
    
    if(current.lastrun<(unsigned long)1) { //If never ran before
      if(current.start <= now - current.delay) { //If initial delay is up
        if(getDebug()) {
          //logMessage(DEBUG, "Task with id #"+String(current.id)+" running first time at "+String(now)+"ms");
        }
        if(current.func(current.args)) {
          shrinkTaskList(i); //If task returns true (it is finished), remove it from list
          //logMessage(INFO, "Task with id #"+String(current.id)+" finished successfully.");
          return;
        }
        if(getDebug()) {
          //logMessage(DEBUG, "Task with id #"+String(current.id)+" done first time. ("+String(current.delay)+"ms initial delay)");
        }
        current.lastrun=millis();
      }
    } else if(current.lastrun <= now - current.interval) { //If it is time to run the function
      if(getDebug()) {
        //logMessage(DEBUG, "Task with id #"+String(current.id)+" running at "+String(now)+"ms");
      }
      if(current.func(current.args)) {
        shrinkTaskList(i); //If task returns true (it is finished), remove it from list
        //logMessage(DEBUG, "Task with id #"+String(current.id)+" finished successfully.");
        return; //Exit function to run new list
      }
      if(getDebug()) {
        //logMessage(DEBUG, "Task with id #"+String(current.id)+" done. ("+String(current.interval)+"ms nominal, "+String(millis()-current.lastrun)+"ms effective)");
      }
      current.lastrun=millis();
    } else if(now >= current.timeout + current.start && current.timeout>0) { //If timeout reached and exists, remove task
      if(getDebug()) {
        //logMessage(DEBUG,"Task with id #"+String(current.id)+" timed out. ("+String(current.timeout)+"ms nominal, "+String(millis()-current.start)+"ms effective)");
      }
      shrinkTaskList(i);
      return; //Exit function to run new list
    }
    if(&tList[i] != NULL) {
      tList[i] = current;
    }
  }
}