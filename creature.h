#ifndef CREATURE_HDR
#define CREATURE_HDR

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

class creature
{
protected:
long HP;
char token;
int  posx,posy;
public:
int getposx();
int getposy();
};


