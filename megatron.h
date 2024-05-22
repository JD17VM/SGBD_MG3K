#include <iostream>
#include <string>
using namespace std;

string completarNumeroConCeros(int numero, int longitud)
{
    string texto = to_string(numero);
    if (longitud > texto.length())
    {
        texto = string(longitud - texto.length(), '0') + texto;
    }
    return texto;
}