#include "pch.h"
#include "Texto.h"

Texto::Texto()
{
}

Texto::Texto(int fecha, string contenido) : 
	Mensaje(fecha, "texto")
{
	this->contenido = contenido;
}

Texto::~Texto()
{
}

string Texto::toJson()
{
	stringstream json;
	json << "{";
	json << "\"fecha\":" << fecha << ",";
	json << "\"tipo\":\"" << tipo << "\",";
	json << "\"contenido\":\"" << contenido << "\"";
	json << "}";
	return json.str();
}
