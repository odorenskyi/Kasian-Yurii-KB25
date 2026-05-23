#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define _BYTE_DEFINED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define BEEP() Beep(1000, 70)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
    #define BEEP() std::cout << "\a" << std::flush
#endif

#include "ModulesKasian.h"

std::string getRuntimeLab12Path() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string exePath(buffer);

    std::string lowerPath = exePath;
    for (size_t i = 0; i < lowerPath.length(); ++i) {
        if (lowerPath[i] == '/') lowerPath[i] = '\\';
        lowerPath[i] = std::tolower(lowerPath[i]);
    }

    size_t labPos = lowerPath.rfind("\\lab12\\");
    if (labPos != std::string::npos) {
        return exePath.substr(0, labPos + 7);
    }
#endif
    return "";
}

int main() {
    #ifdef _WIN32
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
    #endif

    std::cout << "=========================================================" << std::endl;
    std::cout << "          АВТОМАТИЗОВАНА ВЕРИФІКАЦІЯ СТРУКТУРИ ПАПОК     " << std::endl;
    std::cout << "=========================================================" << std::endl;

    std::string buildTimePath = __FILE__;
    std::string normalizedBuildPath = buildTimePath;
    for (size_t i = 0; i < normalizedBuildPath.length(); ++i) {
        if (normalizedBuildPath[i] == '/') normalizedBuildPath[i] = '\\';
        normalizedBuildPath[i] = std::tolower(normalizedBuildPath[i]);
    }

    std::string requiredSegment = "\\lab12\\prj\\";
    size_t prjPos = normalizedBuildPath.rfind(requiredSegment);

    if (prjPos == std::string::npos) {
        std::cout << "[ПОРІВНЯННЯ] Перевірка макросу __FILE__: НЕ В ПАПЦІ \\lab12\\prj\\" << std::endl;
        std::cout << "=> АКТИВАЦІЯ СЦЕНАРІЮ А: Порушено регламент." << std::endl;

        std::ofstream violationFile("TestResults.txt");
        if (violationFile.is_open()) {
            violationFile << "Встановлені вимоги порядку виконання лабораторної роботи порушено!" << std::endl;
            violationFile.close();
        }

        for (int i = 0; i < 100; ++i) {
            BEEP();
            SLEEP(40);
        }
        return 1;
    }

    std::cout << "[ПОРІВНЯННЯ] Перевірка макросу __FILE__: УСПІШНО (в папці prj)" << std::endl;
    std::cout << "=> АКТИВАЦІЯ СЦЕНАРІЮ Б: Автоматичне модульне тестування." << std::endl;

    std::string baseLab12Path = getRuntimeLab12Path();
    if (baseLab12Path.empty()) {
        std::cerr << "Критична помилка: Не вдалося визначити робочу директорію проєкту!" << std::endl;
        return 1;
    }

    std::string inputTestSuite = baseLab12Path + "TestSuite\\suite_var16.txt";
    std::string outputResults   = baseLab12Path + "TestSuite\\TestResults.txt";

    std::cout << "\n[ШЛЯХИ ФАЙЛІВ]:" << std::endl;
    std::cout << "  -> Читання тестів з: " << inputTestSuite << std::endl;
    std::cout << "  -> Запис звіту в:    " << outputResults << std::endl;

    class LocalTestSuiteProcessor {
    public:
        static void process(const std::string& inPath, const std::string& outPath) {
            std::ifstream inFile(inPath);
            std::ofstream outFile(outPath);

            if (!inFile.is_open()) {
                std::cerr << "\n[ПОМИЛКА ВО] Не вдалося відкрити файл тестів!" << std::endl;
                std::cerr << "Будь ласка, перевірте, чи файл suite_var16.txt дійсно лежить у папці \\lab12\\TestSuite\\" << std::endl;
                return;
            }
            if (!outFile.is_open()) {
                std::cerr << "\n[ПОМИЛКА ВО] Не вдалося створити файл результатів!" << std::endl;
                inFile.close();
                return;
            }

            outFile << "=========================================================\n";
            outFile << "   ПРОТОКОЛ АВТОМАТИЗОВАНОГО ТЕСТУВАННЯ (ISO/IEC 12207)\n";
            outFile << "=========================================================\n\n";

            std::string line;
            const double EPSILON = 1e-5;
            int totalTests = 0;
            int passedTests = 0;

            while (std::getline(inFile, line)) {
                if (line.empty() || line[0] == '#') continue;

                std::stringstream ss(line);
                std::string token;

                std::string testCaseID;
                double r = 0.0, h = 0.0, expectedArea = 0.0;

                if (std::getline(ss, token, ';')) testCaseID = token;
                try {
                    if (std::getline(ss, token, ';')) r = std::stod(token);
                    if (std::getline(ss, token, ';')) h = std::stod(token);
                    if (std::getline(ss, token, ';')) expectedArea = std::stod(token);
                } catch (const std::exception&) {
                    outFile << testCaseID << " -> СБОЙ: Пошкоджена структура даних тест-кейса.\n";
                    continue;
                }

                totalTests++;

                ClassLab12_Kasian testObj;
                testObj.setAttributes(r, h);
                double actualArea = testObj.getLateralArea();

                bool isPassed = std::fabs(actualArea - expectedArea) < EPSILON;
                std::string verdict = isPassed ? "PASSED" : "FAILED";

                if (isPassed) passedTests++;

                outFile << "Test Case ID: " << testCaseID << " | Action: R=" << r << ", H=" << h << "\n"
                        << "  -> Expected Area: " << expectedArea << "\n"
                        << "  -> Actual Area:   " << actualArea << "\n"
                        << "  -> Verdict:       [" << verdict << "]\n"
                        << "---------------------------------------------------------\n";
            }

            outFile << "\nПІДСУМОК ТЕСТУВАННЯ:\n";
            outFile << "Всього виконано тест-кейси: " << totalTests << "\n";
            outFile << "Успішно пройдено (Passed):  " << passedTests << " з " << totalTests << "\n";

            inFile.close();
            outFile.close();

            std::cout << "\n[УСПІХ] Тестування завершено! Результати збережено в TestResults.txt" << std::endl;
        }
    };

    LocalTestSuiteProcessor::process(inputTestSuite, outputResults);

    return 0;
}
