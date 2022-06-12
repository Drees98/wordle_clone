#include <iostream>
#include <array>
#include "Wordle_Clone.h"
#include <SFML/Graphics.hpp>

using namespace std;

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
    for(int i{0}; i<26; i++){
        
        
        sf::Texture keyboard_texture;
        if(!keyboard_texture.loadFromFile(resource_pathname + letter_png[i])){
            ;
        }
        sf::Sprite keyboard_sprite;
        keyboard_sprite.setTexture(keyboard_texture);
        sf::RectangleShape keyboard_background(sf::Vector2f(32.f, 32.f));
        keyboard_background.setOutlineThickness(-1.f);
        keyboard_background.setOutlineColor(sf::Color::Black);
        switch (letterState[i])
        {
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

// Main Function of the driver program
int main(){

    // Creates a game object
    //Wordle_Clone game{}; 

    // Activates the game
    //game.start_game(game.get_word(), game.get_word_list());
    
    sf::RenderWindow window(sf::VideoMode(600, 575), "Wordle Clone", sf::Style::Titlebar|sf::Style::Close);
    
    array<int, 2> xandy {-1, -1};
    array<int, 26> letterState{0};
    char selectedLetter{' '};
    int guessNum{0};
    int letterCount{0};
    string word{" "};
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
                }
            }
        }
        window.clear(sf::Color::White);
        createKeyboard(window, letterState);
        createTopbar(window, {letterState[1],letterState[8],letterState[3],letterState[12],letterState[18],letterState[2]});
        createBlanks(window, guessNum, letterCount);
        if(xandy[0] != -1 || xandy[1] != -1){
            selectedLetter = clickKeyboard(xandy);  
        }
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

