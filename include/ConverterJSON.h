#ifndef CONVERTERJSON_SEARCHSERVER_H
#define CONVERTERJSON_SEARCHSERVER_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include "nlohmann/json.hpp"

struct Config;
struct Respone;

class ConverterJSON {

public:
    Respone *resp;
    ConverterJSON() = default;

    void GetResponses() ;
    int GetResponsesLimit();
    std::vector<std::string> GetTextDocuments();
    std::vector<std::string> GetRequests();
//    void PutAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

};

#endif //CONVERTERJSON_SEARCHSERVER_H

