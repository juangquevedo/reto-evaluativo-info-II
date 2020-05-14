#include "combo.h"


void combo::crear(map <int,producto> inv){
    //esta funcion facilita la creacion de el nuevo combo
    int temp[2];
    bool ban=1;
    cout<<"cual es el contenido del combo: ";
    cin>>contenido;
    for(int i=1;ban;i++){
        temp[0]=-1;
        while(inv.find(temp[0])==inv.end()){
            cout<<"cual es el id del "<<i<<" producto que se incluye: ";
            cin>>temp[0];
            if(inv.find(temp[0])==inv.end()) cout<<"\nEl producto ingresado no esta en el inventerio\n";
        }
        cout<<"cual es la cantidad que se incluye: ";
        cin>>temp[1];
        ff.insert(pair<int,int>(temp[0],temp[1]));
        cout<<"el combo incluye algo mas? (1 si, 0 no) ";
        cin>>ban;
    }
    cout<<"cual es el costo del combo: ";
    cin>>costo;
}

void combo::iniciar(string cont, long long cost, map<int, int> f){
    //esta funcion es la que se invoca para iniciar los combos cuando se inicia el programa
    contenido=cont;
    costo=cost;
    ff=f;
}

string combo::ver_combo(){
    //esta funcion facilita la visualizacion de las caracteristicas del objeto para mostraselas al usuario
    string ver='|' + contenido;
    for(unsigned int i=0;i<(50-contenido.length());i++) ver.push_back(' ');
    ver.push_back('|');
    if(costo>=1000 && costo<10000) ver= ver + "  ";
    else ver.push_back(' ');
    ver= ver + int2str(costo) + '|';
    return ver;
}

string combo::guardado(){
    //facilita la funcion de guardado retornando en un string los datos privados a guardar
    string datos;
    map <int,int>::iterator it;
    datos=contenido + ';' + int2str(costo) + ';';
    for(it=ff.begin();it!=ff.end();it++)
        datos= datos + int2str(it->first) + '-' + int2str(it->second) + ';';
    datos.pop_back();
    return datos;
}

bool combo::disponibilidad(map<int, producto> inv){
    //esta funcion se basa en los profuctos existente para devolver un true si si se puede vender o un false en caso contrario
    map <int,int>::iterator it;
    for(it=ff.begin();it!=ff.end();it++){
        if(inv[it->first].disponible<unsigned(it->second) || inv.find(it->first)==inv.end())
            return 0;
    }
    return 1;
}

void combo::comprar_com(map<int, producto> &inv){
    //esta funcion se ejecuta cundo se compra un combo, lo que hace es sacar del inventario los productos que lleva el combo
    map <int,int>::iterator it;
    for(it=ff.begin();it!=ff.end();it++){
        inv[it->first].sacar_producto(it->second);
    }
}

string combo::int2str(int long long a){
    //esta funncion se usa para convertir las caracteristicas int a string y poder manejarlas mejor
    int long long c=0,i=1;
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
