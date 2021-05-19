#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>

class Force
{
	// It is good practice to keep class attributes private when possible
private:
	double angle;
	double force;
	double position;
	double permForce;
	double varForce;
public:
	// Have to have the default constructor due to the compiler not making one when a custom constructor is declared.
	Force()
	{

	}

	// Force in Newtons (N)
	Force(double force, double angle, double position)
	{
		this->force = force;
		this->angle = angle;
		this->position = position;
	}


	void setPermanent(bool ULS, double force)
	{
		if (ULS)
		{
			this->permForce = force * 1.35;
		}
		else
		{
			this->permForce = force;
		}
	}

	double getPermanent()
	{
		return permForce;
	}

	void setVariable(bool ULS, double force)
	{
		if(ULS)
		{
			this->varForce = force * 1.5;
		}
		else
		{
			this->varForce = force;
		}
	}

	double getVariable()
	{
		return varForce;
	}

	void setPosition(double position)
	{
		this->position = position;
	}

	double getPosition()
	{
		return position;
	}

	void setAngle(double angle)
	{
		this->angle = angle;
	}

	double getAngle()
	{
		if (angle)
		{
			return angle;
		}
		else 
		{
			std::cout << "Angle not known." << std::endl;
			return 0;
		}
	}

	double getForce()
	{
		if (force)
		{
			return force;
		}
		else
		{
			std::cout << "Force not known." << std::endl;
			return 0;
		}
	}

	void setForce(double force)
	{
		this->force = force;
	}

};

class Moment
{
private:
	Force force;
	double position;
	double momentValue;
	double angle;

	bool set = false;

	double toRadians(double degree)
	{
		return (M_PI * degree) / 180;
	}
public:
	// Have to have the default constructor due to the compiler not making one when a custom constructor is declared.
	Moment()
	{

	}

	// Used for them we wanna calculate a moment at certain position in beam but don't know the forces
	Moment(double position)
	{
		this->position = position;
	}

	// angle is 90 as vertical and -90 as downwards
	Moment(double position, double forceVec, double angle)
	{
		
		angle = abs(angle);

		this->force.setForce(forceVec);
		this->force.setPosition(position);
		this->force.setAngle(toRadians(angle));

		// Might need work
		//this->momentValue = (cos(toRadians(angle)) * sin(toRadians(angle)) * forceVec) * position;
		this->momentValue = forceVec * position;

		set = true;
	}

	void setMoment()
	{
		if (set)
		{
			std::cout << "Moment already set." << std::endl;
		}
		else
		{
			momentValue = force.getForce() * position * sin(force.getAngle());
		}
	}

	// Make getters and setters for length and force
	double getMoment()
	{
		if (momentValue)
		{
			return momentValue;
		}
		else {
			std::cout << "Moment not set." << std::endl;
		}
	}
	
	// CTRL K, CTRL U TO REMOVE
	/*void addForce(Force force)
	{
		forces.push_back(force);
	}*/

	void setForce(Force force)
	{
		this->force = force;
	}

	Force getForce() 
	{
		return force;
	}

	void setPosition(double position)
	{
		this->position = position;
	}

	double getPosition()
	{
		return position;
	}
};


class Support
{
private:
	double position;
	Force reactionForce;
public:
	// Have to have the default constructor due to the compiler not making one when a custom constructor is declared.
	Support()
	{
		this->position = 0;
	}

	Support(double position)
	{
		this->position = position;
		reactionForce = Force(0, 90, position);
	}

	void setReactionForce(Force reactionForce)
	{
		this->reactionForce = reactionForce;
	}

	Force getReactionForce()
	{
		return reactionForce;
	}

	void addToReactionForce(Force force)
	{
		reactionForce.setForce(reactionForce.getForce() + force.getForce());
	}

	void setPosition(double position)
	{
		this->position = position;
	}

	double getPosition()
	{
		return position;
	}
};

// Support with Vertical and Horizontal reactions with a moment.
class FixedSupport : public Support
{
private:
	double position;
	double horizontalForce;
	double verticalForce;
	Force reactionForce;
	Moment moment;
public:
	FixedSupport(double position)
	{
		this->position = position;
	}
};

// Support with just the Vertical reaction force.
class RollerSupport : public Support
{
private:
	double position;
	double verticalForce;
	Force reactionForce;
public:

