#include "Utils.h"

namespace Utils
{
    Document ReadDocumentFile(const std::string& filename) {
        Document document;
        ReadFileLines(filename, [&](const std::string& line) {
            std::stringstream ss(line);
            DocumentRow row;
            std::string catalogStr;

            ss >> row._position >> row._ammount;
            std::getline(ss, catalogStr);

            // Очищаем каталоги от лишних символов
            row._catalogs.clear();
            if (!catalogStr.empty()) {
                std::stringstream catalogSS(catalogStr);
                std::string catalog;
                while (std::getline(catalogSS, catalog, ',')) {
                    TrimStr(catalog);
                    if (!catalog.empty()) {
                        row._catalogs.emplace_back(catalog);
                    }
                }
            }
            document.emplace_back(std::move(row));
        });

        return document;
    }

    Kits ReadKitsFile(const std::string& filename) {
        Kits kits;
        ReadFileLines(filename, [&](const std::string& line) {
            std::stringstream ss(line);
            std::string catalogStr;
            int count;

            ss >> catalogStr >> count;
            TrimStr(catalogStr);

            if (!catalogStr.empty()) {
                kits.emplace(catalogStr, count);
            }
        });

        return kits;
    }

    bool CheckKitInDocuments(const Document& document, const Kits& kit, Result& result) {
        // Сортируем документы по количеству каталогов (меньше каталогов - сначала)
        auto sortedDoc = document;
        std::sort(sortedDoc.begin(), sortedDoc.end(), [](const DocumentRow& a, const DocumentRow& b) {
            return a._catalogs.size() < b._catalogs.size();
        });

        // Сначала используем позиции с меньшим количеством каталогов
        result.clear();
        auto kitCopy = kit;

        for (const auto& row : sortedDoc) {
            for (const auto& catalog : row._catalogs) {
                auto it = kitCopy.find(catalog);
                if (it != kitCopy.end() && it->second > 0) {
                    int positionAmmount = std::min(row._ammount, it->second);
                    if (positionAmmount > 0) {
                        // Проверяем, не использовали ли мы уже эту позицию для другого каталога
                        bool isUsed = false;
                        for (const auto& line : result) {
                            if (line.first == row._position) {
                                isUsed = true;
                                break;
                            }
                        }

                        if (!isUsed) {
                            result[row._position].emplace_back(catalog, positionAmmount);
                            it->second -= positionAmmount;

                            if (it->second <= 0) {
                                kitCopy.erase(it);
                            }
                        }
                    }
                }
            }
        }

        // Если все требования выполнены
        return kitCopy.empty();
    }

    void PrintResult(bool success, const Result& result) {
    if (success) {
        std::cout << "Набор содержится в документе\n"
                << "Состав набора\n"
                << "Позиция\tКол-во\tКаталог\n";

        for (const auto& resItem : result) {
            for (const auto& internalVecItem : resItem.second) {
                std::cout << resItem.first << "\t" << internalVecItem.second << "\t\"" << internalVecItem.first << "\"\n";
            }
        }
    }
    else {
        std::cout << "Набор не содержится в документе\n";
    }
}
    void TrimStr(std::string& str)
    {
        str.erase(0, str.find_first_not_of(" \t\""));
        str.erase(str.find_last_not_of(" \t\"") + 1);
    }

#ifdef __linux__
    void CleanStr(std::string& str) {
        str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    }
#endif
}

