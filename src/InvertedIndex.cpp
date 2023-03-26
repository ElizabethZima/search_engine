#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(){
    using namespace std;
    docs = GetTextDocuments();
    GetRequests();
    fillFreqDictionary();
}

void InvertedIndex::addToFreqDictionary(std::string word , int & numberOfDoc){
    auto iter = freq_dictionary.find(word); // search key in freq dictionary

    if (iter != freq_dictionary.end()) {
        freq_dictionary[word].at(numberOfDoc).count += 1; // increment number of words in freq dictionary
    }

    else {
        std::vector<Entry> s(docs.size()); //initialize entries for insert in freq dictionary
        for(int j = 0; j < s.size(); j++) {
            s[j].doc_id = j;
            s[j].count = 0;
        }
        s[numberOfDoc].doc_id = numberOfDoc;
        s[numberOfDoc].count += 1;
        freq_dictionary.insert(make_pair(word, s));
    }
}

void InvertedIndex::Parse(int& numberOfDoc, std::string& document) {
    using namespace std;
    string word;
    for (int i = 0; i < document.size(); i++) {
        if ( word.empty() && (document[i] == ',' || document[i] == ';' )) i++;
        else if (document[i] != ' ' && document[i] != ',' && document[i] != ';' && i + 1 != document.size()) word += document[i];
       else if (i + 1 == document.size() && !word.empty()){
            addToFreqDictionary(word, numberOfDoc);
            word.clear();
       }
        else if (!word.empty() ) {
            addToFreqDictionary(word, numberOfDoc);
            word.clear();
        }

    }

}

void InvertedIndex::fillFreqDictionary() {
    using namespace std;
   IndexingMutex.lock();
    for (int i = 0; i < docs.size(); i++) {
        thread call([&](){
            Parse(i, docs[i]);
        });
        call.join();
        if (call.joinable()) call.detach();
    } // thread call
    IndexingMutex.unlock();
}


std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word){
    using namespace std;
    if (IndexingMutex.try_lock()) {
        auto it = freq_dictionary.find(word);
        if (it != freq_dictionary.end()) {
            IndexingMutex.unlock();
            return it->second;
        } else {
            return {};
        }

    } else {
        std::cout << "Index is on going, please repeat the request later.\n";
        return {};
    }
}


