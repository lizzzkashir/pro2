#ifndef BULLSANDCOWS_H
#define BULLSANDCOWS_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>

class MyString {
private:
    char* data;
    int length;

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);
    MyString& operator=(const char* str);

    char operator[](int index) const;
    char& operator[](int index);

    int getLength() const;
    const char* c_str() const;
    bool isEmpty() const;

    void append(char c);
    void clear();

    MyString substr(int start, int count) const;
    int find(char c) const;

    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend std::istream& operator>>(std::istream& is, MyString& str);
};

class DigitSet {
private:
    bool digits[10];
    int count;

public:
    DigitSet();

    void add(int digit);
    void remove(int digit);
    bool contains(int digit) const;
    void clear();
    int getCount() const;
    bool hasUniqueDigits(const MyString& str) const;
    bool isValidNumber(const MyString& str) const;
};

class HistoryNode {
private:
    MyString guess;
    int bulls;
    int cows;
    HistoryNode* next;

public:
    HistoryNode(const MyString& g, int b, int c);
    ~HistoryNode();

    MyString getGuess() const;
    int getBulls() const;
    int getCows() const;
    HistoryNode* getNext() const;
    void setNext(HistoryNode* node);
};

class HistoryList {
private:
    HistoryNode* head;
    HistoryNode* tail;
    int size;

public:
    HistoryList();
    ~HistoryList();

    void addRecord(const MyString& guess, int bulls, int cows);
    void displayHistory() const;
    void clear();
    int getSize() const;
    HistoryNode* getHead() const;
    bool isEmpty() const;

    HistoryList(const HistoryList&) = delete;
    HistoryList& operator=(const HistoryList&) = delete;
};

class GameException : public std::exception {
private:
    char* message;

public:
    explicit GameException(const char* msg);
    ~GameException();
    const char* what() const noexcept override;
};

class BullsAndCowsGame {
private:
    MyString secretNumber;
    HistoryList history;
    int attempts;
    bool gameActive;
    bool gameWon;

    MyString generateSecretNumber();
    bool isValidGuess(const MyString& guess) const;
    void calculateBullsAndCows(const MyString& guess, int& bulls, int& cows) const;
    bool hasUniqueDigits(const MyString& str) const;
    bool isAllDigits(const MyString& str) const;

public:
    BullsAndCowsGame();
    ~BullsAndCowsGame();

    void startNewGame();
    bool makeGuess(const MyString& guess);
    void displayStatus() const;
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);

    int getAttempts() const;
    const HistoryList& getHistory() const;
    MyString getSecretNumber() const;
    bool isGameActive() const;
    bool isGameWon() const;
};

class UserInterface {
private:
    BullsAndCowsGame game;
    bool gameInProgress;

    void displayMainMenu();
    void displayRules();
    void displayWelcomeMessage();

    int getChoice(int min, int max);
    MyString getGuessInput();
    MyString getFilenameInput();
    void waitForEnter();

    void handleNewGame();
    void handleGuess();
    void handleShowHistory();
    void handleSaveGame();
    void handleLoadGame();

public:
    UserInterface();
    ~UserInterface();

    void run();
};

#endif
