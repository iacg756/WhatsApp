#include "pch.h"
#include "Archivo.h"

Archivo::Archivo()
{
}

Archivo::Archivo(int fecha, string nombre, string extension)
	: Mensaje(fecha, "archivo")
{
	this->nombre = nombre;
	this->extension = extension;
}

Archivo::~Archivo()
{
}

string Archivo::toJson()
{
	stringstream json;
	json << "{";
	json << "\"fecha\":" << fecha << ",";
	json << "\"tipo\":\"" << tipo << "\",";
	json << "\"nombre\":\"" << nombre << "\",";
	json << "\"extension\":\"" << extension << "\"";
	json << "}";
	return json.str();
}
