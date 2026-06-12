#include "BullsAndCows.h"


MyString::MyString() : data(nullptr), length(0) {
    data = new char[1];
    data[0] = '\0';
}

MyString::MyString(const char* str) {
    if (str) {
        length = 0;
        while (str[length] != '\0') length++;

        data = new char[length + 1];
        for (int i = 0; i <= length; i++) {
            data[i] = str[i];
        }
    } else {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }
}

MyString::MyString(const MyString& other) {
    length = other.length;
    data = new char[length + 1];
    for (int i = 0; i <= length; i++) {
        data[i] = other.data[i];
    }
}

MyString::~MyString() {
    delete[] data;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        for (int i = 0; i <= length; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

MyString& MyString::operator=(const char* str) {//оператор присваивания
    delete[] data;
    if (str) {
        length = 0;
        while (str[length] != '\0') length++;

        data = new char[length + 1];
        for (int i = 0; i <= length; i++) {
            data[i] = str[i];
        }
    } else {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }
    return *this;
}

char MyString::operator[](int index) const {
    if (index >= 0 && index < length) {
        return data[index];
    }
    return '\0';
}

char& MyString::operator[](int index) {
    static char dummy = '\0';
    if (index >= 0 && index < length) {
        return data[index];
    }
    return dummy;
}

int MyString::getLength() const {
    return length;
}

const char* MyString::c_str() const {
    return data;
}

bool MyString::isEmpty() const {
    return length == 0;
}

void MyString::append(char c) {
    char* newData = new char[length + 2];
    for (int i = 0; i < length; i++) {
        newData[i] = data[i];
    }
    newData[length] = c;
    newData[length + 1] = '\0';

    delete[] data;
    data = newData;
    length++;
}

void MyString::clear() {
    delete[] data;
    data = new char[1];
    data[0] = '\0';
    length = 0;
}

MyString MyString::substr(int start, int count) const {
    MyString result;
    if (start < 0 || start >= length) return result;

    int end = start + count;
    if (end > length) end = length;

    for (int i = start; i < end; i++) {
        result.append(data[i]);
    }
    return result;
}

int MyString::find(char c) const {
    for (int i = 0; i < length; i++) {
        if (data[i] == c) return i;
    }
    return -1;
}

bool MyString::operator==(const MyString& other) const {
    if (length != other.length) return false;
    for (int i = 0; i < length; i++) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    char buffer[256];
    is >> buffer;
    str = buffer;
    return is;
}


DigitSet::DigitSet() : count(0) {
    for (int i = 0; i < 10; i++) {
        digits[i] = false;
    }
}

void DigitSet::add(int digit) {
    if (digit >= 0 && digit <= 9 && !digits[digit]) {
        digits[digit] = true;
        count++;
    }
}

void DigitSet::remove(int digit) {
    if (digit >= 0 && digit <= 9 && digits[digit]) {
        digits[digit] = false;
        count--;
    }
}

bool DigitSet::contains(int digit) const {
    if (digit >= 0 && digit <= 9) {
        return digits[digit];
    }
    return false;
}

void DigitSet::clear() {
    for (int i = 0; i < 10; i++) {
        digits[i] = false;
    }
    count = 0;
}

int DigitSet::getCount() const {
    return count;
}

bool DigitSet::hasUniqueDigits(const MyString& str) const {
    DigitSet temp;
    for (int i = 0; i < str.getLength(); i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            int digit = c - '0';
            if (temp.contains(digit)) {
                return false;
            }
            temp.add(digit);
        }
    }
    return true;
}

bool DigitSet::isValidNumber(const MyString& str) const {
    if (str.getLength() != 4) return false;

    DigitSet temp;
    for (int i = 0; i < str.getLength(); i++) {
        char c = str[i];
        if (c < '0' || c > '9') return false;

        int digit = c - '0';
        if (temp.contains(digit)) return false;
        temp.add(digit);
    }
    return true;
}


HistoryNode::HistoryNode(const MyString& g, int b, int c)
    : guess(g), bulls(b), cows(c), next(nullptr) {}

HistoryNode::~HistoryNode() {}

MyString HistoryNode::getGuess() const { return guess; }
int HistoryNode::getBulls() const { return bulls; }
int HistoryNode::getCows() const { return cows; }
HistoryNode* HistoryNode::getNext() const { return next; }
void HistoryNode::setNext(HistoryNode* node) { next = node; }


HistoryList::HistoryList() : head(nullptr), tail(nullptr), size(0) {}

HistoryList::~HistoryList() {
    clear();
}

void HistoryList::addRecord(const MyString& guess, int bulls, int cows) {//добавление записи в историю
    HistoryNode* newNode = new HistoryNode(guess, bulls, cows);

    if (!head) {//если список пуст
        head = tail = newNode;
    } else {
        tail->setNext(newNode);
        tail = newNode;
    }
    size++;
}

void HistoryList::displayHistory() const {
    using namespace std;
    if (!head) {
        cout << "\nИстория попыток пуста.\n";
        return;
    }

    cout << "\nИСТОРИЯ ПОПЫТОК \n";
    cout << "Попытка\tЧисло\t\tБыки\tКоровы\n";

    HistoryNode* current = head;
    int attemptNum = 1;
    while (current) {
        cout << attemptNum++ << "\t"
                  << current->getGuess() << "\t\t"
                  << current->getBulls() << "\t"
                  << current->getCows() << "\n";
        current = current->getNext();
    }
}

void HistoryList::clear() {
    HistoryNode* current = head;
    while (current) {
        HistoryNode* temp = current;
        current = current->getNext();
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}

int HistoryList::getSize() const { return size; }
HistoryNode* HistoryList::getHead() const { return head; }
bool HistoryList::isEmpty() const { return head == nullptr; }


GameException::GameException(const char* msg) {
    int len = 0;
    while (msg[len] != '\0') len++;

    message = new char[len + 1];
    for (int i = 0; i <= len; i++) {
        message[i] = msg[i];
    }
}

GameException::~GameException() {
    delete[] message;
}

const char* GameException::what() const noexcept {
    return message;
}


BullsAndCowsGame::BullsAndCowsGame() : attempts(0), gameActive(false), gameWon(false) {
    srand(static_cast<unsigned>(time(nullptr)));
}

BullsAndCowsGame::~BullsAndCowsGame() {}

MyString BullsAndCowsGame::generateSecretNumber() {//генерация сектретного числа
    char digits[] = {'0','1','2','3','4','5','6','7','8','9'};
    // Перемешиваем массив
    for (int i = 0; i < 10; i++) {
        int j = rand() % 10;
        char temp = digits[i];
        digits[i] = digits[j];
        digits[j] = temp;
    }
    // Берем первые 4 цифры после перемешивания
    char result[5];
    result[0] = digits[0];
    result[1] = digits[1];
    result[2] = digits[2];
    result[3] = digits[3];
    result[4] = '\0';
    // Проверяем, не начинается ли число с 0
    if (result[0] == '0') {
        for (int i = 1; i < 4; i++) {
            if (result[i] != '0') {
                char temp = result[0];// Меняем местами первый и найденный
                result[0] = result[i];
                result[i] = temp;
                break;
            }
        }
    }

    return MyString(result);
}

bool BullsAndCowsGame::hasUniqueDigits(const MyString& str) const {
    DigitSet set;
    for (int i = 0; i < str.getLength(); i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            int digit = c - '0';
            if (set.contains(digit)) {
                return false;
            }
            set.add(digit);
        }
    }
    return true;
}

bool BullsAndCowsGame::isAllDigits(const MyString& str) const {
    for (int i = 0; i < str.getLength(); i++) {
        char c = str[i];
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

bool BullsAndCowsGame::isValidGuess(const MyString& guess) const {
    if (guess.getLength() != 4) return false;
    if (!isAllDigits(guess)) return false;
    if (!hasUniqueDigits(guess)) return false;
    return true;
}

void BullsAndCowsGame::calculateBullsAndCows(const MyString& guess, int& bulls, int& cows) const {//вычисление быков и коров
    bulls = 0;
    cows = 0;
    // Проходим по каждой позиции в предположении
    for (int i = 0; i < 4; i++) {
        if (guess[i] == secretNumber[i]) {// Если цифра на том же месте, то это бык
            bulls++;
        } else {
            for (int j = 0; j < 4; j++) {
                if (guess[i] == secretNumber[j]) {
                    cows++;//корова
                    break;
                }
            }
        }
    }
}

void BullsAndCowsGame::startNewGame() {
    using namespace std;
    history.clear();
    attempts = 0;
    gameActive = true;
    gameWon = false;
    secretNumber = generateSecretNumber();
    cout << "\nЗагадано 4-значное число с уникальными цифрами.\n";
}

bool BullsAndCowsGame::makeGuess(const MyString& guess) {//обработка новой попытки
    if (!gameActive) {
        throw GameException("Игра не активна. Начните новую игру.");
    }

    if (gameWon) {
        throw GameException("Игра уже выиграна. Начните новую игру.");
    }

    if (!isValidGuess(guess)) {
        throw GameException("Неверный формат! Введите 4 уникальные цифры.");
    }

    int bulls, cows;
    calculateBullsAndCows(guess, bulls, cows);//вычисление быков и коров

    history.addRecord(guess, bulls, cows);
    attempts++;
//вывод результатов
    std::cout << "\nРЕЗУЛЬТАТ " << bulls << " бык" << (bulls != 1 ? "а" : "")
              << ", " << cows << " коров" << (cows != 1 ? "ы" : "") << "\n";

    if (bulls == 4) {
        gameWon = true;//флаг победы
        gameActive = false;
        std::cout << "\nПОБЕДА  " << secretNumber
                  << " за " << attempts << " попыток!\n";
        return true;
    }

    return false;
}

void BullsAndCowsGame::displayStatus() const {
    using namespace std;
    cout << "\n СТАТУС ИГРЫ \n";
    cout << "Сделано попыток: " << attempts << "\n";
    if (gameWon) {
        cout << "Статус: Игра ВЫИГРАНА!\n";
    } else if (gameActive) {
        cout << "Статус: Игра продолжается\n";
    }
    history.displayHistory();
}

void BullsAndCowsGame::saveToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw GameException("Не удалось открыть файл для сохранения");
    }

    file << secretNumber.c_str() << "\n";
    file << attempts << "\n";
    file << gameActive << "\n";
    file << gameWon << "\n";

    HistoryNode* current = history.getHead();
    while (current) {
        file << current->getGuess().c_str() << " "
             << current->getBulls() << " "
             << current->getCows() << "\n";
        current = current->getNext();
    }

    file.close();
    std::cout << "\n Игра сохранена в файл: " << filename << "\n";
}

void BullsAndCowsGame::loadFromFile(const char* filename) {
    using namespace std;
    ifstream file(filename);
    if (!file.is_open()) {
        throw GameException("Не удалось открыть файл для загрузки");
    }

    history.clear();

    char buffer[256];
    file >> buffer;
    secretNumber = MyString(buffer);

    file >> attempts;
    file >> gameActive;
    file >> gameWon;

    char guessBuffer[256];
    int bulls, cows;

    while (file >> guessBuffer >> bulls >> cows) {
        MyString guess(guessBuffer);
        if (isValidGuess(guess)) {
            history.addRecord(guess, bulls, cows);
        }
    }

    file.close();
    cout << "\n Игра загружена из файла: " << filename << "\n";
}

int BullsAndCowsGame::getAttempts() const { return attempts; }
const HistoryList& BullsAndCowsGame::getHistory() const { return history; }
MyString BullsAndCowsGame::getSecretNumber() const { return secretNumber; }
bool BullsAndCowsGame::isGameActive() const { return gameActive; }
bool BullsAndCowsGame::isGameWon() const { return gameWon; }


UserInterface::UserInterface() : gameInProgress(false) {}

UserInterface::~UserInterface() {}

int UserInterface::getChoice(int min, int max) {//выбор пунка меню
    using namespace std;
    char input[100];

    while (true) {
        cin.getline(input, 100);

        // Проверка на пустую строку
        if (strlen(input) == 0) {
            cout << "Ошибка! Ввод не может быть пустым. Введите число от " << min << " до " << max << ": ";
            continue;
        }

        // Проверка, что все символы - цифры
        bool onlyDigits = true;
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] < '0' || input[i] > '9') {
                onlyDigits = false;
                break;
            }
        }

        if (!onlyDigits) {
            cout << "Ошибка! Вводите только цифры.\n";
            cout << "Повторите ввод (" << min << "-" << max << "): ";
            continue;
        }

        // Преобразуем в число
        int value = atoi(input);

        // Проверка диапазона
        if (value < min || value > max) {
            cout << "Ошибка! Введите число от " << min << " до " << max << ". Повторите: ";
            continue;
        }

        return value;
    }
}


