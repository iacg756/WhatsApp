#include "pch.h"
#include "SingletonDeUsuarios.h"

SingletonDeUsuarios::SingletonDeUsuarios() :
	usuarios(4)
{
}

SingletonDeUsuarios::~SingletonDeUsuarios()
{
}

SingletonDeUsuarios& SingletonDeUsuarios::getInstancia()
{
	// static porque siempre sera la misma instancia en todas las llamadas a getInstancia
	static SingletonDeUsuarios instancia;
	return instancia;
}

void SingletonDeUsuarios::registrarUsuario(Usuario* usuario)
{
	Usuario* encontrado = buscarPorTelefono(usuario->getTelefono());
	// si ya existe el usuario
	if (encontrado != nullptr) {
		throw exception("Ya existe el usuario");
	} // cuando no existe el usuario
	else {
		usuarios.registrar(usuario);
	}
}

string SingletonDeUsuarios::toJson()
{
	stringstream json;
	json << "[";
	for (int i = 0; i < usuarios.getCantidad();i++) {
		json << usuarios[i]->toJson();
		if (i < usuarios.getCantidad() - 1) {
			json << ",";
		}
	}
	json << "]";
	return json.str();
}

Usuario* SingletonDeUsuarios::buscarPorTelefono(int telefono)
{
	try {
		Usuario buscado(telefono);
		Usuario* encontrado = usuarios.buscar(&buscado, Usuario::compararUsuarios);
		return encontrado;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	return nullptr;
}
// Me ayuda a registrar un chat entre varios usuarios
void SingletonDeUsuarios::registrarChat(int telefono, Chat* chat)
{
	// Dado un "telefono" buscar el usuario y registrar Chat
	Usuario* encontrado = buscarPorTelefono(telefono);
	if (encontrado) {
		// Tiene que saber como registrarChat
		encontrado->registrarChat(chat);
	}
}

void SingletonDeUsuarios::enviarMensaje(int origen, int destino, Mensaje* mensaje)
{
	// busco al usuario con telefono origen
	Usuario* encontrado = buscarPorTelefono(origen);
	if (encontrado) {
		// registrar
		encontrado->enviarMensaje(destino, mensaje);
	}
	else {
		throw exception();
	}
}

void SingletonDeUsuarios::recibirMensaje(int destino, int origen, Mensaje* mensaje)
{
	// busco al usuario con telefono destino
	Usuario* encontrado = buscarPorTelefono(destino);
	if (encontrado) {
		encontrado->recibirMensaje(origen, mensaje);
	}
	else {
		throw exception();
	}
}
