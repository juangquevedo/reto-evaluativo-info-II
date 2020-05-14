#include "funciones.h"

void iniciar_admi(map <int,producto> &inv,map <int,combo> &com){
    //esta funcion pide la clave y la compara con la codificada en sudo.dat
    //recibe como parametros los map que contiene el inventario y  los  combos para pasarselos a la funcion administrador
    string clave;
    cout<<"\nIngrese la clave de administrador: ";
    cin>>clave;
    if(clave!=desifrar()){
        cout<<"\nla clave esta errada\n";
        return;}
    else{
        cout<<"\nBienvenido administrador\n";
        system("pause");
        administrador(inv,com);}
}

void administrador(map <int,producto> &inv,map <int,combo> &com){
/*esta es la interfaz que manejara el administrador en la que se pueden modificar el inventario
que le permite añadir productos al inventario, crear combos y ver el reporte de venta
recibe como parametros los map que contiene el inventario y  los  combos para modificarlos*/
    short op;
    int el,temp;
    cout<<"\nEste es el inventario actual\n";
    mostrar_inv(inv);
    while(true){
        cout<<"\nQue desea hacer?\n1)Ingresar un nuevo producto\n2)Abastecer un producto\n3)Quitar un producto\n";
        cout<<"4)Mostrar inventario\n5)Crear un nuevo combo\n6)Quitar un combo\n7)Mostrar combos\n";
        cout<<"8)Ver un el reporte de ventas\n0)Salir\n(digite el numero de la opcion a realizar) ";
        cin>>op;
        switch(op){
        case 1:
            agregar_pro(inv);
            break;
        case 2:
            cout<<"\nEscriba el ID del producto a abastecer: ";
            cin>>el;
            if(inv.find(el)==inv.end())
                cout<<"\nEl ID dado no esta en el inventario\n";
            else{
                cout<<"\nIngrese la cantidad que llego del producto: ";
                cin>>temp;
                inv[el].anadir_cant(temp);}
            break;
        case 3:
            cout<<"\nIngrese el ID del producto a eliminar: ";
            cin>>el;
            if(inv.find(el)==inv.end())
                cout<<"\nEl ID dado no esta en el inventario\n";
            else inv.erase(el);
            break;
        case 4:
            mostrar_inv(inv);
            break;
        case 5:
            crear_combo(com,inv);
            break;
        case 6:
            cout<<"\nIngrese el numero del combo a eliminar: ";
            cin>>el;
            if(com.find(el)==com.end())
                cout<<"\nEl numero dado no esta dentro de los combos actuales\n";
            else com.erase(el);
            break;
        case 7:
            mostrar_com(com,inv);
            break;
        case 8:
            cout<<leer_Txt("reporte.txt");
            break;
        case 0:
            return;
        default:
            cout<<"\nLa opcion digitada es invalida intente otra vez\n";
            break;
        }
        system("pause");
    }
}

void ingresar_usu(map <int,producto> &inv,map <int,combo> com){
/*esta es la funcion que se encarga de pedir la cedula y la clave del usuario,
creando un map donde almacena la cedula y clave de cada usuario que este en "usuarios.txt"
para poder pedir la comida, recibe como parametros los maps que contienen el inventario y
los combos y cuando se comprueba los datos del usuario pasa a la funcion "usuario", si despues
de 3 intentos no se comprueba se devuelve al menu principal*/
    string user,clave;
    map <string,string> users;//en este map se almacenaran la cedula y contraseña de cada usuario
    map <string,string>::iterator it;
    cargar_usuarios(users);
    for(int i=1;i<=3;i++){
        cout<<"\nIngrese su numero de cedula: ";
        cin>>user;
        if(users.find(user)==users.end())
            cout<<"\nEl numero de cedula ingresada no se encuentra registada intento "<<i<<" de 3\n";
        else{
            for(int j=1;j<=3;j++){
                cout<<"\nIngrese su clave: ";
                cin>>clave;
                if(clave==users[user]){
                    j=4;
                    i=4;
                    usuario(inv,com,user);}
                else
                    cout<<"\nLa clave ingresada no coincide intento "<<i<<" de 3\n";
            }
        }
    }
}

