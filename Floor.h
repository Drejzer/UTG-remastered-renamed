#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED

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

int roll(int);

extern int depth;


class Floor
	{
	public:
		int xsize,ysize;
		vector<vector <Room *> > layout;
		Floor();
	};

	extern Floor mapa;

#endif // FLOOR_H_INCLUDED
