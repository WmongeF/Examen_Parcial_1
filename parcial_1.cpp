#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#define j 30
#define s 5

using namespace std;

const char *nom_arch = "Empresa.dat";
const char *nom_temp = "temp.dat";

struct Empresa
{
    int codigo_emp;
    char nombre[j];
    char apellido[j];
    char puesto[j];
    float sueldo;
    float bonificacion;
    float total;
};
void menu();
void ingresar_Empleado();
void mostrar_Empleado();
void modificar_Emp();
void buscar_Emp();
void eliminar_Empleado();

int main()
{
    menu();
}

void menu()
{
    int a;
    do
    {
        system("cls");
        cout << (" 1. Insertar Empleado\n");
        cout << (" 2. Buscar Empleado\n");
        cout << (" 3. Ver lista de empleados\n");
        cout << (" 4. Modificar Empleado\n");
        cout << (" 5. Eliminar Empleado\n");
        cout << (" 6. Salir\n");
        cout << ("Ingrese opcion: ");
        cin >> a;
        switch (a)
        {
        case 1:
            system("cls");
            ingresar_Empleado();
            break;
        case 2:
            system("cls");
            buscar_Emp();
            break;
        case 3:
            system("cls");
            mostrar_Empleado();
            break;
        case 4:
            system("cls");
            modificar_Emp();
            break;

        case 5:
            system("cls");
            eliminar_Empleado();
            break;
        }
    } while (a != 6);
}

void ingresar_Empleado()
{
    char continuar;
    FILE *archivo = fopen(nom_arch, "ab");
    Empresa emp;
        string nombre,apellido,puesto;
    do
    {
        system("cls");
        fflush(stdin);
        emp.codigo_emp = 0;
        emp.codigo_emp = emp.codigo_emp + 1;
        cout << "Ingrese nombre: ";
        getline(cin, nombre);
        strcpy(emp.nombre, nombre.c_str());
        cout << "Ingrese apellido: ";
        getline(cin, apellido);
        strcpy(emp.apellido, apellido.c_str());
        cout << "Ingrese puesto: ";
        getline(cin, puesto);
        strcpy(emp.puesto, puesto.c_str());
        cout << "sueldo base:Q";
        cin >> emp.sueldo;
        cin.ignore();
        cout << "Bonificacion:Q";
        cin >> emp.bonificacion;
        cin.ignore();
        emp.total = emp.sueldo + emp.bonificacion;

        fwrite(&emp, sizeof(Empresa), 1, archivo);

        cout << "Desea ingresar otro Empleado s/n : ";
        cin >> continuar;
    } while ((continuar == 's') || (continuar == 'S'));
    fclose(archivo);
    system("cls");
}

void buscar_Emp()
{

   FILE* archivo = fopen(nom_arch, "rb");
	
	int pos=0;
	cout<<"Que Empleado desea ver?: ";
	cin>>pos;
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Empresa), SEEK_SET );
	
	Empresa emp;
    
    fread(&emp, sizeof(Empresa), 1, archivo);

    cout << "Codigo: " <<pos<< endl;
    cout << "Nombre: " << emp.nombre << endl;
    cout << "Apellido: " << emp.apellido << endl;
    cout << "puesto: " << emp.puesto << endl;
    cout << "Sueldo Base:Q" << emp.sueldo << endl;
    cout << "Bonificacion:Q" << emp.bonificacion << endl;
    cout << "Total:Q " << emp.total << endl;
    cout << endl;

    fclose(archivo);
    system("PAUSE");
}
void mostrar_Empleado()
{
    system("cls");
    FILE *archivo = fopen(nom_arch, "rb");
    if (!archivo)
    {
        archivo = fopen(nom_arch, "w+b");
    }

    Empresa emp;
    int registro = 0;
    fread(&emp, sizeof(Empresa), 1, archivo);
    cout << "_________________________________________________________________________________" << endl;
    cout << "Codigo_Emp|"
         << "NOMBRE\t|"
         << "APELLIDO\t|"
         << "Puesto\t|"
         << "SUELDO\t|"
         << "BONIFICACION\t|"
         << "TOTAL\t|" << endl;

    do
    {

        cout << "_______________________________________________________________________________" << endl;
        cout << registro <<"\t"<<emp.nombre<< "|\t" << emp.apellido << "|\t" << emp.puesto << "|\t" << emp.sueldo << "|\t" << emp.bonificacion << "|\t|" << emp.total << endl;

        fread(&emp, sizeof(Empresa), 1, archivo);
        registro += 1;

    } while (feof(archivo) == 0);

    cout << endl;

    fclose(archivo);
    getch();
	}

