#include "BullsAndCows.h"

int main() {
    system("chcp 65001 > nul");
    system("cls");

    UserInterface ui;

    while (true) {
        std::cout << "ВЫБЕРИТЕ РЕЖИМ РАБОТЫ\n";
        std::cout << "  1. Игровой режим\n";
        std::cout << "  2. Выход\n";

        std::cout << "Ваш выбор (1 или 2): ";

        char input[100];
        std::cin.getline(input, 100);

        // Проверка на пустую строку
        if (strlen(input) == 0) {
            std::cout << "\nОшибка! Ввод не может быть пустым.\n";
            std::cin.get();
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
            std::cout << "\nОшибка! Вводите только цифры\n";
            std::cout << "Вы ввели: " << input << "\n";
            std::cin.get();
            continue;
        }

        int choice = atoi(input);

        if (choice < 1 || choice > 2) {
            std::cout << "\nОшибка! Введите 1 или 2.\n";
            std::cin.get();
            continue;
        }

        if (choice == 1) {
            ui.run();
        } else if (choice == 2) {
            std::cout << "\nДо свидания!\n";
            break;
        }
    }

    return 0;
}
