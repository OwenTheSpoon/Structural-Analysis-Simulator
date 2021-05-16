

// Need to add moment distribution for beams with more than 2 supports
//void failedAdditionOfMomentDistribution()
//{
//	// loop through supports
//	// get distance to next support (POS S2 - POS S1)
//	// get forces between those 2 positions
//	// loop through forces
//	// calculate how far forces are from S1 abs(FORCE POS - SUPPORT POS)
//	// total moments then divide by distance from 1 support to the other
//
//	for (int i = 0; i < supports.size(); i++)
//	{
//		std::vector<Force> validForces;
//
//		bool backwards = false;
//		bool repeat = false;
//
//		Support s1 = *supports[i];
//		Support s2;
//
//		int index = 0;
//
//		if ((i + 1) < supports.size())
//		{
//			index = i + 1;
//			s2 = *supports[index];
//		}
//		else {
//			index = i - 1;
//			s2 = *supports[index];
//		}
//
//		for (int y = 0; y < 2; y++)
//		{
//			// Swap supports when y = 1
//			if (y == 0)
//			{
//				backwards = false;
//			}
//			else {
//				Support temp = s1;
//				s1 = s2;
//				s2 = temp;
//				backwards = true;
//			}
//
//			double distanceToNextSupport = abs(s2.getPosition() - s1.getPosition());
//			double momentTotal = 0;
//
//			for (int x = 0; x < forces.size(); x++)
//			{
//				if (backwards)
//				{
//					if (forces[x].getPosition() < s1.getPosition() && forces[x].getPosition() > s2.getPosition())
//					{
//						Force f = forces[x];
//						double distanceFromSupportToForce = (f.getPosition() - s1.getPosition());
//						Moment m = Moment(distanceFromSupportToForce, f.getForce(), f.getAngle());
//						momentTotal += m.getMoment();
//					}
//				}
//				else
//				{
//					if (forces[x].getPosition() < s2.getPosition() && forces[x].getPosition() > s1.getPosition())
//					{
//						Force f = forces[x];
//						double distanceFromSupportToForce = (f.getPosition() - s1.getPosition());
//						Moment m = Moment(distanceFromSupportToForce, f.getForce(), 90);
//						momentTotal += m.getMoment();
//					}
//				}
//			}
//
//			double forceMag = momentTotal / distanceToNextSupport;
//
//			Force reactionForceAtSupport = Force(forceMag, 90, s2.getPosition());
//
//			// Add the force to the correct support
//			if (backwards)
//			{
//				(*supports[index - 1]).addToReactionForce(reactionForceAtSupport);
//				std::cout << "Reaction force at " << (*supports[index - 1]).getPosition() << "m is " << (*supports[index - 1]).getReactionForce().getForce() << "N." << std::endl;
//			}
//			else
//			{
//				(*supports[index]).addToReactionForce(reactionForceAtSupport);
//				std::cout << "Reaction force at " << (*supports[index]).getPosition() << "m is " << (*supports[index]).getReactionForce().getForce() << "N." << std::endl;
//			}
//		}
//	}
//}

