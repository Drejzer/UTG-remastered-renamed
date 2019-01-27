#ifndef ROOM_HDR
#define ROOM_HDR

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

#define VISITED 0b00001
#define EXIT 0b00010
#define COMBAT 0b00100
#define BONUS 0b01000
#define UPGRADE 0b10000


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
		char getflag(){return flag;}
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


#endif // ROOM_HDR
