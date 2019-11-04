#include "Game.h"


using namespace std;

Game::Game()
{

	playing = true;

}

void Game::gameLoop() {

	MoveDex* movedex = new MoveDex();
	Pokedex* pokedex = new Pokedex();
	string* options;


	Pokemon* playerPokemon1 = new Pokemon(pokedex->getPokemonData("LUCARIO"), 55);
	Pokemon* playerPokemon2 = new Pokemon(pokedex->getPokemonData("STARAPTOR"), 50);
	Pokemon* playerPokemon3 = new Pokemon(pokedex->getPokemonData("TORTERRA"), 55);
	Pokemon* playerPokemon4 = new Pokemon(pokedex->getPokemonData("GARCHOMP"), 50);

	playerPokemon1->setNickname("Lucarchy");
	playerPokemon2->setNickname("Starchy");
	playerPokemon3->setNickname("Tortarchy");
	playerPokemon4->setNickname("Garchy");

	MoveData* lucarioMoves[4] = {
		movedex->getMoveData("SWORDSDANCE"),
		movedex->getMoveData("AURASPHERE"),
		movedex->getMoveData("CALMMIND"),
		movedex->getMoveData("BULLETPUNCH") };

	MoveData* staraptorMoves[4] = {
		movedex->getMoveData("CLOSECOMBAT"),
		movedex->getMoveData("BRAVEBIRD"),
		movedex->getMoveData("FLY"),
		movedex->getMoveData("RETURN") };

	
	playerPokemon1->setMoves(lucarioMoves);
	playerPokemon2->setMoves(staraptorMoves);

	Pokemon* foePokemon1 = new Pokemon(pokedex->getPokemonData("BLISSEY"), 60);
	Pokemon* foePokemon2 = new Pokemon(pokedex->getPokemonData("TOGEKISS"), 60);
	Pokemon* foePokemon3 = new Pokemon(pokedex->getPokemonData("MISMAGIUS"), 60);
	Pokemon* foePokemon4 = new Pokemon(pokedex->getPokemonData("RHYPERIOR"), 60);

	Trainer* player = new Trainer("Andre", "PKMN Trainer", playerPokemon2);
	player->addPokemon(playerPokemon1);
	player->addPokemon(playerPokemon3);
	player->addPokemon(playerPokemon4);

	Trainer* foe = new Trainer("Kevin", "Ace Trainer", foePokemon1);
	foe->addPokemon(foePokemon2);
	foe->addPokemon(foePokemon3);
	foe->addPokemon(foePokemon4);

	if (battleTrainer(player, foe)) {
		printAndWait("YOU WON!");
		printAndWait("Kevin: *laughs sadly*");
	}
	else {
		printAndWait("YOU LOST!");
		printAndWait("Kevin: *laughs happily*");
	}
	
	playing = false;
	return;
	/*
	string input;

	printAndWait("Hello, I am Professor Oak!");
	printAndWait("I study these creatures known as Pokemon.");
	printAndWait("Enough of that, though. First, tell me your name!");

	
	while (input == "") {

		cout << endl << endl << "Name: ";
		cin >> input;
		if (input == "") {
			printAndWait("Why so quiet? Tell me your name!");
		}
	}

	string name = input;

	cout << "Hm, yes, " << name << "! Now I remember. How are you doing?" << endl;

	options = new string[3]{ 
		"Doing ok I guess",
		"What's it to you gramps",
		"Honestly I'm a little depressed" };

	switch (getOption(options, 3)) {
	default:
	case 0:
		printAndWait("I'm glad to hear it!");
		break;
	case 1:
		printAndWait("Settle down there, we're getting to the good part.");
		break;
	case 2:
		printAndWait("Wow... I'm not sure what to say. Get that checked out.");
		break;
	}

	printAndWait("Anyway, I think it's time you choose a starter Pokemon.");
	
	options = new string[3]{
		"Piplup, the Water Pokemon",
		"Cyndaquil, the Fire Pokemon",
		"Treecko, the Grass Pokemon"
	};
	
	Pokemon* starter;

	switch (getOption(options, 3)) {
	default:
	case 0:
		starter = new Pokemon(pokedex->getPokemonData("PIPLUP"), 5); break;
	case 1:
		starter = new Pokemon(pokedex->getPokemonData("CYNDAQUIL"), 5); break;
	case 2:
		starter = new Pokemon(pokedex->getPokemonData("TREECKO"), 5); break;
	}

	printAndWait("Congratulations on your starter Pokemon, " + starter->getName() + "!");
	
	options = new string[3]{
		"Yes please I can't wait to show it the love and care my father never showed me!",
		"I don't care about this stupid animal"
	};

	printAndWait("Would you like the rundown on you new friend? Maybe give it a nickname?");

	switch (getOption(options, 2)) {
	default:
	case 0:
	{
		starter->print(); break;
		cout << endl << "NICKNAME FOR " << starter->getName() << ": ";
		string nickname;
		cin >> nickname;
		starter->setNickname(nickname);
	}
	case 1:
		printAndWait("Oh... ok."); break;

	}

	printAndWait("So are you ready to start your journey?");

	//Change this to reflect player name later
	Trainer* player = new Trainer("Andre", "PKMN Trainer", starter);

	printAndWait("Oh no, here comes your dickwad Rival Ambrish!");

	printAndWait("Ambrish: Fuck you boomer gramps. Give me the good one!");

	Pokemon* rivalStarter;

	if (starter->getInternalName() == "PIPLUP") {
		rivalStarter = new Pokemon(pokedex->getPokemonData("TREECKO"), 5);
	}
	else if (starter->getInternalName() == "CYNDAQUIL") {
		rivalStarter = new Pokemon(pokedex->getPokemonData("PIPLUP"), 5);
	}
	else {
		rivalStarter = new Pokemon(pokedex->getPokemonData("CYNDAQUIL"), 5);
	}

	Trainer* rival = new Trainer("Ambrish", "PKMN Trainer", rivalStarter);

	battleTrainer(player, rival);

	printAndWait("GAME OVER");
	playing = false;
	*/
}

int Game::getOption(string* messages, int count) const
{

	for (int i = 0; i < count; i++) {
		cout << i << ": " << messages[i] << endl;
	}

	int result;
	cin >> result;
	waitEnter(false);
	return result;

}

