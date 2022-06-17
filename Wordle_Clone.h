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

    // Initialize variables used in function

    
    // Converts the entered word to all lowercase letters
    for_each(guess.begin(), guess.end(), [](char & c){
        c = tolower(c);
    });

    // If word is correct length, checks if it is valid and not previously guessed
        

    // Loops through previously guessed word list returns false if previously guessed
    for(int i{0}; i < guessed.size(); i++){
        if(guess == guessed[i]){
            return false;
         }
    }

    // Ensures that the word is in the list of valid words, if true, exits early and returns guess
    for(int i{0}; i < word_list_vw.size(); i++){
        if(guess == word_list_vw[i]){
            return true;
        }
    }
    return false;   
}

// Function that compares guess to target word, returns boolean value depending on if they match
bool compare(string word_c, string guess_c, array<int, 26>& letter_state, int guessNum, array<string, 6>& wordLetterState){ 
        
    // If guess and target word match, return true
    if(word_c == guess_c){
        cout << "You win" << endl;
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

void createTopbar(sf::RenderWindow& window, array<int, 6> letterState){
    array<string, 6> letter{"resources/w.png", "resources/o.png", "resources/r.png", "resources/d.png", "resources/l.png", "resources/e.png",};

    for(int i{0}; i<6; i++){
        sf::Texture titleTexture;
        if(!titleTexture.loadFromFile(letter[i])){
            ;
        }
        sf::Sprite titleSprite;
        titleSprite.setTexture(titleTexture);
        titleSprite.scale(1.5f, 1.5f);
        sf::RectangleShape titleBackground(sf::Vector2f(48.f, 48.f));
        titleBackground.setOutlineThickness(-1.f);
        titleBackground.setOutlineColor(sf::Color::Black);
        switch (letterState[i])
        {
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

        titleBackground.setPosition(126 + (58*i), 10);
        titleSprite.setPosition(126 + (58*i), 10);

        window.draw(titleBackground);
        window.draw(titleSprite);
    }
}

void createCurrentGuess(sf::RenderWindow& window, int guessNum, int letterCount, string word){
    string fileExtension{".png"};
    string resourcePathname{"resources/"};
    for (int i{0}; i < letterCount; i++){
        sf::RectangleShape letterBackground(sf::Vector2f(48.f, 48.f));
        letterBackground.setOutlineThickness(-1.f);
        letterBackground.setOutlineColor(sf::Color::Black);
        letterBackground.setFillColor(sf::Color::White);
        letterBackground.setPosition(155 + (58*i),88 + (58*guessNum));
        window.draw(letterBackground);

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

void createPastGuesses(sf::RenderWindow& window, int guessNum, array<string, 6>& pastGuesses, array<string, 6>& guessLetterState){
    string fileExtension{".png"};
    string resourcePathname{"resources/"};
    for (int i{0}; i < guessNum; i++){
        for (int j{0}; j < 5; j++){
            sf::RectangleShape letterBackground(sf::Vector2f(48.f, 48.f));
            letterBackground.setOutlineThickness(-1.f);
            letterBackground.setOutlineColor(sf::Color::Black);

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

            letterBackground.setPosition(155 + (58*j),88 + (58*i));
            window.draw(letterBackground);

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

void createBlanks(sf::RenderWindow& window, int guessNum, int letterCount){
    for(int i{guessNum}; i <6; i++){
        for(int j{0}; j<5; j++){
            if(j==0 && i==guessNum){
                if(letterCount == 5){
                    break;
                }
                else j=letterCount;
            }
            sf::RectangleShape blankLetter(sf::Vector2f(48.f, 48.f));
            blankLetter.setOutlineThickness(-1.f);
            blankLetter.setOutlineColor(sf::Color(160, 160, 160));
            blankLetter.setFillColor(sf::Color::White);
            blankLetter.setPosition(155 + (58*j),88 + (58*i));
            window.draw(blankLetter);
        }
    }
}

void createKeyboard(sf::RenderWindow& window, array<int, 26>& letterState){

    array<string, 26> letter_png{"q.png","w.png","e.png","r.png","t.png","y.png","u.png","i.png","o.png","p.png",
        "a.png","s.png","d.png","f.png","g.png","h.png","j.png","k.png","l.png",
        "z.png","x.png","c.png","v.png","b.png","n.png","m.png"};  
    string resource_pathname{"resources/"};
    string enterPng{"resources/enter.png"};
    string backspacePng{"resources/backspace.png"};
    for(int i{0}; i<26; i++){
        sf::Texture keyboard_texture;
        if(!keyboard_texture.loadFromFile(resource_pathname + letter_png[i])){
            cout << "error loading texture" << endl;
        }
        sf::Sprite keyboard_sprite;
        keyboard_sprite.setTexture(keyboard_texture);
        sf::RectangleShape keyboard_background(sf::Vector2f(32.f, 32.f));
        keyboard_background.setOutlineThickness(-1.f);
        keyboard_background.setOutlineColor(sf::Color::Black);
        switch (letterState[i]){
            case 0:
                keyboard_background.setFillColor(sf::Color::White);
                break;

            case 1:
                keyboard_background.setFillColor(sf::Color::Green);
                break;

            case 2:
                keyboard_background.setFillColor(sf::Color(240,200,70));
                break;

            case 3:
                keyboard_background.setFillColor(sf::Color(152,154,158));
                break;
        
            default:
                break;
        }
        
        if(i < 10){
            keyboard_background.setPosition(95 + (i*42),449);
            keyboard_sprite.setPosition(95 + (i*42),449);
        }
        else if(i < 19){
            keyboard_background.setPosition(116 + ((i-10)*42),491);
            keyboard_sprite.setPosition(116 + ((i-10)*42),491);
        }
        else{
            keyboard_background.setPosition(158 + ((i-19)*42),533);
            keyboard_sprite.setPosition(158 + ((i-19)*42),533);
        }
        window.draw(keyboard_background);
        window.draw(keyboard_sprite);
    }

    sf::Texture enterTexture, backspaceTexture;
    if(!enterTexture.loadFromFile(enterPng) || !backspaceTexture.loadFromFile(backspacePng)){
        cout << "error loading texture" << endl;
    }

    sf::Sprite enterSprite, backspaceSprite;
    enterSprite.setTexture(enterTexture);
    backspaceSprite.setTexture(backspaceTexture);

    sf::RectangleShape enterBackground(sf::Vector2f(64.f, 32.f));
    enterBackground.setOutlineThickness(-1.f);
    enterBackground.setFillColor(sf::Color::White);
    enterBackground.setOutlineColor(sf::Color::Black);
    enterBackground.setPosition(84, 533);  
    enterSprite.setPosition(84, 533);
    window.draw(enterBackground);
    window.draw(enterSprite);

    sf::RectangleShape backspaceBackground(sf::Vector2f(64.f, 32.f));
    backspaceBackground.setOutlineThickness(-1.f);
    backspaceBackground.setFillColor(sf::Color::White);
    backspaceBackground.setOutlineColor(sf::Color::Black);
    backspaceBackground.setPosition(452, 533);  
    backspaceSprite.setPosition(452, 533);
    window.draw(backspaceBackground);
    window.draw(backspaceSprite);
}

char clickKeyboard(array<int, 2> xandy){
    if (xandy[1] >= 449 && xandy[1] <= 481){
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
        else return ' ';
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
        else return ' ';
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
        else return ' ';
    }

    else return ' ';
}