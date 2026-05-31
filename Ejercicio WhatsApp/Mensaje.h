#pragma once
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
// [{"fecha":20241201,"tipo":"texto","contenido":"Mandame la foto"}]
class Mensaje
{
protected:
	int fecha;
	string tipo;
public:
	Mensaje();
	Mensaje(int fecha, string tipo);
	~Mensaje();
	virtual string toJson();
};
