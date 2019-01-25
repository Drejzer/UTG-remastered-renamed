#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <pair>
#include <thread>
#include "Floor.h"

using namespace std;

class creature
{
protected:
string name;
long HP,maxHP,Atk,Def,Dmg;
bool defend;
pair<int,int> curRoom;
public:
pair<int,int> getroom();
virtual void act();
void attack(creature *target);
void defend();
};

class Player : public creature
{
virtual void act();
void relocate();
};

class Enemy : public creature
{
virtual void act()
   (attack((Player*)Floor.population[0]);)
};

class Room
{
#define SECRET 1
#define ENEMY 2
#define LOOT 4
#define BUFF 8
public:
pair<int,int> roompos;
char flags;
Room(pair<int,int> pos,);
}


class Floor
{
public:
int xsize,ysize;
vector<vector <Room> > layout;
vector <bool> xpass,ypass;
vector<creature*> population;
friend void populate();
};




int main()
{
return 0;
}
