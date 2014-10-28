#include "StatusBoard.h"
#include <iostream>

using namespace std;

StatusBoard::StatusBoard()
{
    this->reset();
		this->resetBeam();
    Beamdir = UP;
		attack = false;
}
void StatusBoard::setBeam(int _row, int _col, bool _a){beam[_row][_col] = _a;}
enum Direction StatusBoard::getBeamdir(){ return Beamdir; }
void StatusBoard::setBeamdir(enum Direction _dir){Beamdir = _dir;}

void StatusBoard::reset() // status를 공백으로 초기화한다.
{
    for(int i=0;i<18;i++)
    {
        for(int j=0;j<18;j++)
        {
            status[i][j] = 0x20;
        }
    }
    rows = 18;
    cols = 18;
    boardRows = 9;
    boardCols = 9;
}
void StatusBoard::resetBeam() // beam을 false로 초기화한다.
{
    for(int i = 0;i<9;i++)
    {
        for(int j = 0; j < 9; j++)
        {
            beam[i][j] = false;
        }
    }

}
void StatusBoard::setCell(Cell* cell) // 셀에 있는 유닛의 종류와 팀, 방향에 따라 유닛을 출력한다.
{
   switch(cell->getUnitTeam())
   {
       case 1:
           switch((int)cell->getUnit())
           {
               case 0:
                   status[cell->getrow()*2][cell->getcol()*2] = ' ';
                   status[cell->getrow()*2+1][cell->getcol()*2] = ' ';
                   status[cell->getrow()*2][cell->getcol()*2+1] = ' ';
                   status[cell->getrow()*2+1][cell->getcol()*2+1] = ' ';
                   break;
               case 1:
                   status[cell->getrow()*2][cell->getcol()*2] = 'K';
                   status[cell->getrow()*2+1][cell->getcol()*2] = 'K';
                   status[cell->getrow()*2][cell->getcol()*2+1] = 'K';
                   status[cell->getrow()*2+1][cell->getcol()*2+1] = 'K';
                   break;
               case 2:
                   switch((int)cell->getUnitDir())
                   {
                        case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = 'A';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '|';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 'L';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '|';
                        break;
                        case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = 'A';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'L';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '-';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '-';
                        break;
                   }
                   break;
               case 3:
                   switch((int)cell->getUnitDir())
                   {
                       case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = '-';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'B';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '-';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 'B';
                        break;
                       case 3:
                        status[cell->getrow()*2][cell->getcol()*2] = 'B';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '-';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 'B';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '-';
                        break;
                       case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = '|';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '|';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 'B';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 'B';
                        break;
                       case 4:
                        status[cell->getrow()*2][cell->getcol()*2] = 'B';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'B';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '|';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '|';
                        break;
                   }
                   break;
               case 4:
                switch(cell->getUnitDir())
                   {
                       case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 'T';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = 'T';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        break;
                       case 3:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'T';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 4:
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 'T';
                        break;
                   }
                break;
               case 5:
                switch((int)cell->getUnitDir())
                   {
                       case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'H';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 'H';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = 'H';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 'H';
                        break;
                  }
                break;
							case 6:
								switch((int)cell->getUnitDir())
								{
									case 1:
                   status[cell->getrow()*2][cell->getcol()*2] = 'S';
                   status[cell->getrow()*2+1][cell->getcol()*2] = '|';
                   status[cell->getrow()*2][cell->getcol()*2+1] = 'L';
                   status[cell->getrow()*2+1][cell->getcol()*2+1] = '|';
								 	break;
							 		case 2:
                   status[cell->getrow()*2][cell->getcol()*2] = '-';
                   status[cell->getrow()*2+1][cell->getcol()*2] = '-';
                   status[cell->getrow()*2][cell->getcol()*2+1] = 'S';
                   status[cell->getrow()*2+1][cell->getcol()*2+1] = 'L';
									break;
								}
							break;
							case 7:
                switch(cell->getUnitDir())
                   {
                       case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 'S';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = 'S';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        break;
                       case 3:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'S';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 4:
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 'S';
                        break;
                   }

							break;	
           }
           break;
       case 2:
           switch((int)cell->getUnit())
           {
               case 0:
                   status[cell->getrow()*2][cell->getcol()*2] = ' ';
                   status[cell->getrow()*2+1][cell->getcol()*2] = ' ';
                   status[cell->getrow()*2][cell->getcol()*2+1] = ' ';
                   status[cell->getrow()*2+1][cell->getcol()*2+1] = ' ';
									 break;
               case 1:
                   status[cell->getrow()*2][cell->getcol()*2] = 'k';
                   status[cell->getrow()*2+1][cell->getcol()*2] = 'k';
                   status[cell->getrow()*2][cell->getcol()*2+1] = 'k';
                   status[cell->getrow()*2+1][cell->getcol()*2+1] = 'k';
                   break;
               case 2:
                   switch((int)cell->getUnitDir())
                   {
                        case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = '|';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'a';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '|';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 'l';
                        break;
                        case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = 'a';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'l';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '-';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '-';
                        break;
                   }
                   break;
               case 3:
                   switch((int)cell->getUnitDir())
                   {
                       case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = '-';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'b';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '-';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 'b';
                        break;
                       case 3:
                        status[cell->getrow()*2][cell->getcol()*2] = 'b';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '-';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 'b';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '-';
                        break;
                       case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = '|';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '|';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 'b';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 'b';
                        break;
                       case 4:
                        status[cell->getrow()*2][cell->getcol()*2] = 'b';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'b';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '|';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '|';
                        break;
                   }
                   break;
               case 4:
                switch((int)cell->getUnitDir())
                   {
                       case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 't';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = 't';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        break;
                       case 3:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 't';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 4:
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 't';
                        break;
                   }
                break;
               case 5:
                switch((int)cell->getUnitDir())
                   {
                       case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 'h';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 'h';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = 'h';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 'h';
                        break;
                  }
                break;
							case 6:
								switch((int)cell->getUnitDir())
								{
									case 1:
                   status[cell->getrow()*2][cell->getcol()*2] = '|';
                   status[cell->getrow()*2+1][cell->getcol()*2] = 's';
                   status[cell->getrow()*2][cell->getcol()*2+1] = '|';
                   status[cell->getrow()*2+1][cell->getcol()*2+1] = 'l';
								 	break;
							 		case 2:
                   status[cell->getrow()*2][cell->getcol()*2] = '-';
                   status[cell->getrow()*2+1][cell->getcol()*2] = '-';
                   status[cell->getrow()*2][cell->getcol()*2+1] = 's';
                   status[cell->getrow()*2+1][cell->getcol()*2+1] = 'l';
									break;
								}
							break;

               case 7:
                switch((int)cell->getUnitDir())
                   {
                       case 1:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2][cell->getcol()*2+1] = 's';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 2:
                        status[cell->getrow()*2][cell->getcol()*2] = 's';
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        break;
                       case 3:
                        status[cell->getrow()*2][cell->getcol()*2] = '\\';
                        status[cell->getrow()*2+1][cell->getcol()*2] = 's';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = '\\';
                        break;
                       case 4:
                        status[cell->getrow()*2+1][cell->getcol()*2] = '/';
                        status[cell->getrow()*2][cell->getcol()*2+1] = '/';
                        status[cell->getrow()*2+1][cell->getcol()*2+1] = 's';
                        break;
                   }
                break;

           }
        break;
   }
}

