#include "funciones.h"

void iniciar_admi(map <int,producto> &inv,map <int,combo> &com){
    //compara la clave ingresada con la codificada en sudo.dat
    string clave;
    cout<<"Ingrese la clave de administrador: ";
    cin>>clave;
    if(clave!=desifrar()){
        cout<<"\nla clave esta errada\n";
        return;}
    else{
        cout<<"\nBienvenido administrador\n";
        administrador(inv,com);}
}

void administrador(map <int,producto> &inv,map <int,combo> &com){
    //esta es la interfaz que manejara el administrador
    map <int,producto>::iterator ii;
    map <int,combo>::iterator ic;
    ic=com.begin();
    cout<<"\nEste es el inventario actual\n";
    for(ii=inv.begin();ii!=inv.begin();ii++){
        if(ii->first<10)
            cout<<"| "<<ii->first;
        else
            cout<<'|'<<ii->first;
        ii->second.ver_producto();
    }
}

void guardar_inv(map <int,producto> &inv){
    //esta funcion resive el map que contiene el inventario para guardarlo en su inventario.txt
    string datos;
    map <int,producto>::iterator ii;
    for(ii=inv.begin();ii!=inv.end();ii++){
        datos= datos + int2str(ii->first) + ';' + ii->second.guardado() + '\n';
    }
    datos.pop_back();
    escribir_txt(datos,"inventario.txt");
}

void guardar_com(map <int,combo> &inv){
    //esta funcion resive el map que contiene los combos para guardarlo en su combos.txt
    string datos;
    map <int,combo>::iterator ii;
    for(ii=inv.begin();ii!=inv.end();ii++){
        datos= datos + int2str(ii->first) + ';' + ii->second.guardado() + '\n';
    }
    datos.pop_back();
    escribir_txt(datos,"combos.txt");
}























//funciones importadas de la practica 3
string desifrar(){
    //en esta funcion se utiliza para desifrar la clave del administrador, esta recompila las otras funciones para desifrar el archivo "sudo.dat" donde se guarda la clave
    string texto;
    texto=leer_Txt("sudo.dat");
    bool *cod= new bool [8*(texto.length())];
    text2bin(texto,cod);
    separacion(5,cod,8*(texto.length()),0);
    texto=bin2text(cod,8*(texto.length()));
    return texto;
}
string leer_Txt(string arch){
    //esta funcion abre el archivo dado y regresa un string con el contenido del archivo
    long long int tam;
    string salida, s2;
    char s;
    fstream k_1(arch, ios::in | ios::ate);
    tam=k_1.tellg();
    k_1.close();
    fstream k(arch.c_str(), ios::in | ios::binary);
    for(long long int i=0;i<tam;i++){
        k.get(s);
        salida.push_back(s);
    }
    k.close();
    return salida;
}
void text2bin(string texto,bool *cod){
    //esta funcion convierte un string dado a binario segunla tabla ASCII, y lo devuelve en un array binario dado
    char s;
    for(unsigned long long int i=0;i<(texto.length());i++){
        s=char(texto[i]);
        for(int j=0;j<8;j++) cod[8*i+j]=(((s<<j)&0x80)==0x80);
    }
}

string bin2text(bool *cod,unsigned long long int l){
    //esta funcion convierte el array binario de la funcion anterior en un string y lo devuelve
    string text="";
    string s;
    int sum=0,c=0;
    for(unsigned long long int i=0;i<l;i+=8){
        c=0;
        sum=0;
        for(int j=7;j>=0;j--){
            sum+=cod[i+j]*pow(2,c);
            c++;
        }
        s=sum;
        text.append(s);
    }
    return text;
}
void separacion(unsigned long long int semilla, bool *cod, unsigned long long int tam,bool dec){
    //esta funcion se encarga de separar el array de bool en la partes de la semilla y le pasa los segmentos a la funcion que los decifra
    short *seg = new short[semilla];
    long long int j=0;
    unsigned short tp=0;
    for(unsigned long long int i=0;i<semilla;i++) seg[i]=-1;
    for(unsigned long long int i=0,l=0; i<tam; i++,j++){
        seg[j]=cod[i];
        if((i+1)%semilla==0 || i==(tam-1)){
            tp=regla_1(seg,&cod[semilla*l],tp,semilla,dec);
            for(unsigned long long int k=0;k<semilla;k++) seg[k]=-1;
            l++;
            j=-1;
        }
    }
}

unsigned short regla_1(short *seg, bool *data, unsigned short regla, unsigned long long int semilla,bool dec){
    //esta funcion impleementa las reglas para decodificar
    int contador[2]={0,0};
    unsigned short reg=0;
    for(unsigned long long int i=0; i<semilla; i++){
        if(seg[i]!=-1){
            switch (regla){
                case 0: data[i]=1-seg[i];

                break;

                case 1: if(i%2!=0) data[i]=1-seg[i];

                break;

                default: if((i+1)%3==0) data[i]=1-seg[i];
            }
          if(dec) contador[seg[i]]++;
          else contador[data[i]]++;
        }
    }
    if(contador[0]>contador[1]) reg=1;
    else if(contador[0]<contador[1]) reg=2;
    return reg;
}

void escribir_txt(string texto,string arch){
    ofstream k(arch.c_str(), ios::out | ios::binary);
    k<<texto;
    k.close();
}

//importados de la practica 2

long int str2int(string a){
    //esta funcion recibe un string y lo convierte en un entero
    int b,l,d=1,c=0;
    l=a.length();
    for(int i=l-1;i>=0;i--){
        b=a[i]-48;
        c+=b*d;
        d*=10;
    }
    return c;
}

string int2str(int long a){
    //esta funcion recibe un numero entero y lo devuelve en string
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
