#ifndef MEGATRON_H
#define MEGATRON_H

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

#endif