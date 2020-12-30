#pragma once
#include <exception>
#include <string>

#define PRINT_LOGS

namespace CTIS476 {

	class SoldierException : public std::exception
	{
	private:
		std::string error;
	public:
		SoldierException(std::string error) :error{ error } {}
		const char* what() const throw()
		{
			return error.c_str();
		}
	};

	struct LocationStruct
	{
		LocationStruct(float x, float y) :x(x), y(y) {}
		LocationStruct() = default;
		float x;
		float y;

		LocationStruct operator-(const LocationStruct& value) const {
			return LocationStruct(x - value.x, y - value.y);
		}

		LocationStruct operator+(const LocationStruct& value) const {
			return LocationStruct(x + value.x, y + value.y);
		}

		LocationStruct operator*(const float value) const {
			return LocationStruct(x * value, y * value);
		}

		LocationStruct operator/(const float value) const {
			return LocationStruct(x / value, y / value);
		}

		LocationStruct normalized() const {
			return *this / magnitude();
		}

		float distance(const LocationStruct& obj) const {
			return sqrtf(this->squaredDistance(obj));
		}

		float squaredDistance(const LocationStruct& obj) const {
			auto distance = *this - obj;
			return (distance.x * distance.x) + (distance.y * distance.y);
		}

		float magnitude() const {
			return sqrtf(squaredMagnitude());
		}

		float squaredMagnitude() const {
			return (x * x) + (y * y);
		}

	};

	class Soldier
	{
	public:
		//constructor
		Soldier(LocationStruct location, float speed, float probabilityOfKill, float range);
		//destructor
		~Soldier();

		//this methods is required for re-initializing models to their first status
		void initialize();

		//getter methods
		const LocationStruct& getLocation() const;
		float getRange() const;
		float getProbabilityOfKill() const;
		float getSpeed() const;
		bool isDead() const;

		//action methods
		void kill();
		void setLocation(LocationStruct location) throw(SoldierException);

		// returns if the soldier was shot and killed this iteration 
		// in other words, returns if the soldier will be dead next iteration
		bool temporaryIsDead() const;

		//this method applies the provisional state to the current state
		//call at the end of each iteration
		void applyState();

	private:
		LocationStruct initialLocation;
		LocationStruct currentLocation;
		LocationStruct temporaryLocation;

		float initialSpeed;
		float currentSpeed;

		float initialProbabilityOfKill;
		float currentProbabilityOfKill;

		float initialRange;
		float currentRange;

		bool initialState;
		bool currentState;
		bool temporaryState;
	};
}