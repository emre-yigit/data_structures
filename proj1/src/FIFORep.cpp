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

using namespace std;

FIFORep::FIFORep()
{
    // It initializes the head and tail features of the Fifo as NULL.
   this->mpHead = NULL;
   this->mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep* head)
{
    // Initializes the head and tail features of the Fifo as head since it is the only node.
   this->mpHead = head;
   this->mpTail = head;
}


FIFORep::~FIFORep()
{
}

void FIFORep::setHead(ProcessRep* head)
{
    // sets the head of the Fifo.
   this->mpHead = head;
}

ProcessRep* FIFORep::getHead()
{
   // returns the head of the Fifo.
   return this->mpHead; // seg fault
}

void FIFORep::setTail(ProcessRep* tail)
{
    // sets the tail of the Fifo.
   this->mpTail = tail;
}

ProcessRep* FIFORep::getTail()
{
    //returns the tail of the Fifo.
   return this->mpTail;
}

void FIFORep::queue(ProcessRep* p)
{
    //   This function adds a process to the tail of the queue.
 
    // Adds to the end of the list if list is not empty.
    if(mpHead != NULL){
        this->mpTail->setNext(p);
        mpTail = p;
    }

    // Since the list is empty it sets tail and head as the first process. 
    else{
        this->mpHead = p;
        this->mpTail = p;
    }

}

ProcessRep* FIFORep::dequeue()
{   
    
//    This function removes a process from the head of the queue and returns it.
    
    // If head is null it can not return a process, so it returns NULL.
    if(this->mpHead == NULL){
        return NULL;
    }

    // If head and tail are the same node it returns that node and sets head and tail as Null.
    if(mpHead == mpTail){ // added later
      ProcessRep* tmp = mpHead;
      mpHead = NULL;
      mpTail = NULL;
      return tmp;  
    }
    // We are setting the next feature of the pointer that will be returned, to NULL
    // avoiding to make the linkedlist circular.
    ProcessRep* tmp = mpHead;
    mpHead = tmp->getNext();
    tmp->setNext(NULL);
    return tmp;
}

ProcessRep* FIFORep::searchID(int id)
{   
   // This function searchs a process by id and returns it if it exist otherwise returns NULL.

   ProcessRep* tmpPointer = mpHead;
   while(tmpPointer != NULL){
        if(tmpPointer->getProcessID() == id){
            return tmpPointer;
        }

        tmpPointer = tmpPointer->getNext();
   }

   return NULL;


}

void FIFORep::printFIFO()
{
   //  This function prints the proceses in the queue starting from Head to tail.

    ProcessRep* tmpPointer = this->getHead();
    // Printing format: <Process Type><ID><" "><start Time><" "><Finish Time><" ">
    while(tmpPointer != NULL){
        cout << tmpPointer->getProcessType() << tmpPointer->getProcessID() << " " 
        << tmpPointer->startTime << " " << tmpPointer->endTime << " ";
        tmpPointer = tmpPointer->getNext();
    }
}