void usuario(map <int,producto> &inv,map <int,combo> com,string usuario){
/*esta es la funcion que le permite al usuario comprar combos
y registra cada compra en el archivo reporte.txt*/
    int temp;
    unsigned long long int precio=0,pago;
    bool ban=1;
    list <int> pedido;
    list <int>::iterator lit;
    string history,silla [2];
    while (ban){
        cout<<"\nEstos son los combos que ofrecemos\n";
        mostrar_com(com,inv);
        cout<<"\nDigite el numero del combo que desea ordenar: ";
        cin>>temp;
        if(temp<1 || temp>signed(com.size()))
            cout<<"\nEl combo elegido no esta en las opciones\n";
        else if(!com[temp].disponibilidad(inv))
            cout<<"\nPor el momento este combo no se encuentra disponible\n";
        else{
            pedido.push_back(temp);
            cout<<"\nDesea ordenar algo mas? (1 si, 0 no): ";
            cin>>ban;}
    }
    pedido.sort(); //no es necesario pero prefiero ponerlo
    for(lit=pedido.begin();lit!=pedido.end();lit++)
        precio+=com[*lit].costo;
    cout<<"\nEl precio total seria "<<precio<<'\n';
    ban=1;
    while(ban){
        cout<<"\nIngrese la cantidad con la que pagara: ";
        cin>>pago;
        if(pago<precio) cout<<"la cantidad ingresada es menor a la cantidad a pagar, ingrese un monto mayor\n";
        else ban=0;
    }
    if(pago==precio)
        cout<<"\nLa cantidad dada es exacta\n";
    else
        devolver(pago-precio);
    for(lit=pedido.begin();lit!=pedido.end();lit++){
        com[*lit].comprar_com(inv);
        history= history + com[*lit].ver_combo() + '\n';
    }
    ban=0;
    while(!ban){
        cout<<"\nCuando su pedido este listo le llevaremos el pedido a su asiento\nIngrese la sala en la que ver la pelicula: ";
        cin>>silla[0];
        cout<<"\nIngrese su asiento: ";
        cin>>silla[1];
        cout<<"\nSeguro que quiere que el pedido se lleve al asiento "<<silla[1]<<" en la sala "<<silla[0]<<"\n(si 1, no 0) ";
        cin>>ban;
    }
    history= history + "la compra fue realizada por el usuario: " + usuario + "\nEl monto pagado fue de " + int2str(precio) + "\nEl pedido fue entrgado en la sala: " + silla[0] + " asiento: " +silla[1];
    guardar_reporte(history);
    cout<<"\nGracias por su compra\n";
}

void registrar_usu(){
/*esta funcion se encarga de registrar a los nuevos usuarios en el txt "usuarios"*/
    map <string,string> users;
    cargar_usuarios(users);
    string clave,usuario,datos=leer_Txt("usuarios.txt");
    usuario=(users.begin())->first;
    while(users.find(usuario)!=users.end()){
        cout<<"\nIngrese el numero de su cedula: ";
        cin>>usuario;
        if(users.find(usuario)!=users.end())cout<<"\nLa cedula ingresada ya esta en el sistema\n";}
    cout<<"\nIngrese la clave de su nuevo usuario: ";
    cin>>clave;
    datos=datos + '\n' + usuario + ';' + clave;
    escribir_txt(datos,"usuarios.txt");
}

void agregar_pro(map <int,producto> &inv){
//esta funcion recibe el map que contiene el inventario para añadir un producto
    int unid[2],id=(inv.begin())->first;
    producto a;
    string nombre;
    long long int costo;
    while(inv.find(id)!=inv.end()){
        cout<<"Cual es el ID del producto (Evite ingresar ID previamente existentes): ";
        cin>>id;
        if(inv.find(id)!=inv.end()) cout<<"\nEl ID ingresado ya existe\n";}
    cout<<"Cual es el nombre del producto (porfavor remplace los espacios por '_'): ";
    cin>>nombre;
    cout<<"Cuantas unidades trae cada producto: ";
    cin>>unid[0];
    cout<<"Cual es la cantidad de producto: ";
    cin>>unid[1];
    cout<<"Cual es el costo total de todo el producto: ";
    cin>>costo;
    a.crear(nombre,unid[0],unid[0],unid[1],costo);
    inv.insert(pair<int,producto>(id,a));
}

