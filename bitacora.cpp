/**
 * @file main.cpp
 * @brief Proyecto Integrador: Bitacora de Campo (Plantas)
 * @details Este programa permite registrar, filtrar y mostrar plantas utilizando POO.
 * Implementa conceptos de Herencia, Polimorfismo (Sobreescritura), Composicion y Agregacion.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;


//Clases

/**
 * @class FichaTecnica
 * @brief Clase componente para cumplir con el requisito de Composicion.
 * @details Representa la parte interna tecnica de una planta.
 */
class FichaTecnica {
public:
    FichaTecnica() {}
    ~FichaTecnica() {}
};

/**
 * @class Planta
 * @brief Clase base abstracta.
 * @details Utiliza COMPOSICION con la clase FichaTecnica (la crea y destruye).
 */
class Planta {
protected:
    string nombreComun;     /**< Nombre  de la planta */
    string climaIdeal;      /**< Clima donde se encontro la planta */
    FichaTecnica* ficha;    /**< Puntero para manejar la composicion */

public:
    /**
     * @brief Constructor de Planta.
     * @param _nombre Nombre comun.
     * @param _clima Clima ideal.
     * @note Inicializa la composicion creando una nueva FichaTecnica.
     */
    Planta(string _nombre, string _clima) : nombreComun(_nombre), climaIdeal(_clima) {
        ficha = new FichaTecnica();
    }

    /**
     * @brief Destructor virtual.
     * @details Libera la memoria de la FichaTecnica cuando borramos a la planta.
     */
    virtual ~Planta() {
        delete ficha;
    }

    /**
     * @brief Metodo virtual para mostrar informacion.
     * @param i Indice numerico para llevar el liistado.
     */
    virtual void mostrarDetalles(int i) = 0;

    /**
     * @brief Metodo virtual puro para obtener el ID del tipo.
     * @return Entero (1=Hierba, 2=Mata, 3=Arbusto, 4=Arbol).
     */
    virtual int getTipoID() = 0;

    string getNombre() { return nombreComun; }
};

//Clases hijas

/**
 * @class Hierba
 * @brief Clase derivada de planta que representa una Hierba.
 */
class Hierba : public Planta {
    bool esMedicinal;
public:
    Hierba(string n, string c, bool med) : Planta(n, c), esMedicinal(med) {}
    
    void mostrarDetalles(int i) override {
        string uso;
        if (esMedicinal == true) uso = "Medicinal";
        else uso = "Decorativa";

        cout << i << ". [HIERBA] " << nombreComun << " [Clima: " << climaIdeal << "] " << "(" << uso << ")" << endl;
    }
    int getTipoID() override { return 1; }
};

/**
 * @class Mata
 * @brief Clase derivada de planta que representa una Mata.
 */
class Mata : public Planta {
    int cantidadTallos;
public:
    Mata(string n, string c, int tallos) : Planta(n, c), cantidadTallos(tallos) {}
    
    void mostrarDetalles(int i) override {
        cout << i << ". [MATA] " << nombreComun << " [Clima: " << climaIdeal << "] " << "(Tallos: " << cantidadTallos << ")" << endl;
    }
    int getTipoID() override { return 2; }
};

/**
 * @class Arbusto
 * @brief Clase derivada de planta que representa un Arbusto.
 */
class Arbusto : public Planta {
    bool tieneEspinas;
public:
    Arbusto(string n, string c, bool esp) : Planta(n, c), tieneEspinas(esp) {}
    
    void mostrarDetalles(int i) override {
        string tacto;
        if (tieneEspinas == true) tacto = "Con Espinas";
        else tacto = "Suave";

        cout << i << ". [ARBUSTO] " << nombreComun << " [Clima: " << climaIdeal << "] " << "(" << tacto << ")" << endl;
    }
    int getTipoID() override { return 3; }
};

/**
 * @class Arbol
 * @brief Clase derivada de planta que representa un Arbol.
 */
class Arbol : public Planta {
    double altura;
public:
    Arbol(string n, string c, double h) : Planta(n, c), altura(h) {}
    
    void mostrarDetalles(int i) override {
        cout << i << ". [ARBOL] " << nombreComun << " [Clima: " << climaIdeal << "] " << "(" << altura << " m)" << endl;
    }
    int getTipoID() override { return 4; }
};

//Bitacora

/**
 * @class Bitacora
 * @brief Clase contenedora que administra la coleccion.
 * @details Implementa AGREGACION usando un vector de punteros.
 */
class Bitacora {
private:
    vector<Planta*> coleccion;

