#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Queue 
{                                                 //  ласс и его методы 
private:
    struct Node 
    {
        int value;
        Node* next;
        Node(int val) : value(val), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int count;

public:
    Queue();
    ~Queue();
    void PushNumber(int value);
    int PopNumber();
    int FrontNumber() const;
    bool IsEmp() const;
    int size() const;
};

class GameDrun 
{                                              //  ласс и его методы 
private:
    Queue player1;
    Queue player2;
    bool usedCards[10];
    bool ValidateCard(int card);
    bool InputCards(Queue& player, const string& prompt);
    void ResetG();

public:
    void SetCA();
    void PlayCA();
};