void modificar_Emp()
{
    FILE *archivo = fopen(nom_arch, "r+b");
    int id;
    char respuesta[s];
    string nombre, apellido, puesto;
    Empresa emp;

    cout << "Ingrese el Codigo_Empleado que desea Modificar: ";
    cin >> id;
    fseek(archivo, id * sizeof(Empresa), SEEK_SET);
    fread(&emp, sizeof(Empresa), 1, archivo);


    cout << ("------------  Listado de Empleados -------------\n");

    cout << ("Nombre:") << emp.nombre << ("\n");

    cout << ("Apellido:") << emp.apellido << ("\n");

    cout << ("Puesto:") << emp.puesto << ("\n");

    cout << ("Sueldo Base:Q") << emp.sueldo << ("\n");

    cout << ("Bonificacion:Q") << emp.bonificacion << ("\n");

    cout << ("---------------------------------------------");

    cout << "<\n Nombre: " << emp.nombre << endl;
    cout << ("Desea cambiar el nombre [s/n]: ");
    cin >> respuesta, s;

    if (strcmp(respuesta, "s") == 0)
    {

        fseek(archivo, id * sizeof(Empresa), SEEK_SET);
        cin.ignore();
        cout << ("Nuevo Nombre: ");
        getline(cin, nombre);
        strcpy(emp.nombre, nombre.c_str());
        fwrite(&emp, sizeof(Empresa), 1, archivo);
    }

    cout << "\nApellido: " << emp.apellido << endl;
    cout << ("Desea modificar el apellido [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0)
    {
        fseek(archivo, id * sizeof(Empresa), SEEK_SET);
        cin.ignore();
        cout << "Ingrese nueva Apellido: ";
        getline(cin, apellido);
        strcpy(emp.apellido, apellido.c_str());
        fwrite(&emp, sizeof(Empresa), 1, archivo);
    }

    cout << "\nPuesto: " << emp.puesto << endl;
    cout << ("Desea modificar el puesto [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0)
    {
        fseek(archivo, id * sizeof(Empresa), SEEK_SET);
        cin.ignore();

        cout << "Ingrese nuevo Puesto: ";
        getline(cin, puesto);
        strcpy(emp.puesto, puesto.c_str());
        fwrite(&emp, sizeof(Empresa), 1, archivo);
    }

    cout << "\nSueldo:Q" << emp.sueldo << endl;
    cout << ("Desea modificar el sueldo [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0)
    {
        fseek(archivo, id * sizeof(Empresa), SEEK_SET);
        cin.ignore();

        cout << "Ingrese nuevo Sueldo:Q";
        cin >> emp.sueldo;
        fwrite(&emp, sizeof(Empresa), 1, archivo);
    }

    cout << "\nBonificacion:Q " << emp.bonificacion << endl;
    cout << ("Desea modificar la bonificacion [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0){
        fseek(archivo, id * sizeof(Empresa), SEEK_SET);
        cin.ignore();

        cout << "Ingrese nueva Bonificacion:Q ";
        cin >> emp.bonificacion;
        emp.total = emp.sueldo + emp.bonificacion;
        fwrite(&emp, sizeof(Empresa), 1, archivo);
    }

    cout << ("Datos actualizados correctamente");
    fclose(archivo);
    getch();
    mostrar_Empleado();
}

void eliminar_Empleado()
{
    Empresa emp;
    FILE *temporal = fopen(nom_temp, "w+b");
    FILE *archivo = fopen(nom_arch, "r+b");
    int id;
    cout << "Ingrese el Codigo_Empleado que desea eliminar: ";
    cin >> id;
    fseek(archivo, id * sizeof(Empresa), SEEK_SET);
    emp.codigo_emp = -1;
    fwrite(&emp, sizeof(Empresa), 1, archivo);
    fclose(archivo);

    archivo = fopen(nom_arch, "r+b");

    fread(&emp, sizeof(Empresa), 1, archivo);
    temporal = fopen(nom_temp, "a+b");
    do
    {
        if (emp.codigo_emp == -1)
        {
            cout << "¡Archivo eliminado!";
        }
        if (emp.codigo_emp >= 0)
        {
            fwrite(&emp, sizeof(Empresa), 1, temporal);
        }
        fread(&emp, sizeof(Empresa), 1, archivo);
    } while (feof(archivo) == 0);
    fclose(temporal);
    fclose(archivo);

    archivo = fopen(nom_arch, "w");
    fclose(archivo);

    temporal = fopen(nom_temp, "r+b");

    fread(&emp, sizeof(Empresa), 1, temporal);
    archivo = fopen(nom_arch, "a+b");
    do
    {
        fwrite(&emp, sizeof(Empresa), 1, archivo);
        fread(&emp, sizeof(Empresa), 1, temporal);
    } while (feof(temporal) == 0);
    fclose(archivo);
    fclose(temporal);

    temporal = fopen(nom_temp, "w");
    fclose(temporal);

    mostrar_Empleado();
}
