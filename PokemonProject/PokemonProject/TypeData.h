#pragma once
#include <string>

enum PokemonType {
	NO_TYPE,
	NORMAL,
	FIGHTING,
	FLYING,
	POISON,
	GROUND,
	ROCK,
	BUG,
	GHOST,
	STEEL,
	FIRE,
	WATER,
	GRASS,
	ELECTRIC,
	PSYCHIC,
	ICE,
	DRAGON,
	DARK
};

using namespace std;

struct TypeData
{

public:
	static float getTypeEffectiveness(PokemonType attacker, PokemonType defender);
	//static float getTypeEffectiveness(PokemonType attacker, Pokemon* defender);
	static string getStringFromType(PokemonType type);
	static string getStringFromType(int type) { 
		return getStringFromType((PokemonType)type); 
	}


	static PokemonType getTypeFromString(string name);

private:
	TypeData() {}

	static const float typeEffectivenessLookupTable[18][18];
	static const string typeNames[];
};