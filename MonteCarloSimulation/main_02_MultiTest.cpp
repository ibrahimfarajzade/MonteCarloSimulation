#include <stdio.h>
#include <iostream>
#include <map> 
#include <windows.h>

#include "CommonHeader.h"
#define NUMBER_OF_RUNS 10

//In this run everything is in a fixed location
//Every entity is in range
//We are testing our ability to shoot for with multiple entities
//PoK is 1.0 which means every shot is a hit
//Think about the difference between this and first one

int main(int argc, char *argv[])
{
	std::cout << "In this run everything is in a fixed location\n";
	std::cout << "Every entity is in range\n";
	std::cout << "We are testing our ability to shoot for with multiple entities\n";
	std::cout << "PoK is 1.0 which means every shot is a hit\n";
	std::cout << "Think about the difference between this and first one\n\n";

	std::list<Soldier*> blues;
	std::list<Soldier*> reds;
	LocationStruct loc1(0.0f, 0.0f);
	LocationStruct loc2(0.0f, 10.0f);
	float pok = 1.0f;
	float speed = 0.0f;
	float range = 15.0f;
	for (int i = 0; i < 10;i++)
	{
		loc1.x++;
		blues.push_back(new Soldier(loc1, speed, pok, range));
		loc2.x++;
		reds.push_back(new Soldier(loc2, speed, pok, range));
	}

	Simulation s(blues, reds);

	runSimulation(s, NUMBER_OF_RUNS);

	system("Pause");

}