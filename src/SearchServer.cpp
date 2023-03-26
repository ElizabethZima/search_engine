#include "SearchServer.h"


/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
std::vector<std::vector<RelativeIndex>> SearchServer::search(const
                                               std::vector<std::string>& queries_input){
    std::vector<std::vector<RelativeIndex>> result{};
    if (queries_input.empty())
    {
        std::cout << "Requests are empty.\n";
        return result;
    }

    index.UpdateDocumentBase();
    index.fillFreqDictionary();

};