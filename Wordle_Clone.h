#include <iostream>
#include <array>
#include <random>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "words.h"

using namespace std;

// Matches letter to QWERTY keyboard position
int letterToPosition(char c){
    switch(c){
        case 'q':
            return 0;
            break; 

        case 'w':
            return 1;
            break; 

        case 'e':
            return 2;
            break; 

        case 'r':
            return 3;
            break; 

        case 't':
            return 4;
            break; 

        case 'y':
            return 5;
            break; 

        case 'u':
            return 6;
            break; 

        case 'i':
            return 7;
            break; 

        case 'o':
            return 8;
            break; 

        case 'p':
            return 9;
            break; 

        case 'a':
            return 10;
            break; 

        case 's':
            return 11;
            break; 

        case 'd':
            return 12;
            break; 

        case 'f':
            return 13;
            break; 

        case 'g':
            return 14;
            break;

        case 'h':
            return 15;
            break; 

        case 'j':
            return 16;
            break; 

        case 'k':
            return 17;
            break; 

        case 'l':
            return 18;
            break; 

        case 'z':
            return 19;
            break; 

        case 'x':
            return 20;
            break; 

        case 'c':
            return 21;
            break; 

        case 'v':
            return 22;
            break; 

        case 'b':
            return 23;
            break; 

        case 'n':
            return 24;
            break; 

        case 'm':
            return 25;
            break;  

        default:
            return -1;
            break;
    }
}

// Turns key code into character
char numToChar(int index){
    string alphabet{"abcdefghijklmnopqrstuvwxyz"};
    return alphabet[index];
}

