#include "../include/MCSTIL_v3.hpp"
#include "Grid_v3.hpp"

/************************************************************************************************************************
    constructor, destructor
************************************************************************************************************************/

MCSTIL::Grid::Grid() {
    // default constructor
}

MCSTIL::Grid::~Grid() {
    // default destructor
}

/************************************************************************************************************************
    pushing event coordinates to grid
************************************************************************************************************************/

void MCSTIL::Grid::PushTransCoords(double x, double y, double z, bool pushflag) {
    if (pushflag == true) {
        std::vector < double > temp_trans_grid = { x, y, z };
        trans_grid.push_back(temp_trans_grid);
    }
}

void MCSTIL::Grid::PushAbsCoords(double x, double y, double z, bool pushflag) {
    if (pushflag == true) {
        std::vector < double > temp_abs_grid = { x, y, z };
        abs_grid.push_back(temp_abs_grid);
    }
}

void MCSTIL::Grid::PushReflCoords(double x, double y, double z, bool pushflag) {
    if (pushflag == true) {
        std::vector < double > temp_refl_grid = { x, y, z };
        refl_grid.push_back(temp_refl_grid);
    }
}

/************************************************************************************************************************
    write information from each grid to their respective output files
************************************************************************************************************************/

void MCSTIL::Grid::WriteTransCoords(std::ostream& outfile, bool outflag) {
    if (outflag == true) {
        for (unsigned int coord_index = 0; coord_index < trans_grid.size(); ++coord_index) {
            outfile << "\n" << trans_grid[coord_index][0] << "\t"
                             << trans_grid[coord_index][1] << "\t"
                             << trans_grid[coord_index][2];
        }
    }
}

void MCSTIL::Grid::WriteAbsCoords(std::ostream& outfile, bool outflag) {
    if (outflag == true) {
        for (unsigned int coord_index = 0; coord_index < abs_grid.size(); ++coord_index) {
            outfile << "\n" << abs_grid[coord_index][0] << "\t"
                             << abs_grid[coord_index][1] << "\t"
                             << abs_grid[coord_index][2];
        }
    }
}

void MCSTIL::Grid::WriteReflCoords(std::ostream& outfile, bool outflag) {
    if (outflag == true) {
        for (unsigned int coord_index = 0; coord_index < refl_grid.size(); ++coord_index) {
            outfile << "\n" << refl_grid[coord_index][0] << "\t"
                             << refl_grid[coord_index][1] << "\t"
                             << refl_grid[coord_index][2];
        }
    }
}

/************************************************************************************************************************
    debugging
************************************************************************************************************************/

void MCSTIL::Grid::PrintTransCoords(int coord_index) {
    std::cout << "\nTransmission: (" << trans_grid[coord_index][0] << ", "
                                     << trans_grid[coord_index][1] << ", "
                                     << trans_grid[coord_index][2] << ")";
}

void MCSTIL::Grid::PrintAbsCoords(int coord_index) {
    std::cout << "\nAbsorption: ("   << abs_grid[coord_index][0] << ", "
                                     << abs_grid[coord_index][1] << ", "
                                     << abs_grid[coord_index][2] << ")";
}

void MCSTIL::Grid::PrintReflCoords(int coord_index) {
    std::cout << "\nReflection: ("   << refl_grid[coord_index][0] << ", "
                                     << refl_grid[coord_index][1] << ", "
                                     << refl_grid[coord_index][2] << ")";
}
