#pragma once
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <complex>
#include <vector>
using namespace std;
typedef complex<double> complex_t;

// Contains the S-parameter matrix and the frequency range
typedef  struct {
    vector<vector<vector<complex_t> > > S;
    vector<double> f;
    vector<double> S11, S22, S12, Ms, Mg, Mu, Mk;
}	spar_t;

#endif