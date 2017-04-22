#include "../include/MCSTIL_v3.hpp"
#include "Photon_v3.hpp"

/************************************************************************************************************************
    bins (weight backscattered, transmitted, absorbed)
************************************************************************************************************************/

double MCSTIL::Photon::backs_   =   0.0;
double MCSTIL::Photon::trans_   =   0.0;
double MCSTIL::Photon::abs_     =   0.0;

/************************************************************************************************************************
    overloaded constructor, default destructor
************************************************************************************************************************/

MCSTIL::Photon::Photon() {
    weight_         =   1.0;
    alive_          =   true;
    step_           =   0.0;
    rem_step_       =   0.0;
    curr_layer_     =   0;
    next_layer_     =   1;
    x_              =   0.0;
    y_              =   0.0;
    z_              =   0.0;
    mu_x_           =   0.0;
    mu_y_           =   0.0;
    mu_z_           =   1.0;
    azimuthal_      =   0.0;
    longitudinal_   =   0.0;
    theta_i_        =   0.0;
    theta_t_        =   0.0;
}

MCSTIL::Photon::~Photon() {
    /* destructor */
}

/************************************************************************************************************************
    step generation/storage
************************************************************************************************************************/

void MCSTIL::Photon::GenStep(double mu_t_, double tissue_top) {
    double xi;
    xi = MCSTIL::MCSTILRandom::Instance() -> MCSTIL::MCSTILRandom::ReturnXi();

    if (mu_t_ == 0) {
        step_ = tissue_top; // takes into account the concept of having a layer of air on top of the tissue
    } else {
        step_ = -log(xi) / mu_t_;
    }

    rem_step_ = 0.0;
}

void MCSTIL::Photon::StepSwitch() {
    step_ = rem_step_;
    rem_step_ = 0.0;
}

void MCSTIL::Photon::StoreStep(double bound) { // recreation of the original function to test a different solution
    rem_step_ = fabs(fabs(step_ * mu_z_) - fabs(bound - z_));
    step_ -= rem_step_;
}

void MCSTIL::Photon::StoreRemaining(double bound) {
    double temp_step;
    temp_step = fabs(rem_step_ * mu_z_) - fabs(bound - z_);
    rem_step_ = temp_step;
}

/************************************************************************************************************************
    movement
************************************************************************************************************************/

void MCSTIL::Photon::Move() {
    x_ += (step_ * mu_x_);
    y_ += (step_ * mu_y_);
    z_ += (step_ * mu_z_);
    step_ = 0.0;
}

void MCSTIL::Photon::MoveRemaining() {
    x_ += (rem_step_ * mu_x_);
    y_ += (rem_step_ * mu_y_);
    z_ += (rem_step_ * mu_z_);
    rem_step_ = 0.0;
}

void MCSTIL::Photon::Scatter(double aniso_) {
    double xi = MCSTIL::MCSTILRandom::Instance() -> MCSTIL::MCSTILRandom::ReturnXi();

    if (aniso_ == 0) {
        longitudinal_ = acosd((2 * xi) - 1);
    } else {
        double temp = (1.0 - aniso_ * aniso_) / (1.0 - aniso_ + 2 * aniso_ * xi);
        longitudinal_ = acosd((1.0 + aniso_ * aniso_ - temp * temp) / (2.0 * aniso_));
    }

    xi = MCSTIL::MCSTILRandom::Instance() -> MCSTIL::MCSTILRandom::ReturnXi();
    azimuthal_ = TWO_PI * xi;

    //std::cout << "\n\nSCATTER" << "\ng: " << aniso_ << "\nlongitudinal: " << longitudinal_ << "\nazimuthal: " << azimuthal_;
}

