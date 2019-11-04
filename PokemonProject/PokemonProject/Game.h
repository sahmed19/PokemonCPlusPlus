#pragma once
#include <iostream>
#include <string>
#include "Trainer.h"
#include "Pokemon.h"
#include "Pokedex.h"
#include "MoveDex.h"

using namespace std;

enum Weather {
	NO_WEATHER,
	SUN,
	RAIN,
	HAIL,
	SAND
};

struct GlobalMapEffects {

	Weather weather;

};

struct SideMapEffects {
	bool mapStealthRocks = false;
	bool leechSeed = false;
	

	int mapSpikes = 0;
	int mapToxicSpikes = 0;
	int mapMist = 0;

	int lightScreenCounter = 0;
	int reflectCounter = 0;
	int safeguardCounter = 0;
	int tailwindCounter = 0;
};

enum MultiplierStat {
	M_ATK,
	M_DEF,
	M_SPA,
	M_SPD,
	M_SPE,
	M_ACC,
	M_EVA
};

enum OtherMultiplier {
	ATTRACTED,
	CHARGED,
	CONFUSED,
	CURLED_UP,
	DROWSY,
	MINIMIZED,
	FLASH_FIRE,
	FOCUS_ENERGY,
	FLINCH
};

class StatMultipliers {
public:

	string causeAttracted();
	string causeCharged();
	string causeConfusion();
	string causeCurledUp();
	string causeDrowsiness();
	string causeMinimization();
	string causeFlashFire();
	string causeFocusEnergy();
	string causeFlinch();

	inline bool inWater() const { return twoTurnDive; }
	inline bool inGround() const { return twoTurnDig; }
	inline bool inSky() const { return twoTurnFly || twoTurnBounce || twoTurnSkyDrop; }

	//Permanent
	SideMapEffects mapEffects;

	float getATKMod() {
		return multipliers[ATK + 6]; 
	}
	float getDEFMod() { 
		return multipliers[DEF + 6]; 
	}
	float getSPAMod() { 
		return multipliers[SPA + 6]; 
	}
	float getSPDMod() { 
		return multipliers[SPD + 6]; 
	}
	float getSPEMod() { 

		return multipliers[SPE + 6]; 
	}
	float getEVAMod() { 
		return EVAACCMultipliers[EVA + 6]; 
	}
	float getACCMod() { 
		return EVAACCMultipliers[ACC + 6]; 
	}

	string modStat(MultiplierStat stat, int m) {
		
		int r = 0;

		int tagIndex = m + 3;
		if (tagIndex > 6) { tagIndex = 6; }
		else if (tagIndex < 0) { tagIndex = 0; }

		string roseOrFell = (m > 0 ? "rose" : "fell");

		switch (stat) {
		default:
		case MultiplierStat::M_ATK:
			r = modATK(m); if (r == 0)
			{
				return "Attack " + roseOrFell + tags[tagIndex];
			} break;
		case MultiplierStat::M_DEF:
			r = modDEF(m); if (r == 0)
			{
				return "Defense " + roseOrFell + tags[tagIndex] + "!";
			} break;
		case MultiplierStat::M_SPA:
			r = modSPA(m); if (r == 0)
			{
				return "Special Attack " + roseOrFell + tags[tagIndex];
			} break;
		case MultiplierStat::M_SPD:
			r = modSPD(m); if (r == 0)
			{
				return "Special Defense " + roseOrFell + tags[tagIndex];
			} break;
		case MultiplierStat::M_SPE:
			r = modSPE(m); if (r == 0)
			{
				return "Speed " + roseOrFell + tags[tagIndex];
			} break;
		case MultiplierStat::M_ACC:
			r = modACC(m); if (r == 0)
			{
				return "Accuracy " + roseOrFell + tags[tagIndex];
			} break;
		case MultiplierStat::M_EVA:
			r = modEVA(m); if (r == 0)
			{
				return "Evasiveness " + roseOrFell + tags[tagIndex];
			} break;
		}


		if (r > 0) { return "couldn't go any higher!"; }
		if (r < 0) { return "couldn't go any lower!"; }
			
	}

