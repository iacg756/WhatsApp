#pragma once
#include "VectorGenerico.h"
#include "Usuario.h"
#include "Chat.h"
class SingletonDeUsuarios
{
private:
	SingletonDeUsuarios();
	VectorGenerico<Usuario*> usuarios;
public:
	~SingletonDeUsuarios();
	// static: porque la funcion getInstancia no depende de crear una variable del tipo SingletonDeUsuarios
	// SingletonDeUsuarios&: porque tengo que retorna la direccion de la unica instacia de SingletonDeUsuarios
	static SingletonDeUsuarios& getInstancia();
	void registrarUsuario(Usuario* usuario);
	string toJson();
	Usuario* buscarPorTelefono(int telefono);
	void registrarChat(int telefono, Chat* chat);
	// enviarMensaje(telefonoOrigen, telefonoDestino, Mensaje*)
	void enviarMensaje(int origen, int destino, Mensaje* mensaje);
	// recibirMensaje(telefonoDestino, telefonoOrigen, Mensaje*)
	void recibirMensaje(int destino, int origen, Mensaje* mensaje);

};

