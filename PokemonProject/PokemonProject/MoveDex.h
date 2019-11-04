#pragma once
#include <string>
#include <map>
#include "MoveData.h"

class MoveDex
{
public:

	MoveDex();

	static const int NUM_OF_MOVES = 559;

	MoveData* getMoveData(string name);

	static MoveDex* Instance();

private:
	map<string, MoveData*> moveMap;

	static MoveDex* instance;

};



