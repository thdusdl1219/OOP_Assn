#include "Board.h"
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
            cell[i*9+j] = new Cell(i, j);
        }
    }
    status = new StatusBoard ();
		srand(time(NULL));
}

Board::~Board()
{
    for(int i = 0; i <81 ; i++)
    {
        delete cell[i];
        cell[i] = NULL;
    }
    for(int i = 0; i < 2; i++)
    {
        delete king[i];
        king[i] = NULL;
    }
    for(int i = 0; i < 4; i++)
    {
        delete laser[i];
        laser[i] = NULL;
    }
}

/* 유닛을 스왑할 떄 쓰이는 함수, 두 셀을 서로 스왑하고 row와 col만 다시 지정해준다. */
void Board::swap(Cell*& _a, Cell*& _b)
{
	int tmprowb;
	int tmpcolb;
	int tmprowa;
	int tmpcola;
	Cell* tmp;

    tmp = _b;
    tmprowb = _b->getrow();
    tmpcolb = _b->getcol();
    tmprowa = _a->getrow();
    tmpcola = _a->getcol();
    _b = _a;
    _b->setrow(tmprowb);
    _b->setcol(tmpcolb);
    _a = tmp;
    _a->setrow(tmprowa);
    _a->setcol(tmpcola);
		cout << "[Log] Player"<< ongoingTeam <<": " << (char)(tmprowa + 65) << " " << (char)(tmpcola + 49) << " => " << (char)(tmprowb + 65) << " " << (char)(tmpcolb + 49) << endl;
	 if(_a->getHyper())
	 {
		_a->setHyper(false);
		Cell** choose = &cell[rand()%81];
		while((*choose)->getUni() != NULL || !(*choose)->movableTo())
			choose = &cell[rand()%81];
		swap(_b, (*choose));
	 }	 
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
        enum Direction tmpdir = status->getBeamdir();
        switch(tmpdir)
        {
            case UP: // 빔 방향에 따라 나눔
                for(int i = tmprow - 1; i>=0; i--)
                {
                    check2 = beamCurCell(cell[i*9+tmpcol]);
                    if(check2 != NULL)
										{
												result = check2;
												if(result->getUnit() == BLOCKMIRROR && status->getBeamdir() != tmpdir)
												{
														result = NULL;
												}
                        break;
										}
                    if(status->getBeamdir() != tmpdir) // 중간에 빔이 반사되거나 하는 이유로 빔의 방향이 바뀌게 되면 check를 1로 변화시켜서 다시 루프에 빠지게 만든다.
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
  												if(result->getUnit() == BLOCKMIRROR && status->getBeamdir() != tmpdir)
												{
														result = NULL;
												}
                        break;
                      break;
										 }
                   if(status->getBeamdir() != tmpdir)
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
 												if(result->getUnit() == BLOCKMIRROR && status->getBeamdir() != tmpdir)
												{
														result = NULL;
												}
                        break;
                       break;
											}
                  if(status->getBeamdir() != tmpdir)
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
 												if(result->getUnit() == BLOCKMIRROR && status->getBeamdir() != tmpdir)
												{
														result = NULL;
												}
                        break;
                       break;
										 }
                   if(status->getBeamdir() != tmpdir)
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

