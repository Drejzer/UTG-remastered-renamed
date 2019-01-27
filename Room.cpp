#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <thread>
#include <ctime>
#include <random>
#include <cstdlib>
#include <cmath>
#include <stack>

#include "Creature.h"
#include "Room.h"
#include "Floor.h"

using namespace std;

Crossroads::Crossroads(int x,int y)
	{
	position=pair<int,int>(x,y);
	}

Arena::Arena(int x,int y)
	{
	position=pair<int,int>(x,y);
	flag=COMBAT;
	for(int i=roll(depth); i>0; --i)
		{
		switch((depth>1)?roll(3):0)
			{
			case 0:
					{
					population.push(new Training);
					break;
					}
			case 1:
					{
					population.push(new Placeholder1);
					break;
					}
			default:
					{
					population.push(new Training);
					}
			}
		}
	}

Upgrade::Upgrade(int x,int y)
	{
	position=pair<int,int>(x,y);
	}

Exit::Exit(int x,int y)
	{
	position=pair<int,int>(x,y);
	flag=COMBAT|EXIT;
	for(int i=roll(depth); i>0; --i)
		{
		switch((depth>1)?roll(3):0)
			{
			case 0:
					{
					population.push(new Training);
					break;
					}
			case 1:
					{
					population.push(new Placeholder1);
					break;
					}
			default:
					{
					population.push(new Training);
					}
			}
		}
	}

void Room::RoomAction()
	{
	switch(hero.act())
		{
		case 1:
				{
				RCombat();
				break;
				}
		case 2:
				{
				RLeave();
				break;
				}
		case 3:
				{
				RInteract();
				break;
				}
		case 4:
				{
				RLook();
				}
		case 0:
				{
				cout<<"Sooo...."<<endl;
				break;
				}
		case -1:
				{
				cout<<"Huh... that was unexpected"<<endl;
				break;
				}
		}
	}
void Crossroads::RLeave()
	{
	cout<<"North, West, South or East?"<<endl;
	string dawae;
	if((cin>>dawae).eof())
		{
		hero.modhp(-hero.getmaxhp());
		return;
		}
	switch(dawae[0])
		{
		case 'N':
		case 'n':
				{
				if(mapa.ysize>position.second+1)
					{
					cout<<"Northwards, then!"<<endl;
					hero.relocate(position.first,position.second+1);
					}
				else
					{
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
					}
				return;
				}
		case 'W':
		case 'w':
				{
				if(0<=position.first-1)
					{
					cout<<"Westwards, then!"<<endl;
					hero.relocate(position.first,position.second+1);
					}
				else
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
				return;
				}
		case 'S':
		case 's':
				{
				if(0<=position.second-1)
					{
					cout<<"Southwards, then!"<<endl;
					hero.relocate(position.first,position.second+1);
					}
				else
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
				return;
				}
		case 'E':
		case 'e':
				{
				if(mapa.xsize>position.first+1)
					{
					cout<<"Eastwards, then!"<<endl;
					hero.relocate(position.first+1,position.second);
					}
				else
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
				return;
				}
		default:
				{
				cout<<"You mean WHERE?"<<endl;
				}
		}
	cin.clear();
	cin.ignore(100,'\n');
	}

void Crossroads::RCombat()
	{
	cout<<"There is nothing to attack!"<<endl;
	}

void Crossroads::RInteract()
	{
	cout<<"There is nothing to do here, move along."<<endl;
	}

void Crossroads::RLook()
	{
	if(flag&BONUS)
		{
		cout<<"There seems to be something hidden away here..."<<endl;
		switch(roll(20))
			{
			case 20:
					{
					if(roll(100)>75)
						{
						hero.modmaxhp(1);
						cout<<"A healthy... whatever. Got more HP"<<endl;
						break;
						}
					hero.modPoints(1);
					}
			default:
					{
					cout<<"Sweet Points!"<<endl;
					hero.modPoints(1);
					break;
					}
			}
		flag^=BONUS;
		}
	else
		{
		cout<<"meh, nothing of note here"<<endl;
		}
	}

void Arena::RCombat()
	{
	if(!population.empty())
		{
		hero.attack(population.top());
		if(population.top()->gethp()<=0)
			{
			cout<<population.top()->getname()<<" has been vanquished!"<<endl;
			hero.modPoints(population.top()->getPoints());
			population.pop();
			if(population.empty())
				{
				flag^=COMBAT;
				return;
				}
			}
		}
	else
		cout<<"There is nothing to attack!"<<endl;
	}

