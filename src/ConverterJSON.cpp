#include "ConverterJSON.h"

std::string nameToRequest(int max, int i) { // name to "request0010"
    std::string str = std::to_string(max);
    std::string number = std::to_string(i);
    std::ostringstream ss;
    if(str.size() <= 3){
        ss << std::setw(3) << std::setfill('0') << number;
    }
    else {
        ss << std::setw(str.size()) << std::setfill('0') << number;
    }
    std::string result = ss.str();
    return "request" + result;
}


void ConverterJSON::GetResponses() {
        using namespace std;
        nlohmann::json respones;


    try {
            ifstream inputFile("jsons/config.json");

            if (inputFile.eof() || !inputFile.is_open()) throw invalid_argument("Error reading");

            else {
                inputFile >> respones;

               name = respones["config"]["name"];
               version = respones["config"]["version"];
               max_responses = respones["config"]["max_responses"];

                files.clear();
                for (const auto& f: respones["files"]) {
                    files.push_back(f);
                }


                inputFile.close();
            }
        }

        catch (...){
            cerr  <<  "File not founded or Empty!"<< endl;
        }

}


int ConverterJSON::GetResponsesLimit(){
    return max_responses;
}

bool isClear(std::vector<RelativeIndex>& answers){
for(auto it = answers.begin(); it != answers.end(); it++) {
    if (it->rank != 0)return true;
}
return false;
}

std::vector<std::string> ConverterJSON::GetTextDocuments(){
    using namespace std;
    GetResponses();

    vector<string> documents;

    for (auto& f : files){

        ifstream inputFile(f);

        string line, fullDocument;

        while(getline(inputFile, line)){

            fullDocument += line + "\n";
            line = "";

        }

        documents.push_back(fullDocument);

        inputFile.close();
    }

    return documents;
}

std::map<std::string, std::vector<std::string>> ConverterJSON::GetRequests(){
    using namespace std;
    std::map<std::string, std::vector<std::string>> result;
    nlohmann::json inputRequests;

    try {
        ifstream inputFile("jsons/requests.json");

        if (inputFile.eof() || !inputFile.is_open()) throw invalid_argument("Error reading");

        else {

            inputFile >> inputRequests;
            int numRequests = 1;
            for (auto& newRequest: inputRequests["requests"]){
                string nameRequest = nameToRequest(max_responses, numRequests);
                result.insert(make_pair(nameRequest, ParseRequest(newRequest)));
                numRequests++;
            }

        }

        inputFile.close();
    }
    catch (...){
        cerr  <<  "File not founded or Empty!"<< endl;
    }

    return result;
}

void ConverterJSON::PutAnswers(std::map<std::string, std::vector<RelativeIndex>> answers, int max_responses) {
    std::ofstream outputFile("jsons/answers.json");
    if(outputFile.is_open()){
        nlohmann::json answerDictionary;
        auto relevance_array = nlohmann::json::array(); // array for docid and rank in json
        for (auto it = answers.begin(); it != answers.end(); it++) { // traversing an array of responses for all requests
           if(isClear(it->second)) { //check if it empty (not that word in files )

               answerDictionary["answers"][it->first]["result"] = true; // for result

               for (auto iter = it->second.begin(); iter != it->second.end(); iter++) { //traversing an array of one reques
                   if (iter - it->second.begin() > max_responses) break; // check max_responses

                   auto relevance_member = nlohmann::json::object();
                   relevance_member["docid"] = iter->doc_id + 1;
                   relevance_member["rank"] = iter->rank;
                   relevance_array.push_back(relevance_member);

                   }
               answerDictionary["answers"][it->first]["relevance"] = relevance_array;
           }
           else{
               answerDictionary["answers"][it->first]["result"] = false;
           }
        }

        outputFile << answerDictionary;
        outputFile.close();
    }
}

std::vector<std::string> ConverterJSON::ParseRequest(std::string request) {
    using namespace std;
    request += " ";
    vector<string> result{};
    string word;
    for (int i = 0; i < request.size(); i++) {
        if ( word.empty() && (request[i] == ',' || request[i] == ';' )) i++;
        else if (request[i] != ' ' && request[i] != ',' && request[i] != ';' && i + 1 != request.size()) word += request[i];
        else if (i + 1 == request.size() && !word.empty()){
            result.push_back(word);
            word.clear();
        }
        else if (!word.empty() ) {
            result.push_back(word);
            word.clear();
        }

    }
    return result;
}







