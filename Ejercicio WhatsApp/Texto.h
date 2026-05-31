#pragma once
#include "Mensaje.h"
class Texto :
    public Mensaje
{
private:
    string contenido;
public:
    Texto();
    Texto(int fecha, string contenido);
    ~Texto();
    string toJson();
};

