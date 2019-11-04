#include "MoveDex.h"
#include <sstream>
#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

MoveDex* MoveDex::instance = NULL;

MoveDex::MoveDex()
{
	//Instance
	instance = this;

	XMLDocument moveXMLDocument;

	moveXMLDocument.LoadFile("movedex.xml");

	XMLElement* movedex = moveXMLDocument.FirstChildElement("movedex");

	XMLElement* move = movedex->FirstChildElement("move");

	for (int i = 0; i < NUM_OF_MOVES; i++) {

		cout << "LOADING MOVES [ " << (int) ((i * 100.0f) / NUM_OF_MOVES) << "% ]" << endl;

		//XML Declarations
		XMLElement* IDElement = move->FirstChildElement("id");
		XMLElement* nameElement = move->FirstChildElement("name");
		XMLElement* internalNameElement = move->FirstChildElement("internal-name");
		XMLElement* functionCodeElement = move->FirstChildElement("function-code");
		XMLElement* basePowerElement = move->FirstChildElement("base-power");
		XMLElement* typeElement = move->FirstChildElement("type");
		XMLElement* categoryElement = move->FirstChildElement("category");
		XMLElement* accuracyElement = move->FirstChildElement("accuracy");
		XMLElement* ppElement = move->FirstChildElement("pp");
		XMLElement* additionalEffectChanceElement = move->FirstChildElement("additional-effect-chance");
		XMLElement* targetElement = move->FirstChildElement("target");
		XMLElement* priorityElement = move->FirstChildElement("priority");
		XMLElement* descriptionElement = move->FirstChildElement("description");
		XMLElement* flagsElement = nullptr;
		if (move->FirstChildElement("flags") != nullptr) {
			flagsElement = move->FirstChildElement("flags");
		}

		//XML Definitions
		stringstream ss("");

		int id, basePower, accuracy, PP, additionalEffectChance, priority;

		ss << IDElement->GetText(); ss >> id; ss.clear();
		ss << basePowerElement->GetText(); ss >> basePower; ss.clear();
		ss << accuracyElement->GetText(); ss >> accuracy; ss.clear();
		ss << ppElement->GetText(); ss >> PP; ss.clear();
		ss << additionalEffectChanceElement->GetText(); ss >> additionalEffectChance; ss.clear();
		ss << priorityElement->GetText(); ss >> priority; ss.clear();

		string name, internalName, functionCode, type, category, target, description;

		name = nameElement->GetText();
		internalName = internalNameElement->GetText();
		functionCode = functionCodeElement->GetText();
		type = typeElement->GetText();
		category = categoryElement->GetText();
		target = targetElement->GetText();
		description = descriptionElement->GetText();

		//FLAGS

		
		char* flags = nullptr;
		int num_flags = 0;

		if (flagsElement != nullptr) {
			string flagsString = flagsElement->GetText();
			num_flags = flagsString.length()+1;
			flags = &flagsString[0];
		}

		//CONSTRUCTOR
		MoveData* moveData = new MoveData(id, name, internalName, functionCode, basePower,
			type, category, accuracy, PP, additionalEffectChance, target, priority, flags,
			num_flags, description);

		moveMap.insert(pair<string, MoveData*> (internalName, moveData));

		move = move->NextSiblingElement("move");

	}
}

MoveData* MoveDex::getMoveData(string name)
{
	return moveMap[name];
}

MoveDex* MoveDex::Instance()
{
	return instance;
}
