#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h> // Бібліотека для роботи з системою Windows

using namespace std;

// Клас для активів (акції, крипта тощо)
class Asset {
public:
    string name;
    double price;
    double volatility; // Як сильно змінюється ціна (ризик)

    Asset(string n, double p, double v) : name(n), price(p), volatility(v) {}

    // Метод оновлення ціни
    void updatePrice() {
        // Генеруємо зміну ціни залежно від волатильності
        double change = (rand() % (int)(volatility * 200 + 1) - (volatility * 100)) / 100.0;
        price += price * (change / 100.0);

        if (price < 0.1) price = 0.1; // Ціна не може бути нульовою
    }
};

int main() {
    // Налаштування української мови в консолі
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    srand(time(0)); // Ініціалізація випадкових чисел

    // Початкові дані гравця
    double balance = 1000.0;
    int appleShares = 0;
    int bitcoinAmount = 0;

    // Створюємо активи: Назва, Початкова ціна, Рівень ризику (0-10)
    Asset apple("Акції Apple", 150.0, 5.0);   // Стабільні
    Asset bitcoin("Біткоїн", 30000.0, 25.0); // Дуже ризиковий

    int choice;
    while (true) {
        system("cls"); // Очищення екрану (робить гру охайнішою)

        cout << "========================================" << endl;
        cout << "      ЕКОНОМІЧНИЙ СИМУЛЯТОР v1.1        " << endl;
        cout << "========================================" << endl;
        cout << "Ваш баланс: $" << balance << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. " << apple.name << ": $" << apple.price << " (У вас: " << appleShares << ")" << endl;
        cout << "2. " << bitcoin.name << ": $" << bitcoin.price << " (У вас: " << bitcoinAmount << ")" << endl;
        cout << "----------------------------------------" << endl;
        cout << "ДІЇ:" << endl;
        cout << "1 - Купити Apple | 2 - Продати Apple" << endl;
        cout << "3 - Купити Біткоїн | 4 - Продати Біткоїн" << endl;
        cout << "5 - Наступний день (Оновити ціни)" << endl;
        cout << "0 - Вийти з гри" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: // Купити Apple
                if (balance >= apple.price) {
                    balance -= apple.price;
                    appleShares++;
                }
                break;
            case 2: // Продати Apple
                if (appleShares > 0) {
                    balance += apple.price;
                    appleShares--;
                }
                break;
            case 3: // Купити BTC
                if (balance >= bitcoin.price) {
                    balance -= bitcoin.price;
                    bitcoinAmount++;
                }
                break;
            case 4: // Продати BTC
                if (bitcoinAmount > 0) {
                    balance += bitcoin.price;
                    bitcoinAmount--;
                }
                break;
            case 5: // Новий день
                apple.updatePrice();
                bitcoin.updatePrice();
                cout << "Ціни змінилися!" << endl;
                Sleep(500); // Невелика затримка для ефекту
                break;
        }
    }

    system("cls");
    cout << "Гра завершена!" << endl;
    cout << "Ваш фінальний капітал: $" << balance + (appleShares * apple.price) + (bitcoinAmount * bitcoin.price) << endl;

    return 0;
}
