#include "Pokemon.h"
#include "Pokedex.h"
#include "TypeData.h"


using namespace std;

const float NatureData::natureMultiplierLookupTable[25][6] = {
{		0, 1, 1, 1, 1, 1				},
{		0, 1.1f, 0.9f, 1, 1, 1			},
{		0, 1.1f, 1, 1, 1, 0.9f			},
{		0, 1.1f, 1, 0.9f, 1, 1			},
{		0, 1.1f, 1, 1, 0.9f, 1			},
{		0, 0.9f, 1.1f, 1, 1, 1			},
{		0, 1, 1, 1, 1, 1				},
{		0, 1, 1.1f, 1, 1, 0.9f			},
{		0, 1, 1.1f, 0.9f, 1, 1			},
{		0, 1, 1.1f, 1, 0.9f, 1			},
{		0, 0.9f, 1, 1, 1, 1.1f			},
{		0, 1, 0.9f, 1, 1, 1.1f			},
{		0, 1, 1, 1, 1, 1				},
{		0, 1, 1, 0.9f, 1, 1.1f			},
{		0, 1, 1, 1, 0.9f, 1.1f			},
{		0, 0.9f, 1, 1.1f, 1, 1			},
{		0, 1, 0.9f, 1.1f, 1, 1			},
{		0, 1, 1, 1.1f, 1, 0.9f			},
{		0, 1, 1, 1, 1, 1				},
{		0, 1, 1, 1.1f, 0.9f, 1			},
{		0, 0.9f, 1, 1, 1.1f, 1			},
{		0, 1, 0.9f, 1, 1.1f, 1			},
{		0, 1, 1, 1, 1.1f, 0.9f			},
{		0, 1, 1, 0.9f, 1.1f, 1			},
{		0, 1, 1, 1, 1, 1				}
};

float NatureData::getNatureStatMultiplier(int _nature, int _stat)
{ return natureMultiplierLookupTable[_nature][_stat]; }


string NatureData::NatureToString(Nature _nature)
{
	const string natureStrings[25] = {
		"HARDY",
		"LONELY",
		"BRAVE",
		"ADAMANT",
		"NAUGHTY",
		"BOLD",
		"DOCILE",
		"RELAXED",
		"IMPISH",
		"LAX",
		"TIMID",
		"HASTY",
		"SERIOUS",
		"JOLLY",
		"NAIVE",
		"MODEST",
		"MILD",
		"QUIET",
		"BASHFUL",
		"RASH",
		"CALM",
		"GENTLE",
		"SASSY",
		"CAREFUL",
		"QUIRKY"
	};

	return natureStrings[(int)_nature];
}

Nature NatureData::getRandomNature() {

	int index = rand() % 24;

	return (Nature)index;

}

Pokemon::Pokemon(PokemonData* _pokemonData,
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
	Status _status)
	
	:
	
	pokemonData(_pokemonData), 
	gender(_gender), nature(_nature),
	shiny(_shiny), pokerus(_pokerus),
	ability(_pokemonData->checkAbility(_ability)),

	IV_HP(_IV_HP),
	IV_ATK(_IV_ATK),IV_DEF(_IV_DEF),
	IV_SPA(_IV_SPA),IV_SPD(_IV_SPD),
	IV_SPE(_IV_SPE),

	nickname(_nickname), level(_level),
	XP(PokemonData::getLevelEXP(_pokemonData->getGrowthRateString(), _level)),

	EV_HP(_EV_HP),
	EV_ATK(_EV_ATK), EV_DEF(_EV_DEF),
	EV_SPA(_EV_SPA), EV_SPD(_EV_SPD),
	EV_SPE(_EV_SPE),
	status(_status),
	ID(Pokedex::Instance()->getNewID())
	
{
	setMoves(_moves);
	updateStats();

}

Pokemon::Pokemon(PokemonData* _pokemonData, int _level) :
	pokemonData(_pokemonData),
	gender(_pokemonData->getRandomGender()),
	nature(NatureData::getRandomNature()),
	shiny((int) (rand()* SHINY_CHANCE) == 2),
	pokerus((int) (rand()* SHINY_CHANCE) == 2),
	ability(_pokemonData->getRandomAbility()),

	IV_HP ((int)(rand() % 32)),
	IV_ATK((int)(rand() % 32)), IV_DEF((int)(rand() % 32)),
	IV_SPA((int)(rand() % 32)), IV_SPD((int)(rand() % 32)),
	IV_SPE((int)(rand() % 32)),

	nickname(""), level(_level),
	XP(PokemonData::getLevelEXP(_pokemonData->getGrowthRateString(), _level)),

	EV_HP(0),
	EV_ATK(0), EV_DEF(0),
	EV_SPA(0), EV_SPD(0),
	EV_SPE(0),

	status(Status::NO_STATUS),
	ID(Pokedex::Instance()->getNewID())
{
	setMoves(_pokemonData->getBestMovesAtLevel(level));
	updateStats();
	modHP(100000);
}

Pokemon::~Pokemon()
{
	
}

void Pokemon::setMoves(MoveData* _moves[4]) {
	for (int i = 0; i < 4; i++) {
		moves[i] = _moves[i];
	}
}

void Pokemon::modHP(int amount)
{
	currentHP += amount;
	if (currentHP < 0) {
		currentHP = 0;
		status = Status::FAINTED;
	}
	else if(currentHP > HP){
		currentHP = HP;
	}
}

