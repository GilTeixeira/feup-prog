#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <windows.h>
#include<algorithm>
#include <conio.h>

#undef max

using namespace std;


void clearScreen();
//apagar?????
//unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int max);
int lenum();
int leInteiro(int min, int max);
float le_float_positivo();


void estrela();
void linha();

bool tem_algarismos(const string &input);
bool BothAreSpaces(char lhs, char rhs);
string le_string();

void espera_input();