bool Game::battleTrainer(Trainer* player, Trainer* opponent)
{

	string* options;
	int choice;

	bool win = false;

	Pokemon* allyPokemon;
	Pokemon* foePokemon;

	StatMultipliers allyMultipliers;
	StatMultipliers foeMultipliers;


	allyPokemon = player->getFirstNonFaintedPokemon();

	bool allyDied = false;
	bool foeDied = false;

	auto checkBothForDeath = [&]() {

		bool cont = false;

		if (foePokemon->checkForDeath()) {
			foeDied = true; cont = true;
		}

		if (allyPokemon->checkForDeath()) {
			allyDied = true; cont = true;
		}

		return cont;

	};

	printAndWait(opponent->getName() + " wants to battle!");

	allyPokemon = player->getFirstNonFaintedPokemon();
	foePokemon = opponent->getFirstNonFaintedPokemon();

	if (allyPokemon == nullptr) {
		cout << "ALLY NULL" << endl;
	}

	printAndWait("They send out " + foePokemon->getName() + "!");
	printAndWait("Go, " + allyPokemon->getName(true) + "!");


	//==================================
	//LOOP FOR WHOLE BATTLE
	while (true) {

		//IF FOE DIED, THEY CHOOSE NEW MON
		if (foeDied) {
			printAndWait("Foe " + foePokemon->getName() + " fainted!");

			foePokemon = opponent->getFirstNonFaintedPokemon();

			if (foePokemon == nullptr) {
				win = true;
				break;
			}

			printAndWait(opponent->getName() + 
				" sends out " + foePokemon->getName() + "!");
			foeDied = false;
		}

		//IF ALLY DIED, YOU CHOOSE NEW MON
		if (allyDied) {
			printAndWait(allyPokemon->getName() + " fainted!");
			
			//Check if player has usable pokemon left

			if (player->getFirstNonFaintedPokemon() == nullptr) {
				win = false;
				break;
			}

			//If so... switch!

			while (allyPokemon != nullptr && allyPokemon->checkForDeath()) {
				cout << "SWITCH TO WHAT POKEMON?" << endl;
				for (int i = 0; i < 6; i++) {
					if (player->getParty()[i] != nullptr) {
						cout << i << ": " "[" <<
							player->getParty()[i]->getHPCurrent() << "/" <<
							player->getParty()[i]->getHP() << "] " <<
							player->getParty()[i]->getName(true) <<
							(player->getParty()[i]->checkForDeath() ? " (FAINTED)" : "")
							<< endl;
					}
				}

				choice = getOption();

				Pokemon* pokeChoice = player->getParty()[choice];

				if (pokeChoice == nullptr) {
					printAndWait("Sike, that's the wrong numba!");
				}
				else if (pokeChoice->checkForDeath()) {
					printAndWait("Can't switch to fainted Pokemon!");
				}
				else {
					printAndWait("You did good, " + allyPokemon->getName() + ".");
					printAndWait("Follow them up, " + pokeChoice->getName() + "!");
					allyPokemon = pokeChoice;
				}
			}

			allyDied = false;
		}

		drawBar(foePokemon->getHPRatio());
		cout << "FOE: LVL " << foePokemon->getLevel() << " " << foePokemon->getName() << endl;
		cout << "HP: " << foePokemon->getHPCurrent() << "/" << foePokemon->getHP() << endl;
		
		drawBar(allyPokemon->getHPRatio());
		cout << "ALY: LVL " << allyPokemon->getLevel() << " " << allyPokemon->getName(true) << endl;
		cout << "HP: " << allyPokemon->getHPCurrent() << "/" << allyPokemon->getHP() << endl;
		
		cout << endl << endl;

		bool skipBattle = false;
		options = new string[4]{
			"FIGHT",
			"POKEMON",
			"ITEM",
			"RUN"
		};

		bool playerAttacks = false;
		MoveData* allyMove = nullptr;

		//PLAYER ACTION
		switch (getOption(options, 4)) {
		case 0:
		{
			//FIGHT
			cout << "USE WHAT MOVE? (4 TO CANCEL)" << endl;
			for (int i = 0; i < 4; i++) {
				if (allyPokemon->getMoves()[i] != nullptr) {
					cout << i << ": " << allyPokemon->getMoves()[i]->getName() << endl;
				}
			}

			choice = getOption();

			if (choice == 4) {
				printAndWait("Carys be like tired.");
				skipBattle = true;
				break;
			}

			MoveData* moveDataChoice = allyPokemon->getMoves()[choice];

			if (moveDataChoice == nullptr) {
				printAndWait("That's not a move!");
			}
			else {
				allyMove = moveDataChoice;
				playerAttacks = true;
				break;
			}

			break;
		}
		case 1:
		{
			//SWITCH
			cout << "SWITCH TO WHAT POKEMON?" << endl;
			for (int i = 0; i < 6; i++) {
				if (player->getParty()[i] != nullptr) {
					cout << i << ": " << "[" <<
						player->getParty()[i]->getHPCurrent() << "/" <<
						player->getParty()[i]->getHP() << "] " <<
						player->getParty()[i]->getName(true) << 
						(player->getParty()[i] == allyPokemon ? " (STAY IN) " : "") <<
						(player->getParty()[i]->checkForDeath() ? " (FAINTED)" : "")
						<< endl;
				}
			}

			choice = getOption();

			Pokemon* pokeChoice = player->getParty()[choice];

			if (pokeChoice == nullptr) {
				printAndWait("Sike, that's the wrong numba!");
				skipBattle = true;
			}
			else if (pokeChoice->checkForDeath()) {
				printAndWait("Can't switch to fainted Pokemon!");
				skipBattle = true;
			}
			else if (pokeChoice == allyPokemon) {
				printAndWait("Cancelled switch.");
				skipBattle = true;
			}
			else {
				printAndWait("You did good, " + allyPokemon->getName() + ".");
				printAndWait("Follow them up, " + pokeChoice->getName() + "!");
				allyPokemon = pokeChoice;
				allyMultipliers = StatMultipliers();
			}

			break;
		}
		case 2:
			//ITEM
			printAndWait("HAVEN'T IMPLEMENTED YET!");
			skipBattle = true;
			break;
		case 3:
			//RUN
			printAndWait("CAN'T RUN FROM TRAINER BATTLES!");
			skipBattle = true;
			break;
		default:
			break;
		}

		//BATTLE
		if (!skipBattle) {

			int foeChoice;
			MoveData* foeMove = nullptr;

			while (foeMove == nullptr) {

				foeChoice = rand() % 4;
				foeMove = foePokemon->getMoves()[foeChoice];

			}

			if (playerAttacks) {

				bool allyFaster = false;
				
				if (allyMove->getPriority() > foeMove->getPriority()) {
					allyFaster = true;
				}
				else if (allyMove->getPriority() < foeMove->getPriority()) {
					allyFaster = false;
				} else {
					if (allyPokemon->getSpeed() > foePokemon->getSpeed()) {
						allyFaster = true;
					}
					else if (allyPokemon->getSpeed() == foePokemon->getSpeed()) {
						allyFaster = (rand() % 2) == 0;
					}
				}
				

				if (allyFaster) {
					damageCalculator(allyPokemon, foePokemon, allyMove, &allyMultipliers, &foeMultipliers);
					if (checkBothForDeath()) { continue; }
					damageCalculator(foePokemon, allyPokemon, foeMove, &foeMultipliers, &allyMultipliers);
					if (checkBothForDeath()) { continue; }
				}
				else {
					damageCalculator(foePokemon, allyPokemon, foeMove, &foeMultipliers, &allyMultipliers);
					if (checkBothForDeath()) { continue; }
					damageCalculator(allyPokemon, foePokemon, allyMove, &allyMultipliers, &foeMultipliers);
					if (checkBothForDeath()) { continue; }
				}
			}
			else {
				damageCalculator(foePokemon, allyPokemon, foeMove, &foeMultipliers, &allyMultipliers);
				if (checkBothForDeath()) { continue; }
			}
		}

	}
	
	return win;
}

