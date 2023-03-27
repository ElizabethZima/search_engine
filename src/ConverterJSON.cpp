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

void ConverterJSON::PutAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
    //if rank != 0
    // result false / true for all requests
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







