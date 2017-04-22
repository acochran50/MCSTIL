#ifndef _GRID_H
#define _GRID_H

namespace MCSTIL {
/****************/
class Grid {
    public:
        Grid();
        ~Grid();
        void PushTransCoords(double x, double y, double z, bool pushflag);
        void PushAbsCoords(double x, double y, double z, bool pushflag);
        void PushReflCoords(double x, double y, double z, bool pushflag);
        void PrintTransCoords(int coord_index);
        void PrintAbsCoords(int coord_index);
        void PrintReflCoords(int coord_index);
        void WriteTransCoords(std::ostream& out_file, bool outflag);
        void WriteAbsCoords(std::ostream& out_file, bool outflag);
        void WriteReflCoords(std::ostream& out_file, bool outflag);
    private:
        std::vector < std::vector < double > > trans_grid;
        std::vector < std::vector < double > > abs_grid;
        std::vector < std::vector < double > > refl_grid;
        int trans_counter;
        int abs_counter;
        int refl_counter;
};
/****************/
}

#endif