	using Support::Support;
	using Support::getReactionForce;
	using Support::addToReactionForce;
	using Support::setReactionForce;
	RollerSupport(double position) : Support(position)
	{
		this->position = position;
	}
};

// Support with just the Vertical reaction force.
class PinnedSupport : public Support
{
private:
	double position;
	double verticalForce;
	double horizontalForce;
	Force reactionForce;
public:
	using Support::Support;
	using Support::getReactionForce;
	using Support::addToReactionForce;
	using Support::setReactionForce;

	PinnedSupport(double position) : Support(position)
	{
		this->position = position;
	}
};

struct BeamData {
	double massPerLength{ 0.0 };
	double depthOfSection{ 0.0 };
	double widthOfSection{ 0.0 };
	double thicknessOfWeb{ 0.0 };
	double thicknessOfFlange{ 0.0 };
	double rootRadius{ 0.0 };
	double depthBetweenFillets{ 0.0 };
	double ratioOfLocalBucklingFlange{ 0.0 };
	double ratioOfLocalBucklingWeb{ 0.0 };
	double secondMomentOfAreaXX{ 0.0 };
	double secondMomentOfAreaYY{ 0.0 };
	double radiusOfGyrationXX{ 0.0 };
	double radiusOfGyrationYY{ 0.0 };

	double elasticModulusXX{ 0.0 };
	double elasticModulusYY{ 0.0 };
	double plasticModulusXX{ 0.0 };
	double plasticModulusYY{ 0.0 };
	double buckingParameter{ 0.0 };
	double torsionalIndex{ 0.0 };
	double warpingConstant{ 0.0 };
	double torsionalConstant{ 0.0 };
	double areaOfSection{ 0.0 };
};

class Beam
{
private:
	double length;
	BeamData beamData;
	std::vector<Force> forces;
	std::vector<Moment> moments;
	std::vector<Support *> supports;
	std::string dimension;
public:
	// Have to have the default constructor due to the compiler not making one when a custom constructor is declared.
	Beam()
	{

	}

	// Creates a beam with a length and at least 1 support
	Beam(double length, std::vector<Support*>* supportPointer)
	{
		this->length = length;
		this->supports = *supportPointer;
	}

