#include <iostream>

using namespace std;
#include <fstream>
#include <math.h>
#include <map>

class producto
{
public:
    void crear(string name,int uni_p,int uni_a,int cant,int long long cost);
    void sacar_producto(int num);
    void ver_producto();
    string guardado();
    unsigned int disponible=((unidades_p-1)*cantidad)+unidades_a;//esta variable es publica para que desde fuera se pueda saber si el combo se puede ofrecer en base a los productos del inventario
private:
    string nombre;
    int unidades_p;
    int unidades_a;
    int cantidad;
    int long long costo;
    string int2str(int long a);
};