bool Game::damageCalculator(Pokemon* attacker,
	Pokemon* defender, MoveData* move,
	StatMultipliers* attackerMults,
	StatMultipliers* defenderMults)
{

	//Stat temps
	int finalAttackerAttack = attacker->getAttack() * attackerMults->getATKMod();
	int finalAttackerSpecialAttack = attacker->getSpecialAttack() * attackerMults->getSPAMod();
	float finalAttackerAccuracy = attackerMults->getACCMod();

	int finalDefenderDefense = defender->getDefense() * defenderMults->getDEFMod();
	int finalDefenderSpecialDefense = defender->getSpecialDefense() * defenderMults->getSPDMod();
	float finalDefenderEvasiveness = defenderMults->getEVAMod();


	//CHECK FOR ACCURACY
	bool accuracyCheck = ((rand() % 100) * (finalAttackerAccuracy / finalDefenderEvasiveness)) > move->getAccuracy();
	bool secondaryEffectHits = (rand() % 100) < move->getAdditionalEffectChance();

	printAndWait(attacker->getName() + " used " + move->getName() + "!");

	float power = move->getBasePower();
	float level = attacker->getLevel();
	float ratingMultiplier;
	float burn;

	if (move->isSpecial()) {
		burn = 1.0f;
		ratingMultiplier =
			((float)finalAttackerSpecialAttack) /
			((float)finalDefenderSpecialDefense);
	}
	else {
		burn = (attacker->getStatus() == Status::BURN ? .5f : 1.0f);
		ratingMultiplier =
			((float)finalAttackerAttack) /
			((float)finalDefenderDefense);
	}

	float targets = 1.0f;
	float weather = 1.0f;

	float criticalChance = 1.0f / 16.0f;
	bool criticalHappened = (rand() % 100) < criticalChance * 100.0f;
	float critical = (criticalHappened ? 2.0f : 1.0f);
	float randomVariation = (85 + (rand() % 15)) / 100.0f;
	float STAB = (attacker->isType(move->getMoveType()) ? 1.5f : 1.0f);
	float typeEffectiveness = defender->getTypeEffectivenessAgainst(move->getMoveType());
	float other = 1.0f;


	
	//MOVE HIT!

	float modifier;

	int damageOverride = -1;

	bool executeDamage = true;

	//Pre-damage additional effect
	moveFunctionCodeEffectPreDamage(
		attacker, defender, move,
		&other, &STAB, &critical, &typeEffectiveness,
		&accuracyCheck, &secondaryEffectHits, &executeDamage,
		&level, &power,
		&ratingMultiplier,
		&damageOverride,
		attackerMults, defenderMults);

	//Set Modifier
	modifier = targets * weather * critical *
		randomVariation * STAB * typeEffectiveness * burn * other;

	//Calculate damage. Override if pre-damage fx gave new damage
	int damage = (damageOverride > 0? damageOverride : 
		rawDamageCalculator(level, power, ratingMultiplier, modifier));

	//Accuracy check
	if (move->getAccuracy() > 0 && accuracyCheck) {
		printAndWait("But it missed!");
		return false;
	}

	//Only deal damage if a non-Status move and we want to do it
	if (!move->isStatus() && executeDamage) {

		cout << endl << endl <<
			"------------------------------------------" << endl <<
			"DEBUG--    LEVEL        : " << level << endl <<
			"DEBUG--    POWER        : " << power << endl <<
			"DEBUG--    WEATHER      : " << weather << endl <<
			"DEBUG--    STAB         : " << STAB << endl <<
			"DEBUG--    CRITICAL     : " << critical << endl <<
			"DEBUG--    EFFECTIVENESS: " << typeEffectiveness << endl <<
			"DEBUG--    MODIFIER     : " << modifier << endl <<
			"DEBUG-------------------------------------" << endl <<
			"DEBUG--    IS SPECIAL? : " << move->isSpecial() << endl <<
			"DEBUG--    ATTACK      : " << attacker->getAttack() << endl <<
			"DEBUG--    ATTACK MOD  : " << attackerMults->getATKMod() << endl <<
			"DEBUG--    SPATTK      : " << attacker->getSpecialAttack() << endl <<
			"DEBUG--    SPATTK MOD  : " << attackerMults->getSPAMod() << endl <<
			"DEBUG--    DEFENSE     : " << defender->getDefense() << endl <<
			"DEBUG--    DEFENSE MOD : " << defenderMults->getDEFMod() << endl <<
			"DEBUG--    SPDEF       : " << defender->getSpecialDefense() << endl <<
			"DEBUG--    SPDEF MOD   : " << defender->getSpecialDefense() << endl <<
			"DEBUG--    RATING      : " << ratingMultiplier << endl <<
			"DEBUG--    FINAL DAMAGE: " << damage << endl <<
			"------------------------------------------" << endl << endl;

		if (damage <= 0) {
			printAndWait("It didn't effect them...");
			return false;
		}

		defender->modHP(-damage);

		if (criticalHappened) {
			printAndWait("Critical hit!");
		}

		if (typeEffectiveness > 1.0f) {
			printAndWait("It's super effective!");
		}
		else if (typeEffectiveness < 1.0f) {
			printAndWait("It wasn't very effective...");
		}
	
	}

	//Additional Effect
	//If status move, always trigger effect
	if (secondaryEffectHits || move->isStatus()) {
		moveFunctionCodeEffectPostDamage(attacker, defender, move, damage,
			attackerMults, defenderMults);
	}
	
	return true;

}

