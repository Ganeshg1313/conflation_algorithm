#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void displayFile(const string &filename) {
    ifstream file(filename);
    string word;
    while (file >> word) {
        cout << word << " ";
    }
    cout << endl;
    file.close();
}

void removePunctuationAndStopWords(const string &inputFile, const string &outputFile) {
    ifstream file(inputFile);
    ofstream outFile(outputFile);
    string word;
    vector<string> stopWords = {"the", "is", "and", "of", "are", "for", "in"};

    while (file >> word) {
        word.erase(remove_if(word.begin(), word.end(), [](char ch) { return !isalpha(ch); }), word.end());
        if (find(stopWords.begin(), stopWords.end(), word) == stopWords.end()) {
            outFile << word << " ";
        }
    }
    outFile.close();
    file.close();
    cout << "File after punctuation removal and stopwords:" << endl;

    ifstream testFile(outputFile);
    while (getline(testFile, word)) {
        cout << word << endl;
    }
    testFile.close();
}

void suffixStripping(const string &inputFile, const string &outputFile) {
    ifstream file(inputFile);
    ofstream outFile(outputFile);
    string word;

    while (file >> word) {
        if (word.size() > 3) {
            if (word.substr(word.size() - 3) == "ier") word = word.substr(0, word.size() - 3) + "y";
            else if (word.substr(word.size() - 3) == "ied") word = word.substr(0, word.size() - 3) + "y";
            else if (word.substr(word.size() - 4) == "iest") word = word.substr(0, word.size() - 4) + "y";
            else if (word.substr(word.size() - 4) == "ness") word = word.substr(0, word.size() - 4);
            else if (word.substr(word.size() - 3) == "ful") word = word.substr(0, word.size() - 3);
            else if (word.substr(word.size() - 2) == "ly") word = word.substr(0, word.size() - 2);
            else if (word.substr(word.size() - 3) == "ing") word = word.substr(0, word.size() - 3) + "y";
            else if (word.substr(word.size() - 2) == "ed") word = word.substr(0, word.size() - 2) + "y";
        }
        outFile << word << " ";
    }
    outFile.close();
    file.close();

    cout << "File after suffix stripping:" << endl;
    ifstream testFile(outputFile);
    while (getline(testFile, word)) {
        cout << word << endl;
    }
    testFile.close();
}

void frequencyCount(const string &inputFile) {
    ifstream file(inputFile);
    unordered_map<string, int> wordFreq;
    string word;

    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        wordFreq[word]++;
    }
    file.close();

    cout << "Word frequencies:" << endl;
    for (const auto &entry : wordFreq) {
        cout << entry.first << "." << entry.second << endl;
    }
}

int main() {
    int choice;
    string inputFile = "Input.txt";
    string noPunctFile = "without_punctuation_and_stopwords.txt";
    string strippedFile = "suffix_stripping2.txt";

    do {
        cout << "1. Display the file\n2. Remove Stop Words\n3. Suffix Stripping\n4. Count Frequency\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayFile(inputFile);
                break;
            case 2:
                removePunctuationAndStopWords(inputFile, noPunctFile);
                break;
            case 3:
                suffixStripping(noPunctFile, strippedFile);
                break;
            case 4:
                frequencyCount(strippedFile);
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
