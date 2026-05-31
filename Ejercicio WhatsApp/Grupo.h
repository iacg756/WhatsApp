#pragma once
#include <string>
#include <sstream>
#include "VectorGenerico.h"
#include "Usuario.h"
using namespace std;

// {"nombre":"Programacion 2","descripcion":"Paralelo 3 del semestre 2-2024","participantes":[...]}
class Grupo
{
private:
	int id;
	string nombre;
	string descripcion;
	VectorGenerico<Usuario*> participantes;
public:
	Grupo();
	Grupo(int id, string nombre, string descripcion, int capacidadParticipantes);
	~Grupo();
	int getId();
	void agregarParticipante(Usuario* usuario);
	string toJson();
	static bool comparador(Grupo* a, Grupo* b);
};
