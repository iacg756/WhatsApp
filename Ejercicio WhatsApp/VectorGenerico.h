#pragma once
#include <iostream>
#include <exception>

using namespace std;
// cuando trabajemos con templates solo se debe tener un archivo .h
template<typename T>
class VectorGenerico {
private:
	int cantidad;
	int capacidad;
	T* elementos; // conjunto de elementos T, donde T puede tomar cualquier forma
public:
	VectorGenerico();
	VectorGenerico(int capacidad);
	~VectorGenerico();
	// 'T elemento' ya contiene datos que se almacenara en 'T* elementos'
	void registrar(T elemento);
	// (*funcionParaMostrar): funcion que apunta a otra para mostrar T
	// T: representa cualquier atributo primitivo o complejo
	void mostrar(void (*funcionParaMostrar)(T));
	void ordenar(bool (*comparador)(T, T));
	T& buscar(T buscado, bool (*comparador)(T, T));
	// retornamos una referencia porque cuando busquemos puede que necesitemos su direccion
	// tambien retornamos la direccion para cuando hagamos un delete en el uso de punteros
	T& operator[](int posicion);
	int getCantidad();
};

template<typename T>
inline VectorGenerico<T>::VectorGenerico(int capacidad) {
	this->capacidad = capacidad;
	this->cantidad = 0;
	this->elementos = new T[this->capacidad];
}
template<typename T>
inline VectorGenerico<T>::VectorGenerico() {
	this->capacidad = 5;
	this->cantidad = 0;
	this->elementos = new T[this->capacidad];
}
template<typename T>
VectorGenerico<T>::~VectorGenerico() {
	delete[] elementos;
}
template<typename T>
inline void VectorGenerico<T>::registrar(T elemento) {
	if (cantidad < capacidad) {
		// no es agregacion, porque el destructor elimina todos los elementos del vector generico
		elementos[cantidad] = elemento;
		cantidad++;
	} else {
		cout << "Se llego al limite de elementos" << endl;
	}
}
template<typename T>
inline void VectorGenerico<T>::mostrar(void(*funcionParaMostrar)(T)) {
	for (int i = 0; i < cantidad; i++) {
		funcionParaMostrar(elementos[i]);
		// cout << elementos[i] << endl;
	}
}
template<typename T>
inline void VectorGenerico<T>::ordenar(bool (*comparador)(T, T)) {
	// burbuja
	// i define la cantida de comparaciones
	for (int i = 0; i < cantidad - 1; i++) {
		// se compara con los que no estan ordenados hasta ordenarlos
		for (int j = 0; j < cantidad - i - 1; j++) {
			// if (elementos[j] > elementos[j + 1]) {
			if (comparador(elementos[j], elementos[j + 1])) {
				swap(elementos[j], elementos[j + 1]);
				// T aux = elementos[j];
				// elementos[j] = elementos[j + 1];
				// elementos[j + 1] = aux;
			}
		}
	}
}

template<typename T>
inline T& VectorGenerico<T>::buscar(T buscado, bool (*comparador)(T, T)) {
	for (int i = 0; i < cantidad; i++) {
		// if (buscado == elementos[i]) {
		if (comparador(buscado, elementos[i])) {
			return elementos[i];
		}
	}
	throw exception("No existe el elemento buscado");
}

template<typename T>
inline T& VectorGenerico<T>::operator[](int posicion)
{
	if (posicion < cantidad) {
		return elementos[posicion];
	}
	// no sabemos que hacer por lo cual podemos decir que es un exception, caso unico, no contemplado, algo raro
	
	// una exception te ayuda a identificar compartamiento inesperado o compartiento que no puedes controlar
	throw exception("No se puede superar la cantidad");
}

template<typename T>
inline int VectorGenerico<T>::getCantidad()
{
	return cantidad;
}