	BeamData getData(std::string dimension, std::string mpl)
	{
		this->dimension = dimension;

		std::vector<std::string> fileData;
		std::string data2 = "";

		std::ifstream beamdata1("./data/beamdata.txt");
		std::ifstream beamdata2("./data/beamdata2.txt");
		std::ifstream beamdatatotalread("./data/beamdata3.txt");

		//beamdatatotal << beamdata1.rdbuf() << beamdata2.rdbuf();

		std::string temp = "";
		std::string temp2 = "";

		char fileSelection = 0;
		bool dimensionFound = false;
		bool lineFound = false;

		while (std::getline(beamdatatotalread, temp, '-'))
		{
			fileData.push_back(temp);

			std::string dimensionC = "=" + dimension;

			std::string formattedDimension = temp;

			formattedDimension.erase(std::remove_if(formattedDimension.begin(), formattedDimension.end(), isspace), formattedDimension.end());

			if (formattedDimension.compare(dimensionC) == 0)
			{
				dimensionFound = true;
			}
			
			if (dimensionFound)
			{
				std::string delimiter3 = " ";
				size_t pos3 = 0;
				size_t pos4 = 0;
				std::string token3;
				int dataType = 0;

				while ((pos3 = temp.find(delimiter3)) != std::string::npos) {
					token3 = temp.substr(0, pos3);

					// Different position of mpl for each file
					if (fileSelection == 1 && lineFound == false)
					{
						char x = 0;

						pos4 = 0;

						// Used to keep the last value of the line
						std::string temp2 = temp;
						while ((pos4 = temp2.find(delimiter3)) != std::string::npos)
						{
							token3 = temp2.substr(0, pos4); 

							if (x == 11)
							{
								std::string formattedToken = token3;

								formattedToken.erase(std::remove_if(formattedToken.begin(), formattedToken.end(), isspace), formattedToken.end());

								token3 = formattedToken;

								break;
							}
							else 
							{
								temp2.erase(0, pos4 + delimiter3.length());
								x++;
							}
							
						}
					}

					// Only add data when its the correct 
					if (token3.compare(mpl) == 0 || lineFound)
					{
						lineFound = true;
						if (fileSelection == 1)
						{
							switch (dataType)
							{
								case 0:
									beamData.elasticModulusXX = std::stod(token3);
									break;
								case 1:
									beamData.elasticModulusYY = std::stod(token3);
									break;
								case 2:
									beamData.plasticModulusXX = std::stod(token3);
									break;
								case 3:
									beamData.plasticModulusYY = std::stod(token3);
									break;
								case 4:
									beamData.buckingParameter = std::stod(token3);
									break;
								case 5:
									beamData.torsionalIndex = std::stod(token3);
									break;
								case 6:
									beamData.warpingConstant = std::stod(token3);
									break;
								case 7:
									beamData.torsionalConstant = std::stod(token3);
									break;
								case 8:
									beamData.areaOfSection = std::stod(token3);
									dimensionFound = false;
									lineFound = false;
									break;
							}

							dataType++;
							temp.erase(0, pos3 + delimiter3.length());
						}
						else
						{
							switch (dataType)
							{
								case 1:
									beamData.massPerLength = std::stod(token3);
									break;
								case 2:
									beamData.depthOfSection = std::stod(token3);
									break;
								case 3:
									beamData.widthOfSection = std::stod(token3);
									break;
								case 4:
									beamData.thicknessOfWeb = std::stod(token3);
									break;
								case 5:
									beamData.thicknessOfFlange = std::stod(token3);
									break;
								case 6:
									beamData.rootRadius = std::stod(token3);
									break;
								case 7:
									beamData.depthBetweenFillets = std::stod(token3);
									break;
								case 8:
									beamData.ratioOfLocalBucklingFlange = std::stod(token3);
									break;
								case 9:
									beamData.ratioOfLocalBucklingWeb = std::stod(token3);
									break;
								case 10:
									beamData.secondMomentOfAreaXX = std::stod(token3);
									break;
								case 11:
									beamData.secondMomentOfAreaYY = std::stod(token3);
									break;
								case 12:
									beamData.radiusOfGyrationXX = std::stod(token3);
									break;
								case 13:
									beamData.radiusOfGyrationYY = std::stod(token3);
									dimensionFound = false;
									lineFound = false;
									fileSelection++;
									break;
							}

							dataType++;
							temp.erase(0, pos3 + delimiter3.length());
						}
					}
					else 
					{
						break;
					}
				}
			}
			temp = "";
		}

		return beamData;

	}

	void addSupport(Support* support)
	{
		supports.push_back(support);
	}

	// Sets the vector of forces
	void setForces(std::vector<Force>* vectorPointer)
	{
		this->forces = *vectorPointer;
	}

	// Returns the pointer to the forces vector
	std::vector<Force>* getForces()
	{
		return &forces;
	}

	// Returns the pointer to the moment vector
	std::vector<Moment>* getMoments()
	{
		return &moments;
	}

	// Adds a force to the vector of forces
	void addForce(Force force)
	{
		forces.push_back(force);
	}

	// Calculates the moments depending on the current forces
	//void calculateMoments()
	//{
	//	for (int i = 0; i < forces.size(); i++)
	//	{
	//		Force force1 = forces.at(i);

	//		// Add angle here eventually
	//		std::cout << "Force of " << force1.getForce() << " acting " << force1.getPosition() << "m away from the left support." << std::endl;
	//		moments.push_back(Moment(force1));
	//	}
	//}


// Just for simply supported beams
	std::vector<Force> calculateReactionForces()
	{

	}

	// Just for simply supported beams, calculates moments at each force along the beam
	std::vector<Moment> calculateBendingMomentDiagram()
	{

	}

	// Just for simply supported beams, calculates shear at each force along the beam
	std::vector<Force> calculateShearForceDiagram() {

	}
	
	// Calculates moment at specific position in beam
	void calculateMomentAtPosition(double position)
	{

	}

	void printMoments()
	{
		for (int i = 0; i < moments.size(); i++)
		{
			Moment m1 = moments.at(i);
			std::cout << "Moment of magnitude " << m1.getMoment() << "Nm at " << m1.getPosition() << "m from the left support.";
		}
	}
};