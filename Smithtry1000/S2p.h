#pragma once
#ifndef _TOUCHSTONE_FILE_H_
#define _TOUCHSTONE_FILE_H_

#include <vector>
#include "Timedes.h"
using namespace std;

typedef enum { GHz, MHz, KHz, Hz }FUnit;
typedef enum { DB, MA, RI }SFormat;

/// <summary>
/// Класс для получения S-параметров.
/// </summary>
class TouchstoneFile
{
public:
    TouchstoneFile();
    ~TouchstoneFile();
    /// can load s1p and s2p files
    spar_t Load2P(const char* filename);


};

#endif