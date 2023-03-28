#include <iostream>
#include "InvertedIndex.h"
#include "SearchServer.h"
int main() {
    InvertedIndex* index = new InvertedIndex();
    index->UpdateDocumentBase();

    SearchServer* server = new SearchServer(*index);

   server->search(index->GetRequests());

    return 0;
}
