#include "funciones.h"

int main(){
    map <int,producto> inv; //en este map se almacenara el inventario de productos la calve es el ID del producto y el contenido es un objeto de la clase producto, que contiene las caracteristicas de cada producto
    map <int,combo> com;
    iniciar_inv(inv);
    iniciar_com(com);
    mostrar_inv(inv);
//    iniciar_admi(inv,com);
    usuario(inv,com);
    mostrar_inv(inv);
    guardar_com(com);
    guardar_inv(inv);
    return 0;
}
