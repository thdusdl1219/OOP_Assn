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
	Unit* uni = cell->getUni();
	if(uni == NULL)
	{
		if(cell->getHyper())
		{
			status[cell->getrow()*2][cell->getcol()*2] = '/';
			status[cell->getrow()*2+1][cell->getcol()*2] = '\\';
			status[cell->getrow()*2][cell->getcol()*2+1] = '\\';
			status[cell->getrow()*2+1][cell->getcol()*2+1] = '/';
		}
		else
		{
			status[cell->getrow()*2][cell->getcol()*2] = ' ';
			status[cell->getrow()*2+1][cell->getcol()*2] = ' ';
			status[cell->getrow()*2][cell->getcol()*2+1] = ' ';
			status[cell->getrow()*2+1][cell->getcol()*2+1] = ' ';
		}
	}
	else
	{
		uni->printUnit(status);
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

