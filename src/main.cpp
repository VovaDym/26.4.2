#include <iostream>
#include "class.h"

int main()
{
    Phone myPhone;
    bool exit = false;
    do
    {
        int action = myPhone.chosenCommand();

        switch (action)
        {
        case 0:
            myPhone.add();
            break;
        case 1:
            myPhone.call();
            break;
        case 2:
            myPhone.sms();
            break;
        case 3:
            exit = true;
            break;
        default:
            std::cout << "Incorrect command. Try again" << std::endl << std::endl;
            break;
        } 
    } while (!exit);
}
