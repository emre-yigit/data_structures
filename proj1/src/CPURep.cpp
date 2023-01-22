/* @Author
Student Name: Emre Yigit
Student ID : 150210715
Date: 26.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    // Initializes the Fifo list for finished processes.
   this->mFinishedProcess = new FIFORep();
}

CPURep::~CPURep()
{
    delete mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{   
    // This function runs the CPU and arranges the remaining time property of the process.

   if(p->remainingTime == 1){
        this->mFinishedProcess->queue(p); // Adds the finished process at the end of the mFinishedProcess queue.
        p->remainingTime = 0; // Since process ends, it makes remaining time 0.
        p->endTime = time; // Saves the time when process ends.
        return NULL; // returns null since the process is done and saved to finished process.
   }

    p->remainingTime--; // If process will continue, it decreases the remaining time of the process.
    return p;

}

FIFORep* CPURep::getFinishedProcess()
{
    // returns the pointer that holds the finished processes.
   return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    // sets the finished processes.
   this->mFinishedProcess = finishedProcess;
}