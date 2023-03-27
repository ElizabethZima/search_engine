#include "SearchServer.h"


/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/

int find_max(std::vector<RelativeIndex>& ranks){
    int max = ranks[0].rank;
    for(auto y = 1; y < ranks.size(); y++){
        if (max < ranks[y].rank) max = ranks[y].rank;
    }
    return max;
}


void sortSearchResult(std::vector<RelativeIndex> results){ // sort results for output later
    using namespace std;
    sort(results.begin(), results.end(), [](RelativeIndex a, RelativeIndex b){
        return a.rank > b.rank;
    });

}


std::vector<RelativeIndex> SearchServer::search(const std::vector<std::string>& queries_input){
    using namespace std;
    std::vector<RelativeIndex> result(5);



    if (queries_input.empty())
    {
        std::cout << "Requests are empty.\n";
        return result;
    }
    index.UpdateDocumentBase();
    for(auto& word: queries_input){
        std::vector<Entry> wordFrequency = index.GetWordCount(word);
        for(int i = 0; i < wordFrequency.size(); i++){
            result[i].doc_id = wordFrequency[i].doc_id;
            result[i].rank += wordFrequency[i].count;
        }
    }
    int max = find_max(result);
    for(int i = 0; i < result.size(); i++){
        result[i].rank /= max;
    }

    sortSearchResult(result);
    return result;
};