void crear_combo(map <int,combo> &com,map <int,producto> inv){
/*esta funcion recibe como parametro el map de combos y el map con el inventario,
para crear un combo con base al inventario actual*/
    cout<<"\nEstos son los combos actuales\n";
    mostrar_com(com,inv);
    int num=(com.begin())->first;
    while(com.find(num)!=com.end()){
        cout<<"Cual es el numero del combo: ";
        cin>>num;
        if(com.find(num)!=com.end()) cout<<"\nEl numero ingresado ya existe\n";}
    combo b;
    cout<<"\nEste es el inventario actual para en base a este pueda crear el combo\n";
    mostrar_inv(inv);
    b.crear(inv);
    com.insert(pair<int,combo>(num,b));
}

void mostrar_inv(map <int,producto> inv){
//esta funcion recibe el map que contien el inventario para imprimir el inventario en una tabla
    map <int,producto>::iterator ii;
    cout<<"|ID|                     producto                |cantidad|costo |\n";
    for(int i=0;i<65;i++) cout<<'-';
    cout<<endl;
    for(ii=inv.begin();ii!=inv.end();ii++){
        if(ii->first<10)
            cout<<"| "<<ii->first;
        else
            cout<<'|'<<ii->first;
        ii->second.ver_producto();
        cout<<endl;
        for(int i=0;i<65;i++) cout<<'-';
        cout<<endl;
    }
}

void mostrar_com(map <int,combo> com,map <int,producto> inv){
/*esta funcion recibe el map que contiene a los combos y los imprime en una tabla y
imprime a su lado si esta disponible o no basandose en el inventario, ayudandose de
la funcion propia de la clase combos "ver_combo"*/
    map <int,combo>::iterator ic;
    for(int i=0;i<62;i++) cout<<'-';
    cout<<endl;
    for(ic=com.begin();ic!=com.end();ic++){
        if(ic->first<10)
            cout<<"| "<<ic->first;
        else
            cout<<'|'<<ic->first;
        cout<<ic->second.ver_combo();
        if(!(ic->second.disponibilidad(inv))) cout<<"producto no disponible por el momento";
        cout<<endl;
        for(int i=0;i<62;i++) cout<<'-';
        cout<<endl;
    }
}

void iniciar_inv(map <int,producto> &inv){
/*esta funcion se encarga de extraer los datos del inventario del archivo "inventario.txt",
y los introduce en el map que se le pasa por referencia*/
    string temp="",name,datos=leer_Txt("inventario.txt");
    int id,j;
    int long long temp_int[4];
    producto a;
    for(unsigned long int i=0;i<datos.length();i++){
        j=0;
        while(i<datos.length()){
            if(datos[i]==';' || datos[i]=='\n' || i+1==datos.length()){
                if(i+1==datos.length()) temp.push_back(datos[i]);
                if(j==0){
                    inv.insert(pair<int,producto>(str2int(temp),a));
                    id=str2int(temp);}
                else if(j==1)
                    name=temp;
                else if(j==2)
                    temp_int[0]=str2int(temp);
                else if(j==3)
                    temp_int[1]=str2int(temp);
                else if(j==4)
                    temp_int[2]=str2int(temp);
                else if(j==5)
                    temp_int[3]=str2int(temp);
                temp="";
                if(datos[i]=='\n') break;
                j++;
            }
            else
                temp.push_back(datos[i]);
            i++;
        }
        inv[id].crear(name,temp_int[0],temp_int[1],temp_int[2],temp_int[3]);
    }
}