void MCSTIL::Photon::ChangeDir() {
    double temp_mu_x = 0.0;
    double temp_mu_y = 0.0;
    double temp_mu_z = 0.0;
    double temp      = 0.0;

    /*std::cout << "\n\nCHANGEDIR";
    std::cout << "\nuxx: " << mu_x_;
    std::cout << "\nuyy: " << mu_y_;
    std::cout << "\nuzz: " << mu_z_;*/

    temp = sqrt(1.0 - pow(mu_z_, 2.0));

    if (mu_z_ < fabs(0.99999)) {
        temp_mu_x = sind(longitudinal_) * (mu_x_ * mu_z_ * cosd(azimuthal_) - mu_y_ * sind(azimuthal_)) / temp + mu_x_ * cosd(longitudinal_);
        temp_mu_y = sind(longitudinal_) * (mu_y_ * mu_z_ * cosd(azimuthal_) + mu_x_ * sind(azimuthal_)) / temp + mu_y_ * cosd(longitudinal_);
        temp_mu_z = -1.0 * sind(longitudinal_) * cosd(azimuthal_) * temp + mu_z_ * cosd(longitudinal_);
    } else {
        temp_mu_x = sind(longitudinal_) * cosd(azimuthal_);
        temp_mu_y = sind(longitudinal_) * sind(azimuthal_);
        if (mu_z_ >= 0.0) {
            temp_mu_z = cosd(longitudinal_);
        } else {
            temp_mu_z = (-1.0) * cosd(longitudinal_);
        }
    }

    mu_x_ = temp_mu_x;
    mu_y_ = temp_mu_y;
    mu_z_ = temp_mu_z;

    /*std::cout << "\nnew uxx: " << mu_x_;
    std::cout << "\nnew uyy: " << mu_y_;
    std::cout << "\nnew uzz: " << mu_z_;*/
}

/************************************************************************************************************************
    layer management
************************************************************************************************************************/

void MCSTIL::Photon::SetLayer(unsigned int new_layer) {
    curr_layer_ = new_layer;
}

unsigned int MCSTIL::Photon::GetLayer() {
    return curr_layer_;
}

void MCSTIL::Photon::SetNextLayer(unsigned int new_layer) {
    next_layer_ = new_layer;
}

unsigned int MCSTIL::Photon::GetNextLayer() {
    return next_layer_;
}

/************************************************************************************************************************
    direction checks
************************************************************************************************************************/

bool MCSTIL::Photon::Up() {
    if (mu_z_ < 0.0) {
        return true;
    } else {
        return false;
    }
}

bool MCSTIL::Photon::Down() {
    if (mu_z_ > 0.0) {
        return true;
    } else {
        return false;
    }
}

/************************************************************************************************************************
    position checks
************************************************************************************************************************/

double MCSTIL::Photon::GetX() {
    return x_;
}

double MCSTIL::Photon::GetY() {
    return y_;
}

double MCSTIL::Photon::GetZ() {
    return z_;
}

/************************************************************************************************************************
    boundary collisions
************************************************************************************************************************/

bool MCSTIL::Photon::HitBound(double bound) {
    if (fabs(step_ * mu_z_) - fabs(bound - z_) >= 0) {
        return true;
    } else {
        return false;
    }
}

bool MCSTIL::Photon::RemHitBound(double bound) {
    if ((fabs(rem_step_ * mu_z_) - fabs(bound - z_)) >= 0) {
        return true;
    } else {
        return false;
    }
}

    bool MCSTIL::Photon::Fresnel(double n_i_, double n_t_, double tissue_top) {
    theta_i_ = acosd(fabs(mu_z_));

    if (((n_i_ * sind(theta_i_)) / n_t_) >= 1.0) {
        mu_z_ *= -1.0;
        return true;
    } else {
        double xi = MCSTIL::MCSTILRandom::Instance() -> MCSTIL::MCSTILRandom::ReturnXi();

        if (theta_i_ == 0 && theta_t_ == 0 && z_ <= tissue_top) {
            double spec;
            spec = pow((n_i_ - n_t_), 2.0) / pow((n_i_ + n_t_), 2.0);
            weight_ -= spec;
            backs_ += spec;

            if (spec == 0) {
                std::cout << "\nn_i_: " << n_i_ << " | n_t_: " << n_t_;
            }
        }

        theta_t_ = asind((n_i_ * sind(theta_i_)) / n_t_);
        double R = (0.5) * ((pow(sind(theta_i_ - theta_t_), 2) / pow(sind(theta_i_ + theta_t_), 2)) + (pow(tand(theta_i_ - theta_t_), 2) / pow(tand(theta_i_ + theta_t_), 2)));

        if (R < xi) { // reflection; reverse z-direction
            mu_z_ *= -1.0;
            return true;
        } else { // transmission; calculate new z-direction for transmission through the boundary
            double temp_mu_z;
            longitudinal_ = theta_t_;
            temp_mu_z = -sind(longitudinal_) * cosd(azimuthal_) * sqrt(1.0 - pow(mu_z_, 2.0)) + mu_z_ * cosd(longitudinal_);
            mu_z_ = temp_mu_z;
            return false;
        }
    }
}

