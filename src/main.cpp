#include "./Header.h"

double beam_length;

int main()
{
	int x = 0;

	std::vector<Support*> supports;
	supports.push_back(new PinnedSupport(0));
	supports.push_back(new RollerSupport(2.5));
	supports.push_back(new RollerSupport(5));

	Beam beam = Beam(5, &supports);

	std::vector<Force> forces = {Force(-3000, 90, 2), Force(-5000, 90, 3), Force(-2000, 90, 4)}; 
	beam.setForces(&forces);

	BeamData beamdata = beam.getData("406x178", "74");

	std::cout << beamdata.thicknessOfFlange << std::endl;

	std::cin >> x;
}


void print(std::string message)
{
	std::cout << message << std::endl;
}