bool Pokemon::checkForDeath()
{
	if (currentHP <= 0) {
		status = Status::FAINTED;
		return true;
	}
	return false;
}

string Pokemon::getName(bool realNameToo)
{
	if (nickname != "") {
		if (realNameToo) {
			return "\"" + nickname + "\" " + pokemonData->getName();
		}

		return nickname;
	}
	return pokemonData->getName();
}

int Pokemon::getNumberOfMoves()
{

	int numMoves = 0;

	for (int i = 0; i < 4; i++) {
		if (moves[i] != nullptr) {
			numMoves++;
		}
	}
	return numMoves;
}

bool Pokemon::isType(PokemonType _type)
{
	return 
		(_type == pokemonData->getPokemonType1()) || 
		(_type == pokemonData->getPokemonType2());
}

string Pokemon::afflictStatus(Status _status)
{
	if (_status == Status::NO_STATUS || status == Status::NO_STATUS) {
		status = _status;
		const string fx[8] = {
			"was cured!", 
			"fell asleep!",
			"was poisoned!",
			"was badly poisoned!",
			"was burned!",
			"was paralyzed!",
			"was frozen solid!",
			"fucking died!"};

		return fx[(int)status];
	}
	else {

	}
}


float Pokemon::getTypeEffectivenessAgainst(PokemonType type) const
{
	return TypeData::getTypeEffectiveness(type, pokemonData->getPokemonType1()) *
		TypeData::getTypeEffectiveness(type, pokemonData->getPokemonType2());
}

void Pokemon::print(bool detailedStats)
{
	const char* genderArray = "NMF";

	cout << "--BASIC" << endl;
	cout << "Name: " << pokemonData->getName() << endl;
	cout << "Level: " << level << endl;
	cout << "Gender: " << genderArray[gender] << endl;
	cout << "Nature: " << NatureData::NatureToString(nature) << endl;
	cout << "Shiny: " << shiny << endl;
	cout << "Pokerus: " << pokerus << endl;
	cout << "Ability: " << ability << endl << endl;
	


	cout << "--MOVES" << endl;
	for (int i = 0; i < 4; i++) {

		if (moves[i] != nullptr) {
			moves[i]->print();
		}
		else {
			cout << "{NO MOVE}" << endl;
		}

		cout << "###" << endl;

	}

	if (detailedStats) {

		cout << "--IVs" << endl;
		cout << "HP: " << IV_HP << endl;
		cout << "ATK: " << IV_ATK << endl;
		cout << "DEF: " << IV_DEF << endl;
		cout << "SPA: " << IV_SPA << endl;
		cout << "SPD: " << IV_SPD << endl;
		cout << "SPE: " << IV_SPE << endl << endl;

		cout << "--EVs" << endl;
		cout << "HP: " << EV_HP << endl;
		cout << "ATK: " << EV_ATK << endl;
		cout << "DEF: " << EV_DEF << endl;
		cout << "SPA: " << EV_SPA << endl;
		cout << "SPD: " << EV_SPD << endl;
		cout << "SPE: " << EV_SPE << endl << endl;

	}

	cout << "--Final Stats" << endl;
	cout << "HP: " << HP << endl;
	cout << "ATK: " << attack << endl;
	cout << "DEF: " << defense << endl;
	cout << "SPA: " << specialAttack << endl;
	cout << "SPD: " << specialDefense << endl;
	cout << "SPE: " << speed << endl << endl;

}

void Pokemon::updateStats()
{
	previousLevelXP = PokemonData::getLevelEXP(pokemonData->getGrowthRateString(), level);
	nextLevelXP = PokemonData::getLevelEXP(pokemonData->getGrowthRateString(), level + 1);

	//HP - Stat = floor((2 * B + I + E) * L / 100 + L + 10)

	float HPRatio = getHPRatio();

	HP = (int)
		((2.0f * pokemonData->getHP() + IV_HP + EV_HP) *
		(level / 100.0f) + level + 10);

	currentHP = (int) (HP * getHPRatio());

	//OTHERS - Stat = floor(floor((2 * B + I + E) * L / 100 + 5) * N)
	attack =
		(int)((int)(
		(2.0f * pokemonData->getATK() + IV_ATK + EV_ATK) *
			(level / 100.0f) + 5) * NatureData::getNatureStatMultiplier(nature, Stat::ATK));

	defense =
		(int)((int)(
		(2.0f * pokemonData->getDEF() + IV_DEF + EV_DEF) *
			(level / 100.0f) + 5) * NatureData::getNatureStatMultiplier(nature, Stat::DEF));

	specialAttack =
		(int)((int)(
		(2.0f * pokemonData->getSPA() + IV_SPA + EV_SPA) *
			(level / 100.0f) + 5) * NatureData::getNatureStatMultiplier(nature, Stat::SPA));

	specialDefense =
		(int)((int)(
		(2.0f * pokemonData->getSPD() + IV_SPD + EV_SPD) *
			(level / 100.0f) + 5) * NatureData::getNatureStatMultiplier(nature, Stat::SPD));

	speed =
		(int)((int)(
		(2.0f * pokemonData->getSPE() + IV_SPE + EV_SPE) *
			(level / 100.0f) + 5) * NatureData::getNatureStatMultiplier(nature, Stat::SPE));
}

bool Pokemon::checkForLevelUp()
{
	int prev = level;
	while (level < 100 && XP > nextLevelXP) {
		level++;
		updateStats();
	}

	return level > prev;

}

