#include <iostream>
#include <string>

class Vehicle
{
public:
	std::string name() { return name_; }
	int number_of_wheels() { return number_of_wheels_; }
	std::string propulsion_type() { return propulsion_type_; }
	double max_speed() { return max_speed_; }

protected:
	Vehicle(const std::string& name, int number_of_wheels,
	        const std::string& propulsion_type, double max_speed)
		: name_(name), number_of_wheels_(number_of_wheels),
		  propulsion_type_(propulsion_type), max_speed_(max_speed) {
	}

	std::string name_;
	int number_of_wheels_;
	std::string propulsion_type_;
	double max_speed_;
private:
	int foo;
};

//class Bike : public/private/protected/_ Vehicle
class Bike : private Vehicle
{
public:
	Bike() : Vehicle("Bike", 2, "Muscles", 30) {
	}


	void bar() {

		std::cout << name();


	}


public:
};

class Bike3Wheels : public Bike
{

	void baz() {

		//std::cout << name();
		bar();
		
	}
	
};

int bar() {
	Bike bike;

	//std::cout << bike.name();
	//std::cout << bike.name_;

	return 0;

}
