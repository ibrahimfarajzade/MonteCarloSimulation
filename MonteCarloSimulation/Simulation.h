#pragma once
#include "Soldier.h"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iostream>
#include <math.h> 

#define M_PI       3.14159265358979323846

namespace CTIS476 {

	class Simulation {
	public:
		//constructor
		Simulation(std::list<Soldier*> blues, std::list<Soldier*> reds);
		//destructor
		~Simulation();

		//this methods is required for re-initializing simulation to its first status
		void initialize();

		//operate simulation models once
		void iterate();

		//return true if one side is annihilated
		bool isCompleted();

		//return alive numbers of each side
		void getNumberOfAlive(int& blue, int& red);

		//return number of survived soldiers
		//positive if blue wins
		//negative if red wins
		int getScore();

	private:
		std::list<Soldier*> getNumberOfRemainingSoldiers(const std::list<Soldier*> soldiers);
		std::list<Soldier*> getEnemiesAround(const Soldier * soldier, const std::list<Soldier*> enemy);

		// random index
		template<typename randomized>
		int randValue(const std::list<randomized>& list) const;

		// random soldier
		template<typename randomized>
		randomized randSoldier(const std::list<randomized>& list) const;

		// changes soldier and enemy locations if shoot attempt failed
		void positionChanged(Soldier* soldier, const std::list<Soldier*> enemy);

		// call probability function and try to kill the enemy object
		void killSoldierAttempt(const Soldier* soldier, Soldier* enemy);

		// try to shoot the enemy object
		bool shootSoldierAttempt(const Soldier* soldier, const std::list<Soldier*> enemy);
		
		// change location of the soldier object
		void changeSoldierLocation(Soldier* soldier, const std::list<Soldier*> enemy);

		// check if team has lost all the soldiers
		bool checkLost(const std::list<Soldier*> side) const;

		// return the number of remaining soldiers
		int remainingSoldiers(const std::list<Soldier*> side) const;

	private:
		std::list<Soldier*> blues;
		std::list<Soldier*> reds;

	private: 
		//get a random number
		float generateProbability() const;
		//helper print functios
		void writeWithTab(std::string val)
		{
#ifdef PRINT_LOGS	
			std::cout << "    " << val;
#endif
		}
		void write(std::string val)
		{
#ifdef PRINT_LOGS	
			std::cout << "" << val;
#endif
		}
		void writeln(std::string val = "")
		{
#ifdef PRINT_LOGS	
			std::cout << "" << val << std::endl;
#endif	
		}
	};

}