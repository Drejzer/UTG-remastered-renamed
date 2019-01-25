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

#define EXIT 1
#define COMBAT 2
#define BONUS 4
#define UPGRADE 8

using namespace std;

int depth=0;

int roll(int d)
	{
	return d>1?((rand()%d)+1):0;
	}

class Room
	{
	protected:
		char flag;
	public:
		pair<int,int> position;
		void RoomAction();
		void setflag();
	};

class Crossroads : public Room
	{
	public:
	Crossroads(int,int);
	};

class Arena : public Room
	{
	public:
	Arena(int,int);
	#warning TODO: combat room
	};

class Upgrade : public Room
	{
	public:
	Upgrade(int,int);
	#warning TODO: upgrade room
	};


class Creature
	{
	protected:
		string name;
		long Hitpoints,Atk,Def,Dmg;
	public:
		virtual int act()=0;
		virtual void attack(Creature *target);
		string getname(){return name;}
		long gethp(){return Hitpoints;}
		long getatk(){return Atk;}
		long getdef(){return Def;}
		long getdmg(){return Dmg;}
	};

class Player : public Creature
	{
	protected:
		long Points;
		long upgradecost;
		pair<int,int> positon;
	public:
		pair<int,int> getRoom(){return positon;}
		Player(string);
		virtual int act();
		void relocate(int,int);
		friend void Room::RoomAction();
	};

Player hero("");

class Enemy : public Creature
	{
	public:
		int loot;
	};

	#warning TODO: more enemies

class Training : public Enemy
	{
	public:
	int act();
	};

class Floor
	{
	public:
		int xsize,ysize;
		vector<vector <Room*> > layout;
		stack<Creature *> population;
		Floor();
	};

Floor mapa;

int main()
	{
	srand(time(NULL));
	depth=1;
	string charname;
	mapa=Floor();
	cout<<"Please, input your Character's name:"<<endl;
	getline(cin,charname);
	hero=Player(charname);
   while(hero.gethp()>0)
		{
		mapa.layout.at(hero.getRoom().first).at(hero.getRoom().second)->RoomAction();
		}
	cout<<"Thus "<<hero.getname()<<"'s existence came to an end..."<<endl;
	return 0;
	}

Floor::Floor()
{
if(depth-1)
	{
	}
else
	{
	xsize=depth;
	ysize=4;
	layout.resize(1);
	layout[0].push_back((Room*)(new Crossroads(0,0)));
	layout[0].push_back((Room*)(new Arena(0,1)));
	layout[0].push_back((Room*)(new Upgrade(0,2)));
	layout[0].push_back((Room*)(new Crossroads(0,3)));
	}
}

void Creature::attack(Creature *target)
	{
	if(Atk+roll(20)>target->Def+roll(20))
		{
		cout<<"Hits";
		target->Hitpoints-=max(Dmg,(long)0);
		}
	else
		{
		cout<<"Misses";
		}
	}

int Training::act()
	{
	cout<<"It can't do anything..."<<endl;
	return 0;
	}

int Player::act()
	{
	cout<<"What do you do?"<<endl;
	string action;
	cin>>action;
	switch(action[0])
		{
		case 'm':
		case 'M':
			{
			return 2;
			}
		default:
			{
			cout<<"The options are:\n attack\n move\n look\n status\n interact"<<endl;
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
	Atk=roll(2)-1;
	Def=roll(2)-1;
	Points=0;
	Hitpoints=roll(4)+1;
	positon.first=0;
	positon.second=0;
	upgradecost=1;
	}

Crossroads::Crossroads(int x,int y)
{
position=pair<int,int>(x,y);
}

Arena::Arena(int x,int y)
{
position=pair<int,int>(x,y);
}

Upgrade::Upgrade(int x,int y)
{
position=pair<int,int>(x,y);
}

void Room::RoomAction()
	{
	switch(hero.act())
		{
		case 1:
			{
			if(!(flag&COMBAT))
				{
				cout<<"There is nothing to attack!"<<endl;
				}
			else
				{}
			}
		case 2:
			{
			if(!(flag&COMBAT))
				{
				cout<<"North, West, South or East?"<<endl;
				string dawae;
				cin>>dawae;
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
							cout<<"It would be a good idea...\n BUT THERE IS NO PASSAGE!"<<endl;
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
			else
				{
				cout<<"There is no way out of this fight!"<<endl;
				mapa.population.top()->act();
				}
			}
		case 0:
			{
			cout<<"Sooo...."<<endl;
			break;
			}
		}
	RoomAction();
	}
