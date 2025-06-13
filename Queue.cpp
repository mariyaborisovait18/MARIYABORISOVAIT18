#include "Queue.h"

Queue::Queue() : head(nullptr), tail(nullptr), count(0) {} // Конструктор Queue. Cписок инициализации, который инициализирует три члена класса:

Queue::~Queue()                                            // Деструктор класса Queue
{                                          
    while (!IsEmp()) {                                     // Пока очередь не станет пустой
        PopNumber();
    }
}

void Queue::PushNumber(int value)                          // Добавление элемента в очередь
{                      
    Node* newNode = new Node(value);
    if (IsEmp()) {
        head = tail = newNode;
    }
    else {                                                 // Реализация добавления элемента 
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

int Queue::PopNumber()                                     // Реализует удаление элемента из начала очереди и возвращает его значение
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

int Queue::FrontNumber() const                               // Возвращает значение элемента, находящегося в начале очереди
{                           
    if (IsEmp()) return -1;
    return head->value;
}

bool Queue::IsEmp() const                                    // Проверяет, пуста ли очередь
{                               
    return head == nullptr;
}

int Queue::size() const                                      // Возвращает текущее количество элементов в очереди                      
{
    return count;
}
    
bool GameDrun::ValidateCard(int card)                        // Проверяет, является ли переданная карта допустимой
{                    
    return card >= 0 && card <= 9 && !usedCards[card];
}

bool GameDrun::InputCards(Queue& player, const string& prompt)               // Ввод карт игроком и проверка их корректности
{                                                                            // Cсылка на объект очереди, в который будут добавляться введенные карты
                                                                             // prompt - cтрока, которая будет выведена пользователю как подсказка для ввода карт
                                                                             

    string input;
    cout << prompt;
    getline(cin, input);

    istringstream iS(input);                                                 
    int card;                                                                 // Переменная для хранения текущей карты, считываемой из потока
    int cardsEnd = 0;                                                         // Cчетчик введенных карт
    bool val = true;

    while (iS >> card && cardsEnd < 5) 
    {
        if (!ValidateCard(card)) 
        {
            cout << "\nОшибка:" << endl;
            val = false;
            break;
        }
        player.PushNumber(card);
        usedCards[card] = true;
        cardsEnd++;
    }

    string remaining;                                                         // Проверка на лишние данные
    if (iS >> remaining)
    {
        val = false;
    }

    if (cardsEnd != 5 || !val)                                                // Проверка на корректный ввод
    {                                        
        cout << "Нужно ввести ровно 5 УНИКАЛЬНЫХ карт через пробел (ЦИФРЫ ОТ 0 ДО 9)!" << endl;
        cout << "Обратите внимание на правила введения карт и попробуйте снова!" << endl;
        while (!player.IsEmp())
        {
            int c = player.PopNumber();
            usedCards[c] = false;
        }
        return false;
    }
    return true;
}

void GameDrun::ResetG()                                                       // Выполняет сброс состояния игры, очищая данные о картах игроков и сбрасывая состояние использованных карт
{                                                     
    while (!player1.IsEmp()) player1.PopNumber();
    while (!player2.IsEmp()) player2.PopNumber();

    for (int i = 0; i < 10; i++) 
    {
        usedCards[i] = false;
    }
}

void GameDrun::SetCA()                                                         // Выполняет ввод карт для двух игроков в игре. 
{                                                      
    while (true) 
    {
        ResetG();                                                              // Сначала чистка от предыдцщего шанса 

        cout << "\n\n\n|------------------------------------------------------------------ Ввод карт первого игрока -------------------------------------------------------------|" << endl;
        if (!InputCards(player1, "\n|Введите 5 карт через пробел в одну строку (Введите 5 цифр от 0 до 9 без повторений!): \n")) 
        {
            cin.clear();
            continue;
        }

        cout << "\n\n\n|------------------------------------------------------------------ Ввод карт второго игрока -------------------------------------------------------------|" << endl;
        if (!InputCards(player2, "\n|Введите 5 карт через пробел в одну строку (Введите 5 цифр от 0 до 9 без повторений, а так же ЦИФРЫ НЕ МОГУТ СОВПАДАТЬ С ЦИФРАМИ ИГРОКА №1!): \n"))
        {
            cin.clear();
            continue;
        }

        break;
    }
}

void GameDrun::PlayCA()                                                         // Реализует игровой процесс для двух игроков в карточной игре
{                                                      
    int MI = 0;
    const int MAXMI = 1000000;

    while (!player1.IsEmp() && !player2.IsEmp() && MI < MAXMI)                  // До тех пор, пока у обоих игроков есть карты
    {              
        int cd1 = player1.PopNumber();                                          // Вытаскивание карт
        int cd2 = player2.PopNumber();
        MI++;

        bool WINNER = false;
                                                                                // Определение победителя раунда


        if (cd1 == 0 && cd2 == 9)                                               // Если первая карта равна 0 и вторая — 9, то выигрывает первый игрок   
        {                                                                               
            WINNER = true;
        }
        else if (cd1 == 9 && cd2 == 0)                                          // Если первая карта равна 9 и вторая — 0, то выигрывает второй игрок
        {                                       
            WINNER = false;
        }
        else if (cd1 > cd2)                                                     // Если первая карта больше второй, то выигрывает первый игрок
        {
            WINNER = true;
        }
        else
        {                                                                       // В противном случае выигрывает второй игрок
            WINNER = false;
        }

        if (WINNER)                                                             // Передача карт победителю
        {                                                           
            player1.PushNumber(cd1);                                            // В зависимости от результата сравнения карт, обе карты помещаются обратно в колоду победившего игрока
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
        cout << "\nsecond - ПОБЕЖДАЕТ ВТОРОЙ ИГРОК! Количество ходов до победы: " << MI << endl;
    }
    else if (player2.IsEmp())
    {                                                                          // Проверяется, у кого из игроков закончились карты
        cout << "\nfirst - ПОБЕЖДАЕТ ПЕРВЫЙ ИГРОК! Количество ходов до победы:" << MI << endl;
    }
    else
    {
        cout << "botva" << endl;
    }
}