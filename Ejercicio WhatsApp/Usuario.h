#pragma once
#include <string>
#include <sstream> // para toJson
#include <iostream>
#include "VectorGenerico.h"
#include "Chat.h"
using namespace std;

// {"telefono":70700001,"nombre":"Paola","chats":[]}
class Usuario
{
private:
	int telefono;
	string nombre;
	// ModuloDeChats chats;
	VectorGenerico<Chat*> chats;
public:
	Usuario();
	Usuario(int telefono);
	Usuario(int telefono, string nombre, int cantidadDeChats); // registrar
	~Usuario();
	string toJson();
	int getTelefono();
	void registrarChat(Chat* chat);
	static bool compararUsuarios(Usuario* a, Usuario* b);
	void enviarMensaje(int telefonoDestino, Mensaje* mensaje);
	void recibirMensaje(int telefonoOrigen, Mensaje* mensaje);
	Chat* buscarChat(int telefono);
};

