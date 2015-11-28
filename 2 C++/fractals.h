#ifndef FRACTALS_H
#define FRACTALS_H

#include "lsystem.h"

class KochCurve : public LSystem
{
    public:
        KochCurve();
        void substitute(Symbol s, std::vector<Symbol> &string);
};

class ArrowHeadCurve : public LSystem
{
    public:
        ArrowHeadCurve();
        void substitute(Symbol s, std::vector<Symbol> &string);
    
};

class RowOfTrees : public LSystem
{
    private:
        double c;
        double p;
        double q;
        double h;
    public:
        RowOfTrees();
        void substitute(Symbol s, std::vector<Symbol> &string);
};

#endif