    /**
     * @brief Metodo privado para limpiar memoria interna.
     */
    void limpiarMemoriaInterna() {
        for (int i = 0; i < (int)coleccion.size(); i++) {
            delete coleccion[i];
        }
        coleccion.clear();
    }

public:
    /**
     * @brief Agrega una planta a la coleccion.
     * @param p Puntero a la planta.
     */
    void agregar(Planta* p) {
        coleccion.push_back(p);
        cout << "--- La planta se ha registrado :).\n";
    }

    /**
     * @brief Muestra las plantas filtradas por categoria.
     * @param categoria 0=Todas, 1-4=Especificas.
     */
    void mostrarFiltrado(int categoria) {
        if (coleccion.empty()) {
            cout << "\nLa bitacora esta vacia.\n";
            return;
        }
        cout << "\n=== LISTADO DE PLANTAS ===\n";
        bool hayResultados = false;
        
        for (int i = 0; i < (int)coleccion.size(); i++) {
            if (categoria == 0 || coleccion[i]->getTipoID() == categoria) {
                coleccion[i]->mostrarDetalles(i + 1);
                hayResultados = true;
            }
        }
        
        if (hayResultados == false) {
            cout << "Aun no has registrado ninguna planta aqui :)\n";
        }
        cout << "==========================\n";
    }

    ~Bitacora() { limpiarMemoriaInterna(); }
};

//Explorador

/**
 * @class Explorador
 * @brief Representa al usuario.
 * @details Interactua con la Bitacora mediante ASOCIACION.
 */
class Explorador {
public:
    /**
     * @brief Crea y registra plantas en la bitacora.
     * @param b Referencia a la Bitacora (Asociacion).
     */
    void registrar(Bitacora& b) {
        int tipo = 0;
        
        do {
            cout << "\n--- REGISTRAR PLANTA ---\n";
            cout << "1. Hierba | 2. Mata | 3. Arbusto | 4. Arbol\n";
            cout << "Selecciona: ";
            cin >> tipo;
            
            if (tipo < 1 || tipo > 4) {
                cout << ">> Opcion incorrecta\n";
            }
        } while (tipo < 1 || tipo > 4);

        string nom, clima;
        cout << "Nombre Comun: "; cin >> nom;
        cout << "Clima ideal: "; cin >> clima;

        Planta* p = nullptr;

        switch(tipo) {
            case 1: {
                int med;
                cout << "Es medicinal? (1:Si / 0:No): "; cin >> med;
                bool esMed = false;
                if (med == 1) esMed = true;
                
                p = new Hierba(nom, clima, esMed);
                break;
            }
            case 2: {
                int t;
                cout << "Numero de Tallos: "; cin >> t;
                p = new Mata(nom, clima, t);
                break;
            }
            case 3: {
                int esp;
                cout << "Tiene espinas? (1:Si / 0:No): "; cin >> esp;
                bool tieneEsp = false;
                if (esp == 1) tieneEsp = true;
                
                p = new Arbusto(nom, clima, tieneEsp);
                break;
            }
            case 4: {
                double alt;
                cout << "Altura (mts): "; cin >> alt;
                p = new Arbol(nom, clima, alt);
                break;
            }
        }

        if (p != nullptr) {
            b.agregar(p);
        }
    }
};


//Main

/**
 * @brief Funcion principal del programa.
 * @return 0 si la ejecucion fue exitosa.
 */
int main() {
    Bitacora miBitacora;
    Explorador yo;
    int opcion = 0;

    cout << "=== BITACORA DE CAMPO ===\n";

    do {
        cout << "\nMENU PRINCIPAL\n";
        cout << "1. Registrar nueva planta\n";
        cout << "2. Ver Bitacora\n";
        cout << "3. Salir\n";
        cout << "Tu seleccion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                yo.registrar(miBitacora);
                break;
            
            case 2: {
                int filtro;
                cout << "\n--- FILTROS ---\n";
                cout << "0.Todo | 1.Hierbas | 2.Matas | 3.Arbustos | 4.Arboles\n";
                cout << "Elije una opcion: ";
                cin >> filtro;
                
                if (filtro >= 0 && filtro <= 4) {
                    miBitacora.mostrarFiltrado(filtro);
                } else {
                    cout << ">> Esa categoria no existe.\n";
                }
                break;
            }

            case 3:
                cout << "Saliendooo...\n";
                break;
            
            default:
                cout << "---Opcion no valida.\n";
                break;
        }

    } while (opcion != 3);

    return 0;
}
