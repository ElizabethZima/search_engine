#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
int main() {
    InvertedIndex* index = new InvertedIndex();
    index->UpdateDocumentBase();

    SearchServer* server = new SearchServer(*index);
    ConverterJSON* conv = new ConverterJSON();

    conv->PutAnswers(server->search(index->GetRequests()));

    return 0;
}
