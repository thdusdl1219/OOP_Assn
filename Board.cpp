#include "Board.h"
#include <cstdio>
#include <cstring>
using namespace std;
Board::Board() // 초기화한다.
{
	rows = 9;
	cols = 9;
	ongoingTeam = ONE;
	for(int i=0;i<9;i++)
	{
		for(int j =0;j<9;j++)
		{
			cell[i*9+j] = new Cell(i, j, this);
		}
	}	
	status = new StatusBoard (this);
	srand(time(NULL));
	attack = false;
	Beamdir = UP;
}

Board::~Board()
{
	for(int i = 0; i <81 ; i++)
	{
		delete cell[i];
		cell[i] = NULL;
	}
	delete status;
}

/* laser의 방향에 따라서 laser을 가동시키는 함수 */
Cell* Board::launchLaser(Cell* _startcell )
{

	Cell* result = NULL;
	while(1)
	{
		int check = 0;
		Cell* check2 = NULL;
		int tmprow = _startcell->getrow();
		int tmpcol = _startcell->getcol();
		enum Direction tmpdir = getBeamdir();
		switch(tmpdir)
		{
			case UP: // 빔 방향에 따라 나눔
				for(int i = tmprow - 1; i>=0; i--)
				{
					check2 = beamCurCell(cell[i*9+tmpcol]);
					if(check2 != NULL)
					{
						result = check2;
						if(result->get_block())
						{
							result->set_block(false);
							result = NULL;
						}
						break;
					}
					if(getBeamdir() != tmpdir) // 중간에 빔이 반사되거나 하는 이유로 빔의 방향이 바뀌게 되면 check를 1로 변화시켜서 다시 루프에 빠지게 만든다.
					{
						_startcell = cell[i*9+tmpcol];
						check = 1;
						break;
					}
				}
				break;
			case DOWN:
				for(int i = tmprow + 1; i<9; i++)
				{
					check2 = beamCurCell(cell[i*9+tmpcol]);
					if(check2 != NULL)
					{
						result = check2;
						if(result->get_block())
						{
							result->set_block(false);
							result = NULL;
						}
						break;
					}
					if(getBeamdir() != tmpdir)
					{
						_startcell = cell[i*9+tmpcol];
						check = 1;
						break;
					}
				}
				break;
			case LEFT:
				for(int i = tmpcol - 1; i>=0; i--)
				{
					check2 = beamCurCell(cell[tmprow*9+i]);
					if(check2 != NULL)
					{
						result = check2;
						if(result->get_block())
						{
							result->set_block(false);
							result = NULL;
						}
						break;
					}
					if(getBeamdir() != tmpdir)
					{
						_startcell = cell[tmprow*9+i];
						check = 1;
						break;
					}
				}
				break;
			case RIGHT:
				for(int i = tmpcol + 1; i<9; i++)
				{
					check2 = beamCurCell(cell[tmprow*9+i]);
					if(check2 != NULL)
					{
						result = check2;
						if(result->get_block())
						{
							result->set_block(false);
							result = NULL;
						}
						break;
					}
					if(getBeamdir() != tmpdir)
					{
						_startcell = cell[tmprow*9+i];
						check = 1;
						break;
					}
				}
				break;
		}
		if(check == 1)
			continue;
		break;
	}

	return result;
}


