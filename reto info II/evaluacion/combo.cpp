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
