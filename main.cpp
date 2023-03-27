#include <iostream>
#include "SearchServer.h"
int main() {
    InvertedIndex* index = new InvertedIndex();
    index->UpdateDocumentBase();

    SearchServer* server = new SearchServer(*index);

    std::vector<std::string> queries{"milk", "sugar", "salt"};  //  support many words ???

    server->search(queries);

    return 0;
}
