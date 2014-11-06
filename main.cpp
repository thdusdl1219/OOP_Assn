#include "Board.h"
using namespace std;
int main()
{
    string choise;
    cout << "<< Welcome to Laser Chess!! >>\n";
    while(1)
    {
        cout << "What do you want to do?\n";
        cout << "1. Start Game  2. Exit Game\n";
        cout << ">> ";
        getline(cin,choise);
				if(choise.size() != 1 || choise.at(0) < 49 || choise.at(0) > 50)
				{
            cout << "You should choose 1 or 2\n";
			continue;
				}
        if(choise.at(0) == 49)
        {
            Board* newboard = new Board();
            newboard->startGame();
        }
        else if(choise.at(0) == 50)
        {
            cout << "Bye!\n";
            return 0;
        }
    }
}
