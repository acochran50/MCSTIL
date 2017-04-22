#ifndef _MCSTIL_H
#define _MCSTIL_H

/*----- Standard Library Headers ----------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <chrono>   // need "-std=c++11" option for g++
#include <random>   // need "-std=c++11" option for g++

/*----- Class Headers ---------------------------------------------------------------------------*/
#include "../src/Photon_v3.hpp"
#include "../src/TissueLayer_v3.hpp"
#include "../src/MCSTILRandom_v3.hpp"
#include "../src/Grid_v3.hpp"

/*----- Function File Headers -------------------------------------------------------------------*/
#include "../src/MCSTIL_ERROR_v3.hpp"

/*----- Trigonometric Functions -----------------------------------------------------------------*/
double sind(double angle);
double cosd(double angle);
double tand(double angle);
double asind(double trig_ratio);
double acosd(double trig_ratio);
double atand(double trig_ratio);

/*----- Constants -------------------------------------------------------------------------------*/
#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define BIRTH_WEIGHT 1.0        // initial photon weight
#define THRESH_WEIGHT 1e-4      // threshold photon weight
#define CHANCE 1e-1             // roulette survival chance

#endif
