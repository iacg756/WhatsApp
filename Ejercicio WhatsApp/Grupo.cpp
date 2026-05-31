#include "pch.h"
#include "Grupo.h"

Grupo::Grupo() : participantes(10)
{
	this->id = 0;
	this->nombre = "";
	this->descripcion = "";
}

Grupo::Grupo(int id, string nombre, string descripcion, int capacidadParticipantes)
	: participantes(capacidadParticipantes)
{
	this->id = id;
	this->nombre = nombre;
	this->descripcion = descripcion;
}

Grupo::~Grupo()
{
}

int Grupo::getId()
{
	return id;
}

void Grupo::agregarParticipante(Usuario* usuario)
{
	participantes.registrar(usuario);
}

string Grupo::toJson()
{
	stringstream json;
	json << "{";
	json << "\"nombre\":\"" << nombre << "\",";
	json << "\"descripcion\":\"" << descripcion << "\",";
	json << "\"participantes\":[";
	for (int i = 0; i < participantes.getCantidad(); i++) {
		json << "{";
		json << "\"telefono\":" << participantes[i]->getTelefono() << ",";
		json << "\"nombre\":\"" << participantes[i]->getNombre() << "\"";
		json << "}";
		if (i < participantes.getCantidad() - 1) {
			json << ",";
		}
	}
	json << "]";
	json << "}";
	return json.str();
}

bool Grupo::comparador(Grupo* a, Grupo* b)
{
	return a->id == b->id;
}
