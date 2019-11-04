#pragma once
#include <string>
#include "Pokemon.h"
using namespace std;
class Trainer
{

public:
	Trainer(string _name, string _title, Pokemon* _pokemon[6]);
	Trainer(string _name, string _title, Pokemon* _pokemon);
	~Trainer() {}

	void setPokemon(Pokemon* _pokemon[6]);

	inline string getName() const { return title + " " + name; }

	void print() const;

	Pokemon* getFirstNonFaintedPokemon();
	bool hasUsablePokemon() { return getFirstNonFaintedPokemon() != nullptr; }

	Pokemon** getParty() { return party; }

	bool addPokemon(Pokemon* pokemon);

private:
	const string name;
	const string title;
	Pokemon* party[6];
	

};

