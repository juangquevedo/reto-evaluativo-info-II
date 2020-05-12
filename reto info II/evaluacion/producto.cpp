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
string producto::guardado(){
    //facilita la funcion de guardado retornando en un string los datos privados a guardar
    string datos;
    datos=nombre+';'+int2str(unidades_p)+';'+int2str(unidades_a)+';'+int2str(cantidad)+';'+int2str(costo);
    return datos;
}

string producto::int2str(int long a){
    int c=0,i=1;
    char e;
    string b;
    for(;(a/i);i=i*10)
        c++;
    for(int j=0;j<c;j++){
        i/=10;
        e=(a/i)+48;
        b.push_back(e);
        a-=(a/i)*i;
    }
    return b;
}






