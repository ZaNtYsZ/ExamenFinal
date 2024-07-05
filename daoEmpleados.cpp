#include <iostream>
#include <cstring>
#include <locale.h>
#include <fstream>
#include <cstdlib>
#include "variables.h"

using namespace std;

EMPLEADO empleados[MAX_EMP];
int emp_pos = 0;

void agregarEmpleado(EMPLEADO *e);
void aumentarSalario5();
void aumentarSalario10();
void mostrarSalarioMayor20k();
void pedirDatosEmpleado();
void mostrarDatosEmpleado(const EMPLEADO &e);
void cargarEmpleados();
void guardarEmpleado(const EMPLEADO &e);

int menu();
void principal();
bool validarCedula(const char *cedula);
bool validarSalario(double salario);

int main() {
    principal();
    return 0;
}

void agregarEmpleado(EMPLEADO *e) {
    if (emp_pos < MAX_EMP) {
        empleados[emp_pos] = *e;
        emp_pos++;
    } else {
        cout << "No se pueden agregar más empleados. Capacidad maxima alcanzada.\n";
    }
}

void aumentarSalario5() {
    for (int i = 0; i < emp_pos; i++) {
        if (empleados[i].salario_base > 10000) {
            empleados[i].salario_base *= 1.05;
        }
    }
    cout << "\nSalarios de empleados con salario mayor a 10,000 actualizados.\n";
}

void aumentarSalario10() {
    for (int i = 0; i < emp_pos; i++) {
        if (empleados[i].salario_base <= 10000) {
            empleados[i].salario_base *= 1.10;
        }
    }
    cout << "\nSalarios de empleados con salario menor o igual a 10,000 actualizados.\n";
}

void mostrarSalarioMayor20k() {
    bool found = false;
    cout << "\nEmpleados con salario mayor a 20,000:\n";
    for (int i = 0; i < emp_pos; i++) {
        if (empleados[i].salario_base > 20000) {
            mostrarDatosEmpleado(empleados[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "No hay empleados con salario mayor a 20,000.\n";
    }
}

void pedirDatosEmpleado() {
    EMPLEADO emp;
    cout << "\nDatos del Empleado\n";
    cout << "==================\n";

    do {
        cout << "Cédula: ";
        cin >> emp.cedula;
        if (!validarCedula(emp.cedula)) {
            cout << "Cedula invalida. Intente de nuevo.\n";
        }
    } while (!validarCedula(emp.cedula));

    cout << "Nombres: ";
    cin.ignore();
    cin.getline(emp.nombres, 50);

    cout << "Apellidos: ";
    cin.getline(emp.apellidos, 50);

    cout << "Cargo: ";
    cin.getline(emp.cargo, 50);

    do {
        cout << "Salario Base: ";
        cin >> emp.salario_base;
        if (!validarSalario(emp.salario_base)) {
            cout << "Salario invalido. Debe ser mayor a 0. Intente de nuevo.\n";
        }
    } while (!validarSalario(emp.salario_base));

    agregarEmpleado(&emp);
    guardarEmpleado(emp);
    cout << "Empleado agregado.\n";
}

void mostrarDatosEmpleado(const EMPLEADO &e) {
    cout << "==============================\n";
    cout << "Cedula: " << e.cedula << endl;
    cout << "Nombres: " << e.nombres << endl;
    cout << "Apellidos: " << e.apellidos << endl;
    cout << "Cargo: " << e.cargo << endl;
    cout << "Salario Base: " << e.salario_base << endl;
    cout << "==============================\n";
}

void cargarEmpleados() {
    ifstream archivo("empleados.txt");
    if (archivo.fail()) {
        cout << "No se pudo abrir\n";
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
        cout << "No se pudo abrir\n";
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
    cout << "\n========= MENU =========\n";
    cout << "1. Agregar Empleado\n";
    cout << "2. Aumentar Salario a los empleados con salario mayor a 10,000 (5%)\n";
    cout << "3. Aumentar Salario a los empleados con salario menor a 20,000 (10%)\n";
    cout << "4. Mostrar Empleados con Salario mayor a  20,000\n";
    cout << "5. Salir\n";
    cout << "========================\n";
    cout << "Digite la opcion: ";
    cin >> op;
    while (cin.fail() || op < 1 || op > 5) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Opción invalida. ";
        cin >> op;
    }
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
            aumentarSalario5();
            break;
        case 3:
            aumentarSalario10();
            break;
        case 4:
            mostrarSalarioMayor20k();
            break;
        case 5:
            cout << "Adiós.....\n";
            break;
        default:
            cout << "Opción no válida\n";
            break;
        }
    } while (op != 5);
}

bool validarCedula(const char *cedula) {
    if (strlen(cedula) < 5 || strlen(cedula) > 19) {
        return false;
    }
    for (int i = 0; i < strlen(cedula); i++) {
        if (!isdigit(cedula[i])) {
            return false;
        }
    }
    return true;
}

bool validarSalario(double salario) {
    return salario > 0;
}
