#include "MoveData.h"
#include <iostream>

MoveData::MoveData(int _id, string _name, string _internalName,
	string _functionCode, int _basePower, string _type,
	string _category, int _accuracy, int _PP,
	int _additionalEffectChance, string _target,
	int _priority, char* _flags, int _num_flags,
	string _description) : 
	id(_id), name(_name), 
	internalName(_internalName),
	functionCode(_functionCode), basePower(_basePower), 
	pokemonType(TypeData::getTypeFromString(_type)),
	category(_category), accuracy(_accuracy),PP(_PP),
	additionalEffectChance(_additionalEffectChance), 
	target(_target), priority(_priority), 
	flags(_flags), num_flags(_num_flags),
	description(_description)
{}

bool MoveData::hasFlag(char c) const
{
	for (int i = 0; i < num_flags; i++) {
		if (flags[i] == c) { return true; }
	}
	return false;
}

bool MoveData::hasFlags(char* c, int count) const
{

	bool* ret = new bool[count];

	for (int i = 0; i < count; i++) {
		ret[i] = false;

		for (int j = 0; j < num_flags; j++) {
			if (c[i] == flags[j]) {
				ret[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < count; i++) {
		if (!ret[i]) {
			return false;
		}
	}

	return true;
}

void MoveData::print() const
{
	cout << "== " << name << endl;
	cout << "[" << TypeData::getStringFromType(pokemonType) << "] -" << category << "-" << endl;
	cout << "Base Power: " << basePower << endl;
	cout << "Accuracy: " << accuracy << "%" << endl;
	cout << "Max PP: " << PP << endl << endl;
	cout << description << endl;

	if (additionalEffectChance > 0) {
		cout << "Additional Effect Chance: " << additionalEffectChance << endl << endl;
	}

	if (priority != 0) {
		cout << "Priority: " << priority << endl << endl;
	}
}
