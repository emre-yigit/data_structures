//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//---Name & Surname: Emre Yigit
//---Student Number: 150210715
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "structs.h"

using namespace std;
//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    head = NULL;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    // Adds to head if the queue is NULL.
    if(head == NULL){
        head = newnode;
        return;
    }
    Node* tmpNode = head;
    // Since it is a priority queue, it checks value property.
    if(newnode->token.val < tmpNode->token.val){
        newnode->next = head;
        head = newnode;
        return;
    }
    // Proceed through queue.
    while(tmpNode->next != NULL && newnode->token.val >= tmpNode->next->token.val){
        tmpNode = tmpNode->next;
    }
    newnode->next = tmpNode->next;
    tmpNode->next = newnode;
};

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    // Gets the first element from the queue.
    if(head == NULL){
        return NULL;
    }
    Node* res = head;
    head = res->next;
    res->next = NULL;
    return res;
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    root = NULL;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    // Calls deleteTree function in order to delete the tree.
    deleteTree(this->root);
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    // This function traverses every node in the tree 
    // and deletes every node in order to avoid memory leak.
    if (node == NULL) 
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
   // Merges two nodes by adding values and concatenating the strings.
   Node* node =  new Node();
   node->left = temp1;
   node->right = temp2;
   node->token.symbol = temp1->token.symbol + temp2->token.symbol;
   node->token.val = temp1->token.val + temp2->token.val;
   node->next = NULL;
   return node;
};

// Traverses the tree and prints each node.
void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};