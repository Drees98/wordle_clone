#include <iostream>
#include <array>
#include "Wordle_Clone.h"
#include <SFML/Graphics.hpp>

using namespace std;

void createKeyboard(sf::RenderWindow& window){

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
        keyboard_background.setFillColor(sf::Color(240,200,70));
        if(i < 10){
            keyboard_background.setPosition(95 + (i*42),574);
            keyboard_sprite.setPosition(95 + (i*42),574);
        }
        else if(i < 19){
            keyboard_background.setPosition(116 + ((i-10)*42),616);
            keyboard_sprite.setPosition(116 + ((i-10)*42),616);
        }
        else{
            keyboard_background.setPosition(158 + ((i-19)*42),658);
            keyboard_sprite.setPosition(158 + ((i-19)*42),658);
        }
        window.draw(keyboard_background);
        window.draw(keyboard_sprite);
    }  
}

// Main Function of the driver program
int main(){

    // Creates a game object
    //Wordle_Clone game{}; 

    // Activates the game
    //game.start_game(game.get_word(), game.get_word_list());
    
    sf::RenderWindow window(sf::VideoMode(600, 700), "Wordle Clone", sf::Style::Default);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        createKeyboard(window);
        window.display();
    }
    
    return 0;

}

