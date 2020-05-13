#include "producto.h"

class combo
{
public:
    long long int costo;
    void crear();
    void iniciar(string cont, long long int cost, map <int,int> ff);
    string ver_combo();
    bool disponibilidad(map <int,producto> inv);
    void comprar_com(map <int,producto> &inv);
    string guardado();
private:
    string contenido;
    map <int,int> ff; //en este map almacenare los productos que se usan en el combo, la clave sera el id del producto y el contenido las unidades de producto de necesita
    string int2str(int long long a);
};
