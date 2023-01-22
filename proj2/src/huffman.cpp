//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//---Name & Surname: Emre Yigit
//---Student Number: 150210715
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>
#include "huffman.h"
#include "structs.h"

using namespace std;
//-----------Reads the key from text file--------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};

//---------Sorts the key in an alpabetic order---------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};

//-------Finds the frequency of the characters---------//
void Huffman::findFrequency(){
    sortKey();
    // Key is sorted, after that every letter's frequency is found.
    // Then new node which also includes token is added to priority queue.
    char prev;
    bool b = true;
    int count = 0;
    // Using count variable we counted how many times a letter occur in a string.
    for(unsigned int i = 0; i < sortedKey.size(); i++){
        // If it is the first character
        if(b){
            b = false;
            prev = sortedKey[0];
            count++;
        }
        // If we reach the end of the string we need to add it to the queue.
        else if(i == sortedKey.size() - 1){
            count++;
            // We have to allocate memory space to add an element to queue.
            Node* newNode = new Node();
            newNode->token.symbol = prev;
            newNode->token.val = count;
            this->queue.enque(newNode);    
        }

        else if(prev == sortedKey[i]){
            count++;
        }
        // If it is a new character we need to save the previous one to the queue.
        else if(prev != sortedKey[i]){
            // We have to allocate memory space to add an element to queue.
            Node* newNode = new Node();
            newNode->token.symbol = prev;
            newNode->token.val = count;
            this->queue.enque(newNode);
            count = 1;
            prev = sortedKey[i];
        }
    }
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    findFrequency();
    Node* node1 = this->queue.dequeue();
    Node* node2;
    // We take two nodes from the queue.
    while(node1 != NULL){
        node2 = this->queue.dequeue();
        if(node2 == NULL){
            // If it is the only letter.
            this->huffmanTree.root = node1;
            break;
        } 
        // Using these two nodes obtained from the queue we merge these two nodes and add the new node
        // which is ancestor node to the queue.
        Node* ancestor;
        ancestor = this->huffmanTree.mergeNodes(node1, node2);
        this->huffmanTree.root = ancestor;
        this->queue.enque(ancestor);
        node1 = this->queue.dequeue();
    }
};

//---------------Prints the Huffman Tree---------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};

//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    // We traverse the huffman tree in order to find binary token using recursion. 
    if (traverse == NULL)
        return this->encodedBinaryPassword ;
    string tokenString(1, tokenChar);

    // If it finds the corresponding character
    if(traverse->token.symbol == tokenString){
        this->encodedBinaryPassword += tokenBinary;
        this->encodedValPassword += to_string(tokenBinary.size());
        return this->encodedBinaryPassword;
    }

    getTokenBinary(tokenChar,traverse->left, tokenBinary + "0");
    getTokenBinary(tokenChar,traverse->right,tokenBinary + "1");
    return this->encodedBinaryPassword;
};

//--------------Encodes the given password-------------//
void Huffman::encodePassword(string password){
    // Using the getTokenBinary function we obtain string's binary value and according to it 
    // we encode the password.
    this->encodedBinaryPassword = "";
    this->encodedValPassword = "";
    for(unsigned int i = 0; i < password.size(); i++){
        string s = getTokenBinary(password[i],this->huffmanTree.root,"");
    }
};

//-------------Prints the encoded password-------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    this->decodedPassword = "";
    int start = 0;
    // We followed the path which is obtained by binary password in order to find the decoded version of password.
    // And we did the same operation for all according to encoded value password.
    for(unsigned int i = 0; i < encodedValPassword.size(); i++){
        int lengthOfEncToken = encodedValPassword[i] - 48;
        string encToken = encodedBinaryPassword.substr(start, lengthOfEncToken);
        start += lengthOfEncToken;
        decodeToken(encToken);
    }
};

//---------------Decodes the given binary--------------//
void Huffman::decodeToken(string encodedToken){
    Node* tmp = this->huffmanTree.root;
    // It finds the decoded version of an encoded token and is used at decodePassword function
    // in order to find the decoded version of the whole password.
    for(unsigned int i = 0; i < encodedToken.size(); i++){
        if(encodedToken[i] == '0'){
            tmp = tmp->left;
        }
        else if(encodedToken[i] == '1'){
            tmp = tmp->right;
        }
    }
   this->decodedPassword += tmp->token.symbol ;
};
//-------------Prints the decoded password-------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};