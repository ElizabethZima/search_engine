#ifndef INVERTEDINDEX_SEARCHSERVER_H
#define INVERTEDINDEX_SEARCHSERVER_H
#include <iostream>
#include <mutex>
#include <map>
#include <ConverterJSON.h>
#include<thread>
//std::mutex IndexingMutex;

struct Entry {
    size_t doc_id, count;
// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};



class InvertedIndex {

private:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь
    std::map<std::string, std::vector<std::string>> requests;

public:
   InvertedIndex() = default;

    void UpdateDocumentBase();

    std::vector<Entry> GetWordCount(std::string &word);
    void Parse(int& numberOfDoc, std::string& document); // parse for string document
    void addToFreqDictionary(std::string& word , int & numberOfDoc); //add or count++ to the word
    void fillFreqDictionary();

    std::map<std::string, std::vector<std::string>> GetRequests();
    int GetNumberOfDoc();

};


#endif //INVERTEDINDEX_SEARCHSERVER_H


