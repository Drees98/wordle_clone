#include <iostream>
#include <array>
#include "wordle_functions.h"

using namespace std;

int main(){
    bool correct{false};
    string word{}, guess{};
    array<string, 5757> words{};
    array<string, 6> guesses{};
    int guess_no{0};
    words = get_words("words.txt");
    word = random_word(words);

    while(guess_no < 6){
        guess = valid_word(words, guesses);
        guesses[guess_no] = guess;
        correct = compare(word, guess);
        guess_no++;

        if(correct){
            cout << "Congratulations! You guessed correctly on attempt #" << guess_no << endl;
            break;
        }

        else if(guess_no == 6){
            cout << "You were not able to guess the word, it was " << word << endl;
        }
    }

    cout << "Click enter to end program" << endl;

    getchar();

    return 0;

}