	int modATK(int m) {
		if (ATK == 6) { return 1; }
		else if (ATK == -6) { return -1; }
		ATK = clamp(ATK + m); return 0;
	}
	int modDEF(int m) {
		if (DEF == 6) { return 1; }
		else if (DEF == -6) { return -1; }
		DEF = clamp(DEF + m); return 0;
	}
	int modSPA(int m) {
		if (SPA == 6) { return 1; }
		else if (SPA == -6) { return -1; }
		SPA = clamp(SPA + m); return 0;
	}
	int modSPD(int m) {
		if (SPD == 6) { return 1; }
		else if (SPD == -6) { return -1; }
		SPD = clamp(SPD + m); return 0;
	}
	int modSPE(int m) {
		if (SPE == 6) { return 1; }
		else if (SPE == -6) { return -1; }
		SPE = clamp(SPE + m); return 0;
	}
	int modEVA(int m) {
		if (EVA == 6) { return 1; }
		else if (EVA == -6) { return -1; }
		EVA = clamp(EVA + m); return 0;
	}
	int modACC(int m) {
		if (ACC == 6) { return 1; }
		else if (ACC == -6) { return -1; }
		ACC = clamp(ACC + m); return 0;
	}
	
	bool twoTurnBounce = false;
	bool twoTurnDig = false;
	bool twoTurnDive = false;
	bool twoTurnFly = false;
	bool twoTurnSolarbeam = false;
	bool twoTurnSkyDrop = false;

	int turnCounter = 0;

private:
	int ATK = 0; 
	int DEF = 0; 
	int SPA = 0; 
	int SPD = 0; 
	int SPE = 0; 
	int EVA = 0; 
	int ACC = 0;

	bool attracted = false;
	bool charged = false;
	bool curledUp = false;
	bool minimized = false;
	bool flashFire = false;
	bool flinch = false;
	bool focusEnergy = false;

	bool protect = false;
	bool foresightIdentified = false;

	int protectCounter = 0;
	int drowsyCounter = 0;
	int confusionCounter = 0;

	int clamp(int x) {
		if (x > 6) { return 6; }
		else if (x < -6) { return -6; }
		return x;
	}
	
	static const float multipliers[13];
	static const float EVAACCMultipliers[13];
	static const string tags[7];
};

class Game
{

public:
	Game();

	inline bool isPlaying() const { return playing; }

	void gameLoop();

	inline int getOption(string* messages = nullptr, int count = 0) const;
	
	inline void waitEnter(bool dotted = true) const {
		if (dotted) { std::cout << endl << "..."; }
		while (std::cin.get() != '\n');
	}

	inline void printAndWait(string s) const {
		cout << endl << s << endl;
		waitEnter();
	}

	bool battleTrainer(Trainer* player, Trainer* opponent);

	bool damageCalculator(
		Pokemon* attacker, Pokemon* defender, MoveData* move,
		StatMultipliers* attackerMults, StatMultipliers* defenderMults);

	int rawDamageCalculator(
		float level, float power, float ratingMultiplier, float modifier);

	void drawBar(float factor, int size = 100);

	bool moveFunctionCodeEffectPreDamage(
		Pokemon* attacker, Pokemon* defender,
		MoveData* move, 
		float* other, float* STAB, 
		float* critical, float* typeEffectiveness,
		bool* accuracyCheck, bool* secondaryEffectCheck,
		bool* executeDamage,
		float* level, float* power, 
		float* ratingMultiplier,
		int* damageOverride,
		StatMultipliers* attackerMults, StatMultipliers* defenderMults);

	bool moveFunctionCodeEffectPostDamage(
		Pokemon* attacker, Pokemon* defender, 
		MoveData* move,
		int finalDamage,
		StatMultipliers* attackerMults, StatMultipliers* defenderMults);

	bool abilityMoveEffect(Pokemon* attacker, Pokemon* defender, 
		MoveData* move, float* other);


private:
	bool playing;
};

