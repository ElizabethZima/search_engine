#include <iostream>
#include <ConverterJSON.h>

int main() {
    ConverterJSON *converter = new ConverterJSON();
    std::cout << converter->GetTextDocuments()[0];
    std::cout << converter->GetRequests()[0];
    std::cout << converter->GetResponsesLimit();
    return 0;
}
