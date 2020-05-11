#include <iostream>

using namespace std;

#include <map>

class combo
{
public:
    combo();
    void ver_combo();
private:
    string contenido;
    long long int costo;
    map <int,int> ff; //en este map almacenare los productos que se usan en el combo, la clave sera el id del producto y el contenido las unidades de producto de necesita
};
