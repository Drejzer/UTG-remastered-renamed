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

#define VISITED 0b00001
#define EXIT 0b00010
#define COMBAT 0b00100
#define BONUS 0b01000
#define UPGRADE 0b10000

using namespace std;

int depth=1;

int roll(int d)
{
return d>1?((rand()%d)+1):1;
}

class Creature;

class Room
{
protected:
	char flag;
	pair<int,int> position;
public:
	pair<int,int> getpos()
		{
		return position;
		}
	void RoomAction();
	virtual void setflag(char f)
		{
		flag=f;
		}
	virtual void RCombat()=0;
	virtual void RLeave()=0;
	virtual void RLook()=0;
	virtual void RInteract()=0;
};

class Crossroads : public Room
{
public:
	Crossroads(int,int);
	virtual void RCombat();
	virtual void RLeave();
	virtual void RLook();
	virtual void RInteract();
};

class Arena : public Room
{
public:
	stack<Creature *> population;
	Arena(int,int);
	virtual void RCombat();
	virtual void RLeave();
	virtual void RLook();
	virtual void RInteract();
};
class Upgrade : public Room
{
public:
	Upgrade(int,int);
	virtual void RCombat();
	virtual void RLeave();
	virtual void RLook();
	virtual void RInteract();
	};

class Exit : public Room
{
protected:
public:
	stack<Creature *> population;
	Exit(int,int);
	virtual void RCombat();
	virtual void RLeave();
	virtual void RLook();
	virtual void RInteract();
};

class Creature
{
protected:
	string name;
	unsigned long Points;
	long Hitpoints,Atk,Def,Dmg,maxHitpoints;
public:
	virtual int act()=0;
	virtual void attack(Creature *target);
	string getname()
		{
		return name;
		}
	long getPoints()
		{
		return Points;
		}
	long gethp()
		{
		return Hitpoints;
		}
		long getmaxhp()
		{
		return maxHitpoints;
		}
	void modhp(long m)
		{
		Hitpoints+=m;
		if(Hitpoints>maxHitpoints)Hitpoints=maxHitpoints;
		}
	long getatk()
		{
		return Atk;
		}
	long getdef()
		{
		return Def;
		}
	long getdmg()
		{
		return Dmg;
		}
	void modDmg(int m)
		{
		Dmg+=m;
		}
};

class Player : public Creature
	{
	protected:
		long upgradecost;
		pair<int,int> positon;
	public:
		pair<int,int> getRoom()
			{
			return positon;
			}
		Player(string);
		virtual int act();
		void relocate(int,int);
		friend void Room::RoomAction();
		long getupgradecost()
			{
			return upgradecost;
			}
		void raiseupgradecost()
			{
			upgradecost<<=1;
			}
		void modPoints(int m)
			{
			Points+=m;
			}
		void modAtk(int m)
			{
			Atk+=m;
			}
		void modDef(int m)
			{
			Def+=m;
			}
		void modmaxhp(int m)
			{
			maxHitpoints+=m;
			Hitpoints+=m;
			}
	};

Player hero("");

#warning TODO: more enemies

class Training : public Creature
	{
	public:
		virtual int act();
		Training();
	};

class Floor
	{
	public:
		int xsize,ysize;
		vector<vector <Room *> > layout;
		Floor();
	};

Floor mapa;

int main()
	{
	srand(time(NULL));
	depth=1;
	string charname;
	vector<Creature*> test;
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
	cout<<"Genrating Floor"<<depth;
	if(depth-1)
		{
		bool hasexit=0,hasupgrade=0;
		xsize=1+roll(depth+1);
		ysize=3+depth-xsize;
		layout.resize(xsize);
		for(int i=0;i<xsize;++i)
			{
			cout<<".";
			for(int ii=0;ii<ysize;++ii)
				{
				layout[i].push_back(new Crossroads(i,ii));
				#warning TODO: Floor gen
				}
			}
		}
	else
		{
		cout<<".";
		xsize=depth;
		ysize=4;
		layout.resize(1);
		layout[0].push_back((new Crossroads(0,0)));
		cout<<".";
		layout[0].push_back(new Arena(0,1));
		cout<<".";
		layout[0].push_back(new Upgrade(0,2));
		cout<<".";
		layout[0].push_back(new Exit(0,3));
		cout<<".";
		}
	cout<<"\nDone!"<<endl;
	}

void Creature::attack(Creature *target)
	{
	if(getatk()+roll(20)>target->getdef()+roll(20))
		{
		cout<<"Hits";
		target->modhp(-max(Dmg,(long)0));
		}
	else
		{
		cout<<"Misses";
		}
	cout<<endl;
	}

int Training::act()
	{
	cout<<"It just stands there..."<<endl;
	return 0;
	}

int Player::act()
	{
	cout<<"What do you do?"<<endl;
	string action;
	cin>>action;
	switch(action[0])
		{
		case 'a':
		case 'A':
				{
				cin.clear();
				return 1;
				}
		case 'm':
		case 'M':
				{
				cin.clear();
				return 2;
				}
		case 'l':
		case 'L':
				{
				cin.clear();
				return 4;
				}
		case 's':
		case 'S':
				{
				cout<<getname()<<"\nAtk: "<<getatk()<<"\nDef: "<<getdef()<<"\n Dmg: "<<getdmg()<<"\n HP: "<<gethp()<<"/"<<getmaxhp()<<endl;
				cin.clear();
				return 0;
				}
		case 'i':
		case 'I':
				{
				cin.clear();
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

Crossroads::Crossroads(int x,int y)
	{
	position=pair<int,int>(x,y);
	}

Arena::Arena(int x,int y)
	{
	position=pair<int,int>(x,y);
	flag=COMBAT;
	for(int i=roll(depth);i>0;--i)
		{
      switch((depth>1)?roll(3):0)
			{
			case 0:
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
			break;
			}
		}
	}
void Crossroads::RLeave()
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

void Arena::RCombat()
{
if(!population.empty())
	{
	hero.attack(population.top());
	if(population.top()->gethp()<0)
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
else cout<<"There is nothing to attack!"<<endl;
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
	cout<<"What aspect do you want to enchance?\nPrecision(+atk)\nReflexes(+def)\nStrenght(+dmg)\nToughness(+HP)"<<endl;
	string levelup;
	cin>>levelup;
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
	if(population.top()->gethp()<0)
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
else cout<<"There is nothing to attack!"<<endl;
}

void Exit::RInteract()
{
cout<<"You delve deeper into the abyss..."<<endl;
depth++;
mapa=Floor();
}