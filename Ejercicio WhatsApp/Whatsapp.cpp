#include "pch.h"
#include "Whatsapp.h"

Whatsapp::Whatsapp() : grupos(10)
{
}

Whatsapp::Whatsapp(int capacidadGrupos) : grupos(capacidadGrupos)
{
}

Whatsapp::~Whatsapp()
{
}

void Whatsapp::enviarYRecibirMensaje(int telefonoOrigen, int telefonoDestino, Mensaje* mensaje)
{
	// Falla silenciosamente si alguno no existe o no tienen chat registrado
	try {
		SingletonDeUsuarios::getInstancia().enviarMensaje(telefonoOrigen, telefonoDestino, mensaje);
	}
	catch (...) {
		return;
	}
	try {
		SingletonDeUsuarios::getInstancia().recibirMensaje(telefonoDestino, telefonoOrigen, mensaje);
	}
	catch (...) {
		// ignora si no puede recibir
	}
}

void Whatsapp::registrarGrupo(int id, string nombre, string descripcion, int capacidadParticipantes)
{
	grupos.registrar(new Grupo(id, nombre, descripcion, capacidadParticipantes));
}

void Whatsapp::agregarParticipante(int idGrupo, int telefonoUsuario)
{
	// Buscar el grupo por id
	Grupo buscado(idGrupo, "", "", 1);
	try {
		Grupo* grupo = grupos.buscar(&buscado, Grupo::comparador);
		// Buscar el usuario en el singleton
		Usuario* usuario = SingletonDeUsuarios::getInstancia().buscarPorTelefono(telefonoUsuario);
		if (usuario && grupo) {
			grupo->agregarParticipante(usuario);
		}
	}
	catch (...) {
		// Grupo no encontrado, ignorar
	}
}

string Whatsapp::toJson()
{
	stringstream json;
	json << "{";
	json << "\"usuarios\":" << SingletonDeUsuarios::getInstancia().toJson() << ",";
	json << "\"grupos\":[";
	for (int i = 0; i < grupos.getCantidad(); i++) {
		json << grupos[i]->toJson();
		if (i < grupos.getCantidad() - 1) {
			json << ",";
		}
	}
	json << "]";
	json << "}";
	return json.str();
}
