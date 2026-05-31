#pragma once

#include "VectorGenerico.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Mensaje.h"
#include "Texto.h"
#include "Archivo.h"
using namespace std;


// {"numero":70700002,"mensajesEnviados":[],"mensajesRecibidos":[]}
class Chat
{
private:
	int telefonoDestino;
	// cantidadDeMensajes opcional como atributo
	VectorGenerico<Mensaje*> mensajesEnviados;
	VectorGenerico<Mensaje*> mensajesRecibidos;
public:
	Chat();
	Chat(int telefonoDestino);
	Chat(int telefonoDestino, int cantidadDeMensajes);
	~Chat();
	string toJson();
	static bool comparador(Chat* chat1, Chat* chat2);
	void enviarMensaje(Mensaje* mensaje);
	void recibirMensaje(Mensaje* mensaje);

};

