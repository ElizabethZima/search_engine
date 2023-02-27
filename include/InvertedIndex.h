#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

struct Entry;

class InvertedIndex {

private:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь

public:
    InvertedIndex() = default;


};



