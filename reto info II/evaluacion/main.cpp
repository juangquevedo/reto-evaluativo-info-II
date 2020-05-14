#include "funciones.h"
//la clave de admin es esta programa es nada_es_verdad

int main(){
    bool ban=1;
    int op;
    map <int,producto> inv; //en este map se almacena el inventario de productos la calve es el ID del producto y el contenido es un objeto de la clase producto, que contiene las caracteristicas de cada producto
    map <int,combo> com; //en este map se almacena los combos disponibles, la clave es el numero del combo y el contenido es un objeto de la clase combo, con las caracteristicas de cada combo
    iniciar_inv(inv);
    iniciar_com(com);
    cout<<"Bienvenido a la confiteria de su cinema\n";
    while(ban){
        cout<<"\nQue le gustaria hacer\n1)Entrar como administrador\n2)Realizar una compra con su usuario\n3)Crear un ususario\n0)Salir\n(digite el numero de la opcion a realizar) ";
        cin>>op;
        switch(op){
        case 1:
            iniciar_admi(inv,com);
            break;
        case 2:
            ingresar_usu(inv,com);
            break;
        case 3:
            registrar_usu();
            break;
        case 0:
            ban=0;
            break;
        default:
            break;
        }
        if(op!=0)system("pause");
    }
    guardar_com(com);
    guardar_inv(inv);
    return 0;
}