MyString UserInterface::getGuessInput() {
    using namespace std;
    char buffer[256];

    while (true) {
        std::cin.getline(buffer, 256);

        // Проверяем длину
        int len = strlen(buffer);

        if (len != 4) {
            cout << "Ошибка! Нужно ввести РОВНО 4 цифры. Вы ввели " << len << " символов.\n";
            cout << "Повторите ввод (4 уникальные цифры): ";
            continue;
        }

        // Проверяем, что все символы - цифры
        bool allDigits = true;
        for (int i = 0; i < len; i++) {
            if (buffer[i] < '0' || buffer[i] > '9') {
                allDigits = false;
                break;
            }
        }

        if (!allDigits) {
            cout << "Ошибка! Введите ТОЛЬКО цифры (0-9). \n";
            cout << "Повторите ввод: ";
            continue;
        }

        // Проверяем, что все цифры уникальные
        bool unique = true;
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if (buffer[i] == buffer[j]) {
                    unique = false;
                    break;
                }
            }
            if (!unique) break;
        }

        if (!unique) {
            cout << "Ошибка! Все цифры должны быть УНИКАЛЬНЫМИ.\n";
            cout << "Повторите ввод: ";
            continue;
        }

        return MyString(buffer);
    }
}

MyString UserInterface::getFilenameInput() {
    char buffer[256];
    std::cin.getline(buffer, 256);
    return MyString(buffer);
}

