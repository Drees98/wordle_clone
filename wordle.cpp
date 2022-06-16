#include <iostream>
#include <array>
#include "Wordle_Clone.h"
#include <SFML/Graphics.hpp>

using namespace std;



// Main Function of the driver program
int main(){
    
    sf::RenderWindow window(sf::VideoMode(600, 575), "Wordle Clone", sf::Style::Titlebar|sf::Style::Close);
    
    array<int, 2> xandy {-1, -1};
    array<int, 26> letterState{0};
    array<string, 5757> wordsList{get_words()};
    array<string, 6> previousGuesses{};
    string targetWord{random_word(wordsList)};
    array<string, 6> wordLetterState{""};
    char selectedLetter{' '};
    int guessNum{0};
    int letterCount{0};
    bool result{false};
    string word{""};
    while (window.isOpen())
    {
    
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    
                    xandy = {event.mouseButton.x, event.mouseButton.y};
                    selectedLetter = clickKeyboard(xandy);
                }
            }

            if (event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::BackSpace && letterCount != 0){
                    letterCount--;
                    word.pop_back();
                }
                if(event.key.code == sf::Keyboard::Enter && letterCount == 5){
                    if(valid_word(word, wordsList, previousGuesses)){
                        result = compare(targetWord, word, letterState, guessNum, wordLetterState);
                        cout << wordLetterState[guessNum] << endl;
                        previousGuesses[guessNum] = word;
                        guessNum++;
                        letterCount = 0;
                        word = "";
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        createKeyboard(window, letterState);
        createTopbar(window, {letterState[1],letterState[8],letterState[3],letterState[12],letterState[18],letterState[2]});
        createBlanks(window, guessNum, letterCount);
        createCurrentGuess(window, guessNum, letterCount, word);
        createPastGuesses(window, guessNum, previousGuesses, wordLetterState);
        
        if(selectedLetter != ' ' && letterCount < 5){
            letterCount++;
            word += selectedLetter;
            cout << word << endl; 
        }
        selectedLetter = ' ';
        xandy = {-1, -1};
        window.display();
    }
    
    return 0;

}

