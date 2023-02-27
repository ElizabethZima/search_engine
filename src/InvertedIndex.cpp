#include "InvertedIndex.h"

struct Entry {
    size_t doc_id, count;
// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

void InvertedIndex::UpdateDocumentBase(){
    using namespace std;
    converter = new ConverterJSON();

    docs = converter->GetTextDocuments();
    converter->GetRequests();

};