void Board::Stun(Cell* _cell) // 스턴상태에 빠졌을 경우를 처리하는 함수
{

    char tmpcol = _cell->getcol() + 49;
    char tmprow = _cell->getrow() + 65;
		cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in stun." << endl;
		_cell->setUnitstun(true);
		_cell->getUni()->setturn(0);

}
/* 빔이 작용하는 셀에 존재하는 유닛의 조건에 따라 어떠한 행동을 취해야 하는지를 정하는 함수 */
Cell* Board::beamCurCell(Cell* _cell)
{
    char tmprow = _cell->getrow() + 65;
    char tmpcol = _cell->getcol() + 49;
    Cell* result = NULL;
		Cell* remove = NULL;
    switch((int)_cell->getUnit()) // 유닛에 따라 나눈다.
    {
        case 0:
            status->setBeam(_cell->getrow(), _cell->getcol(), true);
            break;
        case 1:
					if(status->getattack())
					{
           static_cast<King *>(_cell->getUni())->set_enable(false, _cell->getUnitTeam()); // 왕 죽음
					}
					else
						Stun(_cell);
					result = _cell;
          break;
        case 3:
          switch(_cell->getUnitDir())
          {
              case UP:
                  if(status->getBeamdir() != DOWN)
                  {
											if(status->getattack())
											{
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											}
											else
												Stun(_cell);
											result = _cell;
                  }
                  else
                  {
                      cout << "[System] BlockMirror blocked laser" << endl;
											status->setBeamdir(UP);
											result = _cell;
                  }
                  break;
              case DOWN:
                   if(status->getBeamdir() != UP)
                  {
											if(status->getattack())
											{
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											}
											else
												Stun(_cell);
											result = _cell;
                  }
                  else
                  {
                      cout << "[System] BlockMirror blocked laser" << endl;
											status->setBeamdir(DOWN);
											result = _cell;
                  }
                 break;
              case LEFT:
                   if(status->getBeamdir() != RIGHT)
                  {
											if(status->getattack())
											{
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											}
											else
												Stun(_cell);
											result = _cell;
                  }
                  else
                  {
                      cout << "[System] BlockMirror blocked laser" << endl;
											status->setBeamdir(LEFT);
											result = _cell;
                  }
                 break;
              case RIGHT:
                   if(status->getBeamdir() != LEFT)
                  {
											if(status->getattack())
											{
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											}
											else
												Stun(_cell);
											result = _cell;
                  }
                  else
                  {
                      cout << "[System] BlockMirror blocked laser" << endl;
											status->setBeamdir(RIGHT);
											result = _cell;
                  }
                 break;
          }
          break;
        case 4:
          switch((int)_cell->getUnitDir())
          {
              case 1:
                  if(status->getBeamdir() == DOWN || status->getBeamdir() == LEFT)
                  {
											if(status->getattack())
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											else
												Stun(_cell);
											result = _cell;
                  }
                  else if(status->getBeamdir() == UP)
                      status->setBeamdir(LEFT); // 빔의 방향을 바꾼다. -> 반사시킨다.
                  else
                      status->setBeamdir(DOWN);
                  break;
              case 2:
                   if(status->getBeamdir() == DOWN || status->getBeamdir() == RIGHT)
                  {
                      result = _cell;
											if(status->getattack())
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											else
												Stun(_cell);	
                  }
                  else if(status->getBeamdir() == UP)
                      status->setBeamdir(RIGHT);
                  else
                      status->setBeamdir(DOWN);
                 break;
              case 3:
                   if(status->getBeamdir() == UP || status->getBeamdir() == RIGHT)
                  {
                      result = _cell;
											if(status->getattack())
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											else
												Stun(_cell);	
                  }
                  else if(status->getBeamdir() == DOWN)
                      status->setBeamdir(RIGHT);
                  else
                      status->setBeamdir(UP);
                  break;
              case 4:
                   if(status->getBeamdir() == UP || status->getBeamdir() == LEFT)
                  {
                      result = _cell;
											if(status->getattack())
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											else
												Stun(_cell);	
                  }
                  else if(status->getBeamdir() == DOWN)
                      status->setBeamdir(LEFT);
                  else
                      status->setBeamdir(UP);
                 break;
          }
          break;
        case 5:
          switch((int)_cell->getUnitDir())
          {
              case 1:
                  if(status->getBeamdir() == UP)
                      status->setBeamdir(LEFT);
                  else if(status->getBeamdir() == DOWN)
                      status->setBeamdir(RIGHT);
                  else if(status->getBeamdir() == LEFT)
                      status->setBeamdir(UP);
                  else
                      status->setBeamdir(DOWN);
                  break;
              case 2:
                  if(status->getBeamdir() == UP)
                      status->setBeamdir(RIGHT);
                  else if(status->getBeamdir() == DOWN)
                      status->setBeamdir(LEFT);
                  else if(status->getBeamdir() == LEFT)
                      status->setBeamdir(DOWN);
                  else
                      status->setBeamdir(UP);
                  break;
          }
          break;
        case 7:
          switch((int)_cell->getUnitDir())
          {
              case 1:
                  if(status->getBeamdir() == DOWN || status->getBeamdir() == LEFT)
                  {
											if(status->getattack())
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											else
												Stun(_cell);	
											result = _cell;
                  }
                  else if(status->getBeamdir() == UP)
									{
											remove = launchLaser(_cell);
											if(remove != NULL && status->getattack())
											{				
												remove->setseam(true);
											}
                      status->setBeamdir(LEFT); // 빔의 방향을 바꾼다. -> 반사시킨다.
									}
                  else
									{
											remove = launchLaser(_cell);
 											if(remove != NULL && status->getattack())
											{			
												remove->setseam(true);
											}
                     status->setBeamdir(DOWN);
									}
                  break;
              case 2:
                   if(status->getBeamdir() == DOWN || status->getBeamdir() == RIGHT)
                  {
                      result = _cell;
											if(status->getattack())
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											else
												Stun(_cell);	
                  }
                  else if(status->getBeamdir() == UP)
									{
											remove = launchLaser(_cell);
 											if(remove != NULL && status->getattack())
											{				
												remove->setseam(true);
											}
                     status->setBeamdir(RIGHT);
									}
                  else
									{
											remove = launchLaser(_cell);
 											if(remove != NULL && status->getattack())
											{				
												remove->setseam(true);
											}
                     status->setBeamdir(DOWN);
									}
                 break;
              case 3:
                   if(status->getBeamdir() == UP || status->getBeamdir() == RIGHT)
                  {
                      result = _cell;
											if(status->getattack())
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											else
												Stun(_cell);	
                  }
                  else if(status->getBeamdir() == DOWN)
									{
											remove = launchLaser(_cell);
 											if(remove != NULL && status->getattack())
											{				
												remove->setseam(true);
											}
                     status->setBeamdir(RIGHT);
									}
                  else
									{
											remove = launchLaser(_cell);
 											if(remove != NULL && status->getattack())
											{				
												remove->setseam(true);
											}
                     status->setBeamdir(UP);
									}
                  break;
              case 4:
                   if(status->getBeamdir() == UP || status->getBeamdir() == LEFT)
                  {
                      result = _cell;
											if(status->getattack())
												cout << "[System] Player "<< _cell->getUnitTeam() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
											else
												Stun(_cell);	
                  }
                  else if(status->getBeamdir() == DOWN)
									{
											remove = launchLaser(_cell);
 											if(remove != NULL && status->getattack())
											{				
												remove->setseam(true);
											}
                     status->setBeamdir(LEFT);
									}
                  else
									{
											remove = launchLaser(_cell);
 											if(remove != NULL && status->getattack())
											{				
												remove->setseam(true);
											}
                     status->setBeamdir(UP);
									}
                 break;
          }
          break;

    }
    return result;
}
/* 게임을 초기화한다. */
void Board::initGame()
{
    cout << "[System] Initializing Game..\n";
    cell[0]->setUnit(ATTLASER);
    laser[0] = static_cast<Laser *>(cell[0]->getUni());
    cell[1]->setaccesible(false);
    cell[4]->setUnit(BLOCKMIRROR);
    cell[4]->setUnitDir(DOWN);
    cell[5]->setUnit(KING);
    king[0] = static_cast<King *>(cell[5]->getUni());
    cell[6]->setUnit(BLOCKMIRROR);
    cell[6]->setUnitDir(DOWN);
		cell[7]->setaccesible(false);
		cell[8]->setUnit(STULASER);
		laser[2] = static_cast<Laser *>(cell[8]->getUni());
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
		laser[1] = static_cast<Laser *>(cell[72]->getUni());
		cell[73]->setaccesible(false);
    cell[74]->setUnit(BLOCKMIRROR);
    cell[74]->setUnitTeam(TWO);
    cell[75]->setUnit(KING);
    cell[75]->setUnitTeam(TWO);
    king[1] = static_cast<King *>(cell[75]->getUni());
    cell[76]->setUnit(BLOCKMIRROR);
    cell[76]->setUnitTeam(TWO);
    cell[79]->setaccesible(false);
    cell[80]->setUnit(STULASER);
    cell[80]->setUnitTeam(TWO);
    laser[3] = static_cast<Laser *>(cell[80]->getUni());
    cout << "[System] Complete Initializing.\n";
}