double MCSTIL::Photon::PosAfterRemStep() {
    return z_ + (mu_z_ * rem_step_);
}

/************************************************************************************************************************
    grid absorption
************************************************************************************************************************/

void MCSTIL::Photon::Absorb(double mu_a_, double mu_s_) {
    double frac_abs;
    double absorbed;
    if (mu_a_ == 0 && mu_s_ == 0) {
        frac_abs = 0;
    } else {
        frac_abs = mu_a_ / (mu_a_ + mu_s_);
    }

    absorbed = frac_abs * weight_;
    abs_ += absorbed;
    weight_ -= absorbed;
}

/************************************************************************************************************************
    weight management, roulette technique
************************************************************************************************************************/

double MCSTIL::Photon::GetWeight() {
    return weight_;
}

bool MCSTIL::Photon::WeightLow() {
    return (weight_ < THRESH_WEIGHT ? true : false);
}

void MCSTIL::Photon::Roulette() {
    double xi = MCSTIL::MCSTILRandom::Instance() -> MCSTIL::MCSTILRandom::ReturnXi();

    if (xi < CHANCE) { // survive
        double mw = weight_ * (1 / CHANCE);
        weight_ += mw;
    } else {
        weight_ = 0;
        alive_ = false;
    }
}

void MCSTIL::Photon::Kill() {
    alive_ = false;
}

/************************************************************************************************************************
    debugging
************************************************************************************************************************/

void MCSTIL::Photon::DisplayInfo(bool debug, std::string label) {
    if (debug == true) {
        std::cout << "\n\n\n----- " << label << " -----";
        std::cout << "\nWeight:\t\t\t" << weight_;
        std::cout << "\nStep size:\t\t" << step_;
        std::cout << "\nRemaining step:\t\t" << rem_step_;
        std::cout << "\nCurrent layer:\t\t" << curr_layer_;
        std::cout << "\nNext layer:\t\t" << next_layer_;
        std::cout << "\nPosition:\t\t(" << x_ << "," << y_ << "," << z_ << ")";
        std::cout << "\nDirections:\t\t(" << mu_x_ << "," << mu_y_ << "," << mu_z_ << ")";
        std::cout << "\nCosines squared:\t  " << pow(mu_x_, 2.0) + pow(mu_y_, 2.0) + pow(mu_z_, 2.0);
        std::cout << "\nAzimuthal:\t\t" << azimuthal_;
        std::cout << "\nLongitudinal:\t\t" << longitudinal_;
        std::cout << "\nIncident angle:\t\t" << theta_i_;
        std::cout << "\nTransmission angle:\t" << theta_t_;
    }
}

bool MCSTIL::Photon::CheckNaN() {
    if (std::isnan(mu_x_) || std::isnan(mu_y_) || std::isnan(mu_z_)) {
        return true;
    } else {
        return false;
    }
}

bool MCSTIL::Photon::CheckCosines() {
    if (pow(mu_x_, 2.0) + pow(mu_y_, 2.0) + pow(mu_z_, 2.0) != 1.0) {
        return false;
    } else {
        return true;
    }
}
