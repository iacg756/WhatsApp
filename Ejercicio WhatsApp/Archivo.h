#pragma once
#include "Mensaje.h"
class Archivo :
    public Mensaje
{
private:
    string nombre;
    string extension;
public:
    Archivo();
    Archivo(int fecha, string nombre, string extension);
    ~Archivo();
    string toJson();
};

