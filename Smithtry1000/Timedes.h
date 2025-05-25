#pragma once
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <complex>
#include <vector>
using namespace std;
typedef complex<double> complex_t;

/// Contains the S-parameter matrix and the frequency range
typedef  struct {
    vector<vector<vector<complex_t> > > S;
    vector<vector<vector<complex_t> > > K;
    vector<double> f;
    vector<double> S11, S22, S12, Ms, Mg, Mu, Mk;
}	spar_t;

/// Strings for the names of the s-parameters
const char SparameterNames[4][4][4] =
{
    {"S11","S12","S13","S14"},
    {"S21","S22","S23","S24"},
    {"S31","S32","S33","S34"},
    {"S41","S42","S43","S44"}
};

/// Enum for the different types that the Chart can plot
typedef enum { DB_PLOT, PHASE_PLOT, DBPHASE_PLOT, MAG_PLOT, MAGPHASE_PLOT, VSWR_PLOT, SMITH_PLOT, POLAR_PLOT }SparType;

/// Amplitude can be in dBm, W or mW
typedef enum
{
    dBm, W, mW
}AmpType;

#endif