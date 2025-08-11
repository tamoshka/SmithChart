#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "S2p.h"

#ifdef WIN32
#include "shlwapi.h"
#include <iomanip>

int strcasecmp(const char* first, const char* second)
{
    return lstrcmpiA(first, second);
}
#define M_PI 3.1415
#endif
using namespace std;
TouchstoneFile::TouchstoneFile()
{
    setlocale(LC_NUMERIC, "C");
}

TouchstoneFile::~TouchstoneFile()
{
}

spar_t TouchstoneFile::Load2P(const char* filename)
{
    ifstream File;
    spar_t spar;
    File.open(filename);
    if (!File.good())return spar;

    spar.S.resize(2);
    for (int i = 0; i < 2; i++)
        spar.S[i].resize(2);

    FUnit fUnit = GHz;
    SFormat sFormat = MA;
    double R;
    double freq, firstS11, secondS11, firstS21, secondS21, firstS12, secondS12, firstS22, secondS22, S11, S12, S22;

    char rawline[4096];
    char* line;
    while (File.getline(rawline, 4095))
    {
        line = rawline;
        while (*line != '\0' && isspace(*line))line++;
        if (line[0] == '!' || line[0] == '\0')continue;
        if (line[0] == '#')
        {
            while (*line != '\0' && (isspace(*line) || *line == '#'))line++;

            char sFUnit[256], sSFormat[256], dontcare[256];
            sscanf(line, "%s %s %s %s %lf", sFUnit, dontcare, sSFormat, dontcare, &R);
            if (strcasecmp((sFUnit), "GHZ") == 0)fUnit = GHz;
            if (strcasecmp((sFUnit), "MHZ") == 0)fUnit = MHz;
            if (strcasecmp((sFUnit), "KHZ") == 0)fUnit = KHz;
            if (strcasecmp((sFUnit), "HZ") == 0)fUnit = Hz;

            if (strcasecmp((sSFormat), "DB") == 0)sFormat = DB;
            if (strcasecmp((sSFormat), "MA") == 0)sFormat = MA;
            if (strcasecmp((sSFormat), "RI") == 0)sFormat = RI;
            continue;
        }
        sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &freq, &firstS11, &secondS11, &firstS21, &secondS21, &firstS12, &secondS12, &firstS22, &secondS22);
        if (fUnit == GHz)freq *= 1e9;
        if (fUnit == MHz)freq *= 1e6;
        if (fUnit == KHz)freq *= 1e3;
        if (spar.f.size() > 0 && freq < spar.f.back()) { cout << "Ignoring Noise Parameters in file" << endl; break; }
        spar.f.push_back(freq);
        complex_t tempS11;
        if (sFormat == DB)tempS11 = complex_t(pow(10, firstS11 / 20), 0) * exp(complex_t(0, secondS11) * complex_t(M_PI / 180, 0));
        if (sFormat == MA)tempS11 = complex_t(firstS11 * cos(secondS11 * M_PI / 180), firstS11 * sin(secondS11 * M_PI / 180));
        if (sFormat == RI)tempS11 = complex_t(firstS11, secondS11);
        spar.S[0][0].push_back(complex_t(firstS11, secondS11));
        complex_t tempS21;
        if (sFormat == DB)tempS21 = complex_t(pow(10, firstS21 / 20), 0) * exp(complex_t(0, secondS21) * complex_t(M_PI / 180, 0));
        if (sFormat == MA)tempS21 = complex_t(firstS21 * cos(secondS21 * M_PI / 180), firstS21 * sin(secondS21 * M_PI / 180));
        if (sFormat == RI)tempS21 = complex_t(firstS21, secondS21);
        spar.S[1][0].push_back(complex_t(firstS21, secondS21));
        complex_t tempS12;
        if (sFormat == DB)tempS12 = complex_t(pow(10, firstS12 / 20), 0) * exp(complex_t(0, secondS12) * complex_t(M_PI / 180, 0));
        if (sFormat == MA)tempS12 = complex_t(firstS12 * cos(secondS12 * M_PI / 180), firstS12 * sin(secondS12 * M_PI / 180));
        if (sFormat == RI)tempS12 = complex_t(firstS12, secondS12);
        spar.S[0][1].push_back(complex_t(firstS12, secondS12));
        complex_t tempS22;
        if (sFormat == DB)tempS22 = complex_t(pow(10, firstS22 / 20), 0) * exp(complex_t(0, secondS22) * complex_t(M_PI / 180, 0));
        if (sFormat == MA)tempS22 = complex_t(firstS22 * cos(secondS22 * M_PI / 180), firstS22 * sin(secondS22 * M_PI / 180));
        if (sFormat == RI)tempS22 = complex_t(firstS22, secondS22);
        spar.S[1][1].push_back(complex_t(firstS22, secondS22));
        complex_t Delta;
        Delta = tempS11 * tempS22 - tempS12 * tempS21;
        double tempK;
        tempK = (1 - pow(abs(tempS11), 2) - pow(abs(tempS22), 2) + pow(abs(Delta), 2)) / (2 * abs(tempS12 * tempS21));
        spar.Mk.push_back(tempK);
        double MSG;
        double MAG;
        if (tempK <= 1)
        {
            MSG = 10 * log10(abs(tempS21) / abs(tempS12));
            MAG = 0;
        }
        else
        {
            MSG = 0;
            MAG = 10 * log10((abs(tempS21) / abs(tempS12)) * (tempK - sqrt(pow(tempK, 2) - 1)));
        }

        spar.Ms.push_back(MSG);
        spar.Mg.push_back(MAG);
        double Mus;
        Mus = (1 - abs(pow(tempS22, 2))) / (abs(tempS11 - Delta * conj(tempS22)) + abs(tempS21 * tempS12));
        spar.Mu.push_back(Mus);
        S11 = 20 * log10(abs(tempS11));
        S22 = 20 * log10(abs(tempS22));
        S12 = 20 * log10(abs(tempS12));
        spar.S11.push_back(S11);
        spar.S22.push_back(S22);
        spar.S12.push_back(S12);
    }
    File.close();
    bool is2port = false;
    bool is4port = false;
    for (int i = 0; i < (int)spar.S[0][0].size(); i++)
    {
        for (int nx = 0; nx < 2; nx++)
        {
            for (int ny = 0; ny < 2; ny++)
                if (abs(spar.S[nx][ny][i]) > 1e-20 && nx * ny > 0)
                {
                    is2port = true;
                    i = spar.S[0][0].size();
                }
        }
    }
    if (!is4port)
    {
        spar.S.resize(2);
        spar.S[0].resize(2);
        spar.S[1].resize(2);
    }
    if (!is2port)
    {
        spar.S.resize(1);
        spar.S[0].resize(1);
    }

    return spar;
}