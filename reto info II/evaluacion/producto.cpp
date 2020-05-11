#include "producto.h"
//pide los valores para crear un objeto de la clase producto
producto::producto(){
    cout << "nombre del prducto: ";
    cin>>nombre;
    cout<<"cuantas unidades trae cada producto: ";
    cin>>unidades_a;
    unidades_p=unidades_a;
    cout<<"que cantidad hay de producto: ";
    cin>>cantidad;
    cout<<"cual es el costo total de este inventario: ";
    cin>>costo;
}
//con los valores de producto a sacar edita el inventario(la cantidad de productos disponibles y el costo del inventario)
void producto::sacar_producto(int num){
    costo-=num*(costo/(((cantidad-1)*unidades_p)+unidades_a));
    unidades_a-=num;
    if (num>unidades_a){
        unidades_a=unidades_p+unidades_a;
        cantidad--;
    }
    if(unidades_a==0){
        unidades_a=unidades_p;
        cantidad--;
    }
}
//perite ver el nombre del producto, la cantidad y el costo, facilita la visualizacion de los productos en el sistema
void producto::ver_producto(){
    cout<<'|'<<nombre<<'|'<<cantidad<<'|'<<costo<<'|';
}
