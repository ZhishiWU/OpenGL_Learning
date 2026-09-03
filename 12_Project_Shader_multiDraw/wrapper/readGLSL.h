#ifndef __READGLSL_H__
#define __READGLSL_H__

#include <string>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::string;

std::string readGLSL(const char *filename);

#endif