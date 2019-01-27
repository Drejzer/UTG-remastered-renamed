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
#include "Creature.h"
#include "Floor.h"

using namespace std;

Floor::Floor()
	{
	cout<<"Genrating Floor"<<depth;
	if(depth-1)
		{
		xsize=1+roll(depth+1);
		ysize=3+depth-xsize;
		int exity=-1+roll(ysize),exitx=-1+roll(xsize),ux=roll(xsize-2),uy=roll(ysize-2);
		while(exitx==ux&&exity==uy)
			{
			(ysize-2)==0?ux=roll(xsize -2):uy=roll(ysize-2);
			}
		layout.resize(xsize);
		for(int i=0; i<xsize; ++i)
			{
			cout<<".";
			for(int ii=0; ii<ysize; ++ii)
				{
				if(i==exitx&&ii==exity)
					{
					layout[i].push_back(new Exit(i,ii));
					}
				else if(i==ux&&ii==uy)
					{
					layout[i].push_back(new Upgrade(i,ii));
					}
				else
					{
					switch(roll(6))
						{
						case 1:
						case 6:
								{
								layout[i].push_back(new Arena(i,ii));
								break;
								}
						default:
								{
								layout[i].push_back(new Crossroads(i,ii));
								break;
								}
						}
					}
				if(roll(100)>95)
					{
					layout[i][ii]->setflag(layout[i][ii]->getflag()&BONUS);
					}
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
