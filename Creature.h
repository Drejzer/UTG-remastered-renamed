#ifndef CREATURE_HDR
#define CREATURE_HDR

using namespace std;

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

#include "Room.h"

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
			if(Hitpoints>maxHitpoints)
				Hitpoints=maxHitpoints;
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

class Training : public Creature
	{
	public:
		virtual int act();
		Training();
	};

class Placeholder1 : public Creature
	{
	public:
		virtual int act();
		virtual void attack(Creature *target);
		Placeholder1();
	};
	#warning TODO: more enemies

extern Player hero;

#endif
