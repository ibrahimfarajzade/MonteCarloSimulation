#include "Simulation.h"

using namespace CTIS476;

template<typename randomized>
int Simulation::randValue(const std::list<randomized>& list) const {
	return rand() % list.size();
}

template<typename randomized>
randomized Simulation::randSoldier(const std::list<randomized>& list) const {
	auto const number = randValue(list);
	return *std::next(list.begin(), number);
}

Simulation::Simulation(std::list<Soldier*> blues, std::list<Soldier*> reds) {
	this->blues = blues;
	this->reds = reds;
	//random number initialization
	srand(time(NULL));
}

Simulation::~Simulation() {
	// do your memory deallocation
	// memory management is important
}

void Simulation::initialize() {
	for (Soldier* soldier : blues)
		soldier->initialize();
	for (Soldier* soldier : reds) 
		soldier->initialize();
}

void Simulation::iterate()
{
	//iterate simulation with a single step
	//the modeling behaviour must be implemented as described in class
	//BEWARE: Model execution order problem

	auto const redscount = getNumberOfRemainingSoldiers(reds);
	auto const bluescount = getNumberOfRemainingSoldiers(blues);

	writeWithTab("Blues: ");

	for (Soldier* blue: blues)
		positionChanged(blue, redscount);

	writeln();

	writeWithTab("Reds : ");
	for (Soldier* red : reds)
		positionChanged(red, bluescount);

	writeln();

	for (Soldier* blue : bluescount)
		blue->applyState();
	for (Soldier* red : redscount)
		red->applyState();
}

void Simulation::positionChanged(Soldier* soldier, const std::list<Soldier*> enemy) {
	
	if (soldier->isDead()) {
		write(".");
		return;
	}

	if (shootSoldierAttempt(soldier, enemy) == false)
		changeSoldierLocation(soldier, enemy);
}

bool Simulation::shootSoldierAttempt(const Soldier* soldier, const std::list<Soldier*> enemy) {
	auto const closeEnemies = getEnemiesAround(soldier, enemy);

	if (closeEnemies.size() <= 0)
		return false;

	killSoldierAttempt(soldier, randSoldier(closeEnemies));
	return true;
}

void Simulation::killSoldierAttempt(const Soldier* soldier, Soldier* enemy) {

	if (generateProbability() <= soldier->getProbabilityOfKill()) {
		write("+");
		enemy->kill();
	}
	else
		write("-");
}

void Simulation::changeSoldierLocation(Soldier* soldier, const std::list<Soldier*> enemy) {
	
	write("M");

	auto const speed = soldier->getSpeed();
	auto const shooterLocation = soldier->getLocation();
	auto const enemyLocation = randSoldier(enemy)->getLocation();
	

	auto const diff = (enemyLocation - shooterLocation).normalized() * speed;
	soldier->setLocation(shooterLocation + diff);
}


std::list<Soldier*> Simulation::getEnemiesAround(const Soldier* soldier, const std::list<Soldier*> enemy) {
	std::list<Soldier*> obj;
	auto const location = soldier->getLocation();

	for (Soldier* soldier : enemy) {
		auto const location = soldier->getLocation();
		auto const distance = location.squaredDistance(location);

		if (distance <= powf(soldier->getRange(), 2))
			obj.push_back(soldier);
	}

	return obj;
}

std::list<Soldier*> Simulation::getNumberOfRemainingSoldiers(const std::list<Soldier*> soldiers) {
	std::list<Soldier*> obj;

	for (Soldier* soldier : soldiers)
		if (!soldier->isDead()) 
			obj.push_back(soldier);

	return obj;
}

bool Simulation::checkLost(const std::list<Soldier*> color) const {
	if (remainingSoldiers(color) <= 0)
		return true;

	return false;
}

int Simulation::remainingSoldiers(const std::list<Soldier*> color) const {
	int aliveCount = color.size();

	for (auto soldier : color)
		if (soldier->isDead())
			aliveCount = aliveCount-1;

	return aliveCount;
}

bool Simulation::isCompleted()
{
	if (checkLost(blues) == true || checkLost(reds) == true)
		return true;
	return false;
}

void Simulation::getNumberOfAlive(int& blue, int& red)
{
	blue = remainingSoldiers(blues);
	red = remainingSoldiers(reds);
	//calculate the number of survivors in each side
}

int Simulation::getScore() {

	//calculate the score
	//look header explanations
	return remainingSoldiers(blues) - remainingSoldiers(reds);
}

float Simulation::generateProbability() const {

	float random = (float)(rand() % 1000) / 1000.0f;
	return random;
}