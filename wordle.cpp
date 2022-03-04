#include <iostream>
#include <array>
#include "Wordle_Clone.h"

using namespace std;

// Main Function of the driver program
int main(){

    // Creates a game object
    Wordle_Clone game{}; 

    // Activates the game
    game.start_game(game.get_word(), game.get_word_list());
    
    return 0;

}