void Arena::RLeave()
	{
	if(flag&COMBAT)
		{
		cout<<"There is no way to leave with enemies present!"<<endl;
		population.top()->act();
		}
	else
		{
		cout<<"North, West, South or East?"<<endl;
		string dawae;
		if((cin>>dawae).eof())
			{
			hero.modhp(-hero.getmaxhp());
			return;
			}
		switch(dawae[0])
			{
			case 'N':
			case 'n':
					{
					if(mapa.ysize>position.second+1)
						{
						cout<<"Northwards, then!"<<endl;
						hero.relocate(position.first,position.second+1);
						}
					else
						{
						cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
						}
					return;
					}
			case 'W':
			case 'w':
					{
					if(0<=position.first-1)
						{
						cout<<"Westwards, then!"<<endl;
						hero.relocate(position.first,position.second+1);
						}
					else
						cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
					return;
					}
			case 'S':
			case 's':
					{
					if(0<=position.second-1)
						{
						cout<<"Southwards, then!"<<endl;
						hero.relocate(position.first,position.second+1);
						}
					else
						cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
					return;
					}
			case 'E':
			case 'e':
					{
					if(mapa.xsize>position.first+1)
						{
						cout<<"Eastwards, then!"<<endl;
						hero.relocate(position.first+1,position.second);
						}
					else
						cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
					return;
					}
			default:
					{
					cout<<"You mean WHERE?"<<endl;
					}
			}
		}
	}

void Arena::RLook()
	{
	if(flag&COMBAT)
		{
		cout<<"Locked pathways, you, ground...\n and "<<population.top()->getname()<<" trying to kill you."<<endl;
		population.top()->act();
		return;
		}
	else
		{
		if(flag&BONUS)
			{
			cout<<"There seems to be something hidden away here..."<<endl;
			switch(roll(20))
				{
				case 20:
						{
						if(roll(100)>75)
							{
							hero.modhp(1);
							cout<<"A healthy... whatever. Got more HP"<<endl;
							break;
							}
						hero.modPoints(1);
						}
				default:
						{
						cout<<"Sweet Points!"<<endl;
						hero.modPoints(1);
						break;
						}
				}
			flag^=BONUS;
			}
		else
			{
			cout<<"meh, nothing of note here"<<endl;
			}
		}
	}

void Arena::RInteract()
	{
	cout<<"There is nothing to do here, move along."<<endl;
	}

void Upgrade::RLook()
	{
	cout<<"Well, a place to upgrade your stats... what did you expect?"<<endl;
	if(flag&BONUS)
		{
		cout<<"There seems to be something hidden away here..."<<endl;
		switch(roll(20))
			{
			case 20:
					{
					if(roll(100)>75)
						{
						hero.modhp(1);
						cout<<"A healthy... whatever. Got more HP"<<endl;
						break;
						}
					hero.modPoints(1);
					}
			default:
					{
					cout<<"Sweet Points!"<<endl;
					hero.modPoints(1);
					break;
					}
			}
		flag^=BONUS;
		}
	else
		{
		cout<<"meh, nothing else of note here"<<endl;
		}
	}

void Upgrade::RLeave()
	{
	cout<<"North, West, South or East?"<<endl;
	string dawae;
	if((cin>>dawae).eof())
		{
		hero.modhp(-hero.getmaxhp());
		return;
		}
	switch(dawae[0])
		{
		case 'N':
		case 'n':
				{
				if(mapa.ysize>position.second+1)
					{
					cout<<"Northwards, then!"<<endl;
					hero.relocate(position.first,position.second+1);
					}
				else
					{
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
					}
				return;
				}
		case 'W':
		case 'w':
				{
				if(0<=position.first-1)
					{
					cout<<"Westwards, then!"<<endl;
					hero.relocate(position.first,position.second+1);
					}
				else
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
				return;
				}
		case 'S':
		case 's':
				{
				if(0<=position.second-1)
					{
					cout<<"Southwards, then!"<<endl;
					hero.relocate(position.first,position.second+1);
					}
				else
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
				return;
				}
		case 'E':
		case 'e':
				{
				if(mapa.xsize>position.first+1)
					{
					cout<<"Eastwards, then!"<<endl;
					hero.relocate(position.first+1,position.second);
					}
				else
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
				return;
				}
		default:
				{
				cout<<"You mean WHERE?"<<endl;
				}
		}
	}

