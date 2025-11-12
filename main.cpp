#include "Utils.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace Utils;

int main()
{
#ifdef _WIN32
    // Устанавливаем UTF-8 для консоли Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // Читаем файлы документа и наборов
    auto document = ReadDocumentFile("document.txt");
    auto kits = ReadKitsFile("kit.txt");

    if (document.empty() || kits.empty()) {
        return 1;
    }

    // Проверяем наличие набора в документе
    Result result;
    bool isContained = CheckKitInDocuments(document, kits, result);

    // Печать результата
    PrintResult(isContained, result);

    return 0;
}
