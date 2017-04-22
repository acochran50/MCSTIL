#include "../include/MCSTIL_v3.hpp"
#include "TissueLayer_v3.hpp"

MCSTIL::TissueLayer::TissueLayer() {
	// default constructor
}

MCSTIL::TissueLayer::~TissueLayer() {
	// default destructor
}

void MCSTIL::TissueLayer::LayerInit(std::string name, int num, double thickness,double absorb, double scatter, double n, double g) {
	layer_name_		=	name;
	layer_num_		=	num;
	thickness_		=	thickness;
	mu_a_			=	absorb;
	mu_s_			=	scatter;
	mu_t_			=	mu_s_ + mu_a_;
	refract_ind_	=	n;
	aniso_			=	g;
}

void MCSTIL::TissueLayer::DispLayer(std::ostream& o) {
	/* write to console (standard output) */
	std::cout << "Layer " << layer_num_ << ": " << layer_name_ << std::endl;
	std::cout << "\tThickness [cm]:\t\t\t" << thickness_ << std::endl;
	std::cout << "\tAbsorption coefficient:\t\t" << mu_a_ << std::endl;
	std::cout << "\tScattering coefficient:\t\t" << mu_s_ << std::endl;
	std::cout << "\tInteraction coefficient:\t" << mu_t_ << std::endl;
	std::cout << "\tRefractive index:\t\t" << refract_ind_ << std::endl;
	std::cout << "\tAnisotropic factor:\t\t" << aniso_ << std::endl;
	std::cout << "\tUpper bound:\t\t\t" << z_top_ << std::endl;
	std::cout << "\tLower bound:\t\t\t" << z_bot_ << std::endl;
	std::cout << std::endl;

	/* write to output file */
	o << "Layer " << layer_num_ << ": " << layer_name_ << std::endl;
	o << "\tThickness [cm]:\t\t\t" << thickness_ << std::endl;
	o << "\tAbsorption coefficient:\t\t" << mu_a_ << std::endl;
	o << "\tScattering coefficient:\t\t" << mu_s_ << std::endl;
	o << "\tInteraction coefficient:\t" << mu_t_ << std::endl;
	o << "\tRefractive index:\t\t" << refract_ind_ << std::endl;
	o << "\tAnisotropic factor:\t\t" << aniso_ << std::endl;
	o << "\tUpper bound:\t\t\t" << z_top_ << std::endl;
	o << "\tLower bound:\t\t\t" << z_bot_ << std::endl;
	o << std::endl;
}