void iniciar_com(map <int,combo> &com){
/*esta funcion extrae la informacion de los combos del archivo "combos.txt"
y se la devuelven al programa en el map que se le da por referencia*/
    map <int,int> ff;
    map <int,int>::iterator it;
    string temp="",name,datos=leer_Txt("combos.txt");
    combo a;
    int j,num,cont[2];
    long long int costo;
    for(unsigned long int i=0;i<datos.length();i++){
        j=0;
        while(i<datos.length()){
            if(datos[i]==';' || datos[i]=='\n' || i+1==datos.length()){
                if(i+1==datos.length()) temp.push_back(datos[i]);
                if(j==0){
                    com.insert(pair<int,combo>(str2int(temp),a));
                    num=str2int(temp);}
                else if(j==1)
                    name=temp;
                else if(j==2)
                    costo=str2int(temp);
                else{
                    cont[1]=str2int(temp);
                    ff.insert(pair<int,int>(cont[0],cont[1]));
                }
                temp="";
                if(datos[i]=='\n') break;
                j++;
            }
            else if (datos[i]=='-'){
                cont[0]=str2int(temp);
                temp="";
            }
            else
                temp.push_back(datos[i]);
            i++;
        }
        com[num].iniciar(name,costo,ff);
        while(ff.size()!=0){
            it=ff.begin();
            ff.erase(it->first);}
    }
}

void cargar_usuarios(map <string,string> &usu){
/*esta funcion extrae los usuarios y claves del archivo "usuarios.txt"
para devolver se lo al sistema en un map por referencia*/
    map <string,string>::iterator is;
    string tempc,temp="",datos=leer_Txt("usuarios.txt");
    for(unsigned int i=0;i<datos.length();i++){
        if(datos[i]==';'){
            tempc=temp;
            temp="";}
        else if(datos[i]=='\n' || i+1==datos.length()){
            if(i+1==datos.length()) temp.push_back(datos[i]);
            if(temp[temp.length()-1]=='\r')
                temp.pop_back();
            usu.insert(pair<string,string>(tempc,temp));
            temp="";
        }
        else
            temp.push_back(datos[i]);
    }
}

void guardar_inv(map <int,producto> &inv){
    //esta funcion resive el map que contiene el inventario para guardarlo en su archivo "inventario.txt"
    string datos;
    map <int,producto>::iterator ii;
    for(ii=inv.begin();ii!=inv.end();ii++){
        datos= datos + int2str(ii->first) + ';' + ii->second.guardado() + '\n';
    }
    datos.pop_back();
    escribir_txt(datos,"inventario.txt");
}

void guardar_com(map <int,combo> &inv){
    //esta funcion resive el map que contiene los combos para guardarlo en su archivo "combos.txt"
    string datos;
    map <int,combo>::iterator ii;
    for(ii=inv.begin();ii!=inv.end();ii++){
        datos= datos + int2str(ii->first) + ';' + ii->second.guardado() + '\n';
    }
    datos.pop_back();
    escribir_txt(datos,"combos.txt");
}

void guardar_reporte(string hist){
/*esta funcion recibe como parametro un string que contiene el pedido realizado por el usuario
y lo incluye con fecha y hora actual al archivo "reporte.txt" que contiene los reportes de todas las compras*/
    string fecha,datos=leer_Txt("reporte.txt");
    time_t now= time(0);
    tm *time= localtime(&now);
    fecha=int2str(time->tm_mday)+ "/" + int2str(time->tm_mon+1) + '/' + int2str(1900+time->tm_year);
    fecha=fecha + "   " + int2str(time->tm_hour) + ':' + int2str(time->tm_min) + ':' + int2str(time->tm_sec) + '\n';
    fecha=datos + fecha + hist + "\n\n";
    escribir_txt((fecha),"reporte.txt");
}





//funciones importadas de la practica 3
string desifrar(){
/*en esta funcion se utiliza para desifrar la clave del administrador,
esta recompila las otras funciones de la practica 3 para desifrar el
archivo "sudo.dat" donde se guarda la clave, la cual esta cifrada con
el metodo 1 y semilla 5 de la practica 3*/
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
//esta funcion escribe en el archivo "arch" el texto "texto"
    ofstream k(arch.c_str(), ios::out | ios::binary);
    k<<texto;
    k.close();
}

//importados de la practica 2

void devolver(int long long a){
//esta funcion se encarga de mostrar al usuario la cantidad que se le devuelve
    int long long c;
    int long long b[10]={50000,20000,10000,5000,2000,1000,500,200,100,50};
    cout<<"\nDevolucion\n";
    for(int long long i=0;i<10;i++){
        c=a/b[i];
        a%=b[i];
        cout<<b[i]<<": "<<c<<endl;
    }
    cout<<"Faltante: "<<a<<endl;
}

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

template <typename t>
string int2str(t a){
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