void StatusBoard::printStatus() // 게임 보드창을 출력한다.
{
    for(int i=0; i<28;i++)
        cout << "=";
    cout << "\n";
    for(int i=0;i<20;i++)
    {
        if(i > 2 && i % 2 == 1)
            cout << (i/2) << " ";
        else
        {
            if(i % 2 == 1)
                cout << "  ";
            else
                cout << " ";
        }
    }
    cout <<"\n";
    for(int i=0; i<18; i++)
    {
        if(i % 2 == 0)
        {
            char a = i/2+65;
            cout << a << " ";
        }
        else
            cout << "  ";
        for(int j=0; j<18; j++)
        {
            if(j % 2 == 0)
                cout << " ";
            cout << status[i][j];
        }
        cout << "\n";
    }
    for(int i=0;i<28;i++)
        cout << "=";
    cout << "\n\n";
}

void StatusBoard::setBeam() // 빔을 설정한다.
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(beam[i][j] == true)
            {
								if(attack)
								{
                	status[i*2][j*2] = '*';
                	status[i*2+1][j*2] = '*';
                	status[i*2][j*2+1] = '*';
                	status[i*2+1][j*2+1] = '*';
								}
								else
								{
                	status[i*2][j*2] = 'X';
                	status[i*2+1][j*2] = 'X';
                	status[i*2][j*2+1] = 'X';
                	status[i*2+1][j*2+1] = 'X';
								}
            }

        }
    }
}
void StatusBoard::printBeam() // 빔을 출력한다.
{
    printStatus();    
}

void StatusBoard::setattack(bool _att)
{
				attack = _att;
}

bool StatusBoard::getattack()
{
				return attack;
}
