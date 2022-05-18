#include <iostream>
#include <array>
#include "Wordle_Clone.h"
#include <SFML/Graphics.hpp>

using namespace std;

// Main Function of the driver program
int main(){

    // Creates a game object
    //Wordle_Clone game{}; 

    // Activates the game
    //game.start_game(game.get_word(), game.get_word_list());

    sf::RenderWindow window(sf::VideoMode(600, 600), "Wordle Clone");
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

        window.clear();
        window.draw(shape);
        window.display();
    }
    
    return 0;

}

