#include "TypeData.h"
#include <iostream>

const float TypeData::typeEffectivenessLookupTable[18][18] = {
	{	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1					},
	{	1,1,1,1,1,1,0.5,1,0,0.5,1,1,1,1,1,1,1,1				},
	{	1,2,1,0.5,0.5,1,2,0.5,0,2,1,1,1,1,0.5,2,1,2			},
	{	1,1,2,1,1,1,0.5,2,1,0.5,1,1,2,0.5,1,1,1,1			},
	{	1,1,1,1,0.5,0.5,0.5,1,0.5,0,1,1,2,1,1,1,1,1			},
	{	1,1,1,0,2,1,2,0.5,1,2,2,1,0.5,2,1,1,1,1				},
	{	1,1,0.5,2,1,0.5,1,2,1,0.5,2,1,1,1,1,2,1,1			},
	{	1,1,0.5,0.5,0.5,1,1,1,0.5,0.5,0.5,1,2,1,2,1,1,2		},
	{	1,0,1,1,1,1,1,1,2,1,1,1,1,1,2,1,1,0.5				},
	{	1,1,1,1,1,1,2,1,1,0.5,0.5,0.5,1,0.5,1,2,1,1			},
	{	1,1,1,1,1,1,0.5,2,1,2,0.5,0.5,2,1,1,2,0.5,1			},
	{	1,1,1,1,1,2,2,1,1,1,2,0.5,0.5,1,1,1,0.5,1			},
	{	1,1,1,0.5,0.5,2,2,0.5,1,0.5,0.5,2,0.5,1,1,1,0.5,1	},
	{	1,1,1,2,1,0,1,1,1,1,1,2,0.5,0.5,1,1,0.5,1			},
	{	1,1,2,1,2,1,1,1,1,0.5,1,1,1,1,0.5,1,1,0				},
	{	1,1,1,2,1,2,1,1,1,0.5,0.5,0.5,2,1,1,0.5,2,1			},
	{	1,1,1,1,1,1,1,1,1,0.5,1,1,1,1,1,1,2,1				},
	{	1,1,0.5,1,1,1,1,1,2,1,1,1,1,1,2,1,1,0.5				}
	
};
const string TypeData::typeNames[] = {
	"---",
	"NORMAL",
	"FIGHTING",
	"FLYING",
	"POISON",
	"GROUND",
	"ROCK",
	"BUG",
	"GHOST",
	"STEEL",
	"FIRE",
	"WATER",
	"GRASS",
	"ELECTRIC",
	"PSYCHIC",
	"ICE",
	"DRAGON",
	"DARK"
};
float TypeData::getTypeEffectiveness(PokemonType attacker, PokemonType defender) {

	int i = (int) attacker;
	int j = (int) defender;

	return TypeData::typeEffectivenessLookupTable[i][j];


}
/*
float TypeData::getTypeEffectiveness(PokemonType attacker, Pokemon* defender)
{
	int i = (int)attacker;
	int j1 = (int)defender->getPokeType1();
	int j2 = (int)defender->getPokeType2();

	return TypeData::typeEffectivenessLookupTable[i][j1] *
		TypeData::typeEffectivenessLookupTable[i][j2];

}
*/
string TypeData::getStringFromType(PokemonType type) {
	int i = (int) type;
	return TypeData::typeNames[i];
}

PokemonType TypeData::getTypeFromString(string name)
{


	for (int i = 1; i < 18; i++) {
		if (typeNames[i] == (name)) {
			return (PokemonType) i;
		}
	}

	return PokemonType::NO_TYPE;

}