int Game::rawDamageCalculator(float level, float power, float ratingMultiplier, float modifier)
{
	return (int)
		((2.0f + 
		((2.0f + (2.0f * level) / 5.0f) * 
			power * ratingMultiplier) / 50.0f) * modifier);
}

void Game::drawBar(float factor, int size)
{
	cout << endl << "{";

	float threshold = size * factor;

	for (int i = 0; i < size; i++) {

		if (i < threshold) {
			cout << "=";
		}
		else {
			cout << " ";
		}

	}

	cout << "}" << endl;

}

bool Game::moveFunctionCodeEffectPreDamage(
	Pokemon* attacker, Pokemon* defender, MoveData* move,
	float* other, float* STAB, float* critical,
	float* typeEffectiveness,
	bool* accuracyCheck, bool* secondaryEffectCheck,
	bool* executeDamage,

	float* level, float* power,
	float* ratingMultiplier,
	int* damageOverride,
	StatMultipliers* attackerMults, StatMultipliers* defenderMults)
{
	string functionCode = move->getFunctionCode();

	const char* functionCodeChar = functionCode.c_str();

	switch (functionCodeChar[0]) {
		default:
		case '0': {
			switch (functionCodeChar[1]) {
			default:
			case '0': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '0': {
					break;
				}
				case '2': {
					//STRUGGLE
					*STAB = 1.0f;
					*typeEffectiveness = 1.0f;
					break;
				}
				}
				break;
			}
			case '6': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '0': {
					break;
				}
				case 'A': {
					//SONIC BOOM
					//Inflict fixed 20, immunity affected.
					*damageOverride = (*STAB < .1f ? 0 : 20);
					break;
				}
				case 'B': {
					//DRAGON RAGE
					//Inflict fixed 40, immunity affected.
					*damageOverride = (*STAB < .1f ? 0 : 40);
					break;
				}
				case 'F': {
					//PSYWAVE
					//Inflict random damage: 50-150% of attacker level
					//Immunities still count
					*damageOverride = (*STAB < .1f ? 0 :
						attacker->getLevel() * ((rand() % 100) + 50.0f) / 100.0f);
					break;
				}
				}
				break;
			}
			case '7': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '0': {
					//ONE HIT KO MOVES
					//Kill the target. Affected by immunities.
					*damageOverride = (*STAB < .1f ? 0 : 10000);
					break;
				}
				case '5': {
					//SURF
					//Hits double on dive
					if (defenderMults->inWater()) {
						*accuracyCheck = true;
						*power = *power * 2;
					}
					break;
				}
				case '6': {
					//EARTHQUAKE
					//Hits double on dig
					if (defenderMults->inGround()) {
						*accuracyCheck = true;
						*power = *power * 2;
					}
					break;
				}
				case '7': {
					//GUST
					//Hits double on bounce, fly, sky drop
					if (defenderMults->inSky()) {
						*power = *power * 2;
					}
					break;
				}
				case '8': {
					//TWISTER
					//Hits double on bounce, fly, sky drop, also cause flinch (in postfx)
					if (defenderMults->inSky()) {
						*power = *power * 2;
					}
					break;
				}
				case 'B': {
					//VENOSHOCK
					//Hits double on if target poisoned
					if (defender->getStatus() == Status::POISONED ||
						defender->getStatus() == Status::TOXIC) {
						*power = *power * 2;
					}
					break;
				}
				}
				break;
			}
			case 'A': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '5': {
					//Always hits.
					*accuracyCheck = true;
					break;
				}
				}
				break;
			}
			case 'C': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '9': {
					//FLY
					//If already flying, attack!
					//If not, do nothing.
					if (attackerMults->twoTurnFly) {
						attackerMults->twoTurnFly = false;
					}
					else {
						attackerMults->twoTurnFly = true;
						*executeDamage = false;
						printAndWait(attacker->getName() + " flew high up!");
					}
					break;
				}
				}
				break;
			}
			}

		}
	}

	return true;
}

