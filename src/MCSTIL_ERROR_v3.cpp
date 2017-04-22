#include "../include/MCSTIL_v3.hpp"
#include "MCSTIL_ERROR_v3.hpp"

int MCSTIL::ERROR::FileNotFound() {
	std::cerr << std::endl;
	std::cerr << "ERROR: File not found in MCSTIL directory. Aborting..." << std::endl;
	std::cerr << std::endl;
	return 0;
}

int MCSTIL::ERROR::InvalidParams() {
	std::cerr << std::endl;
	std::cerr << "ERROR: One or more simulation parameters is invalid." << std::endl;
	std::cerr << "Check input files and restart MCSTIL. Aborting..." << std::endl;
	std::cerr << std::endl;
	return 0;
}

int MCSTIL::ERROR::InvalidTissue(int index) {
	std::cerr << std::endl;
	std::cerr << "ERROR: One or more tissue layers is invalid." << std::endl;
	std::cerr << "Reference tissue layer #" << (++index) << "." << std::endl;
	std::cerr << "Check tissue input file and restart MCSTIL. Aborting..." << std::endl;
	std::cerr << std::endl;
	return 0;
}

void MCSTIL::ERROR::InvalidLayer() {
	std::cerr << std::endl;
	std::cerr << "ERROR: Photon is not in a valid layer." << std::endl;
	std::cerr << "Photon terminated." << std::endl;
	std::cerr << std::endl;
}
