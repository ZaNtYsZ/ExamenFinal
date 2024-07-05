#ifndef VARIABLES_H
#define VARIABLES_H

const int MAX_EMP = 100;

struct EMPLEADO {
    char cedula[20];
    char nombres[50];
    char apellidos[50];
    char cargo[50];
    double salario_base;
};

extern EMPLEADO empleados[MAX_EMP];
extern int emp_pos;

#endif
