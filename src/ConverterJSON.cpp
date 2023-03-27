#include "ConverterJSON.h"

struct Config {
    std::string name, version;
    int max_responses{};
};

struct Response {
    Config configuration;
    std::vector<std::string> files;
};

void ConverterJSON::GetResponses() {
        using namespace std;
        nlohmann::json respones;

        try {
            ifstream inputFile("jsons/config.json");

            if (inputFile.eof() || !inputFile.is_open()) throw invalid_argument("Error reading");

            else {
                inputFile >> respones;


                resp->configuration.name = respones["config"]["name"];
                resp->configuration.version = respones["config"]["version"];
                resp->configuration.max_responses = respones["config"]["max_responses"];


                for (const auto& f : respones["files"]) {

                    resp->files.push_back(f);

                }

                inputFile.close();
            }
        }

        catch (...){
            cerr  <<  "File not founded or Empty!"<< endl;
        }

}


int ConverterJSON::GetResponsesLimit(){
    return resp->configuration.max_responses;
}


std::vector<std::string> ConverterJSON::GetTextDocuments(){
    using namespace std;
    GetResponses();

    vector<string> documents;

    for (const auto& f : resp->files){

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

    nlohmann::json inputRequests;

    try {
        ifstream inputFile("jsons/requests.json");

        if (inputFile.eof() || !inputFile.is_open()) throw invalid_argument("Error reading");

        else {

            inputFile >> inputRequests;

            for(int i = 0 ; i < inputRequests.size(); i++) {
                    string nameRequest = "request" + i;

                    //vector of words and split function !!!
            }
}            //parse request to vector
            //
            //
            //
            //


//            for (const auto& f : inputRequests["requests"]) {
//
//                requestsVec.push_back(f);
//
//            }

     //   }

        inputFile.close();
    }
    catch (...){
        cerr  <<  "File not founded or Empty!"<< endl;
    }

   // return requestsVec;   ????

}

void ConverterJSON::PutAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
    //if rank != 0
    // result false / true for all requests
}


