#include "./Header.h"

double beam_length;

void print(std::string message)
{
	std::cout << message << std::endl;
}

void print(double message)
{
	std::cout << message << std::endl;
}

int main()
{
	int x = 0;

	std::vector<Support*> supports;
	supports.push_back(new PinnedSupport(0));
	supports.push_back(new RollerSupport(10.8));

	std::vector<LateralRestraint*> lateralRestraints;
	lateralRestraints.push_back(new LateralRestraint(2.5));
	lateralRestraints.push_back(new LateralRestraint(5.7));

	Beam beam = Beam(5, &supports, &lateralRestraints);

	std::vector<Force> forces = {Force(-478, 2.5), Force(-267, 5.7)};
	beam.setForces(&forces);
	beam.setData("762x267", "173");
	beam.setSteel(265.0);


	BeamData data = beam.getData();
	

	/*for(int i = 0; i < forces.size(); i++)
	{
		std::cout << "Total Force [" << i << "] : " << (forces[i].getVariable(true) + forces[i].getPermanent(true)) << std::endl;
	}*/


	for (int x = 0; x < data.getAllData().size(); x++)
	{
		std::cout << "[" << x << "]" << data.getAllData()[x] << std::endl;
	}

	std::cout << "Class for outstand flange in compression: " << beam.calculateClassOutstandFlange() << std::endl;
	std::cout << "Class for web in bending: " << beam.calculateClassOutstandFlange() << std::endl;
	std::cout << "Bending Moment Capacity:  " << beam.calculateBucklingResistanceMoment() << std::endl;

	beam.calculateReactionForces();
	beam.calculateShearForceDiagram();
	beam.calculateBendingMomentDiagram();

	std::vector<Moment> moments = (*beam.getMoments());
	std::vector<Force> shearForceDiagram = (*beam.getShearForceDiagram());
	std::vector<Force> allForces = (*beam.getForces());

	std::cout << "All Forces" << std::endl;


	for (int y = 0; y < allForces.size(); y++)
	{
		std::cout << "[" << y << "] " << allForces[y].getForce() << " at " << allForces[y].getPosition() << "m from left support." << std::endl;
	}

	std::cout << "Shear Force Diagram" << std::endl;

	for (int y = 0; y < shearForceDiagram.size(); y++)
	{
		std::cout << "[" << y << "] " << shearForceDiagram[y].getForce() << " at " << shearForceDiagram[y].getPosition() << "m from left support." << std::endl;
	}

	beam.printBendingMomentDiagram();

	std::cout << beam.getMaxBendingMoment().getMoment() << std::endl;
	std::cout << beam.isBendingMomentCapacitySatisfactory() << std::endl;
	std::cout << beam.calculateElasticCriticalMoment() << std::endl;

	std::cin >> x;
}


