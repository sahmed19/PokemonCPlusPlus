#pragma once
#include <string>
#include "TypeData.h"
#include "PokemonData.h"

using namespace std;

class MoveData
{
public:

	MoveData(int _id, string _name, string _internalName,
		string _functionCode, int _basePower, string _type, 
		string _category, int _accuracy, int _PP,
		int _additionalEffectChance, string _target,
		int _priority, char* _flags, int _num_flags, 
		string _description);

	inline int getID() const { return id; }
	inline string getName() const { return name; }
	inline string getInternalName() const { return internalName; }

	inline string getFunctionCode() const { return functionCode; }

	inline string getTarget() const { return target; }

	inline string getCategory() const {return category; }
	inline int getBasePower() const {return basePower; }
	inline int getAccuracy() const {return accuracy; }
	inline int getTotalPP() const {return PP; }
	inline int getAdditionalEffectChance() const { return additionalEffectChance; }

	inline int getPriority() const { return priority; }

	PokemonType getMoveType() const { return pokemonType; }

	inline bool hasFlag(char c) const;
	inline bool hasFlags(char* c, int count) const;

	inline bool isSpecial() const { return category == "Special"; }
	inline bool isStatus() const { return category == "Status"; }

	void print() const;

private:
	const int id;
	const string name;
	const string internalName;
	const string description;
	const string functionCode;


	/*
	00 - Single Pokémon other than the user
	01 - No target(i.e.Counter, Metal Burst, Mirror Coat, Curse)
	02 - Single opposing Pokémon selected at random(i.e.Outrage, Petal Dance, Thrash, Uproar)
	04 - All opposing Pokémon
	08 - All Pokémon other than the user
	10 - User
	20 - Both sides(e.g.Sunny Day, Trick Room)
	40 - User's side (e.g. Light Screen, Mist)
	80 - Opposing side(i.e.Spikes, Toxic Spikes, Stealth Rocks)
	100 - User's partner (i.e. Helping Hand)
	200 - Single Pokémon on user's side (i.e. Acupressure)
	400 - Single opposing Pokémon(i.e.Me First)
	800 - Single opposing Pokémon directly opposite of user
	*/
	const string target;
	
	/*
	a - The move makes physical contact with the target.
	b - The target can use Protect or Detect to protect itself from the move.
	c - The target can use Magic Coat to redirect the effect of the move.Use this flag if the move deals no damage but causes a negative effect on the target. (Flags c and d are mutually exclusive.)
	d - The target can use Snatch to steal the effect of the move. Use this flag for most moves that target the user. (Flags c and d are mutually exclusive.)
	e - The move can be copied by Mirror Move.
	f - The move has a 10% chance of making the opponent flinch if the user is holding a King's Rock/Razor Fang. Use this flag for all damaging moves that don't already have a flinching effect.
	g - If the user is frozen, the move will thaw it out before it is used.
	h - The move has a high critical hit rate.
	i - The move is a biting move (powered up by the ability Strong Jaw).
	j - The move is a punching move(powered up by the ability Iron Fist).
	k - The move is a sound-based move.
	l - The move is a powder-based move (Grass-type Pokémon are immune to them).
	m - The move is a pulse-based move(powered up by the ability Mega Launcher).
	n - The move is a bomb-based move(resisted by the ability Bulletproof).
	*/
	const char* flags;
	const int num_flags;

	const string category;
	const int basePower;
	const int accuracy;
	const int PP;
	const int additionalEffectChance;

	const int priority;

	const PokemonType pokemonType;
};