void Board::UnitMove(Cell** curcell) // 유닛이 움직이는 경우를 처리하는 함수
{
				int turn = ongoingTeam;
				string input;
				while(1)
				{
								cout << "Which Position do you want it to move?\n"; // 유닛을 이동시킨다.
								cout << ">> ";
								getline(cin,input);
								cout << "\n";
								if(input.size() != 3 || input.at(0) < 65 || input.at(0) > 105 || (input.at(0) > 73 && input.at(0) < 97) || input.at(1) != 32 || input.at(2) < 49 || input.at(2) > 57)
								{
												cout << "[System] Input Format of position is \"Row Col\".\n";
												cout << "         ex) D 4, e 2, or etc.\n"; 
												continue;
								}
								else
								{
												if(input.at(0) > 96)
																input.at(0) -= 32;
												Cell** movTo = &cell[(input.at(0)-65)*9 + (input.at(2)-49)];
												if((*movTo) == *curcell)
												{
													cout << "You must move your Unit\n";
													continue;
												}
												if((*movTo)->getrow() <= (*curcell)->getrow()+1 && (*movTo)->getrow() >= (*curcell)->getrow()-1 && (*movTo)->getcol() <= (*curcell)->getcol()+1 && (*movTo)->getcol() >= (*curcell)->getcol()-1)
												{
																if((*curcell)->getUnit() != HYPERMIRROR)
																{
																	if((*movTo)->movableTo())
																	{
																				swap(*curcell,*movTo);
																				cout << endl;
																				break;
																	}
																	else
																	{
																				cout << "[System] You can't move your Unit to there\n";
																				continue;
																	}
																}
																else
																{
																	if((*movTo)->getaccesible())
																	{
																				swap(*curcell,*movTo);
																				cout << endl;
																				break;
																	}
																	else
																	{
																				cout << "[System] You can't move your Unit to there\n";
																				continue;
																	}
																}

												}
												else
												{
																cout << "[System] You can't move your Unit to there\n";
																continue;                                   
												}
								}
				}

}

