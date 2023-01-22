/* @Author
Student Name: Emre Yigit
Student ID : 150210715
Date: 26.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string>
#include "ProcessRep.h"


using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime)
{   
    // Initailazing variables of the class.
    this->mProcessType = processType;
    this->mProcessID = processID;
    this->mDeliverTime = deliverTime;
    this-> mProcessTime = processTime;
    this->remainingTime = processTime;
    this->startTime = -1;
    this->endTime = -1;
}

ProcessRep::~ProcessRep()
{
    delete mpNext;
}

ProcessRep* ProcessRep::getNext()
{
    // returns the pointer which holds the next process's address.
   return this->mpNext;
}

void ProcessRep::setNext(ProcessRep *next)
{
   // sets the pointer which holds the next process's address.d
   this->mpNext = next;
}

string ProcessRep::getProcessType()
{
    // returns the process type of the process.
   return this->mProcessType;
 }

void ProcessRep::setProcessType(string processType)
{
    // sets the process type of the process.
   this->mProcessType = processType;
}

int ProcessRep::getDeliverTime()
{
    // returns deliver time.
   return mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime)
{
    // sets deliver time.
   mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID()
{
    // returns id of the process.
   return this->mProcessID;
}

void ProcessRep::setProcessID(int processID)
{
    // sets process id.
   this->mProcessID = processID;
}

int ProcessRep::getProcessTime()
{
    // returns process time of the process
   return this->mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime)
{
    // sets process time of the process
    this->mProcessTime = ProcessTime;
}