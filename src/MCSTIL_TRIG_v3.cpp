#include "../include/MCSTIL_v3.hpp"

/*-------------------------------------------------------------------------------------------------------------------*/
/*----- Trigonometric functions that return angles in degrees  ------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

double sind(double angle) {
	double angle_rad = angle * (PI / 180.0);
	return sin(angle_rad);
}

double cosd(double angle) {
	double angle_rad = angle * (PI / 180.0);
	return cos(angle_rad);
}

double tand(double angle) {
	double angle_rad = angle * (PI / 180.0);
	return tan(angle_rad);
}

/*-------------------------------------------------------------------------------------------------------------------*/
/*----- Inverse trigonometric functions that return angles in degrees -----------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

double asind(double trig_ratio) {
	double angle_rad = asin(trig_ratio);
	double angle_deg = angle_rad * (180.0 / PI);
	return angle_deg;
}

double acosd(double trig_ratio) {
	double angle_rad = acos(trig_ratio);
	double angle_deg = angle_rad * (180.0 / PI);
	return angle_deg;
}

double atand(double trig_ratio) {
	double angle_rad = atan(trig_ratio);
	double angle_deg = angle_rad * (180.0 / PI);
	return angle_deg;
}
