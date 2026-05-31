// este pch.h solo en los cpp, ya lo agrega el compilador
#include "pch.h"
#include "Usuario.h"

Usuario::Usuario()
{
	this->telefono = 0;
	this->nombre = "";
}

Usuario::Usuario(int telefono)
{
	this->telefono = telefono;
}

Usuario::Usuario(int telefono, string nombre, int cantidadDeChats) : 
	chats(cantidadDeChats)
{
	this->telefono = telefono;
	this->nombre = nombre;
	// de momento no usamos la cantidadDeChats
}

Usuario::~Usuario()
{
}

string Usuario::toJson()
{
	stringstream json;
	json << "{";
	json << "\"telefono\":" << telefono << ",";
	json << "\"nombre\":\"" << nombre << "\",";
	// json << "\"chats\":" << chats.toJson(Chat::toJson);
	// json << "\"chats\":[]";
	json << "\"chats\":[";
	for (int i = 0; i < chats.getCantidad(); i++) {
		json << chats[i]->toJson();
		if (i < chats.getCantidad() - 1) {
			json << ",";
		}
	}
	json << "]";
	json << "}";
	return json.str();
}

int Usuario::getTelefono()
{
	return telefono;
}

void Usuario::registrarChat(Chat* chat)
{
	chats.registrar(chat);
}

bool Usuario::compararUsuarios(Usuario* a, Usuario* b)
{
	return a->telefono == b->telefono;
}

void Usuario::enviarMensaje(int telefonoDestino, Mensaje* mensaje)
{
	// Busco el chat y envio(registrar) mensaje 
	Chat* encontrado = buscarChat(telefonoDestino);
	if (encontrado) {
		encontrado->enviarMensaje(mensaje);
	}
	else {
		throw exception();
	}
}

void Usuario::recibirMensaje(int telefonoOrigen, Mensaje* mensaje)
{
	// Busco el chat y recibo(registrar) mensaje 
	Chat* encontrado = buscarChat(telefonoOrigen);
	if (encontrado) {
		encontrado->recibirMensaje(mensaje);
	}
	else {
		throw exception();
	}
}

Chat* Usuario::buscarChat(int telefono)
{
	try {
		Chat buscado(telefono);
		Chat* encontrado = chats.buscar(&buscado, Chat::comparador);
		return encontrado;
	}
	catch (exception e) {
		cout << "No se encontro el chat" << endl;
	}
	return nullptr;
}
