#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>

namespace Utils
{
    struct DocumentRow {
        int _position = 0;
        int _ammount = 0;
        std::vector<std::string> _catalogs;
    };

    using Document = std::vector<DocumentRow>;
    using Kits = std::unordered_map<std::string, int>;
    using Result = std::map<int, std::vector<std::pair<std::string, int>>>;

#ifdef __linux__
    void CleanStr(std::string& str);
#endif

    template <typename Func>
    void ReadFileLines(const std::string& filename, Func handleLine) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл: " << filename << std::endl;
            return;
        }

        std::string line;
        // Пропускаем заголовок
        std::getline(file, line); 

        while (std::getline(file, line)) {
#ifdef __linux__
            CleanStr(line);
#endif
            if (line.empty()) {
                continue;
            } 
            handleLine(line);
        }
    }

    Document ReadDocumentFile(const std::string& filename);
    Kits ReadKitsFile(const std::string& filename);
    bool CheckKitInDocuments(const Document& document, const Kits& kit, Result& result);
    void PrintResult(bool success, const Result& result);

    void TrimStr(std::string& str);
}
