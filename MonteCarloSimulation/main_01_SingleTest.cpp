#include <stdio.h>
#include <iostream>
#include <map> 

#include <windows.h>

#include "CommonHeader.h"
#define NUMBER_OF_RUNS 1

//In this run everything is in a fixed location
//Every entity is in range
//We are testing our ability to shoot for a single entity
//PoK is 1.0 which means every shot is a hit

int main(int argc, char *argv[])
{
	std::cout << "In this run everything is in a fixed location\n";
	std::cout << "Every entity is in range\n";
	std::cout << "We are testing our ability to shoot for a single entity\n";
	std::cout << "PoK is 1.0 which means every shot is a hit\n\n";

	std::list<CTIS476::Soldier*> blues;
	std::list<CTIS476::Soldier*> reds;
	CTIS476::LocationStruct loc1(0.0f, 0.0f);
	CTIS476::LocationStruct loc2(10.0f, 10.0f);
	float pok = 1.0f;
	float speed = 0.0f;
	float range = 15.0f;
	blues.push_back(new CTIS476::Soldier(loc1, speed, pok, range));
	reds.push_back(new CTIS476::Soldier(loc2, speed, pok, range));

	CTIS476::Simulation s(blues, reds);

	runSimulation(s, NUMBER_OF_RUNS);

	system("Pause");

}