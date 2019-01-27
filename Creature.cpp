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
#include "Floor.h"
#include "Room.h"

using namespace std;

void Creature::attack(Creature *target)
	{
	if(getatk()+roll(20)>target->getdef()+roll(20))
		{
		cout<<getname()<<" Hits";
		target->modhp(-max(Dmg,(long)0));
		}
	else
		{
		cout<<getname()<<" Misses";
		}
	cout<<endl;
	}

int Training::act()
	{
	cout<<"It just stands there..."<<endl;
	return 0;
	}

int Placeholder1::act()
	{
	attack(&hero);
	return 1;
	}

void Placeholder1::attack(Creature *target)
	{
	cout<<getname()<<" attacks wildly and";
	if(getatk()+roll(20)>target->getdef()+roll(20))
		{
		cout<<getname()<<" Hits";
		target->modhp(-max(Dmg,(long)0));
		}
	else
		{
		cout<<getname()<<" Misses";
		}
	if(getatk()-7+roll(20)>target->getdef()+roll(20))
		{
		cout<<getname()<<" and Hits";
		target->modhp(-max(Dmg,(long)0));
		}
	else
		{
		cout<<getname()<<"and Misses";
		}
	cout<<endl;
	}

int Player::act()
	{
	cout<<"What do you do?"<<endl;
	string action;
	if((cin>>action).eof())
		{
		hero.Hitpoints=-1;
		return -1;
		}
	switch(action[0])
		{
		case 'a':
		case 'A':
				{
				cin.clear();
				cin.ignore(100,'\n');
				return 1;
				}
		case 'm':
		case 'M':
				{
				cin.clear();
				cin.ignore(100,'\n');
				return 2;
				}
		case 'l':
		case 'L':
				{
				cin.clear();
				cin.ignore(100,'\n');
				return 4;
				}
		case 's':
		case 'S':
				{
				cout<<getname()<<"\nAtk: "<<getatk()<<"\nDef: "<<getdef()<<"\n Dmg: "<<getdmg()<<"\n HP: "<<gethp()<<"/"<<getmaxhp()<<endl;
				cin.clear();
				cin.ignore(100,'\n');
				return 0;
				}
		case 'i':
		case 'I':
				{
				cin.clear();
				cin.ignore(100,'\n');
				return 3;
				}
		case 'K':
				{
				if(action=="KILL")
					{
					cin>>action;
					if(action=="MYSELF")
						{
						cin.clear();
						cin.ignore(100,'\n');
						cout<<hero.getname()<<" commited sucide."<<endl;
						hero.Hitpoints=-1;
						return -1;
						}
					}
				}
		default:
				{
				cout<<"The options are:\n attack\n move\n look\n status\n interact"<<endl;
				cin.clear();
				cin.ignore(100,'\n');
				return 0;
				}
		}
	}

void Player::relocate(int x,int y)
	{
	positon=pair<int,int>(x,y);
	}


Player::Player(string charname)
	{
	name=charname;
	Atk=roll(3)-1;
	Def=roll(3)-1;
	Dmg=1;
	Points=0;
	maxHitpoints=roll(4)+1;
	Hitpoints=maxHitpoints;
	positon.first=0;
	positon.second=0;
	upgradecost=1;
	}

Training::Training()
	{
	name = "Training Dummy";
	Atk=-1000;
	Def=-5;
	maxHitpoints=2;
	Hitpoints=2;
	Points=1;
	Dmg=0;
	}

Placeholder1::Placeholder1()
	{
	name="Placeholder1 ";
	Atk=0+roll(depth/2);
	Def=0+roll(depth/2);
	maxHitpoints=1+roll(depth/2);
	Dmg=1+roll(depth/5);
	Hitpoints=maxHitpoints;
	Points=2+roll(depth/4);
	}


