#include "combo.h"

combo::combo(){
    int temp[2];
    bool ban=1;
    cout<<"cual es el contenido del combo: ";
    cin>>contenido;
    for(int i=1;ban;i++){
        cout<<"cual es el id del "<<i<<" producto que se incluye: ";
        cin>>temp[0];
        cout<<"cual es la cantidad que se incluye: ";
        cin>>temp[1];
        ff.insert(pair<int,int>(temp[0],temp[1]));
        cout<<"el combo incluye algo mas? (1 si, 0 no) ";
        cin>>ban;
    }
    cout<<"cual es el costo del combo: ";
    cin>>costo;
}

void combo::ver_combo(){
    cout<<'|'<<contenido<<'|'<<costo<<"|\n";
}

string combo::guardado(){
    //facilita la funcion de guardado retornando en un string los datos privados a guardar
    string datos;
    map <int,int>::iterator it;
    datos=contenido + ';';
    for(it=ff.begin();it!=ff.end();it++)
        datos= datos + int2str(it->first) + '-' + int2str(it->second) + ';';
    datos=datos + int2str(costo);
    return datos;
}

string combo::int2str(int long long a){
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
