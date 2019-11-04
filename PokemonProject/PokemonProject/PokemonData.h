#pragma once
#include <string>
#include <vector>
#include <map>
#include "TypeData.h"

using namespace std;


enum Status {
	NO_STATUS,
	SLEEP,
	POISONED,
	TOXIC,
	BURN,
	PARALYSIS,
	FREEZE,
	FAINTED
};
enum Gender {
	NO_GENDER,
	MALE,
	FEMALE
};

enum Stat {
	HP,
	ATK,
	DEF,
	SPA,
	SPD,
	SPE
};

struct learnedMove {
	int level;
	string name;
};

struct evolution {
	string pokemon;
	string type;
	string requirement;
};

struct growthRateData {
	const static int EXPTableErratic[100];
	const static int EXPTableFast[100];
	const static int EXPTableMedium[100];
	const static int EXPTableParabolic[100];
	const static int EXPTableSlow[100];
	const static int EXPTableFluctuating[100];
};

class PokemonData
{

public:
	PokemonData(int _id,
		string _name, string _internalName,
		string _species, string _description,
		string _type1, string _type2,
		
		int _HP,
		int _ATK, int _DEF,
		int _SPA, int _SPD,
		int _SPE,

		double _height, double _weight,
		string _genderRate, string _growthRate,
		
		int _rareness, int _baseHappiness, int _baseEXP,

		int _EV_HP,
		int _EV_ATK, int _EV_DEF,
		int _EV_SPA, int _EV_SPD,
		int _EV_SPE,

		int _battlerPlayerY,
		int _battlerEnemyY,
		int _battlerAltitude,

		int _eggHatchSteps,
		string _eggGroup1, string _eggGroup2,

		string* _abilities, int _num_abilities, 
		string _hiddenAbility,
		
		learnedMove* _learnedMoves, int _num_learnedMoves,
		string* _eggMoves, int _num_eggMoves,

		evolution* _evolutions, int _num_evolutions
		);
	
	

	string getName() const { return name; }
	string getInternalName() const { return internalName; }
	string getSpecies() const { return species; }
	string getDescription() const { return description; }
	
	PokemonType getPokemonType1() const { return type1; }
	PokemonType getPokemonType2() const { return type2; }

	int getHP() const { return HP; }
	int getATK() const { return ATK; }
	int getDEF() const { return DEF; }
	int getSPA() const { return SPA; }
	int getSPD() const { return SPD; }
	int getSPE() const { return SPE; }


	double getHeight() const { return height; }
	double getWeight() const { return weight; }

	string getGenderRateString() const { return genderRate; }
	string getGrowthRateString() const { return growthRate; }
	
	string checkAbility (string ability) const;

	int getEVYield_HP() const { return EV_HP; }
	int getEVYield_ATK() const { return EV_ATK; }
	int getEVYield_DEF() const { return EV_DEF; }
	int getEVYield_SPA() const { return EV_SPA; }
	int getEVYield_SPD() const { return EV_SPD; }
	int getEVYield_SPE() const { return EV_SPE; }

	Gender getRandomGender() { return getRandomGender(genderRate); }
	string getRandomAbility(bool includeHidden = false);

	class MoveData** getBestMovesAtLevel(int level);

	void print() const;

	//STATICS
	static float getFemaleRate(string _genderRate);
	static int getLevelEXP(string _growthRate, int currentLevel);

	static Gender getRandomGender(float _femaleRate);
	static Gender getRandomGender(string _genderRate);

	

private:
	const int id;
	const string name;
	const string internalName;
	const string species;
	const string description;

	const PokemonType type1;
	const PokemonType type2;
	
	//STATS
	const int HP;
	const int ATK;
	const int DEF;
	const int SPA;
	const int SPD;
	const int SPE;

	const double height;
	const double weight;
	
	const string genderRate;
	const string growthRate;

	const int rareness;
	const int baseHappiness;
	const int baseEXP;

	//EV Yield
	const int EV_HP;
	const int EV_ATK;
	const int EV_DEF;
	const int EV_SPA;
	const int EV_SPD;
	const int EV_SPE;

	const int battlerPlayerY;
	const int battlerEnemyY;
	const int battlerAltitude;

	const int eggHatchSteps;
	const string eggGroup1, eggGroup2;

	const string* abilities;
	const int num_abilities;
	const string hiddenAbility;

	
	learnedMove* learnedMoves;
	const int num_learnedMoves;
	const string* eggMoves;
	const int num_eggMoves;

	evolution* evolutions;
	const int num_evolutions;

	const static map<string, float> GENDER_RATE;

};

