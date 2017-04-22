#ifndef _MCSTIL_RANDOM
#define _MCSTIL_RANDOM

namespace MCSTIL
{

class MCSTILRandom
{
	private:
		std::mt19937 mc_rng;
		std::uniform_real_distribution<double> mc_dist;
		static MCSTILRandom *g_instance;
		MCSTILRandom();
		MCSTILRandom(const MCSTILRandom&);
		MCSTILRandom& operator = (const MCSTILRandom&);
	public:
		double ReturnXi();
		static MCSTILRandom* Instance();
};

}

#endif
