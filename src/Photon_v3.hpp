#ifndef _PHOTON
#define _PHOTON

namespace MCSTIL {
/****************/
class Photon {
    public:
        Photon();   // default constructor
        ~Photon();  // default destructor

        /* step methods */
        void GenStep(double mu_t_, double tissue_top);
        void StepSwitch();
        void StoreStep(double bound);
        void StoreRemaining(double bound);

        /* movement methods */
        void Move();
        void MoveRemaining();
        void Scatter(double aniso_);
        void ChangeDir();

        /* layer management methods */
        void SetLayer(unsigned int new_layer);
        unsigned int GetLayer();
        void SetNextLayer(unsigned int new_layer);
        unsigned int GetNextLayer();

        /* direction checks */
        bool Up();
        bool Down();

        /* position access */
        double GetX();
        double GetY();
        double GetZ();

        /* boundary collisions */
        bool HitBound(double bound);
        bool RemHitBound(double bound);
        bool Fresnel(double n_i_, double n_t_, double tissue_top);
        double PosAfterRemStep();

        /* grid absorption */
        void Absorb(double mu_a_, double mu_s_);

        /* weight managment, roulette technique */
        double GetWeight();
        bool WeightLow();
        void Roulette();
        void Kill();

        /* debugging */
        void DisplayInfo(bool debug, std::string label);
        bool CheckNaN();
        bool CheckCosines();

        /* bins */
        static double backs_;
        static double trans_;
        static double abs_;

        /* status */
        bool alive_;

    private:
        double weight_;
        unsigned int curr_layer_;
        unsigned int next_layer_;

        /* Cartesian mapping */
        double x_, y_, z_;
        double mu_x_, mu_y_, mu_z_;
        double step_;
        double rem_step_;
        double theta_t_;
        double theta_i_;
        double longitudinal_;
        double azimuthal_;
};
/****************/
}

#endif
