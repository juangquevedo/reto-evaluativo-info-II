#include <iostream>

using namespace std;
#include <fstream>
#include <math.h>

#include "combo.h"
#include "producto.h"
#include <map>

void iniciar_admi(map <int,producto> &inv,map <int,combo> &com);
void administrador(map <int,producto> &inv,map <int,combo> &com);
void guardar_inv(map <int,producto> &inv);






//importados de la practica 3
string leer_Txt(string arch);
void text2bin(string texto,bool *cod);
string bin2text(bool *cod,unsigned long long int l);
void separacion(unsigned long long int semilla, bool *cod, unsigned long long int tam,bool dec);
unsigned short regla_1(short *seg,bool *data,unsigned short regla, unsigned long long semilla,bool dec);
string desifrar();
void escribir_txt(string texto,string arch);


//importados de la practica 2
long int str2int(string a);
string int2str(int long a);
