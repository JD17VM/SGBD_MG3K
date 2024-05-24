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


void completarTextoCon(string &texto,char caracter, int longitud, string posicion){
    if (longitud > texto.length()){
        if(posicion == "derecha"){
            texto = texto + string(longitud - texto.length(),caracter);
        }else if(posicion == "izquierda"){
            texto = string(longitud - texto.length(),caracter) + texto;
        }
    }
    else{
        texto = texto.substr(0,longitud-3) + "...";
    }
}



string textoCompletadoCon(string texto,char caracter, int longitud, string posicion){
    if (longitud > texto.length()){
        if(posicion == "derecha"){
            texto = texto + string(longitud - texto.length(),caracter);
        }else if(posicion == "izquierda"){
            texto = string(longitud - texto.length(),caracter) + texto;
        }
    } else{
        texto = texto.substr(0,longitud-3) + "...";
    }
    return texto;
}