/* 빔이 작용하는 셀에 존재하는 유닛의 조건에 따라 어떠한 행동을 취해야 하는지를 정하는 함수 */
Cell* Board::beamCurCell(Cell* _cell)
{
	char tmprow = _cell->getrow() + 65;
	char tmpcol = _cell->getcol() + 49;
	Cell* result = NULL;
	Cell* remove = NULL;
	Unit* uni = _cell->getUni();
	if(uni == NULL)
		status->setBeam(_cell->getrow(), _cell->getcol(), true);
	else
	{
		result = uni->beamCurUnit();
	}   
	return result;
}
/* 게임을 초기화한다. */
void Board::initGame()
{
	cout << "[System] Initializing Game..\n";
	cell[0]->setUnit(ATTLASER);
	cell[1]->setaccesible(false);
	cell[4]->setUnit(BLOCKMIRROR);
	cell[4]->setUnitDir(DOWN);
	cell[5]->setUnit(KING);
	king[0] = cell[5]->getUni();
	cell[6]->setUnit(BLOCKMIRROR);
	cell[6]->setUnitDir(DOWN);
	cell[7]->setaccesible(false);
	cell[8]->setUnit(STULASER);
	cell[9]->setaccesible(false);
	cell[10]->setUnit(SPLITTER);
	cell[10]->setUnitDir(LEFT);

	cell[16]->setUnit(TRIMIRROR);
	cell[16]->setUnitDir(LEFT);
	cell[17]->setaccesible(false);

	cell[27]->setUnit(TRIMIRROR);
	cell[27]->setUnitDir(DOWN);

	cell[29]->setUnit(TRIMIRROR);
	cell[29]->setUnitTeam(TWO);

	cell[31]->setUnit(HYPERMIRROR);

	cell[32]->setUnit(HYPERMIRROR);

	cell[33]->setUnit(TRIMIRROR);
	cell[33]->setUnitDir(LEFT);

	cell[35]->setUnit(TRIMIRROR);
	cell[35]->setUnitDir(RIGHT);
	cell[35]->setUnitTeam(TWO);

	cell[40]->setHyper(true);

	cell[45]->setUnit(TRIMIRROR);
	cell[45]->setUnitDir(LEFT);

	cell[47]->setUnit(TRIMIRROR);
	cell[47]->setUnitDir(RIGHT);
	cell[47]->setUnitTeam(TWO);

	cell[48]->setUnit(HYPERMIRROR);
	cell[48]->setUnitTeam(TWO);
	cell[49]->setUnit(HYPERMIRROR);
	cell[49]->setUnitTeam(TWO);
	cell[51]->setUnit(TRIMIRROR);
	cell[51]->setUnitDir(DOWN);
	cell[53]->setUnit(TRIMIRROR);
	cell[53]->setUnitTeam(TWO);

	cell[63]->setaccesible(false);
	cell[64]->setUnit(TRIMIRROR);
	cell[64]->setUnitDir(RIGHT);
	cell[64]->setUnitTeam(TWO);


	cell[70]->setUnit(SPLITTER);
	cell[70]->setUnitDir(RIGHT);
	cell[70]->setUnitTeam(TWO);
	cell[71]->setaccesible(false);
	cell[72]->setUnit(ATTLASER);
	cell[72]->setUnitTeam(TWO);
	cell[73]->setaccesible(false);
	cell[74]->setUnit(BLOCKMIRROR);
	cell[74]->setUnitTeam(TWO);
	cell[75]->setUnit(KING);
	king[1] = cell[75]->getUni();
	cell[75]->setUnitTeam(TWO);
	cell[76]->setUnit(BLOCKMIRROR);
	cell[76]->setUnitTeam(TWO);
	cell[79]->setaccesible(false);
	cell[80]->setUnit(STULASER);
	cell[80]->setUnitTeam(TWO);
	cout << "[System] Complete Initializing.\n";
}

