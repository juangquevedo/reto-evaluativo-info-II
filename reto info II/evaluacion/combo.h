#include "producto.h"

class combo
{
public:
    void crear();
    void iniciar(string cont, long long int cost, map <int,int> ff);
    void ver_combo();
    string guardado();
private:
    string contenido;
    long long int costo;
    map <int,int> ff; //en este map almacenare los productos que se usan en el combo, la clave sera el id del producto y el contenido las unidades de producto de necesita
    string int2str(int long long a);
};
