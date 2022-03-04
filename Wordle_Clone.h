#include <iostream>
#include <array>
#include <random>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <sstream>
#include "words.h"

using namespace std;

// Class for the wordle game
class Wordle_Clone{
public:

    // Constructor for the game, initializes word list and selects word
    // words is a variable defined in the words.h resource file
    Wordle_Clone(){
        word_list = get_words(words);
        word = random_word(word_list);
    }

    // Function for starting the game, takes word list and selected word
    void start_game(string word_sg, array<string, 5757> word_list_sg){

        // Initializes the variables used in the game loop
        bool correct{false};
        string guess{};
        array<string, 6> guesses{};
        int guess_no{0};

        // Loops through the process up to six times, stopping if the correct word is guessed
        while(guess_no < 6){

            // Ensures that the word is a valid 5 letter word, and makes sure it has not been guessed,
            // then returns it as a string
            guess = valid_word(word_list_sg, guesses);

            // Saves a valid guess into a list that can be referenced to on future guesses
            guesses[guess_no] = guess;

            // Compares the guess to the correct word, prints out the relevance to the correct word,
            // then returns a boolean variable depending on if it was correct
            correct = compare(word_sg, guess);

            // Increases guess count by 1
            guess_no++;

            // If the compare function returns true, display the attempt number and end game loop
            if(correct){
                cout << "Congratulations! You guessed correctly on attempt #" << guess_no << endl;
                break;
            }

            // If the user does not guess correctly on the 6th try, the game will end and word will reveal
            else if(guess_no == 6){
                cout << "You were not able to guess the word, it was " << word_sg << endl;
            }
        }

        // Prevents the command window from dissapearing instantly while prompting user to close the window
        cout << "Press enter to end program" << endl;
        getchar();
    }

    // Function that returns the target word
    string get_word(){
        return word;
    }

    // Function that returns the array of all valid words
    array<string, 5757> get_word_list(){
        return word_list;
    }    

private:

    // Initializes object variables
    string word;
    array<string, 5757> word_list;

    // Function that returns all valid words in an array
    array<string, 5757> get_words(string raw_data){
        
        // Initializes all variables used in function
        array<string, 5757> word_list_gw{};
        string word;
        istringstream f(raw_data);
        int i{0};

        // Loops through string setting each array position to a word
        while(getline(f, word)){
            word_list_gw[i] = word;
            i++;
        }

        // Returns the words in an array
        return word_list_gw;
    }

    // Function that selects a random word from the list to be the target word, returns as string
    string random_word(array<string, 5757> word_list_rw){

        int select{};

        // Takes the system time, then multiplies it by a large number as a seed 
        // for the random number generator, then gets a number limited to the list size
        srand(time(NULL) * 9573);
        select = rand() % word_list_rw.size();

        // Returns selected word as a string
        return word_list_rw[select];
    }

    // Function that ensures the user enters a valid word, then returns it as a string
    string valid_word(array<string, 5757> word_list_vw, array<string, 6> guessed){

        // Initialize variables used in function
        bool isValid{false}, alreadyGuessed{};
        string word{};

        // Loop that breaks once a valid word is entered
        do{

            // Prompts the user to enter a word, then resets the already guessed boolean
            cout << "Enter your guess: ";
            cin >> word;
            cin.clear();
            cin.ignore(10000, '\n');
            alreadyGuessed = false;

            // Converts the entered word to all lowercase letters
            for_each(word.begin(), word.end(), [](char & c){
                c = tolower(c);
            });

            // Checks if word is correct length, prompts user to enter new word if not
            if(word.size() != 5){
                cout << "Word must be 5 letters long." << endl;
            }

            // If word is correct length, checks if it is valid and not previously guessed
            else{

                // Loops through previously guessed word list, reprompts user if true
                for(int i{0}; i < guessed.size(); i++){
                    if(word == guessed[i]){
                        cout << "You have already guessed this word." << endl;
                        alreadyGuessed = true;
                        break;
                    }
                }

                // Restarts loop if guessed word is in the previously guessed list
                if(alreadyGuessed){
                    continue;
                }

                // Ensures that the word is in the list of valid words, if true, exits early and returns guess
                for(int i{0}; i < word_list_vw.size(); i++){
                    if(word == word_list_vw[i]){
                        isValid = true;
                        break;
                    }
                }

                // If the word is not valid, reprompts user
                if(!isValid){
                    cout << "Please enter a valid 5 letter word." << endl;
                }
            }
        }while(!isValid);

        // Returns word as string once valid word is found
        return word;
    }

    // Function that compares guess to target word, returns boolean value depending on if they match
    bool compare(string word_c, string guess_c){ 
        
        // If guess and target word match, return true
        if(word_c == guess_c){
            return true;
        }

        // Else, give user clues and return false
        else{

            // Loops through each char in the guess, comparing it to the target word
            for(int i{0}; i < 5; i++){
                
                // Informs the user of a match if the char is in the correct position
                if(word_c[i] == guess_c[i]){
                    cout << word_c[i] << " is in position " << (i + 1) << endl;
                }

                // If not, checks to see if char is in word
                else{
                    bool inWord{false};

                    // Checks each char in target word, comparing to current char in guess word, if there is a match, informs user
                    // that char is in word but not in position i, then moves to next guess char
                    for(int j{0}; j < 5; j++){
                        if(word_c[j] == guess_c[i]){
                            cout << guess_c[i] << " exists in the word, just not in position " << (i + 1) << endl;
                            inWord = true;
                            break;
                        }
                    }

                    // If char is not in word, informs user
                    if(!inWord){
                        cout << guess_c[i] << " is not in the word." << endl;
                    }
                }
            }

            // If not a match, return false after giving clues
            return false;
        }
    }
};


