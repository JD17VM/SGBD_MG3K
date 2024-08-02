#ifndef MEGATRON_H
#define MEGATRON_H

#include <cmath>

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

string textoCompletadoConSinPuntosSuspensivos(string texto,char caracter, int longitud, string posicion){
    if (longitud >= texto.length()){
        const int espacios_por_completar = longitud - texto.length();
        if(posicion == "derecha"){
            texto = texto + string(espacios_por_completar,caracter);
        }else if(posicion == "izquierda"){
            texto = string(espacios_por_completar,caracter) + texto;
        }
    } 
    return texto;
}


vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    for (char ch : str) {
        if (ch == delimiter) {
            tokens.push_back(token);  // Añadir el token actual al vector
            token.clear();  // Limpiar el token
        } else {
            token += ch;  // Añadir el carácter actual al token
        }
    }
    // Añadir el último token
    tokens.push_back(token);
    return tokens;
}

int contador_digitos(int num) {
    if (num == 0) return 1;
    return log10(num) + 1;
}

#endif