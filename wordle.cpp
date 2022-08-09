#include <iostream>
#include <array>
#include "Wordle_Clone.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

// Main Function of the driver program
int main(){
    
    // Initializes the window
    sf::RenderWindow window(sf::VideoMode(600, 575), "Wordle Clone", sf::Style::Titlebar|sf::Style::Close);
    
    // Initializes the variables used in the driver program
    array<int, 2> xandy {-1, -1};
    array<int, 26> letterState{0};
    unordered_set<string> wordsList{get_words()};
    array<string, 6> previousGuesses{};
    string targetWord{random_word(wordsList)};
    array<string, 6> wordLetterState{""};
    int gameState{0};
    char selectedLetter{' '};
    int guessNum{0};
    int letterCount{0};
    bool result{false};
    string word{""};

    // Keeps program loop going while window is open
    while (window.isOpen())
    {
        
        // Refreshes event every loop
        sf::Event event;

        // Loops through the event triggers
        while (window.pollEvent(event))
        {   

            // closes the window if close event is triggered
            if (event.type == sf::Event::Closed)
                window.close();

            // Instructiopns for click events
            if (event.type == sf::Event::MouseButtonPressed){

                // Left click trigger
                if (event.mouseButton.button == sf::Mouse::Left){
                    
                    // Takes the coordinates of the mouse click 
                    xandy = {event.mouseButton.x, event.mouseButton.y};
                    
                    // If game is in playstate
                    if(gameState == 0){

                        // Checks if the coordinates clicked match a letter's position
                        selectedLetter = clickKeyboard(xandy);

                        // If no letter was selected, checks if enter or backspace was clicked
                        if (selectedLetter == ' ' && xandy[1] >= 533 && xandy[1] <= 565){
                            
                            // If enter is clicked
                            if(xandy[0] >= 84 && xandy[0] <=148){
                                
                                // checks if the guess is a valid word
                                if(letterCount == 5 && valid_word(word, wordsList, previousGuesses)){
                                    
                                    // Compares current word to target
                                    result = compare(targetWord, word, letterState, guessNum, wordLetterState);

                                    // Adds guess to list, increments the guess count, and resets the current word 
                                    previousGuesses[guessNum] = word;
                                    guessNum++;
                                    letterCount = 0;
                                    word = "";
                                    
                                    // If the guess is correct, enter end menu with win
                                    if(result){
                                        gameState = 1;
                                        recordStats(guessNum - 1);
                                    }

                                    // If the guess is incorrect and you are out of attempts, enter end menu with loss
                                    else if(guessNum > 5 ){
                                        gameState = 2;
                                        recordStats(guessNum);
                                    }
                                }
                            }

                            // If backspace is clicked
                            else if(xandy[0] >= 452 && xandy[0] <=516 && letterCount != 0){
                                
                                // Lower the lettercount and remove last letter from word
                                letterCount--;
                                word.pop_back();
                            }
                        }
                    }

                    // If game is in end state
                    else if(gameState == 1 || gameState == 2){

                        // Checks if new game or quit is clicked
                        if(xandy[0] >= 175 && xandy[0] <= 425){

                            // If new game is pressed
                            if(xandy[1] >= 376 && xandy[1] <= 418){

                                // Resets game to initial state
                                guessNum = 0;
                                letterCount = 0;
                                word = "";
                                previousGuesses = {""};
                                targetWord = random_word(wordsList);
                                letterState = {0};
                                gameState = 0;
                                result = false;
                                wordLetterState = {""};
                            }

                            // If quit is pressed
                            else if(xandy[1] >= 438 && xandy[1] <= 480){
                                
                                // Closes window
                                window.close();
                            }
                        }
                    }
                }
            }

            // Instructions for key button releases
            if (event.type == sf::Event::KeyReleased){

                // If backspace is pressed and lettercount is not 0
                if(event.key.code == sf::Keyboard::BackSpace && letterCount != 0){

                    // Removes last letter and decrements letter count
                    letterCount--;
                    word.pop_back();
                }

                // If enter is pressed and word is correct length
                else if(event.key.code == sf::Keyboard::Enter && letterCount == 5){
                    
                    // if the word is valid
                    if(valid_word(word, wordsList, previousGuesses)){

                        // Compares word, increments guess guess count, and resets word
                        result = compare(targetWord, word, letterState, guessNum, wordLetterState);
                        previousGuesses[guessNum] = word;
                        guessNum++;
                        letterCount = 0;
                        word = "";

                        // If guess is correct, enter end state with win 
                        if(result){
                            gameState = 1;
                            recordStats(guessNum - 1);
                        }

                        // if incorrect and out of guess attempts, enter endstate with loss
                        else if(guessNum > 5 ){
                            gameState = 2;
                            recordStats(guessNum);
                        }
                    }
                }

                // If key pressed was a letter
                else if(event.key.code >=0 && event.key.code < 26){

                    // Takes key code and returns letter
                    selectedLetter =  numToChar(event.key.code);
                }
            }
        }

        // Clears window and sets background to white
        window.clear(sf::Color::White);

        // Draws the game to the window
        createKeyboard(window, letterState);
        createTopbar(window, {letterState[1],letterState[8],letterState[3],letterState[12],letterState[18],letterState[2]});
        createBlanks(window, guessNum, letterCount);
        createCurrentGuess(window, guessNum, letterCount, word);
        createPastGuesses(window, guessNum, previousGuesses, wordLetterState);

        // If game is in end state
        if (gameState == 1 || gameState == 2){

            // Draws end menu to window
            createEndMenu(window, gameState, targetWord);
        }
        

        // If letter is entered and letter count is less than 5
        if(selectedLetter != ' ' && letterCount < 5){

            // Adds letter to word and increments letter count
            letterCount++;
            word += selectedLetter;
        }

        // Resets selected letter and click coordinates for next loop
        selectedLetter = ' ';
        xandy = {-1, -1};

        // Displays the drawn window
        window.display();
    }
    
    // Program succesfully executed
    return 0;
}