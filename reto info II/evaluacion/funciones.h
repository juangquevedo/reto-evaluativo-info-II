#include "combo.h"

//al lado de cada funcion se encuntra la linea dese la que comienza

void iniciar_admi(map <int,producto> &inv,map <int,combo> &com); //3
void administrador(map <int,producto> &inv,map <int,combo> &com); //18
void ingresar_usu(map <int,producto> &inv,map <int,combo> &com); //81
void usuario(map <int,producto> &inv,map <int,combo> &com,string usuario); //111
void registrar_usu(); //167
void agregar_pro(map <int,producto> &inv); //183
void crear_combo(map <int,combo> &com,map <int,producto> &inv); //205
void mostrar_inv(map <int,producto> &inv); //222
void mostrar_com(map <int,combo> &com,map <int,producto> &inv); //240
void iniciar_inv(map <int,producto> &inv); //260
void iniciar_com(map <int,combo> &com); //297
void cargar_usuarios(map <string,string> &usu); //341
void guardar_inv(map <int,producto> &inv); //362
void guardar_com(map <int,combo> &inv); //373
void guardar_reporte(string hist); //384





//importados de la practica 3 //400
string leer_Txt(string arch);
void text2bin(string texto,bool *cod);
string bin2text(bool *cod,unsigned long long int l);
void separacion(unsigned long long int semilla, bool *cod, unsigned long long int tam,bool dec);
unsigned short regla_1(short *seg,bool *data,unsigned short regla, unsigned long long semilla,bool dec);
string desifrar();
void escribir_txt(string texto,string arch);


//importados de la practica 2 //507
void devolver(int long long a);
long int str2int(string a);
template <typename t>
string int2str(t a);
