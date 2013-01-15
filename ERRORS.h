#ifndef ERRORS_H
#define ERRORS_H
#include <exception>
using namespace std;

class MemoryFull: public exception
{};

class NoSuchData: public exception
{};

class WrongInput: public exception
{};


#endif