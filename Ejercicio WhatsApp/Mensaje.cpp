#include "pch.h"
#include "Mensaje.h"

Mensaje::Mensaje()
{
}

Mensaje::Mensaje(int fecha, string tipo)
{
	this->fecha = fecha;
	this->tipo = tipo;
}

Mensaje::~Mensaje()
{
}

string Mensaje::toJson()
{
	return string();
}