Cell** Board::getCell(int i)
{
	return &cell[i];
}
Cell* Board::choiceLaser() // Laser를 고르고 launch시키는 함수
{
	Cell* remove;
	string choice;
	while(1)
	{
		cout << "Which Laser do you want to launch?\n";
		cout << "1. Attack 2. Stun\n";
		cout << ">> ";
		getline(cin,choice);
		if(choice.size() !=1 || (choice.at(0) != 49 && choice.at(0) != 50))
		{
			cout << "[System] Please correct choice!\n";
			continue;
		}
		else if(choice.at(0) == 49)
		{
			setattack(true);
			break;
		}
		else
		{
			setattack(false);
			break;
		}
	}
	switch((int)ongoingTeam) // 턴을 종료하기 전에 레이저의 현재 방향을 고려하여 빔의 방향을 정하고 레이저를 쏜다.
	{
		case 1:
			if(getattack())
			{
				switch((int)cell[0]->getUni()->get_dir())
				{
					case 1:
						setBeamdir(DOWN);
						remove = launchLaser(cell[0]);
						break;
					case 2:
						setBeamdir(RIGHT);
						remove = launchLaser(cell[0]);
						break;
				}
			}
			else
			{
				switch((int)cell[8]->getUni()->get_dir())
				{
					case 1:
						setBeamdir(DOWN);
						remove = launchLaser(cell[8]);
						break;
					case 2:
						setBeamdir(LEFT);
						remove = launchLaser(cell[8]);
						break;
				}
			}
			break;
		case 2:
			if(getattack())
			{
				switch((int)cell[72]->getUni()->get_dir())
				{
					case 1:
						setBeamdir(UP);
						remove = launchLaser(cell[72]);
						break;
					case 2:
						setBeamdir(RIGHT);
						remove = launchLaser(cell[72]);
						break;
				}
			}
			else
			{
				switch((int)cell[80]->getUni()->get_dir())
				{
					case 1:
						setBeamdir(UP);
						remove = launchLaser(cell[80]);
						break;
					case 2:
						setBeamdir(LEFT);
						remove = launchLaser(cell[80]);
						break;
				}

			}	
			break;
	}
	return remove;
}
/* 게임을 진행하는 메인 함수 */
void Board::startGame(bool load)
{

	if(!load)
		initGame();
	showBoard();
	while(1)
	{

		int check = 0, i;
		int turn = ongoingTeam;
		Cell** curcell;
		Unit* curunit;
		string choice;
		string input;
		Cell* remove;
		cout << "Player " << turn << "'s Turn !\n";
		while(1)
		{
			cout << "Which Unit do you want to control?\n";
			cout << "(Input 'x' or \"exit\" if you want to save and exit.)" << endl;
			cout << ">> ";
			getline(cin,input);
			if((input.size() == 1 && input.at(0) == 120) || (input.size() == 4 && input == "exit" ))
			{
				saveGame();
				exit(0);
			}
			else if(input.size() != 3 || input.at(0) < 65 || input.at(0) > 105 || (input.at(0) > 73 && input.at(0) < 97) || input.at(1) != 32 || input.at(2) < 49 || input.at(2) > 57)
			{ // 잘못된 입력
				cout << "[System] Input Format of position is \"Row Col\".\n";
				cout << "         ex) D 4, e 2, or etc.\n"; 
				continue;
			}
			else
			{
				if(input.at(0) > 96)
					input.at(0) -= 32;
				curcell = &cell[(input.at(0)-65)*9 + (input.at(2)-49)];
				enum Team unitteam = (*curcell)->getUnitTeam();
				curunit = (*curcell)->getUni();
				if(curunit != NULL) // 컨트롤 할 유닛을 선택한다.
				{
					if(unitteam == ongoingTeam)
					{
						cout << "\n";
						if((*curcell)->getUnitstun())
						{
							cout << "The Unit is in stun!!\n";
							continue;
						}
						break;
					}
					else
					{
						cout << "[System] You can't control other's Unit!\n";
						continue;
					}
				}
				else
				{
					cout << "[System] You can't control empty space :)\n";
					continue;
				}
			}
		}
		check = curunit->control_unit();
		if(check == 1)
		{
			continue;
		}

		remove = choiceLaser();

		showBeam(); // 레이저를 출력한다.
		if(!king[0]->get_enable() && !king[1]->get_enable())
		{
			cout << "[System] Draw!!" << endl;
			return;
		}
		if(!king[0]->get_enable()) // 왕이 죽었는지를 판정한다.
		{
			cout << "[System] Player 2's Victory!!" << endl;
			return;
		}
		else if(!king[1]->get_enable())
		{
			cout << "[System] Player 1's Victory!!" << endl;
			return;
		}
		if(remove != NULL && getattack())
		{				
			remove->removeUnit();
		}
		showBoard(); // 체스보드를 출력한다.
		if(ongoingTeam == ONE) // 턴을 종료하기 전에 다음 턴의 팀을 변경한다.
			ongoingTeam = TWO;
		else
			ongoingTeam = ONE;


		for(i = 0; i < 81 ; i++)
		{
			if(cell[i]->getUnitstun())
			{
				if(cell[i]->getUnitTeam() == ongoingTeam)
				{
					if(cell[i]->getUni()->getturn() == 1)
					{
						cell[i]->setUnitstun(false);
						cell[i]->getUni()->setturn(0);
					}
					else
					{
						cell[i]->getUni()->incturn();
					}
				}
			}
		}
		setattack(false);
	}
}
/* 보드를 출력하는 함수 */
void Board::showBoard()
{
	status->reset();
	for(int i=0;i<81;i++)
	{
		if(cell[i]->getseam())
		{
			cell[i]->removeUnit();
			cell[i]->setseam(false);
		}
		status->setCell(cell[i]);
	}
	status->printStatus();
}
/* 빔을 출력하는 함수 */
void Board::showBeam()
{
	status->reset();
	for(int i=0;i<81;i++)
	{
		status->setCell(cell[i]);
	}
	status->setBeam();
	status->printBeam();
	status->resetBeam();
}

