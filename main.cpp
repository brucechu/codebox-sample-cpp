#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

typedef struct
{
    unsigned chip;
    string tipo;
    float largo;
    float ancho;
    float alto;
    float precio;

} TAnimal;

const unsigned MAX_DIM = 100;
typedef TAnimal TLista[MAX_DIM];

typedef struct
{
    TLista animales;
    unsigned num;

} TTienda;

void pause();
void clear();
void Vaciar(TTienda &tienda);
void MostrarAnimal(TAnimal animal);
void Mostrar(TTienda &tienda);
void LeerAnimal(TAnimal &animal);
int Buscar(TTienda &tienda, unsigned chip);
bool Entrada(TTienda &tienda, TAnimal animal);
void Elimina(TTienda &tienda, int posicion);
bool Vender(TTienda &tienda, unsigned chip);
int BuscarPeq(TTienda &tienda);
bool VenderPeq(TTienda &tienda);

int Menu();

int main()
{

    int opcion;
    bool seguir, insertado, vendido;
    TTienda tienda;
    TAnimal animal;
    unsigned chip;

    // La tienda empieza vacia
    Vaciar(tienda);

    seguir = true;
    do
    {
        opcion = Menu();

        switch (opcion)
        {
        case 1:
            LeerAnimal(animal);
            cout << endl << "Animal leido: ";
            MostrarAnimal(animal);
            insertado = Entrada(tienda, animal);
            if(insertado)
            {
                cout << "El animal ha sido insertado correctamente.";
            }
            else
            {
                cout << "Ya existe un animal con ese chip o se alcanzo el limite de la tienda.";
            }

            break;

        case 2:
            Mostrar(tienda);
            break;
        case 3:
            Vaciar(tienda);
            cout << "La tienda se ha vaciado correctamente.";
            break;

        case 4:
            cout << "Introduzca el numero de chip: ";
            cin >> chip;

            vendido = Vender(tienda, chip);
            if(vendido)
            {
                cout << "El animal ha sido vendido correctamente.";
            }
            else
            {
                cout << "No se ha encontrado el animal en la tienda.";
            }

            break;

        case 5:
            vendido = VenderPeq(tienda);
            if(vendido)
            {
                cout << "El animal ha sido vendido correctamente.";
            }
            else
            {
                cout << "No hay animales en la tienda.";
            }


            break;

        case 0:
            cout << endl << endl<<"Saliendo de la aplicación.";
            seguir = false;
            break;
        default:
            cout << endl << endl<<"Opcion invalida.";

        }

        cout << endl << endl;
        pause();
    }
    while (seguir);

    return 0;
}

void pause(){
    // UNIX
    cout << "Press [Enter] to continue ..."; 
    cin.ignore(); // ignores the newline
    cin.get(); //waits for character
    
    // WINDOWS
    //system("PAUSE");
}

void clear(){
    // UNIX
    system("clear");
    
    // WINDOWS
    //system("CLS");
}

int Menu()
{
    int op;

    system("clear");
    cout<<endl<<endl;


    cout<<"\t 1. Insertar animal."<<endl;
    cout<<"\t 2. Mostrar tienda."<<endl;
    cout<<"\t 3. Vaciar tienda."<<endl;
    cout<<"\t 4. Vender animal."<<endl;
    cout<<"\t 5. Vender animal mas pequeno."<<endl;

    cout<<"\t 0. Salir"<<endl<<endl;
    cout<<"Elige una opcion: ";

    cin>>op;
    cout << endl;

    return op;
}

void Vaciar(TTienda &tienda)
{
    tienda.num = 0;
}

void MostrarAnimal(TAnimal animal)
{
    cout << "chip=" << animal.chip << ", ";
    cout << "tipo='" << animal.tipo << "', ";
    cout << "medidas=" << animal.largo << "x" << animal.ancho << "x" << animal.ancho << ", ";
    cout << "precio=" << animal.precio << endl;
}

void Mostrar(TTienda &tienda)
{
    TAnimal animal;
    int i;

    cout << "Tienda: " << tienda.num << " animales" << endl;

    for(i=0; i<tienda.num; i++)
    {
        animal = tienda.animales[i];
        cout << "\t - Animal[" << i << "]: ";
        MostrarAnimal(animal);
    }
}

void LeerAnimal(TAnimal &animal)
{
    cout << "Introduzca datos del animal: " << endl;
    cout <<"\t chip: ";
    cin >> animal.chip;
    cout << "\t tipo: ";
    cin >> animal.tipo;
    cout << "\t largo: ";
    cin >> animal.largo;
    cout << "\t ancho: ";
    cin >> animal.ancho;
    cout << "\t alto: ";
    cin >> animal.alto;
    cout << "\t precio: ";
    cin >> animal.precio;
}

int Buscar(TTienda &tienda, unsigned chip)
{
    int i, posicion;
    TAnimal animal;

    // El programa busca la posicion del animal con el mismo chip
    // Si no lo encuentra devuelve -1
    i = 0;
    posicion = -1;

    while((posicion == -1) && (i<tienda.num))
    {
        animal = tienda.animales[i];

        if(animal.chip == chip)
        {
            posicion = i;
        }

        i++;
    }

    return posicion;
}

bool Entrada(TTienda &tienda, TAnimal animal)
{
    bool insertado;
    int posicion;

    posicion = Buscar(tienda, animal.chip);

    if((posicion < 0) && (tienda.num < MAX_DIM))
    {
        tienda.animales[tienda.num] = animal;
        tienda.num++;

        insertado = true;
    }
    else
    {
        insertado = false;
    }

    return insertado;
}

void Elimina(TTienda &tienda, int posicion)
{
    TAnimal animal;

    if((posicion >= 0) && (posicion == (tienda.num -1)))
    {
        // Se trata de eliminar el ultimo
        tienda.num--;
    }
    else if ((posicion >= 0) && (posicion < (tienda.num -1)))
    {
        // Movemos el ultimo animal a la posicion del eliminado
        animal = tienda.animales[tienda.num -1];
        tienda.animales[posicion] = animal;
        tienda.num--;
    }
}

bool Vender(TTienda &tienda, unsigned chip)
{
    int posicion;
    bool vendido;

    posicion = Buscar(tienda, chip);

    if(posicion >= 0){
        Elimina(tienda, posicion);
        vendido = true;
    }else{
        vendido = false;
    }

    return vendido;
}

int BuscarPeq(TTienda &tienda){
    int i, posicion;
    TAnimal animal;
    float menorVolumen, volumen;

    // Busca el animal con menor volumen y devuelve su posicion
    // Si no lo encuentra devuelve la posicion -1

    if(tienda.num > 0){
        posicion = 0;
        animal = tienda.animales[0];
        menorVolumen = animal.alto * animal.ancho * animal.largo;

        for(i = 1; i < tienda.num; i++){
            animal = tienda.animales[i];
            volumen = animal.alto * animal.ancho * animal.largo;

            if(volumen < menorVolumen){
                posicion = i;
                menorVolumen = volumen;
            }
        }
    }else{
        posicion = -1;
    }

    return posicion;
}

bool VenderPeq(TTienda &tienda){
    int posicion;
    bool vendido;

    posicion = BuscarPeq(tienda);

    if(posicion >= 0){
        Elimina(tienda, posicion);
        vendido = true;
    }else{
        vendido = false;
    }

    return vendido;
}