void UserInterface::waitForEnter() {
    std::cin.get();
}

void UserInterface::displayWelcomeMessage() {
    using namespace std;
    cout << "       ИГРА «КОРОВЫ И БЫКИ»\n";
}

void UserInterface::displayRules() {
    using namespace std;
    cout << "ПРАВИЛА ИГРЫ\n";
    cout << "1. Компьютер загадывает 4-значное число\n";
    cout << "   из уникальных цифр (0-9).\n";
    cout << "2. Вы пытаетесь угадать это число.\n";
    cout << "3. Подсказка:\n";
    cout << "   • БЫК - цифра на правильном месте\n";
    cout << "   • КОРОВА - цифра есть, но не на своем месте\n";
    cout << "4. Формат ввода: 4 уникальные цифры\n";
}

void UserInterface::displayMainMenu() {
    using namespace std;
    cout << "ГЛАВНОЕ МЕНЮ\n";
    cout << "  1. Новая игра\n";
    cout << "  2. Сделать попытку\n";
    cout << "  3. Показать историю и статус\n";
    cout << "  4. Показать правила\n";
    cout << "  5. Сохранить игру\n";
    cout << "  6. Загрузить игру\n";
    cout << "  7. Выход\n";
}

void UserInterface::handleNewGame() {
    using namespace std;
    try {
        game.startNewGame();
        gameInProgress = true;
    } catch (const GameException& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void UserInterface::handleGuess() {
    using namespace std;
    if (!gameInProgress || !game.isGameActive()) {
        cout << "\n Сначала начните новую игру!\n";
        return;
    }

    cout << "\nВведите 4 уникальные цифры: ";
    MyString guess = getGuessInput();

    try {
        bool won = game.makeGuess(guess);
        if (won) {
            gameInProgress = false;
        }
    } catch (const GameException& e) {
        cout << "\nОШИБКА " << e.what() << "\n";
    }
}

void UserInterface::handleShowHistory() {
    game.displayStatus();
}

void UserInterface::handleSaveGame() {
    using namespace std;
    if (!gameInProgress) {
        cout << "\n Нет активной игры для сохранения.\n";
        return;
    }

    cout << "Введите имя файла: ";
    MyString filename = getFilenameInput();

    try {
        game.saveToFile(filename.c_str());
    } catch (const GameException& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void UserInterface::handleLoadGame() {
    using namespace std;
    cout << "Введите имя файла: ";
    MyString filename = getFilenameInput();

    try {
        game.loadFromFile(filename.c_str());
        gameInProgress = true;
        if (game.isGameWon()) {
            cout << "\nЗагружена завершённая игра!\n";
            gameInProgress = false;
        }
    } catch (const GameException& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void UserInterface::run() {
    using namespace std;
    bool running = true;
    displayWelcomeMessage();

    while (running) {
        displayMainMenu();
        cout << "\nВаш выбор (1-7): ";

        int choice = getChoice(1, 7);

        switch (choice) {
            case 1:
                handleNewGame();
                break;
            case 2:
                handleGuess();
                break;
            case 3:
                handleShowHistory();
                break;
            case 4:
                displayRules();
                waitForEnter();
                break;
            case 5:
                handleSaveGame();
                break;
            case 6:
                handleLoadGame();
                break;
            case 7:
                cout << "\nВыход в меню\n";
                running = false;
                break;
        }
    }
}
