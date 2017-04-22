/*----- Preprocessor(s) ---------------------------------------------------------------------------------------------*/

#include "../include/MCSTIL_v3.hpp"

/*----- Header & timer initialize -----------------------------------------------------------------------------------*/

int main() {
	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << "<< MCSTIL: Monte Carlo Simulation for Tissue Incident Light >>" << std::endl;
	std::cout << "                                                              " << std::endl;
	std::cout << "              Written by Alex Cochran, 2016-2017              " << std::endl;
	std::cout << "                   The Ohio State University                  " << std::endl;
	std::cout << "        Deptartment of Materials Science & Engineering        " << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

/*----- Open output file --------------------------------------------------------------------------------------------*/

	std::ofstream MCSTIL_output;	// output file
	MCSTIL_output.open("output/MCSTIL.log", std::ostream::out);

	if (!MCSTIL_output.is_open()) {
		return MCSTIL::ERROR::FileNotFound();	// aborts simulation
	}

/*----- Open coordinate output files --------------------------------------------------------------------------------*/

	std::ofstream trans_output;	// transmission data file
	std::ofstream abs_output;	// absorption data file
	std::ofstream refl_output;	// reflection data file

	trans_output.open("output/trans.out", std::ostream::out);
	abs_output.open("output/abs.out", std::ostream::out);
	refl_output.open("output/refl.out", std::ostream::out);

	if (!trans_output.is_open() || !abs_output.is_open() || !refl_output.is_open()) {
		return MCSTIL::ERROR::FileNotFound();	// aborts simulation
	}

/*----- Simulation parameter input ----------------------------------------------------------------------------------*/

	unsigned int num_photons;
	std::string header;

	std::ifstream param_input;
	param_input.open("input/params.in", std::ifstream::in);

	if (!param_input.is_open()) {
		return MCSTIL::ERROR::FileNotFound();
	}

	std::getline(param_input, header);

	while (param_input.good() && !param_input.eof()) {
		param_input >> num_photons;
	}

	unsigned int initial_total_weight = num_photons * BIRTH_WEIGHT;
	param_input.close();

/*----- Tissue profile input ----------------------------------------------------------------------------------------*/

	unsigned int num_layers;
	std::string layer_name;
	int layer_num;
	double thickness;
	double mu_a;
	double mu_s;
	double refract_ind;
	double g;
	std::vector<MCSTIL::TissueLayer> tissue;
	MCSTIL::TissueLayer newLayer;

	std::ifstream tissue_input;
	tissue_input.open("input/brain.in", std::ifstream::in);

	if (!tissue_input.is_open()) {
		return MCSTIL::ERROR::FileNotFound();
	}

	std::getline(tissue_input, header);
	tissue_input >> num_layers;

	while (tissue_input.good() && !tissue_input.eof()) {
		tissue_input
			>> layer_name
			>> layer_num
			>> thickness
			>> mu_a
			>> mu_s
			>> refract_ind
			>> g;

		newLayer.LayerInit(layer_name, layer_num, thickness, mu_a, mu_s, refract_ind, g);
		tissue.push_back(newLayer);
	}

	if (tissue.size() < num_layers) {
		return MCSTIL::ERROR::InvalidParams();
	}

	std::cout << std::endl;
	std::cout << "Tissue profile (from surface):" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << std::endl;

	MCSTIL_output << std::endl;
	MCSTIL_output << "Tissue profile (from surface):" << std::endl;
	MCSTIL_output << "------------------------------" << std::endl;
	MCSTIL_output << std::endl;

	for (unsigned int count = 0; count < tissue.size() - 1; ++count) {
		if (count == 0) {
			tissue[count].z_top_ = 0.0;
			tissue[count].z_bot_ = tissue[count].thickness_;
		} else {
			tissue[count].z_top_ = tissue[count - 1].z_bot_;
			tissue[count].z_bot_ = tissue[count - 1].z_bot_ + tissue[count].thickness_;
		}

		tissue[count].DispLayer(MCSTIL_output);
	}

	std::cout << "------------------------------" << std::endl;

	std::cout << "Tissue vector size: " << tissue.size() << std::endl;

	tissue_input.close();

/*-------------------------------------------------------------------------------------------------------------------*/
/*----- PHOTON PROPAGATION ALGORITHM (see /dev/algorithm.md) --------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

	MCSTIL::MCSTILRandom* MCEngine;
	MCEngine = MCSTIL::MCSTILRandom::Instance();
	MCSTIL::Photon *photon;
	MCSTIL::Grid grid;

	int trans_counter				=	0;
	int total_transmission 			=	0;
	int backscatter_reflection		=	0;
	int backscatter_transmission	=	0;
	int internal_reflection			=	0;

	/* simulation flags */
	bool outflag = true;	// write grid output to file?
	bool pushflag = true;	// push event coordinates to grid?
	bool debug = true;		// print debugging statements?

	while (num_photons) {
	    MCSTIL::Photon *photon = new MCSTIL::Photon;
	    bool step_left;

	    while (photon -> alive_) {
	        for (unsigned int count = 0; count < tissue.size() - 1; ++count) {
	            if ((photon -> GetZ() >= tissue[count].z_top_) && (photon -> GetZ() <= tissue[count].z_bot_)) {
	                photon -> SetLayer(count);
	            }
	        }

			/* check the next layer */
			if (photon -> Up()) {
				if (photon -> GetLayer() != 0) {
					photon -> SetNextLayer(photon -> GetLayer() - 1);
				}
			/* photon facing into body */
			} else if (photon -> Down()) {
				photon -> SetNextLayer(photon -> GetLayer() + 1);
			/* contingency measure if the photon's direction is completely lateral */
			} else {
				std::cerr << "\n\n\nFAILURE DURING UP/DOWN CHECK. Aborting...";
				return 0;
			}

	        photon -> GenStep(tissue[photon -> GetLayer()].mu_t_, tissue[0].z_bot_);
	        step_left = true;

			if (photon -> GetZ() > 5.0) {
				photon -> DisplayInfo(debug, "step generated");
			}

	        if (photon -> GetLayer() >= tissue.size() - 1) { // guard
	            MCSTIL::ERROR::InvalidLayer();
	            photon -> Kill();
	        }

	        /* boundary contact */
	        if ((photon -> Up() && photon -> HitBound(tissue[photon -> GetLayer()].z_top_)) || (photon -> Down() && photon -> HitBound(tissue[photon -> GetLayer()].z_bot_))) {
				photon -> DisplayInfo(debug, "boundary contact");

	            if (photon -> Up()) {
	                photon -> StoreStep(tissue[photon -> GetLayer()].z_top_);
	                if (photon -> GetLayer() != 0) {
	                    photon -> SetNextLayer(photon -> GetLayer() - 1);
	                }
	            } else if (photon -> Down()) {
	                photon -> StoreStep(tissue[photon -> GetLayer()].z_bot_);
	                photon -> SetNextLayer(photon -> GetLayer() + 1);
	            }

	            photon -> Move(); // move to boundary

				photon -> DisplayInfo(debug, "moved to boundary, Fresnel check");

	            /* continues to operate until no step is remaining */
	            while (step_left == true && photon -> alive_) {
	                /* reflection */
	                if (photon -> Fresnel(tissue[photon -> GetLayer()].refract_ind_, tissue[photon -> GetNextLayer()].refract_ind_, tissue[0].z_bot_)) {
	                    /* backscatter reflection */
	                    if (photon -> GetLayer() == 0) {
	                        photon -> backs_ += photon -> GetWeight();
							backscatter_reflection++;
							grid.PushReflCoords(photon -> GetX(), photon -> GetY(), photon -> GetZ(), pushflag);
	                        photon -> Kill();
							break;
	                    /* internal reflection */
	                    } else {
	                        if ((photon -> Up() && !(photon -> RemHitBound(tissue[photon -> GetLayer()].z_top_))) || (photon -> Down() && !(photon -> RemHitBound(tissue[photon -> GetLayer()].z_bot_)))) {
								internal_reflection++;
	                            step_left = false;
								break;
	                        }
	                    }
	                /* transmission */
	                } else {
						photon -> DisplayInfo(debug, "transmission");
	                    /* total transmission */
	                    if (photon -> PosAfterRemStep() > tissue[tissue.size() - 3].z_bot_) {
	                        photon -> trans_ += photon -> GetWeight();
							total_transmission++;
							grid.PushTransCoords(photon -> GetX(), photon -> GetY(), photon -> GetZ(), pushflag);
	                        photon -> Kill();
							break;
	                    /* backscatter transmission (technically a reflection) */
	                    } else if (photon -> PosAfterRemStep() < tissue[1].z_top_) {
	                        photon -> backs_ += photon -> GetWeight();
							backscatter_transmission++;
							grid.PushReflCoords(photon -> GetX(), photon -> GetY(), photon -> GetZ(), pushflag);
	                        photon -> Kill();
							break;
	                    /* internal transmission */
	                    } else {
	                        if ((photon -> Up() && !(photon -> RemHitBound(tissue[photon -> GetNextLayer()].z_top_))) || (photon -> Down() && !(photon -> RemHitBound(tissue[photon -> GetNextLayer()].z_bot_)))) {
								if (photon -> GetLayer() == 0) {
									trans_counter++;
								}
	                            step_left = false;
								break;
	                        }
	                    }
	                }

	                /**********
	                    HERE: a boundary has been hit, and photon has been moved to said boundary. Remaining step will still hit a boundary. Need to:
	                        1. Move to the next boundary. The Fresnel function has calculated the new direction after reflection/transmission, so this comparison should be easy.
	                        2. Store the new remaining step. This will be used for the next set of comparisons to find if said new remaining step will make boundary contact.
	                **********/

					/* photon facing out of tissue */
	                if (photon -> Up()) {
						photon -> SetNextLayer(photon -> GetLayer() - 1);
	                    photon -> StoreRemaining(tissue[photon -> GetNextLayer()].z_top_);
					/* photon facing into body */
	                } else if (photon -> Down()) {
						photon -> SetNextLayer(photon -> GetLayer() + 1);
	                    photon -> StoreRemaining(tissue[photon -> GetNextLayer()].z_bot_);
	                /* contingency measure if the photon's direction is completely lateral */
	                } else {
	                    std::cerr << "\n\n\nFAILURE DURING UP/DOWN CHECK. Aborting...";
	                    return 0;
	                }

	                photon -> Move(); // move to next boundary using step

					/* check the layer */
					for (unsigned int count = 0; count < tissue.size() - 1; ++count) {
						if ((photon -> GetZ() >= tissue[count].z_top_) && (photon -> GetZ() <= tissue[count].z_bot_)) {
							photon -> SetLayer(count);
						}
					}
	            } // END WHILE

			photon -> DisplayInfo(debug, "check next layer, move remaining");

			/* check the layer */
			for (unsigned int count = 0; count < tissue.size() - 1; ++count) {
				if ((photon -> GetZ() >= tissue[count].z_top_) && (photon -> GetZ() <= tissue[count].z_bot_)) {
					photon -> SetLayer(count);
				}
			}

			/* check the next layer */
			if (photon -> Up()) {
				if (photon -> GetLayer() != 0) {
					photon -> SetNextLayer(photon -> GetLayer() - 1);
				}
			/* photon facing into body */
			} else if (photon -> Down()) {
				photon -> SetNextLayer(photon -> GetLayer() + 1);
			/* contingency measure if the photon's direction is completely lateral */
			} else {
				std::cerr << "\n\n\nFAILURE DURING UP/DOWN CHECK. Aborting...";
				return 0;
			}


	        photon -> MoveRemaining();

	        /* no boundary contact */
	        } else {
	            photon -> Move();
	        }

	        photon -> Absorb(tissue[photon -> GetLayer()].mu_a_, tissue[photon -> GetLayer()].mu_s_);

	        if (photon -> WeightLow()) {
	            photon -> Roulette();
	        }

	        if (photon -> GetLayer() != 0) {
	            photon -> Scatter(tissue[photon -> GetLayer()].aniso_);
	        }

			photon -> ChangeDir();
	    } // end while (photon -> alive_)

	    num_photons--;
	}

	std::cout << "\nInternal transmissions:\t\t" << trans_counter;
	std::cout << "\nBackscatter reflections:\t" << backscatter_reflection;
	std::cout << "\nInternal reflections:\t\t" << internal_reflection;
	std::cout << "\nBackscatter transmissions:\t" << backscatter_transmission;
	std::cout << "\nTotal transmissions:\t\t" << total_transmission << std::endl;

	delete MCEngine; // free memory for random number generator

/*-------------------------------------------------------------------------------------------------------------------*/
/*----- END ALGORITHM -----------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

/*----- Write transmission, absorption, and reflection data to corresponding files ----------------------------------*/

	grid.WriteTransCoords(trans_output, outflag);
	grid.WriteAbsCoords(abs_output, outflag);
	grid.WriteReflCoords(refl_output, outflag);

/*----- Calculate final energy loss ---------------------------------------------------------------------------------*/

	double final_total_weight;
	double energy_diff;
	double percent_trans;
	double percent_abs;
	double percent_backs;

	final_total_weight = (photon -> trans_) + (photon -> abs_) + (photon -> backs_);
	energy_diff = fabs((initial_total_weight - final_total_weight) / initial_total_weight);
	percent_trans = (photon -> trans_) / initial_total_weight * 100.0;
	percent_abs = (photon -> abs_) / initial_total_weight * 100.0;
	percent_backs = (photon -> backs_) / initial_total_weight * 100.0;

	std::cout << "\nWeight absorbed:\t" << photon -> abs_ << "\t(" << percent_abs << "%)" << std::endl;
	std::cout << "Weight backscattered:\t" << photon -> backs_ << "\t(" << percent_backs << "%)" << std::endl;
	std::cout << "Weight transmitted:\t" << photon -> trans_ << "\t(" << percent_trans << "%)" << std::endl;

/*----- Timer stop; write results to log file --------------------------------------------------------------------------*/

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
	std::cout << "\nExecution time: " << seconds << " s" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;

	MCSTIL_output << "Percent error: " << energy_diff << "%" << std::endl;
	MCSTIL_output << "Weight absorbed: " << photon -> abs_ << std::endl;
	MCSTIL_output << "Weight backscattered: " << photon -> backs_ << std::endl;
	MCSTIL_output << "Weight transmitted: " << photon -> trans_ << std::endl;
	MCSTIL_output << "Execution time: " << seconds << " s" << std::endl;
	std::cout << std::endl;

	MCSTIL_output.close();

/*----- End ---------------------------------------------------------------------------------------------------------*/

	return 0;
}
