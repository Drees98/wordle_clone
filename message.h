#include <iostream>
#ifndef MESSAGE_H
#define MESSAGE_H
using namespace std;
class GuessMessage{
    public:
        GuessMessage(string mes){
            message = mes;
            life = 0;
        }
        string getString(){
            return message;
        }

        bool ageUp(){
            life += 1;
            if(life >= 450){
                return true;
            }
            return false;
        }
    private:
        int life;
        string message;
};

#endif