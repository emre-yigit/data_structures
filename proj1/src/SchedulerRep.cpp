/* @Author
Student Name: Emre Yigit
Student ID : 150210715
Date: 26.10.2022
*/
#include "SchedulerRep.h"
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

SchedulerRep::SchedulerRep()
{
    // Initializing the variables.
    mpProcessFIFO[0] = new FIFORep();
    mpProcessFIFO[1] = new FIFORep(); 
    mpProcessFIFO[2] = new FIFORep(); 
    mpRunningProcess = NULL;
    pCpuObj = new CPURep();
    timeSliceCount = 0;
    totalTime = 0;
}
SchedulerRep::~SchedulerRep()
{
    delete mpProcessFIFO[0];
    delete mpProcessFIFO[1];
    delete mpProcessFIFO[2];
    delete pCpuObj;
    delete mpRunningProcess;
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
    // Returns the requested Fifo inside the scheduler according to the given index.
    return this->mpProcessFIFO[index]; 

}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    // sets the Fifo accorrding to the given index
    this->mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    //sets running process
    this->mpRunningProcess = p;
}

ProcessRep* SchedulerRep::getRunningProcess()
{
    // returns running process.
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
    // It pushes a process into the Fifo according to process types.
    if(p->getProcessType() == "A"){
        this->mpProcessFIFO[0]->queue(p);
    }

    else if(p->getProcessType() == "B"){
        this->mpProcessFIFO[1]->queue(p);
    }

    else if(p->getProcessType() == "C"){
        this->mpProcessFIFO[2]->queue(p);
    }

    else{
        // Indicates an error
        cout << "There is no process type like this";
    }
}

ProcessRep* SchedulerRep::popProcess()
{
    // It pops process from Fifo according to priorities of the jobs.
    // In other words, it tries to pop A first, B second and C third.
    if(mpProcessFIFO[0]->getHead() != NULL){
        return mpProcessFIFO[0]->dequeue();
    }

    else if(mpProcessFIFO[1]->getHead() != NULL){
        return mpProcessFIFO[1]->dequeue();
    }

    else if(mpProcessFIFO[2]->getHead() != NULL){
        return mpProcessFIFO[2]->dequeue();
    }

    else{
        // Returns NULL if there is no available process in Fifo.
        return NULL;
    }
}

bool SchedulerRep::checkTimeSlice()
{ 
    // Returns true if it reaches the quantum limit, otherwise returns false.
    // Limit for A type is 2^1 = 2  
    if(mpRunningProcess->getProcessType() == "A"){
       if(timeSliceCount == 2){
            return true;
       }
    }

    // Limit for B type is 2^2 = 4
    else if(mpRunningProcess->getProcessType() == "B"){
       if(timeSliceCount == 4){
            return true;
       }
    }

    // Limit for C type is 2^3 = 8
    else if(mpRunningProcess->getProcessType() == "C"){
       if(timeSliceCount == 8){
            return true;
       }
    }

    return false;
}
ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){
    mpRunningProcess = p;
    //checks whether p is null or not
    if(p == NULL){
        this->totalTime++;
        return p;
    }
    // assigns the time that process starts to be executed first time.
    if(p->startTime == -1){
        p->startTime = totalTime;
    }
    // Increasing total time and quantum.
    this->totalTime++;
    this->timeSliceCount++;
    return this->pCpuObj->runCPU(p,totalTime);

}
void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{   
    /*  
        This function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.

    */
    ProcessRep* job = new ProcessRep(type, id, arrivalTime, processTime);
    // Returned job is required to check whether returned process is Null or not.
    ProcessRep* returnedJob;
    if(mpRunningProcess == NULL){
        pushProcess(job);
        returnedJob = sendProcessToCPU(this->popProcess()); // Process is popped from fifo list accordingly and sent to CPU.
    }
    // checks if running process is finished.
    else if(mpRunningProcess->remainingTime == 0){
         pushProcess(job);
         timeSliceCount = 0;
         returnedJob = sendProcessToCPU(this->popProcess());
    }

    // if there is a process which is already running.
    else{
        // Basic check with Ascii Characters
        char c1 = job->getProcessType()[0];
        char c2 = mpRunningProcess->getProcessType()[0];
        if(c1 - c2 < 0){ // Incoming job has more priority than the existing one.
            
            // Running process is taken from CPU to appropriate FIFO.
             pushProcess(mpRunningProcess);

            timeSliceCount = 0; // Reset
            returnedJob = sendProcessToCPU(job);
        }

        else{ // Incoming job has less or equal priority with the running one.
            pushProcess(job);
            bool b = this->checkTimeSlice();
           
            if(b){ // If it reaches the limit.
                pushProcess(mpRunningProcess);
                timeSliceCount = 0;
                returnedJob = sendProcessToCPU(this->popProcess());
            }
            else{
                 returnedJob = sendProcessToCPU(mpRunningProcess);
            }

        } 
    }

    // It checks whether running process is finished or not. If it is finished
    // it pops another process
    if(returnedJob == NULL){
        mpRunningProcess = this->popProcess();
        timeSliceCount = 0;
    }
    
}
void SchedulerRep::schedule(ProcessRep* p)
{   
    // p has to be NULL to run this function
    if(p != NULL){
        return;
    }
     // Returned job is required to check whether returned process is Null or not.
     ProcessRep* returnedJob;
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.
    */
   // If running process is Null it means that that process is finished so we can
   // skip to the next iteration
    if(mpRunningProcess == NULL){
        return;
    }
    // checks if running process is finished.
    if(mpRunningProcess->remainingTime == 0){
        timeSliceCount = 0;
        returnedJob = sendProcessToCPU(this->popProcess());
    }

    else{ // Running job will continue
        bool b = this->checkTimeSlice();
    
        if(b){ // If it reaches the limit.
            pushProcess(mpRunningProcess);
            timeSliceCount = 0;
            returnedJob = sendProcessToCPU(this->popProcess());
        }
        else{
            returnedJob = sendProcessToCPU(mpRunningProcess);
        }

      } 
    // It checks whether running process is finished or not. If it is finished
    // it pops another process
    if(returnedJob == NULL){
        mpRunningProcess = this->popProcess();
        timeSliceCount = 0;          
    }

}
