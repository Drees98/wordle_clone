#include <iostream>
#include <array>
#include <random>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

array<string, 5757> get_words(string filename){
    const int fileSize{5757};
    array<string, fileSize> words{};
    string word{};
    fstream file;

    file.open(filename.c_str());
    int i{0};
    while(file >> word){
        words[i] = word;
        i++;
    }

    file.close();

    return words;
}

string random_word(array<string, 5757> words){
    int select{};
    srand(time(NULL) * 9573);
    select = rand() % words.size();

    return words[select];
}

string valid_word(array<string, 5757> words, array<string, 6> guessed){
    bool isValid{false}, alreadyGuessed{};
    string word{};

    do{
        cout << "Enter your guess: ";
        cin >> word;
        cin.clear();
        cin.ignore(10000, '\n');
        alreadyGuessed = false;

        for_each(word.begin(), word.end(), [](char & c){
            c = tolower(c);
        });

        if(word.size() != 5){
            cout << "Word must be 5 letters long." << endl;
        }

        else{
            for(int i{0}; i < guessed.size(); i++){
                if(word == guessed[i]){
                    cout << "You have already guessed this word." << endl;
                    alreadyGuessed = true;
                    break;
                }
            }

            if(alreadyGuessed){
                continue;
            }

            for(int i{0}; i < words.size(); i++){
                if(word == words[i]){
                    isValid = true;
                    break;
                }
            }
            
            if(!isValid){
                cout << "Please enter a valid 5 letter word." << endl;
            }
        }
    }while(!isValid);

    return word;
}

bool compare(string word, string guess){ 

    if(word == guess){
        return true;
    }

    else{
        for(int i{0}; i < 5; i++){

            if(word[i] == guess[i]){
                cout << word[i] << " is in position " << (i + 1) << endl;
            }
        
            else{
                bool inWord{false};
                for(int j{0}; j < 5; j++){
                    if(word[j] == guess[i]){
                        cout << guess[i] << " exists in the word, just not in position " << (i + 1) << endl;
                        inWord = true;
                        break;
                    }
                }

                if(!inWord){
                     cout << guess[i] << " is not in the word." << endl;
                }
            }
        }

        return false;
    }
}