// Function that returns all valid words in an array
 array<string, 5757> get_words(){
        
    // Initializes all variables used in function
    array<string, 5757> word_list_gw{};
    string word;
    istringstream f(words);
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
bool valid_word(string guess, array<string, 5757> word_list_vw, array<string, 6> guessed){

    // Converts the entered word to all lowercase letters
    for_each(guess.begin(), guess.end(), [](char & c){
        c = tolower(c);
    });

    // Loops through previously guessed word list, returns false if previously guessed
    for(int i{0}; i < guessed.size(); i++){
        if(guess == guessed[i]){
            return false;
         }
    }

    // Ensures that the word is in the list of valid words, if true, exits early and returns true
    for(int i{0}; i < word_list_vw.size(); i++){
        if(guess == word_list_vw[i]){
            return true;
        }
    }

    // Returns false if not encountered in list
    return false;   
}

// Function that compares guess to target word, returns boolean value depending on if they match
bool compare(string word_c, string guess_c, array<int, 26>& letter_state, int guessNum, array<string, 6>& wordLetterState){ 
        
    // If guess and target word match, return true
    if(word_c == guess_c){
        wordLetterState[guessNum] += "11111";
        return true;
    }

    // Else, give user clues and return false
    else{

        // Loops through each char in the guess, comparing it to the target word
        for(int i{0}; i < 5; i++){
                
            // Informs the user of a match if the char is in the correct position
            if(word_c[i] == guess_c[i]){
                letter_state[letterToPosition(word_c[i])] = 1;
                wordLetterState[guessNum] += '1';
            }

            // If not, checks to see if char is in word
            else{
                bool inWord{false};

                // Checks each char in target word, comparing to current char in guess word, if there is a match, informs user
                // that char is in word but not in position i, then moves to next guess char
                for(int j{0}; j < 5; j++){
                    if(word_c[j] == guess_c[i]){
                        if(letter_state[letterToPosition(guess_c[i])] != 1){
                            letter_state[letterToPosition(guess_c[i])] = 2;
                        }
                        wordLetterState[guessNum] += '2';
                        inWord = true;
                        break;
                    }
                }

                // If char is not in word, informs user
                if(!inWord){
                    letter_state[letterToPosition(guess_c[i])] = 3;
                    wordLetterState[guessNum] += '3';
                }
            }
        }

            // If not a match, return false after giving clues
            return false;
    }
}

// Creates the title at the top of the screes
void createTopbar(sf::RenderWindow& window, array<int, 6> letterState){

    // Resources for titlebar images
    array<string, 6> letter{"resources/w.png", "resources/o.png", "resources/r.png", "resources/d.png", "resources/l.png", "resources/e.png",};

    // Loop to draw titlebar
    for(int i{0}; i<6; i++){

        // Texture creation and initialization
        sf::Texture titleTexture;
        if(!titleTexture.loadFromFile(letter[i])){
            ;
        }

        // Sprite creation and initialization
        sf::Sprite titleSprite;
        titleSprite.setTexture(titleTexture);
        titleSprite.scale(1.5f, 1.5f);

        // Creates a rectangular background for the sprite
        sf::RectangleShape titleBackground(sf::Vector2f(48.f, 48.f));
        titleBackground.setOutlineThickness(-1.f);
        titleBackground.setOutlineColor(sf::Color::Black);

        // Sets the background color according to the information gained from guesses
        switch (letterState[i]){
            case 0:
                titleBackground.setFillColor(sf::Color::White);
                break;

            case 1:
                titleBackground.setFillColor(sf::Color::Green);
                break;

            case 2:
                titleBackground.setFillColor(sf::Color(240,200,70));
                break;

            case 3:
                titleBackground.setFillColor(sf::Color(152,154,158));
                break;
        
            default:
                break;
        }

        // Sets position of background and sprite
        titleBackground.setPosition(126 + (58*i), 10);
        titleSprite.setPosition(126 + (58*i), 10);

        // Draws the sprite on top of the background, then draws to window
        window.draw(titleBackground);
        window.draw(titleSprite);
    }
}

// Draws the current guess on the screen 
void createCurrentGuess(sf::RenderWindow& window, int guessNum, int letterCount, string word){

    // Extenions for the resouce files
    string fileExtension{".png"};
    string resourcePathname{"resources/"};

    // Loops through current guess
    for (int i{0}; i < letterCount; i++){

        // Creates and draws background
        sf::RectangleShape letterBackground(sf::Vector2f(48.f, 48.f));
        letterBackground.setOutlineThickness(-1.f);
        letterBackground.setOutlineColor(sf::Color::Black);
        letterBackground.setFillColor(sf::Color::White);
        letterBackground.setPosition(155 + (58*i),88 + (58*guessNum));
        window.draw(letterBackground);

        // Creates and draws the texture and sprite
        sf::Texture letterTexture;
        if(!letterTexture.loadFromFile(resourcePathname + word[i] + fileExtension)){
            ;
        }
        sf::Sprite letterSprite;
        letterSprite.setTexture(letterTexture);
        letterSprite.scale(1.5f, 1.5f);
        letterSprite.setPosition(155 + (58*i), 88 + (58*guessNum));
        window.draw(letterSprite);
    }
}

// Draws the pst guesses on screen
void createPastGuesses(sf::RenderWindow& window, int guessNum, array<string, 6>& pastGuesses, array<string, 6>& guessLetterState){

    // File extension variables
    string fileExtension{".png"};
    string resourcePathname{"resources/"};

    // Loops through past guess list
    for (int i{0}; i < guessNum; i++){

        // Loops through past guess strings
        for (int j{0}; j < 5; j++){

            // Creates the letter background
            sf::RectangleShape letterBackground(sf::Vector2f(48.f, 48.f));
            letterBackground.setOutlineThickness(-1.f);
            letterBackground.setOutlineColor(sf::Color::Black);

            // Sets background color based on information gained
            switch (guessLetterState[i][j]){
                case '0':
                    letterBackground.setFillColor(sf::Color::White);
                    break;

                case '1':
                    letterBackground.setFillColor(sf::Color::Green);
                    break;

                case '2':
                    letterBackground.setFillColor(sf::Color(240,200,70));
                    break;

                case '3':
                    letterBackground.setFillColor(sf::Color(152,154,158));
                    break;
        
                default:
                    break;
            }

            // Sets position and draws background
            letterBackground.setPosition(155 + (58*j),88 + (58*i));
            window.draw(letterBackground);

            // Creates and draws the texture and sprite
            sf::Texture letterTexture;
            if(!letterTexture.loadFromFile(resourcePathname + pastGuesses[i][j] + fileExtension)){
                ;
            }
            sf::Sprite letterSprite;
            letterSprite.setTexture(letterTexture);
            letterSprite.scale(1.5f, 1.5f);
            letterSprite.setPosition(155 + (58*j), 88 + (58*i));
            window.draw(letterSprite);
        }
    }
}

// Creates the blank spaces beyond the current guess 
void createBlanks(sf::RenderWindow& window, int guessNum, int letterCount){

    // Loops from current guess to end
    for(int i{guessNum}; i <6; i++){

        // Loops through the current and future guess
        for(int j{0}; j<5; j++){

            // If this is the current guess and the first iteration of inner loop
            if(j==0 && i==guessNum){

                // If guess is at max length end inner loop
                if(letterCount == 5){
                    break;
                }

                // If not, sets iterator to correct position
                else {
                    j=letterCount;
                }
            }

            // Creates and draws the background
            sf::RectangleShape blankLetter(sf::Vector2f(48.f, 48.f));
            blankLetter.setOutlineThickness(-1.f);
            blankLetter.setOutlineColor(sf::Color(160, 160, 160));
            blankLetter.setFillColor(sf::Color::White);
            blankLetter.setPosition(155 + (58*j),88 + (58*i));
            window.draw(blankLetter);
        }
    }
}

// Draws the on-screen keyboard
void createKeyboard(sf::RenderWindow& window, array<int, 26>& letterState){

    // Resouce pathways
    array<string, 26> letterPng{"q.png","w.png","e.png","r.png","t.png","y.png","u.png","i.png","o.png","p.png",
        "a.png","s.png","d.png","f.png","g.png","h.png","j.png","k.png","l.png",
        "z.png","x.png","c.png","v.png","b.png","n.png","m.png"};  
    string resourcePathname{"resources/"};
    string enterPng{"resources/enter.png"};
    string backspacePng{"resources/backspace.png"};

    // Loops through all letters
    for(int i{0}; i<26; i++){

        // Creates all textures, sprites and backgrounds 
        sf::Texture keyboardTexture;
        if(!keyboardTexture.loadFromFile(resourcePathname + letterPng[i])){
            ;
        }
        sf::Sprite keyboardSprite;
        keyboardSprite.setTexture(keyboardTexture);
        sf::RectangleShape keyboardBackground(sf::Vector2f(32.f, 32.f));
        keyboardBackground.setOutlineThickness(-1.f);
        keyboardBackground.setOutlineColor(sf::Color::Black);

        // Sets background color based on gained information
        switch (letterState[i]){
            case 0:
                keyboardBackground.setFillColor(sf::Color::White);
                break;

            case 1:
                keyboardBackground.setFillColor(sf::Color::Green);
                break;

            case 2:
                keyboardBackground.setFillColor(sf::Color(240,200,70));
                break;

            case 3:
                keyboardBackground.setFillColor(sf::Color(152,154,158));
                break;
        
            default:
                break;
        }
        
        // Sets position based on iteration count
        if(i < 10){
            keyboardBackground.setPosition(95 + (i*42),449);
            keyboardSprite.setPosition(95 + (i*42),449);
        }
        else if(i < 19){
            keyboardBackground.setPosition(116 + ((i-10)*42),491);
            keyboardSprite.setPosition(116 + ((i-10)*42),491);
        }
        else{
            keyboardBackground.setPosition(158 + ((i-19)*42),533);
            keyboardSprite.setPosition(158 + ((i-19)*42),533);
        }

        // Draws the background and the sprite
        window.draw(keyboardBackground);
        window.draw(keyboardSprite);
    }

    // Creates the textures for enter and backspace
    sf::Texture enterTexture, backspaceTexture;
    if(!enterTexture.loadFromFile(enterPng) || !backspaceTexture.loadFromFile(backspacePng)){
        ;
    }

    // Creates the enter sprite
    sf::Sprite enterSprite, backspaceSprite;
    enterSprite.setTexture(enterTexture);
    backspaceSprite.setTexture(backspaceTexture);

    // Creates the baackground for the enter sprite and draws both to window
    sf::RectangleShape enterBackground(sf::Vector2f(64.f, 32.f));
    enterBackground.setOutlineThickness(-1.f);
    enterBackground.setFillColor(sf::Color::White);
    enterBackground.setOutlineColor(sf::Color::Black);
    enterBackground.setPosition(84, 533);  
    enterSprite.setPosition(84, 533);
    window.draw(enterBackground);
    window.draw(enterSprite);

    // Creates background for the backspace sprite and draws both
    sf::RectangleShape backspaceBackground(sf::Vector2f(64.f, 32.f));
    backspaceBackground.setOutlineThickness(-1.f);
    backspaceBackground.setFillColor(sf::Color::White);
    backspaceBackground.setOutlineColor(sf::Color::Black);
    backspaceBackground.setPosition(452, 533);  
    backspaceSprite.setPosition(452, 533);
    window.draw(backspaceBackground);
    window.draw(backspaceSprite);
}

// Takes x and y position of click to see if on-screen keyboard letter was clicked
char clickKeyboard(array<int, 2> xandy){
    
    // Checks the row
    if (xandy[1] >= 449 && xandy[1] <= 481){

        // Checks the letter, and returns letter as char or blank space if not letter 
        if (xandy[0] >= 95 && xandy[0] <= 127){
            return 'q';
        }
        else if(xandy[0] >= 137 && xandy[0] <= 169){
            return 'w';
        }
        else if(xandy[0] >= 179 && xandy[0] <= 211){
            return 'e';
        }
        else if(xandy[0] >= 221 && xandy[0] <= 253){
            return 'r';
        }
        else if(xandy[0] >= 263 && xandy[0] <= 295){
            return 't';
        }
        else if(xandy[0] >= 305 && xandy[0] <= 337){
            return 'y';
        }
        else if(xandy[0] >= 347 && xandy[0] <= 379){
            return 'u';
        }
        else if(xandy[0] >= 389 && xandy[0] <= 421){
            return 'i';
        }
        else if(xandy[0] >= 431 && xandy[0] <= 463){
            return 'o';
        }
        else if(xandy[0] >= 473 && xandy[0] <= 505){
            return 'p';
        }
        else {
            return ' ';
        }
    }

    else if (xandy[1] >= 491 && xandy[1] <= 523){
        if(xandy[0] >= 116 && xandy[0] <= 148){
            return 'a';
        }
        else if(xandy[0] >= 158 && xandy[0] <= 190){
            return 's';
        }
        else if(xandy[0] >= 200 && xandy[0] <= 232){
            return 'd';
        }
        else if(xandy[0] >= 242 && xandy[0] <= 274){
            return 'f';
        }
        else if(xandy[0] >= 284 && xandy[0] <= 316){
            return 'g';
        }
        else if(xandy[0] >= 326 && xandy[0] <= 358){
            return 'h';
        }
        else if(xandy[0] >= 368 && xandy[0] <= 400){
            return 'j';
        }
        else if(xandy[0] >= 410 && xandy[0] <= 442){
            return 'k';
        }
        else if(xandy[0] >= 452 && xandy[0] <= 484){
            return 'l';
        }
        else {
            return ' ';
        }
    }

    else if (xandy[1] >= 533 && xandy[1] <= 565){
        if (xandy[0] >= 158 && xandy[0] <= 190){
            return 'z';
        }
        else if(xandy[0] >= 200 && xandy[0] <= 232){
            return 'x';
        }
        else if(xandy[0] >= 242 && xandy[0] <= 274){
            return 'c';
        }
        else if(xandy[0] >= 284 && xandy[0] <= 316){
            return 'v';
        }
        else if(xandy[0] >= 326 && xandy[0] <= 358){
            return 'b';
        }
        else if(xandy[0] >= 368 && xandy[0] <= 400){
            return 'n';
        }
        else if(xandy[0] >= 410 && xandy[0] <= 442){
            return 'm';
        }
        else {
            return ' ';
        }
    }

    // returns blank space if not letter
    else {
        return ' ';
    }
}

// Creates the end menu when game is won or lost
void createEndMenu(sf::RenderWindow& window, int gameState, string target){

    // Creates and draws the menu background
    sf::RectangleShape endMenuBackground(sf::Vector2f(300, 425));
    endMenuBackground.setFillColor(sf::Color::White);
    endMenuBackground.setOutlineThickness(-1.f);
    endMenuBackground.setOutlineColor(sf::Color(160,160,160));
    endMenuBackground.setPosition(150, 75);
    window.draw(endMenuBackground);

    // Creates and draws the new game button
    sf::RectangleShape newGameButton(sf::Vector2f(250, 42));
    newGameButton.setFillColor(sf::Color::White);
    newGameButton.setOutlineThickness(-1.f);
    newGameButton.setOutlineColor(sf::Color::Black);
    newGameButton.setPosition(175, 376);
    window.draw(newGameButton);

    // Creates and draws the end game button
    sf::RectangleShape endGameButton(sf::Vector2f(250, 42));
    endGameButton.setFillColor(sf::Color::White);
    endGameButton.setOutlineThickness(-1.f);
    endGameButton.setOutlineColor(sf::Color::Black);
    endGameButton.setPosition(175, 438);
    window.draw(endGameButton);

    // Creates the font used in the text
    sf::Font font;
    if(!font.loadFromFile("resources/arial.ttf")){
        ;
    }

    // Creates the text objects
    sf::Text newGameText, endGameText, wordReveal, winLossText;

    // Sets values and draws the new game button text
    newGameText.setFont(font);
    newGameText.setString("New Game");
    newGameText.setPosition(175 + ((250 - newGameText.getLocalBounds().width) / 2), 376);
    newGameText.setFillColor(sf::Color::Black);
    window.draw(newGameText);

    // Sets values and draws the quit button text 
    endGameText.setFont(font);
    endGameText.setString("Quit to Desktop");
    endGameText.setPosition(175 + ((250 - endGameText.getLocalBounds().width) / 2), 438);
    endGameText.setFillColor(sf::Color::Black);
    window.draw(endGameText);

    // Set message for end text based on win or loss
    if(gameState == 1){
        winLossText.setString("You Win!");
    }
    else {
        winLossText.setString("You Lose!");
    }

    // Set values for message and draw
    winLossText.setFont(font);
    winLossText.setCharacterSize(45);
    winLossText.setPosition(150 + ((300 - winLossText.getLocalBounds().width) / 2), 75);
    winLossText.setFillColor(sf::Color::Black);
    window.draw(winLossText);

    // Set values for the word reveal, then draw
    wordReveal.setFont(font);
    wordReveal.setFillColor(sf::Color::Black);
    wordReveal.setString("The word was: " + target);
    wordReveal.setPosition(150 + ((300 - wordReveal.getLocalBounds().width) / 2), 90 + winLossText.getLocalBounds().height);
    window.draw(wordReveal);
}