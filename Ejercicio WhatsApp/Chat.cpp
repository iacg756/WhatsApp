#include "pch.h"
#include "Chat.h"

Chat::Chat()
{
}

Chat::Chat(int telefonoDestino)
{
	this->telefonoDestino = telefonoDestino;
}

Chat::Chat(int telefonoDestino, int cantidadDeMensajes) 
	: mensajesEnviados(cantidadDeMensajes), mensajesRecibidos(cantidadDeMensajes)
{
	this->telefonoDestino = telefonoDestino;
}

Chat::~Chat()
{
}

string Chat::toJson()
{
	stringstream json;
	json << "{";
	json << "\"numero\":" << telefonoDestino << ",";
	json << "\"mensajesEnviados\":[";
	for (int i = 0; i < mensajesEnviados.getCantidad(); i++) {
		json << mensajesEnviados[i]->toJson();
		if (i < mensajesEnviados.getCantidad() - 1) {
			json << ",";
		}
	}
	json << "],";
	json << "\"mensajesRecibidos\":[";
	for (int i = 0; i < mensajesRecibidos.getCantidad(); i++) {
		json << mensajesRecibidos[i]->toJson();
		if (i < mensajesRecibidos.getCantidad() - 1) {
			json << ",";
		}
	}
	json << "]";
	json << "}";
	return json.str();
}

bool Chat::comparador(Chat* chat1, Chat* chat2)
{
	return chat1->telefonoDestino == chat2->telefonoDestino;
}

void Chat::enviarMensaje(Mensaje* mensaje)
{
	mensajesEnviados.registrar(mensaje);
}

void Chat::recibirMensaje(Mensaje* mensaje)
{
	mensajesRecibidos.registrar(mensaje);
}