bool Game::moveFunctionCodeEffectPostDamage(
	Pokemon* attacker, Pokemon* defender, MoveData* move, 
	int finalDamage,
	StatMultipliers* attackerMults, StatMultipliers* defenderMults)
{
	string functionCode = move->getFunctionCode();

	auto commonModStat = [&](MultiplierStat stat, int m, StatMultipliers* sm, Pokemon* p) {
		printAndWait(p->getName() + "'s " + sm->modStat(stat, m));
	};
	auto attackerModStat = [&](MultiplierStat stat, int m) {
		commonModStat(stat, m, attackerMults, attacker);
	};
	auto defenderModStat = [&](MultiplierStat stat, int m) {
		commonModStat(stat, m, defenderMults, defender);
	};

	auto commonModCauseMultiplier = [&](OtherMultiplier m, StatMultipliers* sm, Pokemon* p) {
		
		string namePlusSpace = p->getName() + " ";

		switch (m) {
			case ATTRACTED:
				printAndWait(namePlusSpace + sm->causeAttracted());
				break;
			case CHARGED:
				printAndWait(namePlusSpace + sm->causeCharged());
				break;
			case CONFUSED:
				printAndWait(namePlusSpace + sm->causeConfusion());
				break;
			case CURLED_UP:
				printAndWait(namePlusSpace + sm->causeCurledUp());
				break;
			case DROWSY:
				printAndWait(namePlusSpace + sm->causeDrowsiness());
				break;
			case MINIMIZED:
				printAndWait(namePlusSpace + sm->causeMinimization());
				break;
			case FLASH_FIRE:
				printAndWait(namePlusSpace + sm->causeFlashFire());
				break;
			case FOCUS_ENERGY:
				printAndWait(namePlusSpace + sm->causeFocusEnergy());
				break;
			case FLINCH:			
				printAndWait(namePlusSpace + sm->causeFlinch());
				break;
		}
	};
	auto attackerModCauseMultiplier = [&](OtherMultiplier m) {
		commonModCauseMultiplier(m, attackerMults, attacker);
	};
	auto defenderModCauseMultiplier = [&](OtherMultiplier m) {
		commonModCauseMultiplier(m, defenderMults, defender);
	};

	auto commonAfflictStatus = [&](Status s, Pokemon* p) {
		printAndWait(p->getName() + " " + p->afflictStatus(s));
	};
	auto attackerAfflictStatus = [&](Status s) {
		commonAfflictStatus(s, attacker);
	};
	auto defenderAfflictStatus = [&](Status s) {
		commonAfflictStatus(s, defender);
	};

	const char* functionCodeChar = functionCode.c_str();

	//First Digit
	switch (functionCodeChar[0]) {
	default: { break; }
	case '0': {
		//Second digit, 0
		switch (functionCodeChar[1]) {
			default: { break; }
			case '0': {
				switch (functionCodeChar[2]) {
					default: { break; }
					/* 000-002 : NO EFFECTS AND PSEUDO MOVES */
					case '0': {
						//Nothing
						break;
					}
					case '1': {
						//Splash
						break;
					}	
					case '2': {
						//STRUGGLE
						attacker->modHP(attacker->getHP() / 4); break;
					}
					/* 003-01B : STATUS PROBLEMS */
					case '3': {
						//PUTS OPPONENT TO SLEEP
						defenderAfflictStatus(Status::SLEEP); break;
					}
					case '4': {
						//MAKES OPPONENT DROWSY
						defenderModCauseMultiplier(OtherMultiplier::DROWSY); break;
					}
					case '5': {
						//POISONS OPPONENT
						if (defender->getTypeEffectivenessAgainst(PokemonType::POISON) > .1f) {
							//Only if the opponent is not poison or steel type
							defenderAfflictStatus(Status::POISONED);
						} break;
					}
					case '6': {
						//BADLY POISONS OPPONENT
						if (defender->getTypeEffectivenessAgainst(PokemonType::POISON) > .1f) {
							//Only if the opponent is not poison or steel type
							defenderAfflictStatus(Status::TOXIC);
						} break;
					}
					case '7': {
						//PARALYZES THE OPPONENT
						if (defender->getTypeEffectivenessAgainst(PokemonType::ELECTRIC) > .1f) {
							defenderAfflictStatus(Status::PARALYSIS);
						} break;
					}
					case '8': {
						//THUNDER
						//Hits even if flying
						break;
					}
					case '9': {
						//THUNDER FANG
						//10% chance for flinch, 10% chance for paralysis
						if ((rand() % 10) == 3) {
							defenderAfflictStatus(Status::PARALYSIS);
						}
						if ((rand() % 10) == 4) {
							defenderModCauseMultiplier(OtherMultiplier::FLINCH);
						}
						break;
					}
					case 'A': {
						//BURNS TARGET
						defenderAfflictStatus(Status::BURN); break;
					}
					case 'B': {
						//FIRE FANG
						//10% chance for flinch, 10% chance for burn
						if ((rand() % 10) == 3) {
							defenderAfflictStatus(Status::BURN);
						}
						if ((rand() % 10) == 4) {
							defenderModCauseMultiplier(OtherMultiplier::FLINCH);
						}
						break;
					}
					case 'C': {
						//FREEZE TARGET
						defenderAfflictStatus(Status::FREEZE); break;
					}
					case 'D': {
						//BLIZZARD
						//Freeze target and has perfect accuracy during hail
						defenderAfflictStatus(Status::FREEZE); break;
					}
					case 'E': {
						//ICE FANG
						//10% chance for flinch, 10% chance for freeze
						if ((rand() % 10) == 3) {
							defenderAfflictStatus(Status::FREEZE);
						}
						if ((rand() % 10) == 4) {
							defenderModCauseMultiplier(OtherMultiplier::FLINCH);
						} break;
					}
					case 'F': {
						//MAKES TARGET FLINCH
						defenderModCauseMultiplier(OtherMultiplier::FLINCH); break;
					}
				}
				break;
			}
			case '1': {
				switch (functionCodeChar[2]) {
					default: { break; }
					case '0': {
						//DRAGON RUSH, STEAMROLLER, STOMP
						//Makes target flinch, perfect accuracy vs. Minimized targets
						defenderModCauseMultiplier(OtherMultiplier::FLINCH); break;
					}
					case '1': {
						//SNORE
						//Flinch, but fail if not sleeping
						defenderModCauseMultiplier(OtherMultiplier::FLINCH); break;
					}
					case '2': {
						//FAKE OUT
						//Flinch but fail if not first turn
						if (defenderMults->turnCounter == 0) {
							defenderModCauseMultiplier(OtherMultiplier::FLINCH);
						}
						break;
					}
					case '3': {
						//CONFUSES TARGET
						defenderModCauseMultiplier(OtherMultiplier::CONFUSED); break;
					}
					case '4': {
						//CONFUSES TARGET (CHATTER, but same)
						defenderModCauseMultiplier(OtherMultiplier::CONFUSED); break;
					}
					case '5': {
						//HURRICANE
						//Confuses target, perfect accuracy during rainy weather,
						//50% accuracy during sunny weather, hits the target even if its
						//Flying, Sky dropping, or Bouncing
						defenderModCauseMultiplier(OtherMultiplier::CONFUSED); break;
					}
					case '6': {
						//ATTRACT
						//Attracts target if different genders.
						if ((attacker->getGender() == Gender::MALE &&
							defender->getGender() == Gender::FEMALE)
							||
							(attacker->getGender() == Gender::FEMALE &&
								defender->getGender() == Gender::MALE)) {
							defenderModCauseMultiplier(OtherMultiplier::ATTRACTED); break;
						}
					}
					case '7': {
						//TRI ATTACK
						switch (rand() % 3) {
						default:
						case 0:
							defenderAfflictStatus(Status::PARALYSIS);
							break;
						case 1:
							defenderAfflictStatus(Status::BURN);
							break;
						case 2:
							defenderAfflictStatus(Status::FREEZE);
							break;
						}
						break;
					}
					case '8': {
						//REFRESH
						//Heals burn, poison, paralysis
						attackerAfflictStatus(Status::NO_STATUS); break;
					}
					case '9': {
						//AROMATHERAPY, HEAL BELL
						//Cures all party of status conditions
						break;
					}
					case 'A': {
						//SAFEGUARD
						//Protects party from status effects
						break;
					}
					case 'B': {
						//PSYCHO SHIFT
						// The target gains the permanent status problem of the user 
						// (bad poisoning is passed across). If it does, the user's permanent 
						// status problem is cured. Fails if the target already has a permanent 
						// status problem, or if it can't be inflicted with the user's permanent 
						// status problem.
						break;
					}
					/* 01C-03F: CHANGES USER'S STAT STAGES */
					case 'C': {
						//Increases User Attack by 1 stage.
						attackerModStat(MultiplierStat::M_ATK, 1); break;
					}
					case 'D': {
						//Increases User Defense by 1 stage.
						attackerModStat(MultiplierStat::M_DEF, 1); break;
					}
					case 'E': {
						//ROLLOUT
						//Increases User Defense by 1 stage.
						//Curls up, making Rollout deal double.
						attackerModStat(MultiplierStat::M_DEF, 1);
						attackerModCauseMultiplier(OtherMultiplier::CURLED_UP); break;
					}
					case 'F': {
						//Increases User Speed by 1 stage.
						attackerModStat(MultiplierStat::M_SPE, 1); break;
					}
				}
				break;
			}
			case '2': {
				switch (functionCodeChar[2]) {
					default: { break; }
					case '0': {
					//Increases User Special Attack by 1 stage.
					attackerModStat(MultiplierStat::M_SPA, 1); break;
				}
					case '1': {
					//CHARGE
					//Increases User Special Defense by 1 stage.
					attackerModStat(MultiplierStat::M_SPD, 1);
					attackerModCauseMultiplier(OtherMultiplier::CHARGED); break;
				}
					case '2': {
					//DOUBLE TEAM
					//Increases User Evasiveness by 1 stage.
					attackerModStat(MultiplierStat::M_EVA, 1); break;
				}
					case '3': {
					//FOCUS ENERGY
					//Increases User Evasiveness by 1 stage.
					attackerModCauseMultiplier(OtherMultiplier::FOCUS_ENERGY); break;
				}
					case '4': {
					//BULK UP
					//Increases User Attack and Defense by 1 stage.
					attackerModStat(MultiplierStat::M_ATK, 1);
					attackerModStat(MultiplierStat::M_DEF, 1); break;
				}
					case '5': {
					//COIL
					//Increases User Attack, Defense and Accuracy by 1 stage.
					attackerModStat(MultiplierStat::M_ATK, 1);
					attackerModStat(MultiplierStat::M_DEF, 1);
					attackerModStat(MultiplierStat::M_ACC, 1); break;
				}
					case '6': {
					//DRAGON DANCE
					//Increases User Attack and Speed by 1 stage.
					attackerModStat(MultiplierStat::M_ATK, 1);
					attackerModStat(MultiplierStat::M_SPE, 1); break;
				}
					case '7': {
					//WORK UP
					//Increases User Attack and Special Attack by 1 stage.
					attackerModStat(MultiplierStat::M_ATK, 1);
					attackerModStat(MultiplierStat::M_SPA, 1); break;
				}
					case '8': {
					//GROWTH
					//Increases Attack and Special Attack by 1, or 2 in sunny weather.
						break;
				}
					case '9': {
					//HONE CLAWS
					//Increases Attack and Accuracy by 1
					attackerModStat(MultiplierStat::M_ATK, 1);
					attackerModStat(MultiplierStat::M_ACC, 1); break;
				}
					case 'A': {
					//COSMIC POWER and DEFEND ORDER
					//Increase Defense and Special Defense by 1
					attackerModStat(MultiplierStat::M_DEF, 1);
					attackerModStat(MultiplierStat::M_SPD, 1); break;
				}
					case 'B': {
					//QUIVER DANCE
					//Increase Specials and Speed by 1
					attackerModStat(MultiplierStat::M_SPA, 1);
					attackerModStat(MultiplierStat::M_SPD, 1);
					attackerModStat(MultiplierStat::M_SPE, 1); break;
				}
					case 'C': {
					//CALM MIND
					//Increase Specials by 1
					attackerModStat(MultiplierStat::M_SPA, 1);
					attackerModStat(MultiplierStat::M_SPD, 1); break;
				}
					case 'D': {
					//ANCIENT POWER, OMINOUS WIND, SILVER WIND
					//Raise all stats by 1
					attackerModStat(MultiplierStat::M_ATK, 1);
					attackerModStat(MultiplierStat::M_DEF, 1);
					attackerModStat(MultiplierStat::M_SPA, 1);
					attackerModStat(MultiplierStat::M_SPD, 1);
					attackerModStat(MultiplierStat::M_SPE, 1); break;
				}
					case 'E': {
					//SWORDS DANCE	
					//Raise attack by 2
					attackerModStat(MultiplierStat::M_ATK, 2); break;
				}
					case 'F': {
					//ACID ARMOR, BARRIER, IRON DEFENSE
					//Raise defense by 2
					attackerModStat(MultiplierStat::M_DEF, 2); break;
				}
				}
				break;
			}
			case '3': {
				switch (functionCodeChar[2]) {
					default: { break; }
					case '0': {
					//AGILITY, ROCK POLISH
					//Raise speed by 2
					attackerModStat(MultiplierStat::M_SPE, 2); break;
				}
					case '1': {
					//AUTOMIZE
					//Raise speed by 2, lower weight
					attackerModStat(MultiplierStat::M_SPE, 2); break;
				}
					case '2': {
					//NASTY PLOT
					//Raise special attack by 2
					attackerModStat(MultiplierStat::M_SPA, 2); break;
				}
					case '3': {
					//AMNESIA
					//Raise special defense by 2
					attackerModStat(MultiplierStat::M_SPD, 2); break;
				}
					case '4': {
					//MINIMIZE
					//Raise Evasion, also minimize
					attackerModStat(MultiplierStat::M_EVA, 2);
					attackerModCauseMultiplier(OtherMultiplier::MINIMIZED); break;
				}
					case '5': {
					//SHELL SMASH
					//Def and SpDef -1, Atk Speed and SpAtk +2
					attackerModStat(MultiplierStat::M_DEF, -1);
					attackerModStat(MultiplierStat::M_SPD, -1);
					attackerModStat(MultiplierStat::M_ATK, 2);
					attackerModStat(MultiplierStat::M_SPA, 2);
					attackerModStat(MultiplierStat::M_SPE, 2); break;
				}
					case '6': {
					//SHIFT GEAR
					//Increases speed by 2, increases attack by 1
					attackerModStat(MultiplierStat::M_SPE, 2);
					attackerModStat(MultiplierStat::M_ATK, 1); break;
				}
					case '7': {
					//ACUPUNCTURE
					//Increase random stat by 2 stages.
						switch (rand() % 7) {
							default:
							case 0:
								attackerModStat(MultiplierStat::M_ATK, 2); break;
							case 1:
								attackerModStat(MultiplierStat::M_DEF, 2); break;
							case 2:
								attackerModStat(MultiplierStat::M_SPA, 2); break;
							case 3:
								attackerModStat(MultiplierStat::M_SPD, 2); break;
							case 4:
								attackerModStat(MultiplierStat::M_SPE, 2); break;
							case 5:
								attackerModStat(MultiplierStat::M_EVA, 2); break;
							case 6:
								attackerModStat(MultiplierStat::M_ACC, 2); break;
						} break;
					}
					case '8': {
					//COTTON GUARD
					//Increase defense by 3
					attackerModStat(MultiplierStat::M_DEF, 3); break;
				}
					case '9': {
					//TAIL GLOW
					//Increase special attack by 3
					attackerModStat(MultiplierStat::M_SPA, 3); break;
				}
					case 'A': {
					//BELLY DRUM
					//Reduces health to half, but only if wont faint.
					//Also fails if attack is at +6.
						break;
				}
					case 'B': {
					//SUPERPOWER
					//Decrease Attack and Defense by 1
					attackerModStat(MultiplierStat::M_ATK, -1);
					attackerModStat(MultiplierStat::M_DEF, -1); break;
				}
					case 'C': {
					//CLOSE COMBAT, DRAGON ASCENT
					//Decrease SP Def and Defense by 1
					attackerModStat(MultiplierStat::M_SPD, -1);
					attackerModStat(MultiplierStat::M_DEF, -1); break;
				}
					case 'D': {
					//V-CREATE
					//Decrease Def, Speed and Sp Def by 1
						break;
				}
					case 'E': {
					//HAMMER ARM
					//Decreases Speed by 1
					attackerModStat(MultiplierStat::M_SPE, -1); break;
				}
					case 'F': {
					//DRACO METEOR, LEAF STORM, OVERHEAT, PSYCHO BOOST
					//Decreases Special Attack by 2 stages
					attackerModStat(MultiplierStat::M_SPA, -2); break;
				}
				}
				break;
			}
			case '4': {
				switch (functionCodeChar[2]) {
					default: { break; }
					/*040-04F : Changes foe stats*/
					case '0': {
					//FLATTER
					//Increases target's special attack by 1 and confuses them
					defenderModStat(MultiplierStat::M_SPA, 1);
					defenderModCauseMultiplier(OtherMultiplier::CONFUSED); break;
				}
					case '1': {
					//SWAGGER
					//Increases target's attack by 2 and confuses them
					defenderModCauseMultiplier(OtherMultiplier::CONFUSED); break;
				}
					case '2': {
					//Decreases Attack by 1 stage
					defenderModStat(MultiplierStat::M_ATK, -1); break;
				}
					case '3': {
					//Decreases Defense by 1 stage
					defenderModStat(MultiplierStat::M_DEF, -1); break;
				}
					case '4': {
					//Decrease Speed by 1 stage
					defenderModStat(MultiplierStat::M_SPE, -1); break;
				}
					case '5': {
					//Decrease Sp Atk by 1 stage
					defenderModStat(MultiplierStat::M_SPA, -1); break;
				}
					case '6': {
					//Decrease target special defense by 1 stage
					defenderModStat(MultiplierStat::M_SPD, -1); break;
				}
					case '7': {
					//Decrease target accuracy by 1 stage
					defenderModStat(MultiplierStat::M_ACC, -1); break;
				}
					case '8': {
						//Decrease target special defense by 1 stage
						defenderModStat(MultiplierStat::M_EVA, -1); break;
					}
					case '9': {}
					case 'A': {}
					case 'B': {}
					case 'C': {}
					case 'D': {}
					case 'E': {}
					case 'F': {}
				}
				break;
			}
			case '5': {
				switch (functionCodeChar[2]) {
					default: { break; }
					/*050-05B : Other changes to stats and stat changes*/
					case '0': {}
					case '1': {}
					case '2': {}
					case '3': {}
					case '4': {}
					case '5': {}
					case '6': {}
					case '7': {}
					case '8': {}
					case '9': {}
					case 'A': {}
					case 'B': {}
					/*05C-069 : Changes attributes of Pokemon*/
					case 'C': {}
					case 'D': {}
					case 'E': {}
					case 'F': {}
				}
				break;
	}
			case '6': {
				switch (functionCodeChar[2]) {
					default: { break; }
					case '0': {}
					case '1': {}
					case '2': {}
					case '3': {}
					case '4': {}
					case '5': {}
					case '6': {}
					case '7': {}
					case '8': {}
					case '9': {}
					/*06A-074 : Inflicts fixed amount of damage*/
					case 'A': {}
					case 'B': {}
					case 'C': {}
					case 'D': {}
					case 'E': {}
					case 'F': {}
				}
				break;
	}
			case '7': {
				switch (functionCodeChar[2]) {
					default: { break; }
					case '0': {}
					case '1': {}
					case '2': {}
					case '3': {}
					case '4': {}
					case '5': {}
					/*075-0A4 : Affects an attack's power, type or effect*/
					case '6': {}
					case '7': {}
					case '8': {
						//TWISTER
						//Cause flinch if in sky
						if (defenderMults->inSky()) {
							defenderModCauseMultiplier(OtherMultiplier::FLINCH);
						}
						break;
					}
					case '9': {}
					case 'A': {}
					case 'B': {}
					case 'C': {}
					case 'D': {}
					case 'E': {}
					case 'F': {}
				}
				break;
	}
			case '8': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '0': {}
				case '1': {}
				case '2': {}
				case '3': {}
				case '4': {}
				case '5': {}
				case '6': {}
				case '7': {}
				case '8': {}
				case '9': {}
				case 'A': {}
				case 'B': {}
				case 'C': {}
				case 'D': {}
				case 'E': {}
				case 'F': {}
				}
				break;
	}
			case '9': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '0': {}
				case '1': {}
				case '2': {}
				case '3': {}
				case '4': {}
				case '5': {}
				case '6': {}
				case '7': {}
				case '8': {}
				case '9': {}
				case 'A': {}
				case 'B': {}
				case 'C': {}
				case 'D': {}
				case 'E': {}
				case 'F': {}
				}
				break;
	}
			case 'A': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '0': {}
				case '1': {}
				case '2': {}
				case '3': {}
				case '4': {}
				/*0A5-0AD : Attacks hitting and being avoided*/
				case '5': {}
				case '6': {}
				case '7': {}
				case '8': {}
				case '9': {}
				case 'A': {}
				case 'B': {}
				case 'C': {}
				case 'D': {}
				/*0AE-0BC : Affects the attack used*/
				case 'E': {}
				case 'F': {}
				}
				break;
	}
			case 'B': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '0': {}
				case '1': {}
				case '2': {}
				case '3': {}
				case '4': {}
				case '5': {}
				case '6': {}
				case '7': {}
				case '8': {}
				case '9': {}
				case 'A': {}
				case 'B': {}
				case 'C': {}
				/*0BD-0D4 : Multi-hit & multi-turn attacks*/
				case 'D': {}
				case 'E': {}
				case 'F': {}
				}
				break;
	}
			case 'C': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '0': {}
				case '1': {}
				case '2': {}
				case '3': {}
				case '4': {}
				case '5': {}
				case '6': {}
				case '7': {}
				case '8': {}
				case '9': {}
				case 'A': {}
				case 'B': {}
				case 'C': {}
				case 'D': {}
				case 'E': {}
				case 'F': {}
				}
				break;
	}
			case 'D': {
				switch (functionCodeChar[2]) {
				default: { break; }
				case '0': {}
				case '1': {}
				case '2': {}
				case '3': {}
				case '4': {}
				/*0D5-0DF : Healing moves*/
				case '5': {}
				case '6': {}
				case '7': {}
				case '8': {}
				case '9': {}
				case 'A': {}
				case 'B': {}
				case 'C': {}
				case 'D': {
					//User gains half damage dealt, min 1
					int halfD = finalDamage / 2;
					attacker->modHP(halfD > 0 ? halfD : 1);
				}
				case 'E': {}
				case 'F': {}
				}
				break;
	}
			case 'E': {
				switch (functionCodeChar[2]) {
				default: { break; }
				/*0E0-0E9 : Involves fainting*/
				case '0': {}
				case '1': {}
				case '2': {}
				case '3': {}
				case '4': {}
				case '5': {}
				case '6': {}
				case '7': {}
				case '8': {}
				case '9': {}
				/*0EA-0EF : Switching and Fleeing*/
				case 'A': {}
				case 'B': {}
				case 'C': {}
				case 'D': {}
				case 'E': {}
				case 'F': {}
				}
				break;
	}
			case 'F': {
				switch (functionCodeChar[2]) {
				default: { break; }
				/*0F0-0F9 : Items*/
				case '0': {}
				case '1': {}
				case '2': {}
				case '3': {}
				case '4': {}
				case '5': {}
				case '6': {}
				case '7': {}
				case '8': {}
				case '9': {}
				/*0FA-0FE : Attacks with recoil*/
				case 'A': {}
				case 'B': {}
				case 'C': {}
				case 'D': {}
				case 'E': {}
				/*0FF-102 : Weather-induces*/
				case 'F': {}
			}
			break;
		}
		}
		break;
	}
	case '1': {
		//Second digit, 1
		switch (functionCodeChar[1]) {
			default:
			case '0': {
				switch (functionCodeChar[2]) {
				default:
				case '0': {}
				case '1': {}
				case '2': {}
				/*103-105 : Entry hazards*/
				case '3': {}
				case '4': {}
				case '5': {}
				/*106-108 : Pledge attacks*/
				case '6': {}
				case '7': {}
				case '8': {}
				/*109+    : Other*/
				case '9': {}
				case 'A': {}
				case 'B': {}
				case 'C': {}
				case 'D': {}
				case 'E': {}
				case 'F': {}
				}
				break;
			}
			case '1': {
				switch (functionCodeChar[2]) {
				default:
				case '0': {}
				case '1': {}
				case '2': {}
				case '3': {}
				case '4': {}
				case '5': {}
				case '6': {}
				case '7': {}
				case '8': {}
				case '9': {}
				case 'A': {}
				case 'B': {}
				case 'C': {}
				case 'D': {}
				case 'E': {}
				case 'F': {}
				}
				break;
			}
			case '2': {
			switch (functionCodeChar[2]) {
			default:
			case '0': {}
			case '1': {}
			case '2': {}
			case '3': {}
			case '4': {}
			case '5': {}
			}
			break;
		}
		}
		break;
	}
	
	}

	return true;
}

