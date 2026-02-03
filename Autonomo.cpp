#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <iomanip>
#include <limits> 

using namespace std;

vector<int> pasos;
vector<int> minutos;
vector<double> calorias;

void menu();
void ingresarDatos();
void insertarRegistro();
void modificarRegistro();
void buscarRegistro();
void ordenarRegistros();
void eliminarRegistro();
void analisisEstadistico();
void mostrarDatos();
int validarEntero(string mensaje, int min, int max);
double validarDouble(string mensaje, double min, double max);
double calcularMediana(vector<double> datos);
double calcularModa(vector<double> datos);

//FUNCION 
int main() {
    menu();
    return 0;
}

void menu() {
    int opcion;
    do {
        cout << "\n   SISTEMA DE SEGUIMIENTO FISICO";
        cout << "\n1. Ingresar datos";
        cout << "\n2. Insertar registro en posicion especifica";
        cout << "\n3. Modificar registro";
        cout << "\n4. Buscar registro";
        cout << "\n5. Ordenar registros";
        cout << "\n6. Eliminar registro";
        cout << "\n7. Analisis Estadistico y Reporte";
        cout << "\n8. Mostrar todos los datos";
        cout << "\n0. Salir";
        opcion = validarEntero("\nSeleccione una opcion: ", 0, 8);

        switch (opcion) {
            case 1: ingresarDatos(); break;
            case 2: insertarRegistro(); break;
            case 3: modificarRegistro(); break;
            case 4: buscarRegistro(); break;
            case 5: ordenarRegistros(); break;
            case 6: eliminarRegistro(); break;
            case 7: analisisEstadistico(); break;
            case 8: mostrarDatos(); break;
        }
    } while (opcion != 0);
}

void ingresarDatos() {
    int n = validarEntero("Cuantos dias desea registrar?: ", 1, 365);
    for (int i = 0; i < n; i++) {
        cout << "\n Dia " << i + 1 << " ";
        pasos.push_back(validarEntero("Pasos: ", 0, 100000));
        minutos.push_back(validarEntero("Minutos de actividad: ", 0, 1440));
        calorias.push_back(validarDouble("Calorias quemadas: ", 0, 10000));
    }
}

void insertarRegistro() {
    int pos = validarEntero("En que posicion (indice) insertar?: ", 0, pasos.size());
    int p = validarEntero("Nuevos Pasos: ", 0, 100000);
    int m = validarEntero("Nuevos Minutos: ", 0, 1440);
    double c = validarDouble("Nuevas Calorias: ", 0, 10000);

    pasos.insert(pasos.begin() + pos, p);
    minutos.insert(minutos.begin() + pos, m);
    calorias.insert(calorias.begin() + pos, c);
    cout << "Registro insertado con exito.\n";
}

void modificarRegistro() {
    if (pasos.empty()) { cout << "No hay datos.\n"; return; }
    int pos = validarEntero("Indice a modificar: ", 0, pasos.size() - 1);
    
    pasos[pos] = validarEntero("Nuevos Pasos: ", 0, 100000);
    minutos[pos] = validarEntero("Nuevos Minutos: ", 0, 1440);
    calorias[pos] = validarDouble("Nuevas Calorias: ", 0, 10000);
}

void buscarRegistro() {
    if (pasos.empty()) return;
    int buscar = validarEntero("Ingrese valor de PASOS a buscar: ", 0, 100000);
    bool encontrado = false;

    for (size_t i = 0; i < pasos.size(); i++) {
        if (pasos[i] == buscar) {
            cout << "\n[Encontrado] Indice: " << i 
                 << " | Pasos: " << pasos[i] 
                 << " | Min: " << minutos[i] 
                 << " | Cal: " << calorias[i];
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontro el valor.\n";
}

void ordenarRegistros() {
    if (pasos.size() < 2) return;
    cout << "1. Ascendente\n2. Descendente\n";
    int modo = validarEntero("Seleccione orden: ", 1, 2);

    for (size_t i = 0; i < pasos.size() - 1; i++) {
        for (size_t j = 0; j < pasos.size() - i - 1; j++) {
            bool condicion = (modo == 1) ? (pasos[j] > pasos[j+1]) : (pasos[j] < pasos[j+1]);
            if (condicion) {
                swap(pasos[j], pasos[j+1]);
                swap(minutos[j], minutos[j+1]);
                swap(calorias[j], calorias[j+1]);
            }
        }
    }
    cout << "Datos ordenados por columna 'Pasos'.\n";
}

void eliminarRegistro() {
    if (pasos.empty()) return;
    int pos = validarEntero("Indice a eliminar: ", 0, pasos.size() - 1);
    
    pasos.erase(pasos.begin() + pos);
    minutos.erase(minutos.begin() + pos);
    calorias.erase(calorias.begin() + pos);
    cout << "Registro eliminado.\n";
}

void analisisEstadistico() {
    if (pasos.empty()) return;
    
    auto procesar = [](string nombre, vector<double> v) {
        double suma = accumulate(v.begin(), v.end(), 0.0);
        double media = suma / v.size();
        
        cout << "\n Analisis: " << nombre << " ";
        cout << "\nMedia: " << fixed << setprecision(2) << media;
        cout << "\nMediana: " << calcularMediana(v);
        cout << "\nModa: " << calcularModa(v);
        
        int superanMedia = 0;
        for(double val : v) if(val > media) superanMedia++;
        cout << "\nDias que superan el promedio: " << superanMedia << "\n";
    };

    vector<double> vP(pasos.begin(), pasos.end());
    vector<double> vM(minutos.begin(), minutos.end());
    
    procesar("PASOS", vP);
    procesar("MINUTOS", vM);
    procesar("CALORIAS", calorias);
}

void mostrarDatos() {
    cout << "\nID\tPasos\tMinutos\tCalorías\n";
    for (size_t i = 0; i < pasos.size(); i++) {
        cout << i << "\t" << pasos[i] << "\t" << minutos[i] << "\t" << calorias[i] << endl;
    }
}

double calcularMediana(vector<double> v) {
    sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 0) return (v[n/2 - 1] + v[n/2]) / 2;
    return v[n/2];
}

double calcularModa(vector<double> v) {
    map<double, int> counts;
    for (double x : v) counts[x]++;
    int maxCount = 0;
    double moda = v[0];
    for (auto const& [val, count] : counts) {
        if (count > maxCount) {
            maxCount = count;
            moda = val;
        }
    }
    return (maxCount > 1) ? moda : -1;
}

int validarEntero(string mensaje, int min, int max) {
    int n;
    while (true) {
        cout << mensaje;
        if (cin >> n) {
            if (n >= min && n <= max) {
                return n;
            }
        }
        cout << "Error: Ingrese un numero entero entre " << min << " y " << max << ".\n";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double validarDouble(string mensaje, double min, double max) {
    double n;
    while (true) {
        cout << mensaje;
        if (cin >> n) {
            if (n >= min && n <= max) {
                return n;
            }
        }
        cout << "Error: Valor fuera de rango o entrada no valida.\n";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}