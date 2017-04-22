#include "../include/MCSTIL_v3.hpp"
#include "MCSTILRandom_v3.hpp"

MCSTIL::MCSTILRandom::MCSTILRandom()
{
	std::mt19937 temp_mc_rng{static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())};
	mc_rng = temp_mc_rng;
}

double MCSTIL::MCSTILRandom::ReturnXi()
{
	return mc_dist(mc_rng);
}

MCSTIL::MCSTILRandom* MCSTIL::MCSTILRandom::g_instance = 0;
MCSTIL::MCSTILRandom* MCSTIL::MCSTILRandom::Instance()
{
	if (!g_instance)
		g_instance = new MCSTILRandom();
	return g_instance;
}