bool Game::abilityMoveEffect(Pokemon* attacker, Pokemon* defender, MoveData* move, float* other)
{
	
	string attackerAbil = attacker->getAbility();
	string defenderAbil = defender->getAbility();


	//ABILITIES EFFECTS ON ATTACK
	

	//ABILITY EFFECTS ON DEFENSE


	return false;

}

string StatMultipliers::causeAttracted() {
	attracted = true;
	return "fell in love!";
}
string StatMultipliers::causeCharged() {
	charged = true;
	return "is getting charged!";
}
string StatMultipliers::causeConfusion() {
	confusionCounter = (rand() % 3) + 1;
	return "became confused!";
}
string StatMultipliers::causeCurledUp() {
	curledUp = true;
	return "is curling up!";
}
string StatMultipliers::causeDrowsiness() {
	drowsyCounter = 1;
	return "is getting drowsy!";
}
string StatMultipliers::causeMinimization() {
	minimized = true;
	return "grew smaller!";
}
string StatMultipliers::causeFlashFire() {
	flashFire = true;
	return "powered up from the flames!";
}
string StatMultipliers::causeFocusEnergy() {
	focusEnergy = true;
	return "is getting pumped!";
}
string StatMultipliers::causeFlinch() {
	flinch = true;
	return "flinched!";
}

const float StatMultipliers::multipliers[13] = {
		0.25f, 0.28f, 0.33f, 0.40f, 0.50f, 0.66f,
		1.00f,
		1.50f, 2.00f, 2.50f, 3.00f, 3.50f, 4.00f
};
const float StatMultipliers::EVAACCMultipliers[13] = {
		0.33f, 0.36f, 0.43f, 0.50f, 0.60f, 0.75f,
		1.00f,
		1.33f, 1.66f, 2.00f, 2.33f, 2.66f, 3.00f
};
const string StatMultipliers::tags[7] = { " severely!", " harshly!", "!", "!", "!", " sharply!", " drastically!" };