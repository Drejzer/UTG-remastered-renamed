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

#include "Floor.h"
#include "Creature.h"
#include "Room.h"


using namespace std;


int depth=1;

int roll(int d)
	{
	return d>1?((rand()%d)+1):1;
	}


Player hero("");
Floor mapa;

int main()
	{
	srand(time(NULL));
	depth=1;
	string charname;
	vector<Creature *> test;
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


