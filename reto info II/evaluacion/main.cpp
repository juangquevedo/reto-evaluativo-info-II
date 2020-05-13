#include "funciones.h"

int main(){
    map <int,producto> inv;
    map <int,combo> com;
    iniciar_inv(inv);
    iniciar_com(com);
    iniciar_admi(inv,com);
    guardar_com(com);
    guardar_inv(inv);
    return 0;
}
