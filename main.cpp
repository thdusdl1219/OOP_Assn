#include "Board.h"
using namespace std;
int main()
{
    string choise;
    cout << "<< Welcome to Laser Chess!! >>\n";
		cout << endl;
    while(1)
    {
        cout << "What do you want to do?\n";
				ifstream openfile("Savefile");
				if(openfile.is_open())
				{
								cout << "1. Start Game 	2. Load Game 	0. Exit Game\n";
								cout << ">> ";
								getline(cin,choise);
								if(choise.size() != 1 || choise.at(0) < 48 || choise.at(0) > 50)
								{
												cout << "You should choose 0 or 1 or 2\n";
												continue;
								}
								if(choise.at(0) == 49)
								{
												Board* newboard = new Board();
												newboard->startGame(false);
								}
								else if(choise.at(0) == 48)
								{
												cout << "Bye!\n";
												return 0;
								}
								else if(choise.at(0) == 50)
								{
												Board* newboard = new Board();
												if(newboard->loadGame(openfile))
													newboard->startGame(true);
								}

				}
				else
				{
        	cout << "1. Start Game  0. Exit Game\n";
        	cout << ">> ";
        	getline(cin,choise);
					if(choise.size() != 1 || choise.at(0) < 48 || choise.at(0) > 49)
					{
         	   cout << "You should choose 0 or 1\n";
						 continue;
					}
        	if(choise.at(0) == 49)
        	{
						Board* newboard = new Board();
            newboard->startGame(false);
        	}
        	else if(choise.at(0) == 48)
        	{
            cout << "Bye!\n";
            return 0;
        	}
				}
    }
}
