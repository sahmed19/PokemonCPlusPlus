#pragma once
#include <iostream>
#include "PokemonData.h"
#include "MoveData.h"

using namespace std;


enum Nature {
	HARDY,
	LONELY,
	BRAVE,
	ADAMANT,
	NAUGHTY,
	BOLD,
	DOCILE,
	RELAXED,
	IMPISH,
	LAX,
	TIMID,
	HASTY,
	SERIOUS,
	JOLLY,
	NAIVE,
	MODEST,
	MILD,
	QUIET,
	BASHFUL,
	RASH,
	CALM,
	GENTLE,
	SASSY,
	CAREFUL,
	QUIRKY
};

struct NatureData {
	
	static float getNatureStatMultiplier(int _nature, int _stat);
	static float getNatureStatMultiplier(Nature _nature, Stat _stat)
	{ 
		return getNatureStatMultiplier((int)_nature, (int)_stat); 
	}
	static string NatureToString(Nature _nature);
	static const float natureMultiplierLookupTable[25][6];
	static Nature getRandomNature();
};

class Pokemon
{
public:
//Constructors

	//General constructor with all details.
	Pokemon(PokemonData* _pokemonData, 
		Gender _gender, Nature _nature, 
		bool _shiny, bool _pokerus,
		string _ability,
		
		int _IV_HP, 
		int _IV_ATK, int _IV_DEF, 
		int _IV_SPA, int _IV_SPD,
		int _IV_SPE,
		
		string _nickname, int _level,
		
		int _EV_HP,
		int _EV_ATK, int _EV_DEF,
		int _EV_SPA, int _EV_SPD,
		int _EV_SPE,
		
		MoveData* _moves[4],
		Status _status
	
	);

	//Common trainer & wild pokemon constructor
	Pokemon(PokemonData* _pokemonData, int _level);

	//Destructor
	~Pokemon();

//Methods
	float getHPRatio() { return (float)currentHP / HP; }
	float getXPRatio() { return (float)(XP - previousLevelXP) / (nextLevelXP - previousLevelXP); }
	
	void modXP(int amount) { XP += abs(amount); checkForLevelUp(); }
	void modHP(int amount);

	inline Gender getGender() const { return gender; }

	bool checkForDeath();
	string getName(bool realNameToo = false);
	string getInternalName() { return pokemonData->getInternalName(); }
	int getNumberOfMoves();
	MoveData** getMoves() { return moves; }
	bool isType(PokemonType _type);
	string afflictStatus(Status _status);
	void setMoves(MoveData* _moves[4]);
	void setNickname(string n) { nickname = n; }
	inline int getLevel() const { return level; }

	inline int getHP() const { return HP; }
	inline int getHPCurrent() const { return currentHP; }
	
	inline int getAttack() const { return attack; }
	inline int getDefense() const { return defense; }
	inline int getSpecialAttack() const { return specialAttack; }
	inline int getSpecialDefense() const { return specialDefense; }
	inline int getSpeed() const { return speed; }

	Status getStatus() const { return status; }

	PokemonType getPokeType1() const { return pokemonData->getPokemonType1(); }
	PokemonType getPokeType2() const { return pokemonData->getPokemonType2(); }
	
	float getTypeEffectivenessAgainst(PokemonType type) const;

	inline string getAbility() const { return ability; }

//Statics
	static const int SHINY_CHANCE = 8192;
	static const int POKERUS_CHANCE = 21845;

	void print(bool detailedStats = false);

private:
//Methods
	void updateStats();
	bool checkForLevelUp();

//Constants
	const PokemonData* pokemonData;
	
	const Gender gender;
	const Nature nature;
	const bool shiny, pokerus;

	const string ability;

	const int IV_HP, 
		IV_ATK, 
		IV_DEF, 
		IV_SPA, 
		IV_SPD, 
		IV_SPE;


	//const string caughtBall;

	//const string metDate;
	//const string metMap;
	const int ID;

//DAM
	string nickname;
	int level;
	int XP, nextLevelXP, previousLevelXP;

	int EV_HP, EV_ATK, EV_DEF, EV_SPA, EV_SPD, EV_SPE;

	int HP, currentHP,
		attack, specialAttack,
		defense, specialDefense,
		speed;

	//int happiness;
	//string heldItem;


	MoveData* moves[4];

	Status status;

};

