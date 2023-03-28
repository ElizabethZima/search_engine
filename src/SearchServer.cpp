#include "SearchServer.h"

int find_max(std::vector<RelativeIndex>& ranks){
    int max = ranks[0].rank;
    for(auto y = 1; y < ranks.size(); y++){
        if (max < ranks[y].rank) max = ranks[y].rank;
    }
    return max;
}


void sortSearchResult(std::vector<RelativeIndex>& results){ // sort results for output later
    using namespace std;
    sort(results.begin(), results.end(), [](RelativeIndex& a, RelativeIndex& b){

        return a.rank > b.rank;
    });

}


std::map<std::string, std::vector<RelativeIndex>> SearchServer::search(std::map<std::string, std::vector<std::string>> requests){
    std::map<std::string, std::vector<RelativeIndex>>  result;

    if (requests.empty())
    {
        std::cout << "Requests are empty.\n";
        return result;
    }

    index.UpdateDocumentBase(); //updating

    for(auto it = requests.begin(); it != requests.end() ; it++ ) {
        std::vector<RelativeIndex> res(index.GetNumberOfDoc());
        std::vector<std::string> wordOfRequest = it->second;
        if(!wordOfRequest.empty()) {
            for (int j = 0; j < wordOfRequest.size(); j++) {
                std::vector<Entry> wordFrequency = index.GetWordCount(it->second[j]);
                if (wordFrequency.size() != 0) {
                    for (int i = 0; i < wordFrequency.size(); i++) {
                        res[i].doc_id = wordFrequency[i].doc_id;
                        res[i].rank += wordFrequency[i].count / 2;
                    }
                }
            }
            int max = find_max(res);
            for(int i = 0; i < res.size(); i++){
                if(max != 0)
                    res[i].rank /= max;
            }

            sortSearchResult(res); // wrong answer

            result.insert(std::make_pair(it->first, res));
        }

    }

    return result;
}