#include "Queue.h"

Queue::Queue() : head(nullptr), tail(nullptr), count(0) {} // ����������� Queue. C����� �������������, ������� �������������� ��� ����� ������:

Queue::~Queue()                                            // ���������� ������ Queue
{                                          
    while (!IsEmp()) {                                     // ���� ������� �� ������ ������
        PopNumber();
    }
}

void Queue::PushNumber(int value)                          // ���������� �������� � �������
{                      
    Node* newNode = new Node(value);
    if (IsEmp()) {
        head = tail = newNode;
    }
    else {                                                 // ���������� ���������� �������� 
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

int Queue::PopNumber()                                     // ��������� �������� �������� �� ������ ������� � ���������� ��� ��������
{                                   
    if (IsEmp()) 
    {
        return -1;
    }
    Node* temp = head;
    int value = temp->value;
    head = head->next;
    if (head == nullptr) 
    {
        tail = nullptr;
    }
    delete temp;
    count--;
    return value;
}

int Queue::FrontNumber() const                               // ���������� �������� ��������, ������������ � ������ �������
{                           
    if (IsEmp()) return -1;
    return head->value;
}

bool Queue::IsEmp() const                                    // ���������, ����� �� �������
{                               
    return head == nullptr;
}

int Queue::size() const                                      // ���������� ������� ���������� ��������� � �������                      
{
    return count;
}
    
bool GameDrun::ValidateCard(int card)                        // ���������, �������� �� ���������� ����� ����������
{                    
    return card >= 0 && card <= 9 && !usedCards[card];
}

bool GameDrun::InputCards(Queue& player, const string& prompt)               // ���� ���� ������� � �������� �� ������������
{                                                                            // C����� �� ������ �������, � ������� ����� ����������� ��������� �����
                                                                             // prompt - c�����, ������� ����� �������� ������������ ��� ��������� ��� ����� ����
                                                                             

    string input;
    cout << prompt;
    getline(cin, input);

    istringstream iS(input);                                                 
    int card;                                                                 // ���������� ��� �������� ������� �����, ����������� �� ������
    int cardsEnd = 0;                                                         // C������ ��������� ����
    bool val = true;

    while (iS >> card && cardsEnd < 5) 
    {
        if (!ValidateCard(card)) 
        {
            cout << "\n������:" << endl;
            val = false;
            break;
        }
        player.PushNumber(card);
        usedCards[card] = true;
        cardsEnd++;
    }

    string remaining;                                                         // �������� �� ������ ������
    if (iS >> remaining)
    {
        val = false;
    }

    if (cardsEnd != 5 || !val)                                                // �������� �� ���������� ����
    {                                        
        cout << "����� ������ ����� 5 ���������� ���� ����� ������ (����� �� 0 �� 9)!" << endl;
        cout << "�������� �������� �� ������� �������� ���� � ���������� �����!" << endl;
        while (!player.IsEmp())
        {
            int c = player.PopNumber();
            usedCards[c] = false;
        }
        return false;
    }
    return true;
}

void GameDrun::ResetG()                                                       // ��������� ����� ��������� ����, ������ ������ � ������ ������� � ��������� ��������� �������������� ����
{                                                     
    while (!player1.IsEmp()) player1.PopNumber();
    while (!player2.IsEmp()) player2.PopNumber();

    for (int i = 0; i < 10; i++) 
    {
        usedCards[i] = false;
    }
}

void GameDrun::SetCA()                                                         // ��������� ���� ���� ��� ���� ������� � ����. 
{                                                      
    while (true) 
    {
        ResetG();                                                              // ������� ������ �� ����������� ����� 

        cout << "\n\n\n|------------------------------------------------------------------ ���� ���� ������� ������ -------------------------------------------------------------|" << endl;
        if (!InputCards(player1, "\n|������� 5 ���� ����� ������ � ���� ������ (������� 5 ���� �� 0 �� 9 ��� ����������!): \n")) 
        {
            cin.clear();
            continue;
        }

        cout << "\n\n\n|------------------------------------------------------------------ ���� ���� ������� ������ -------------------------------------------------------------|" << endl;
        if (!InputCards(player2, "\n|������� 5 ���� ����� ������ � ���� ������ (������� 5 ���� �� 0 �� 9 ��� ����������, � ��� �� ����� �� ����� ��������� � ������� ������ �1!): \n"))
        {
            cin.clear();
            continue;
        }

        break;
    }
}

void GameDrun::PlayCA()                                                         // ��������� ������� ������� ��� ���� ������� � ��������� ����
{                                                      
    int MI = 0;
    const int MAXMI = 1000000;

    while (!player1.IsEmp() && !player2.IsEmp() && MI < MAXMI)                  // �� ��� ���, ���� � ����� ������� ���� �����
    {              
        int cd1 = player1.PopNumber();                                          // ������������ ����
        int cd2 = player2.PopNumber();
        MI++;

        bool WINNER = false;
                                                                                // ����������� ���������� ������


        if (cd1 == 0 && cd2 == 9)                                               // ���� ������ ����� ����� 0 � ������ � 9, �� ���������� ������ �����   
        {                                                                               
            WINNER = true;
        }
        else if (cd1 == 9 && cd2 == 0)                                          // ���� ������ ����� ����� 9 � ������ � 0, �� ���������� ������ �����
        {                                       
            WINNER = false;
        }
        else if (cd1 > cd2)                                                     // ���� ������ ����� ������ ������, �� ���������� ������ �����
        {
            WINNER = true;
        }
        else
        {                                                                       // � ��������� ������ ���������� ������ �����
            WINNER = false;
        }

        if (WINNER)                                                             // �������� ���� ����������
        {                                                           
            player1.PushNumber(cd1);                                            // � ����������� �� ���������� ��������� ����, ��� ����� ���������� ������� � ������ ����������� ������
            player1.PushNumber(cd2);
        }
        else 
        {
            player2.PushNumber(cd1);
            player2.PushNumber(cd2);
        }
    }

    if (player1.IsEmp()) 
    {
        cout << "\nsecond - ��������� ������ �����! ���������� ����� �� ������: " << MI << endl;
    }
    else if (player2.IsEmp())
    {                                                                          // �����������, � ���� �� ������� ����������� �����
        cout << "\nfirst - ��������� ������ �����! ���������� ����� �� ������:" << MI << endl;
    }
    else
    {
        cout << "botva" << endl;
    }
}