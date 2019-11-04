#include "Pokedex.h"
#include <sstream>
#include <string>
#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

Pokedex* Pokedex::instance = NULL;

Pokedex::Pokedex()
{
	//IDSETTER
	ID_SETTER = 0;
	instance = this;

	XMLDocument pokedexXMLDocument;

	pokedexXMLDocument.LoadFile("pokedex.xml");

	XMLElement* pokedex = pokedexXMLDocument.FirstChildElement("pokedex");
	
	XMLElement* pokemon = pokedex->FirstChildElement("pokemon");
	
	for (int i = 0; i < NUM_OF_POKEMON; i++) {
		
		cout << "LOADING POKEMON [ " << (int) ((i * 100.0f) / NUM_OF_POKEMON) << "% ]" << endl;

		//XML Definitions

		XMLElement* nameElement = pokemon->FirstChildElement("name");
		XMLElement* internalNameElement = pokemon->FirstChildElement("internal-name");
		XMLElement* speciesElement = pokemon->FirstChildElement("species");
		XMLElement* descriptionElement = pokemon->FirstChildElement("description");
		
		XMLElement* type1Element = pokemon->FirstChildElement("type");
		XMLElement* type2Element = nullptr;
		if (type1Element->NextSibling() != nullptr) { type2Element = type1Element->NextSiblingElement("type"); }

		XMLElement* statElement = pokemon->FirstChildElement("base-stats");

		XMLElement* HPElement = statElement->FirstChildElement("HP");
		XMLElement* ATKElement = statElement->FirstChildElement("ATK");
		XMLElement* DEFElement = statElement->FirstChildElement("DEF");
		XMLElement* SPAElement = statElement->FirstChildElement("SPA");
		XMLElement* SPDElement = statElement->FirstChildElement("SPD");
		XMLElement* SPEElement = statElement->FirstChildElement("SPE");

		
		XMLElement* heightElement = pokemon->FirstChildElement("height");
		XMLElement* weightElement = pokemon->FirstChildElement("weight");
		
		XMLElement* genderRateElement = pokemon->FirstChildElement("gender-rate");
		XMLElement* growthRateElement = pokemon->FirstChildElement("growth-rate");
		
		
		XMLElement* rarenessElement = pokemon->FirstChildElement("rareness");
		XMLElement* baseHappinessElement = pokemon->FirstChildElement("happiness");
		XMLElement* baseEXPElement = pokemon->FirstChildElement("base-exp");




		XMLElement* effortPointsElement = pokemon->FirstChildElement("effort-points");

		XMLElement* EV_HPElement = effortPointsElement->FirstChildElement("HP");
		XMLElement* EV_ATKElement = effortPointsElement->FirstChildElement("ATK");
		XMLElement* EV_DEFElement = effortPointsElement->FirstChildElement("DEF");
		XMLElement* EV_SPAElement = effortPointsElement->FirstChildElement("SPA");
		XMLElement* EV_SPDElement = effortPointsElement->FirstChildElement("SPD");
		XMLElement* EV_SPEElement = effortPointsElement->FirstChildElement("SPE");


		

		XMLElement* battlerPlayerYElement = pokemon->FirstChildElement("battler-player-y");
		XMLElement* battlerEnemyYElement = pokemon->FirstChildElement("battler-enemy-y");
		XMLElement* battlerAltitudeElement = pokemon->FirstChildElement("battler-altitude");

		XMLElement* eggHatchStepsElement = pokemon->FirstChildElement("egg-hatch-steps");

		XMLElement* eggGroup1Element = nullptr;
		if (pokemon->FirstChildElement("egg-group") != nullptr) { eggGroup1Element = pokemon->FirstChildElement("egg-group"); }
		XMLElement* eggGroup2Element = nullptr;
		if (eggGroup1Element != nullptr && eggGroup1Element->NextSibling() != nullptr) { eggGroup2Element = eggGroup1Element->NextSiblingElement("egg-group"); }



		XMLElement* abilitiesElement = pokemon->FirstChildElement("abilities");
		XMLElement* hiddenAbilityElement = nullptr;
		if (abilitiesElement->FirstChildElement("hidden-ability") != nullptr) { hiddenAbilityElement = abilitiesElement->FirstChildElement("hidden-ability"); }

		XMLElement* learnedMovesElement = pokemon->FirstChildElement("moves");

		XMLElement* eggMovesElement = nullptr; 
		if (pokemon->FirstChildElement("egg-moves") != nullptr) { eggMovesElement = pokemon->FirstChildElement("egg-moves"); }

		XMLElement* evolutionsElement = nullptr;
		if (pokemon->FirstChildElement("evolutions") != nullptr) { evolutionsElement = pokemon->FirstChildElement("evolutions"); }

		//Definitions


		string name = nameElement->GetText();
		string internalName = internalNameElement->GetText();
		string species = speciesElement->GetText();
		string description = descriptionElement->GetText();
		

		//Type
		string type1 = type1Element->GetText();
		string type2 = "";
		if (type2Element != nullptr) {	type2 = type2Element->GetText(); }

		
		
		//string ability = abilityElement->GetText();

		stringstream ss("");

		int HP, ATK, DEF, SPA, SPD, SPE;

		ss << HPElement->GetText(); ss >> HP; ss.clear();
		ss << ATKElement->GetText(); ss >> ATK; ss.clear();
		ss << DEFElement->GetText(); ss >> DEF; ss.clear();
		ss << SPAElement->GetText(); ss >> SPA; ss.clear();
		ss << SPDElement->GetText(); ss >> SPD; ss.clear();
		ss << SPEElement->GetText(); ss >> SPE; ss.clear();


		//Height Weight
		double height, weight;

		ss << heightElement->GetText(); ss >> height; ss.clear();
		ss << weightElement->GetText(); ss >> weight; ss.clear();

		//Gender & Growth
		string genderRate = genderRateElement->GetText(); 
		string growthRate = growthRateElement->GetText();;

		//Rareness, Happiness, base EXP
		int rareness, baseHappiness, baseEXP;

		ss << rarenessElement->GetText(); ss >> rareness; ss.clear();
		ss << baseHappinessElement->GetText(); ss >> baseHappiness; ss.clear();
		ss << baseEXPElement->GetText(); ss >> baseEXP; ss.clear();

		//Effort Points

		int EV_HP, EV_ATK, EV_DEF, EV_SPA, EV_SPD, EV_SPE = 0;

		ss << EV_HPElement->GetText(); ss >> EV_HP; ss.clear();
		ss << EV_ATKElement->GetText(); ss >> EV_ATK; ss.clear();
		ss << EV_DEFElement->GetText(); ss >> EV_DEF; ss.clear();
		ss << EV_SPAElement->GetText(); ss >> EV_SPA; ss.clear();
		ss << EV_SPDElement->GetText(); ss >> EV_SPD; ss.clear();
		ss << EV_SPEElement->GetText(); ss >> EV_SPE; ss.clear();

		//Sprite Positioning & Egg Hatch Steps
		int battlerPlayerY, battlerEnemyY, battlerAltitude, eggHatchSteps = 0;

		ss << battlerPlayerYElement->GetText(); ss >> battlerPlayerY; ss.clear();
		ss << battlerEnemyYElement->GetText(); ss >> battlerEnemyY; ss.clear();
		ss << battlerAltitudeElement->GetText(); ss >> battlerAltitude; ss.clear();
		ss << eggHatchStepsElement->GetText(); ss >> eggHatchSteps; ss.clear();


		//Egg Groups
		string eggGroup1 = "";
		if (eggGroup1Element != nullptr) { eggGroup1 = eggGroup1Element->GetText(); }
		string eggGroup2 = "";
		if (eggGroup2Element != nullptr) { eggGroup2 = eggGroup2Element->GetText(); }



		//Abilities
		string* abilities;
		int num_abilities = 0;

		vector<string> abilityVector;

		for (XMLElement* abilityElement = abilitiesElement->FirstChildElement();
			abilityElement != NULL;
			abilityElement = abilityElement->NextSiblingElement()) {

			abilityVector.push_back(abilityElement->GetText());

			num_abilities++;
		}

		abilities = new string[num_abilities];

		for (int i = 0; i < num_abilities; i++) {
			abilities[i] = abilityVector.at(i);
		}

		abilityVector.clear();

		//Hidden Ability
		string hiddenAbility = "";
		if (hiddenAbilityElement != nullptr) { hiddenAbility = hiddenAbilityElement->GetText(); }


		//Moves
		learnedMove* learnedMoves;
		int num_learnedMoves = 0;

		vector<learnedMove> learnedMoveVector;

		for (XMLElement* learnedMoveElement = learnedMovesElement->FirstChildElement();
			learnedMoveElement != NULL;
			learnedMoveElement = learnedMoveElement->NextSiblingElement()) {

			learnedMove lm;

			XMLElement* learnedMoveLevelElement = learnedMoveElement->FirstChildElement();
			XMLElement* learnedMoveNameElement = learnedMoveLevelElement->NextSiblingElement();
			


			ss << learnedMoveLevelElement->GetText(); ss >> lm.level; ss.clear();
			lm.name = learnedMoveNameElement->GetText();
			

			learnedMoveVector.push_back(lm);

			num_learnedMoves++;
		}

		learnedMoves = new learnedMove[num_learnedMoves];

		for (int i = 0; i < num_learnedMoves; i++) {
			learnedMoves[i] = learnedMoveVector.at(i);
		}

		learnedMoveVector.clear();


		//Egg Moves
		string* eggMoves;
		
		int num_eggMoves = 0;

		if (eggMovesElement != nullptr) {


			vector<string> eggMoveVector;

			for (XMLElement* eggMoveElement = eggMovesElement->FirstChildElement();
				eggMoveElement != NULL;
				eggMoveElement = eggMoveElement->NextSiblingElement()) {

				eggMoveVector.push_back(eggMoveElement->GetText());

				num_eggMoves++;
			}

			eggMoves = new string[num_eggMoves];

			for (int i = 0; i < num_eggMoves; i++) {
				eggMoves[i] = eggMoveVector.at(i);
			}

			eggMoveVector.clear();
		
		}
		else {
			eggMoves = new string[0];
		}


		//Evolutions
		evolution* evolutions;

		int num_evolutions = 0;

		if (evolutionsElement != nullptr) {

			vector<evolution> evolutionVector;

			for (XMLElement* evolutionElement = evolutionsElement->FirstChildElement();
				evolutionElement != NULL;
				evolutionElement = evolutionElement->NextSiblingElement()) {

				evolution e;

				XMLElement* evolutionPokemonElement = evolutionElement->FirstChildElement();
				XMLElement* evolutionTypeElement = evolutionPokemonElement->NextSiblingElement();
				XMLElement* evolutionRequirementElement = nullptr;
				if (evolutionTypeElement->NextSiblingElement() != nullptr)
				{
					evolutionRequirementElement = evolutionTypeElement->NextSiblingElement();
				}

				e.pokemon = evolutionPokemonElement->GetText();
				e.type = evolutionTypeElement->GetText();
				if (evolutionRequirementElement != nullptr)
				{
					e.requirement = evolutionRequirementElement->GetText();
				}

				evolutionVector.push_back(e);

				num_evolutions++;
			}

			evolutions = new evolution[num_evolutions];

			for (int i = 0; i < num_evolutions; i++) {
				evolutions[i] = evolutionVector.at(i);
			}

			evolutionVector.clear();

		}
		else {
			evolutions = new evolution[0];
		}


		//CONSTRUCTOR
		PokemonData* pokemonData = new PokemonData(
			i+1, 
			name, internalName, 
			species, description, 
			type1, type2,
			
			HP, 
			ATK, DEF, 
			SPA, SPD, 
			SPE,
			
			height, weight,
			genderRate, growthRate, 
			
			rareness, baseHappiness, baseEXP,
			
			EV_HP, 
			EV_ATK, EV_DEF, 
			EV_SPA, EV_SPD, 
			EV_SPE,
			
			battlerPlayerY, 
			battlerEnemyY, 
			battlerAltitude, 
			
			eggHatchSteps, 
			eggGroup1, eggGroup2, 
			
			abilities, num_abilities,
			hiddenAbility,
			
			learnedMoves, num_learnedMoves,
			eggMoves, num_eggMoves,
			
			evolutions, num_evolutions);

		pokedexMap.insert(pair<string, PokemonData*> (internalName, pokemonData));

		pokemon = pokemon->NextSiblingElement("pokemon");
	}
}



PokemonData* Pokedex::getPokemonData(string name)
{
	return pokedexMap[name];
}

Pokedex* Pokedex::Instance()
{
	return instance;
}
