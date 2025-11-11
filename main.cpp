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

    auto documents = ReadDocumentFile("document.txt");
    auto kitsMap = ReadKitsFile("kit.txt");

    if (documents.empty() || kitsMap.empty()) {
        return 1;
    }

    Result result;

    bool isContained = CheckKitInDocuments(documents, kitsMap, result);

    PrintResult(isContained, result);

    return 0;
}
