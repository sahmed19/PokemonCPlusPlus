#include "Trainer.h"
#include <iostream>

Trainer::Trainer(string _name, string _title, Pokemon* _pokemon[6]) :
	name(_name), title(_title)
{
	setPokemon(_pokemon);
}

Trainer::Trainer(string _name, string _title, Pokemon* _pokemon)
	: name(_name), title(_title)
{
	Pokemon* _party[6] = { _pokemon, nullptr, nullptr, nullptr,
	nullptr, nullptr };

	setPokemon(_party);

}

void Trainer::print() const
{

	cout << title << " " << name << endl;

	for (int i = 0; i < 6; i++) {
		if (party[i] != nullptr) {
			party[i]->print();
		}
	}

}

Pokemon* Trainer::getFirstNonFaintedPokemon()
{
	
	for (int i = 0; i < 6; i++) {
		
		if(party[i] != nullptr && !party[i]->checkForDeath()) {
			
			return party[i];

		}

	}

	return nullptr;

}

bool Trainer::addPokemon(Pokemon* pokemon)
{

	for (int i = 0; i < 6; i++) {
		if (party[i] == nullptr) {
			party[i] = pokemon;
			return true;
		}
	}

	return false;
}

void Trainer::setPokemon(Pokemon* _pokemon[6]) {

	for (int i = 0; i < 6; i++) {
		party[i] = _pokemon[i];
	}


}