int Board::Rotate_only(Cell** curcell) // 유닛이 회전하는 경우를 처리하는 함수
{
				int check = 0;
				int turn = ongoingTeam;
				string choice;
                        while(1)
                        {
                            enum Direction curdir = (*curcell)->getUnitDir(); 
                            cout << "Do you want it to Rotate?\n"; // 유닛을 회전시킬지 말지를 정한다.
                            cout << "1. OK 2. Cancel\n";
                            cout << ">> ";
                            getline(cin,choice);
                            if(choice.size() != 1)
                            {
                                cout << "[System] Please correct choice!\n";
                                continue;
                            }
                            if(choice.at(0) == 49)
                            {
                                if(curdir == 1)
                                {
                                    (*curcell)->setUnitDir((enum Direction)(curdir + 1));
                                }
                                else
                                {
                                    (*curcell)->setUnitDir((enum Direction)(curdir - 1));
                                }
                                cout << endl;
                                char tmprow = (*curcell)->getrow() + 65;
                                char tmpcol = (*curcell)->getcol() + 49;
                                cout << "[Log] Player"<< turn <<": " << tmprow << " " << tmpcol << " ROTATE\n"; 
                                break;
                            }
                            else if(choice.at(0) == 50)
                            {
                                cout << "[System] Don't rotate!\n";
                                check = 1;
                                break;
                            }
                            else
                            {
                                cout << "[System] You should input 1 or 2\n";
                                continue;
                            }
                        }
	return check;
}
void Board::Rotate(Cell** curcell) // 유닛이 회전하는 경우를 처리하는 함수 2
{
				string choice;
				int turn = ongoingTeam;
				while(1)
				{
								enum Direction curdir = (*curcell)->getUnitDir();
								cout << "Do you want it to Rotate?\n";
								cout << "1. LEFT 2. RIGHT\n";
								cout << ">> ";
								getline(cin,choice);
								if(choice.size() != 1)
								{
												cout << "[System] Please correct choice!\n";
												continue;
								}
								if(choice.at(0) == 49)
								{
												if(curdir != 4)
												{
																(*curcell)->setUnitDir((enum Direction)(curdir + 1));
												}
												else
												{
																(*curcell)->setUnitDir((enum Direction)1);
												}
												cout << endl;
												char tmprow = (*curcell)->getrow() + 65;
												char tmpcol = (*curcell)->getcol() + 49;
												cout << "[Log] Player"<< turn <<": " << tmprow << " " << tmpcol << " ROTATE\n"; 
												break;
								}
								else if(choice.at(0) == 50)
								{
												if(curdir != 1)
												{
																(*curcell)->setUnitDir((enum Direction)(curdir - 1));
												}
												else
												{
																(*curcell)->setUnitDir((enum Direction)4);
												}
												break;
								}
								else
								{
												cout << "[System] You should input 1 or 2\n";
												continue;
								}
				}

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
				status->setattack(true);
				break;
		}
		else
		{
				status->setattack(false);
				break;
		}
		}
    switch((int)ongoingTeam) // 턴을 종료하기 전에 레이저의 현재 방향을 고려하여 빔의 방향을 정하고 레이저를 쏜다.
    {
        case 1:
					if(status->getattack())
					{
            switch((int)laser[0]->get_dir())
            {
                case 1:
                    status->setBeamdir(DOWN);
                    remove = launchLaser(cell[0]);
                    break;
                case 2:
                    status->setBeamdir(RIGHT);
                    remove = launchLaser(cell[0]);
                    break;
            }
					}
					else
					{
            switch((int)laser[2]->get_dir())
            {
                case 1:
                    status->setBeamdir(DOWN);
                    remove = launchLaser(cell[8]);
                    break;
                case 2:
                    status->setBeamdir(LEFT);
                    remove = launchLaser(cell[8]);
                    break;
						}
					}
            break;
        case 2:
					if(status->getattack())
					{
            switch((int)laser[1]->get_dir())
            {
                case 1:
                    status->setBeamdir(UP);
                    remove = launchLaser(cell[72]);
                    break;
                case 2:
                    status->setBeamdir(RIGHT);
                    remove = launchLaser(cell[72]);
                    break;
            }
					}
					else
					{
            switch((int)laser[3]->get_dir())
            {
                case 1:
                    status->setBeamdir(UP);
                    remove = launchLaser(cell[80]);
                    break;
                case 2:
                    status->setBeamdir(LEFT);
                    remove = launchLaser(cell[80]);
                    break;
            }

					}	
            break;
    }
		return remove;
}
/* 게임을 진행하는 메인 함수 */
void Board::startGame()
{

    initGame();
    showBoard();
    while(1)
    {

        int check = 0, i;
        int turn = ongoingTeam;
        Cell** curcell;
        enum UnitType curunit;
        string choice;
        string input;
				Cell* remove;
        cout << "Player " << turn << "'s Turn !\n";
        while(1)
        {
            cout << "Which Unit do you want to control?\n";
            cout << ">> ";
            getline(cin,input);
            if(input.size() != 3 || input.at(0) < 65 || input.at(0) > 105 || (input.at(0) > 73 && input.at(0) < 97) || input.at(1) != 32 || input.at(2) < 49 || input.at(2) > 57)
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
                curunit = (*curcell)->getUnit();
                if(curunit != NONE) // 컨트롤 할 유닛을 선택한다.
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
        switch((int)curunit) // 유닛의 종류에 따라 나눈다.
        {
            case 1: // 왕
                while(1)
                {
                    cout << "What's your Command of this unit?\n"; // 유닛을 어떻게 컨트롤할지 결정한다.
                    cout << "1. Move\n";
                    cout << ">> ";
                    getline(cin,choice);
                    cout << "\n";
                    if(choice.size() != 1||choice.at(0) != 49 )
                    {
                        cout << "[System] Please correct choice!\n";
                        continue;
                    }
                    else
                    {
												UnitMove(curcell);
                        break;
                    }
                }
                break;
            case 2: // 레이저
                while(1)
                {
                    cout << "What's your Command of this unit?\n";
                    cout << "1. Rotate\n";
                    cout << ">> ";
                    getline(cin,choice);
                    if( choice.size() != 1 || choice.at(0) != 49 )
                    {
                        cout << "[System] Please correct choice!\n";
                        continue;
                    }
                    else
                    {
												check = Rotate_only(curcell);
                        break;
                    }
                }
                break;
            case 3: // 블락미러
            case 4: // 삼각미러
						case 7:
                while(1)
                {
                    cout << "What's your Command of this unit?\n";
                    cout << "1. Move 2. Rotate\n";
                    cout << ">> ";
                    getline(cin,choice);
                    if( choice.size() != 1 || (choice.at(0) != 49 && choice.at(0) != 50) )
                    {
                        cout << "[System] Please correct choice!\n";
                        continue;
                    }
                    else if(choice.at(0) == 49)
                    {
												UnitMove(curcell);
                        break;
                    }
                    else
                    {
												Rotate(curcell);
                        break;
                    }
                }
                break;
            case 5: // 하이퍼미러
                while(1)
                {
                    cout << "What's your Command of this unit?\n";
                    cout << "1. Move 2. Rotate\n";
                    cout << ">> ";
                    getline(cin,choice);
                    if(choice.size() != 1 || (choice.at(0) != 49 && choice.at(0) != 50))
                    {
                        cout << "[System] Please correct choice!\n";
                        continue;
                    }
                    else if(choice.at(0) == 49)
                    {
												UnitMove(curcell);
                        break;
                    }
                    else
                    {
											check = Rotate_only(curcell);
                       break;
                    } 
                }
            break;
            case 6: // 레이저
                while(1)
                {
                    cout << "What's your Command of this unit?\n";
                    cout << "1. Rotate\n";
                    cout << ">> ";
                    getline(cin,choice);
                    if( choice.size() != 1 || choice.at(0) != 49 )
                    {
                        cout << "[System] Please correct choice!\n";
                        continue;
                    }
                    else
                    {
												check = Rotate_only(curcell);
                        break;
                    }
                }
                break;
        }
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
		if(remove != NULL && status->getattack())
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
		status->setattack(false);
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
