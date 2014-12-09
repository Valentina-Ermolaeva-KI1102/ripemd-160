#pragma once
#include <fstream>
unsigned int rotlFixed(unsigned int x, unsigned int y);
void InitState(unsigned int *state);
void Transform (unsigned int *digest, const unsigned int *X);
unsigned char* ripemd(std::ifstream &ifst);
