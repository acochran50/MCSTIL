#ifndef _TISSUE_LAYER
#define _TISSUE_LAYER

namespace MCSTIL {
/****************/
class TissueLayer {
	public:
		/* methods */
		TissueLayer();
		~TissueLayer();
		void LayerInit(std::string name, int num, double thick, double absorb, double scatter, double n, double g);
		void DispLayer(std::ostream& o);

		/* properties */
		std::string layer_name_;
		int layer_num_;
		double thickness_;
		double z_top_;
		double z_bot_;
		double mu_a_;
		double mu_s_;
		double mu_t_;
		double refract_ind_;
		double aniso_;
};
/****************/
}

#endif