void Upgrade::RCombat()
	{
	cout<<"There is nothing to attack!"<<endl;
	}

void Upgrade::RInteract()
	{
	if(hero.getupgradecost()<0)
		{
		cout<<"You have reached the apex of awesomeness.\nNothing to gain here"<<endl;
		}
	else if(hero.getPoints()<hero.getupgradecost())
		{
		cout<<"Gather more points!"<<endl;
		}
	else
		{
		cout<<"What aspect do you want to enchance?\nPrecision(+atk)\nReflexes(+def)\nStrength(+dmg)\nToughness(+HP)"<<endl;
		string levelup;
		if((cin>>levelup).eof())
			{
			hero.modhp(-hero.getmaxhp());
			return;
			}
		switch(levelup[0])
			{
			case 'p':
			case 'P':
					{
					cout<<"Your aim got better!"<<endl;
					hero.modAtk(roll(depth)/2+1);
					break;
					}
			case 'r':
			case 'R':
					{
					cout<<"You are better at not getting hit!"<<endl;
					hero.modDef(roll(depth)/2+1);
					break;
					}
			case 's':
			case 'S':
					{
					cout<<"You deal MOAR DAMAGES!"<<endl;
					hero.modDmg(roll(depth)/2+1);
					}
			case 't':
			case 'T':
					{
					cout<<"You are harder to kill!"<<endl;
					hero.modmaxhp(roll(depth)+1);
					}
			}
		hero.raiseupgradecost();
		}
	}

void Exit::RLook()
	{
	if(!population.empty())
		cout<<"A passage leading deeper!\n ...blocked by an enemy"<<endl;
	else if(flag&BONUS)
		{
		cout<<"There seems to be something hidden away here..."<<endl;
		switch(roll(20))
			{
			case 20:
					{
					if(roll(100)>75)
						{
						hero.modhp(1);
						cout<<"A healthy... whatever. Got more HP"<<endl;
						break;
						}
					hero.modPoints(1);
					}
			default:
					{
					cout<<"Sweet Points!"<<endl;
					hero.modPoints(1);
					break;
					}
			}
		flag^=BONUS;
		}
	else
		{
		cout<<"meh, nothing else of note here"<<endl;
		}
	}

void Exit::RLeave()
	{
	cout<<"North, West, South or East?"<<endl;
	string dawae;
	if((cin>>dawae).eof())
		{
		hero.modhp(-hero.getmaxhp());
		return;
		}
	switch(dawae[0])
		{
		case 'N':
		case 'n':
				{
				if(mapa.ysize>position.second+1)
					{
					cout<<"Northwards, then!"<<endl;
					hero.relocate(position.first,position.second+1);
					}
				else
					{
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
					}
				return;
				}
		case 'W':
		case 'w':
				{
				if(0<=position.first-1)
					{
					cout<<"Westwards, then!"<<endl;
					hero.relocate(position.first,position.second+1);
					}
				else
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
				return;
				}
		case 'S':
		case 's':
				{
				if(0<=position.second-1)
					{
					cout<<"Southwards, then!"<<endl;
					hero.relocate(position.first,position.second+1);
					}
				else
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
				return;
				}
		case 'E':
		case 'e':
				{
				if(mapa.xsize>position.first+1)
					{
					cout<<"Eastwards, then!"<<endl;
					hero.relocate(position.first+1,position.second);
					}
				else
					cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
				return;
				}
		default:
				{
				cout<<"You mean WHERE?"<<endl;
				}
		}
	if(flag&COMBAT)
		{
		cout<<"As you try to flee the enemy attacks!"<<endl;
		population.top()->act();
		}
	}

void Exit::RCombat()
	{
	if(!population.empty())
		{
		hero.attack(population.top());
		if(population.top()->gethp()<=0)
			{
			cout<<population.top()->getname()<<" has been vanquished!"<<endl;
			hero.modPoints(population.top()->getPoints());
			population.pop();
			if(population.empty())
				{
				flag^=COMBAT;
				return;
				}
			}
		}
	else
		cout<<"There is nothing to attack!"<<endl;
	}

void Exit::RInteract()
	{
	if(population.empty())
		{
		cout<<"You delve deeper into the abyss..."<<endl;
		depth++;
		mapa=Floor();
		hero.relocate(0,0);
		}
	else
		{
		cout<<population.top()->getname()<<" bolcks the way"<<endl;
		population.top()->act();
		}
	}
