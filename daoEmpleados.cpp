#include <iostream>
#include <cstring>
#include "variables.h"
#include <locale.h>
#include <fstream>
#include <cstdlib>

using namespace std;

EMPLEADO empleados[MAX_EMP];
int emp_pos = 0;

void agregarEmpleado(EMPLEADO *e);
void aumentarSalario();
void mostrarSalarioMayor20k();
void pedirDatosEmpleado();
void mostrarDatosEmpleado(EMPLEADO &e);
void cargarEmpleados();
void guardarEmpleado(const EMPLEADO &e);

int menu();
void principal();

int main() {
    principal();
    return 0;
}

void agregarEmpleado(EMPLEADO *e) {
    empleados[emp_pos] = *e;
    emp_pos++;
}

void aumentarSalario() {
    for (int i = 0; i < emp_pos; i++) {
        if (empleados[i].salario_base > 10000) {
            empleados[i].salario_base *= 1.05;
        } else {
            empleados[i].salario_base *= 1.10;
        }
    }
    cout << "Salarios actualizados.\n";
}

void mostrarSalarioMayor20k() {
    for (int i = 0; i < emp_pos; i++) {
        if (empleados[i].salario_base > 20000) {
            mostrarDatosEmpleado(empleados[i]);
        }
    }
}

void pedirDatosEmpleado() {
    EMPLEADO emp;
    cout << "Datos del Empleado\n";
    cout << "Cédula: ";
    cin >> emp.cedula;
    cout << "Nombres: ";
    cin.ignore();
    cin.getline(emp.nombres, 50);
    cout << "Apellidos: ";
    cin.getline(emp.apellidos, 50);
    cout << "Cargo: ";
    cin.getline(emp.cargo, 50);
    cout << "Salario Base: ";
    cin >> emp.salario_base;
    agregarEmpleado(&emp);
    guardarEmpleado(emp);
    cout << "Empleado agregado.\n";
}

void mostrarDatosEmpleado(EMPLEADO &e) {
    cout << "==============================\n";
    cout << "Cédula: " << e.cedula << endl;
    cout << "Nombres: " << e.nombres << endl;
    cout << "Apellidos: " << e.apellidos << endl;
    cout << "Cargo: " << e.cargo << endl;
    cout << "Salario Base: " << e.salario_base << endl;
    cout << "==============================\n";
}

void cargarEmpleados() {
    ifstream archivo("empleados.txt");
    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }
    
    while (!archivo.eof() && emp_pos < MAX_EMP) {
        archivo.getline(empleados[emp_pos].cedula, 20);
        archivo.getline(empleados[emp_pos].nombres, 50);
        archivo.getline(empleados[emp_pos].apellidos, 50);
        archivo.getline(empleados[emp_pos].cargo, 50);
        archivo >> empleados[emp_pos].salario_base;
        archivo.ignore();
        emp_pos++;
    }
    archivo.close();
}

void guardarEmpleado(const EMPLEADO &e) {
    ofstream archivo("empleados.txt", ios::app);
    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    archivo << e.cedula << endl;
    archivo << e.nombres << endl;
    archivo << e.apellidos << endl;
    archivo << e.cargo << endl;
    archivo << e.salario_base << endl;
    archivo.close();
}

int menu() {
    setlocale(LC_ALL, "spanish");
    int op;
    cout << "Menu \n";
    cout << "1. Agregar Empleado\n";
    cout << "2. Aumentar Salario\n";
    cout << "3. Mostrar Empleados con Salario > 20000\n";
    cout << "4. Salir\n";
    cout << "Digite la opción: ";
    cin >> op;
    return op;
}

void principal() {
    cargarEmpleados();
    int op;
    do {
        op = menu();
        switch (op) {
        case 1:
            pedirDatosEmpleado();
            break;
        case 2:
            aumentarSalario();
            break;
        case 3:
            mostrarSalarioMayor20k();
            break;
        case 4:
            cout << "Adiós\n";
            break;
        default:
            cout << "Opción no válida\n";
            break;
        }
    } while (op != 4);
}
