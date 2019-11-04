#pragma once
#include "PokemonData.h"

#include <map>

class Pokedex
{
public:

	Pokedex();

	static const int NUM_OF_POKEMON = 650;

	PokemonData* getPokemonData(string name);

	int getNewID() {
		return ID_SETTER++;
	}

	static Pokedex* Instance();

private:

	int ID_SETTER = 0;

	map<string, PokemonData*> pokedexMap;

	static Pokedex* instance;

};

