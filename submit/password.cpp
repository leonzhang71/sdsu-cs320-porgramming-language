#include <iostream>
#include <string>
#include <algorithm>
#include <list>
using namespace std;

std::string input = "Leadership is a two-way street, loyalty up and loyalty down.";

std::list<char> tokenDetector() {
    input.erase(remove_if(input.begin(), input.end(), ispunct()), input.end());
    transform(input.begin(),input.end(), input.begin(), ::tolower);
    std::list<char> tokens(input.begin(), input.end());
    cout << tokens;
    return tokens;
}

int main() {
tokenDetector();
    return 0;
}