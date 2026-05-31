#pragma once
#include <string>
#include <sstream>
#include "VectorGenerico.h"
#include "Grupo.h"
#include "SingletonDeUsuarios.h"
using namespace std;

// {"usuarios":[...],"grupos":[...]}
class Whatsapp
{
private:
	VectorGenerico<Grupo*> grupos;
public:
	Whatsapp();
	Whatsapp(int capacidadGrupos);
	~Whatsapp();

	// Envia y recibe el mismo mensaje entre origen y destino.
	// Si alguno de los usuarios no existe o no tienen chat, falla silenciosamente.
	void enviarYRecibirMensaje(int telefonoOrigen, int telefonoDestino, Mensaje* mensaje);

	void registrarGrupo(int id, string nombre, string descripcion, int capacidadParticipantes);
	void agregarParticipante(int idGrupo, int telefonoUsuario);

	string toJson();
};