bool Board::testFile(std::ifstream& file)
{
	char buf[45];
	int j = 0;
	file.clear();
	file.seekg(0, file.beg);

	while(!file.eof())
	{

		file.getline(buf, 46);
		if(j != 9)
		{
			if(strlen(buf) != 45)
			{
				return false;
			}
		}
		j++;
	}
	file.clear();
	file.seekg(0, file.beg);
	if(j != 10)
		return false;
	else
		return true;
}

bool Board::loadGame(std::ifstream& in)
{
	char buffer[45];
	int i, j, l = 0, k = 0;
	cout << "[System] Loading Game.." << endl;
	if(!testFile(in))
	{
		cout << "[System] Failure to Load Game!" << endl << endl;
		in.close();
		remove("Savefile");
		startGame(false);
		return false;
	}
	for(j = 0; j < 9; j++)
	{				
		in.getline(buffer, 46);
		for(i = 0; i < 9; i++)
		{

			cell[j*9+i]->setUnit((enum UnitType)(buffer[i*5+2] - 48));
			if(buffer[i*5+2]-48 == 2 || buffer[i*5+2]-48 == 6)
			{
				if((j*9 + i) == 0 || (j*9 + i) == 8 || (j*9 + i) == 72 || (j*9 + i) == 80)
					l++;
				else
				{
					cout << "[System] Failure to Load Game!" << endl << endl;
					in.close();
					remove("Savefile");
					Board* board = new Board();
					board->startGame(false);
					return false;
				}
			}
			else if(buffer[i*5+2]-48 == 1)
			{
				king[k++] = cell[j*9+i]->getUni();
			}
			else if(buffer[i*5+2]-48 == 8)
			{
				cell[j*9+i]->setHyper(true);
				cell[j*9+i]->setUnit(NONE);
			}
			cell[j*9+i]->setUnitTeam((enum Team)(buffer[i*5] - 48));
			cell[j*9+i]->setUnitDir((enum Direction)(buffer[i*5+1] - 48));
			cell[j*9+i]->setUnitstun((bool)(buffer[i*5+3] - 48));
			cell[j*9+i]->setUnitstunturn(buffer[i*5+4]-48);
		}
	}
	if(k != 2 || l != 4)
	{
		cout << "[System] Failure to Load Game!" << endl << endl;
		in.close();
		remove("Savefile");
		Board* board = new Board();
		board->startGame(false);
		return false;

	}
	in.getline(buffer, 2);
	if(buffer[0] - 48 == 1 || buffer[0]-48 == 2)
	{
		ongoingTeam = (enum Team)(buffer[0]-48);
	}
	else
	{
		cout << "[System] Failure to Load Game!" << endl << endl;
		in.close();
		remove("Savefile");
		Board* board = new Board();
		board->startGame(false);
		return false;
	}
	cell[1]->setaccesible(false);
	cell[7]->setaccesible(false);
	cell[9]->setaccesible(false);
	cell[17]->setaccesible(false);

	cell[63]->setaccesible(false);
	cell[71]->setaccesible(false);
	cell[73]->setaccesible(false);
	cell[79]->setaccesible(false);
	in.close();
	cout << "[System] Complete Loading" << endl << endl;
	return true;
}

void Board::saveGame()
{
	ofstream outfile("Savefile");
	int j, i;
	for(j = 0; j < 9; j ++ )
	{
		for(i = 0; i < 9; i++ )
		{
			outfile << cell[j*9 + i];
		}
		outfile<<endl;
	}
	outfile<<ongoingTeam;
	outfile.close();
}

bool Board::getattack(){return attack;}
void Board::setattack(bool a){attack = a;}

enum Direction Board::getBeamdir(){return Beamdir;}
void Board::setBeamdir(enum Direction _dir){Beamdir = _dir;}


