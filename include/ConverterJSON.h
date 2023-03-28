#ifndef CONVERTERJSON_SEARCHSERVER_H
#define CONVERTERJSON_SEARCHSERVER_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include <sstream>
#include <map>
#include "nlohmann/json.hpp"

struct RelativeIndex ;

class ConverterJSON {
private:
    std::string name, version;
    int max_responses;
    std::vector<std::string> files;
public:

    ConverterJSON() = default;

    void GetResponses() ;
    int GetResponsesLimit();
    std::vector<std::string> GetTextDocuments();
    std::map<std::string, std::vector<std::string>> ConverterJSON::GetRequests();
   // void PutAnswers(std::map<std::string, std::vector<RelativeIndex>> answers);

    std::vector<std::string> ParseRequest(std::string string);
};

#endif //CONVERTERJSON_SEARCHSERVER_H

