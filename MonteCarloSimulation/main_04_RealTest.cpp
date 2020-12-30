#include <stdio.h>
#include <iostream>
#include <map> 
#include <windows.h>

#include "CommonHeader.h"
#define NUMBER_OF_RUNS 10000

//In this run sides are apart
//Every entity is out of range
//We are building a complete test  
//PoK is 0.1 which means every shot has a %10 probability to hit

int main(int argc, char *argv[])
{
	std::cout << "In this run sides are apart\n";
	std::cout << "Every entity is out of range\n";
	std::cout << "We are building a complete test  \n";
	std::cout << "PoK is 0.1 which means every shot has a %10 probability to hit\n\n";
	std::list<Soldier*> blues;
	std::list<Soldier*> reds;
	LocationStruct loc1(0.0f, 0.0f);
	LocationStruct loc2(0.0f, 100.0f);
	float pok = 0.1f;
	float speed = 10.0f;
	float range = 15.0f;
	for (int i = 0; i < 100; i++)
	{
		loc1.x++;
		blues.push_back(new Soldier(loc1, speed, pok, 15.0f));
		loc2.x++;
		reds.push_back(new Soldier(loc2, speed, pok, 15.0f));
	}

	Simulation s(blues, reds);

	runSimulation(s, NUMBER_OF_RUNS);

	system("Pause");

}