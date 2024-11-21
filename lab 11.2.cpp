#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // Для ispunct

using namespace std;

// Функція, що перевіряє, чи символ є знаком пунктуації
bool IsPunctuation(char ch) {
    return ispunct(ch); // Не використовуємо static_cast, просто передаємо char
}

// Функція для переписування тексту з урахуванням умов
void RewriteFile(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Error: Unable to open input file \"" << inputFileName << "\".\n";
        return;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cerr << "Error: Unable to open output file \"" << outputFileName << "\".\n";
        inputFile.close();
        return;
    }

    string word;
    char nextChar;
    bool wasPunctuation = false;

    while (inputFile >> word) { // Читаємо кожне слово
        inputFile.get(nextChar); // Отримуємо наступний символ після слова

        if (IsPunctuation(nextChar)) {
            // Якщо це знак пунктуації, вилучаємо пробіли перед ним
            outputFile << word << nextChar;
            wasPunctuation = true;
        }
        else {
            // Якщо це не знак пунктуації, додаємо слово з пробілом
            if (!wasPunctuation) {
                outputFile << word << ' ';
            }
            else {
                outputFile << word;
            }
            wasPunctuation = false;

            // Повертаємо символ назад у потік
            inputFile.unget();
        }
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    string inputFileName = "t1.txt"; // Назва вхідного файлу
    string outputFileName = "t2.txt"; // Назва вихідного файлу

    RewriteFile(inputFileName, outputFileName);

    cout << "Processing completed. Check the output file \"" << outputFileName << "\".\n";
    return 0;
}
