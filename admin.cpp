#include <iostream>
#include <string>
#include <process.h>
#include <stdio.h>
#include <conio.h>


using namespace std;

struct Usuario {
    int codigo;
    char nombre[20];
    char apellido[20];
    char agencia[20];
    char password[20];
};

struct Transaccion {
    int codigo;
    int numRamdon1;
    int numRamdon2;
    int numRamdon3;
    int numeroIngresado;
    bool gano;
};

struct Usuario usuario;
struct Transaccion transaccion;


FILE *usuariosTxt, *transaccionesTxt;

void crearUsuarioTxt() {

  if ((usuariosTxt = fopen("Usuarios.txt", "w")) == NULL)
    cout << ("Error al abrir el archivo clientes.txt\n");
  cout << "Archivo creado correctamente " << endl;
  fclose(usuariosTxt);

}

void crearTransaccionTxt() {

  transaccionesTxt = fopen("Transacciones.txt", "w");

  if (transaccionesTxt == NULL) {

    cout << ("Error al abrir el archivo clientes.txt\n");
    fclose(transaccionesTxt);
    return;
  }
  cout << "Archivo creado correctamente " << endl;
  fclose(transaccionesTxt);
}

void mostrarUsuarios() {

  usuariosTxt = fopen("Usuarios.txt", "r");

  if (usuariosTxt == NULL) {
    cout << "Error al abrir el archivo de clientes";
    fclose(usuariosTxt);
    return;
  }
  rewind(usuariosTxt);
  fread(&usuario, sizeof(usuario), 1, usuariosTxt);
  printf("%-15s%-15s%-15s%-15s", "Codigo", "Nombre", "Apellido", "Agencia");
  cout << endl;
  while (!feof(usuariosTxt)) {
    printf("%-15d%-15s%-15s%-15s", usuario.codigo, usuario.nombre, usuario.apellido, usuario.agencia);
    cout << endl;
    fread(&usuario, sizeof(usuario), 1, usuariosTxt);
  }

  fclose(usuariosTxt);
  cout << endl << "_______________________________" << endl << endl;

}

bool usuarioYaExiste(int codigo) {
  struct Usuario usuario;
  usuariosTxt = fopen("Usuarios.txt", "r");
  if (usuariosTxt == NULL) {
    cout << "Error al abrir el archivo de usuarios\n";
    cout << endl;
    fclose(usuariosTxt);
    return true;
  }
  fread(&usuario, sizeof(usuario), 1, usuariosTxt);
  while (!feof(usuariosTxt)) {
    if (usuario.codigo == codigo) {
      fclose(usuariosTxt);
      cout << "El usuario ya existe, ingrese otro codigo: " << endl;
      return true;
    }
    fread(&usuario, sizeof(usuario), 1, usuariosTxt);
  }
  fclose(usuariosTxt);
  return false;
}

void mostrarTransacciones() {
  transaccionesTxt = fopen("Transacciones.txt", "r");

  if (transaccionesTxt == NULL) {
    cout << "Error al abrir el archivo de transacciones" <<endl;
    fclose(transaccionesTxt);
    return;
  }

  fread(&transaccion, sizeof(transaccion), 1, transaccionesTxt);
  printf("%-20s%-20s%-20s%-20s%-20s%-20s", "Codigo", "Numero random 1", "Numero random 2", "Numero random 3",
         "Numero ingresado",
         "Gano");

  cout << endl;
  while (!feof(transaccionesTxt)) {
    printf("%-20d%-20d%-20d%-20d%-20d%-20d", transaccion.codigo, transaccion.numRamdon1, transaccion.numRamdon2,
           transaccion.numRamdon3, transaccion.numeroIngresado, transaccion.gano);

    fread(&transaccion, sizeof(transaccion), 1, transaccionesTxt);
  }

  fclose(transaccionesTxt);
  cout << endl << "_______________________________" << endl << endl;

}


void agregarUsuario() {
  cout << "Ingrese el codigo del usuario: " << endl;

  bool yaExiste;
  do {
    cin >> usuario.codigo;
    yaExiste = usuarioYaExiste(usuario.codigo);
  } while (yaExiste);

  cout << "Ingrese el nombre del usuario: " << endl;
  cin >> usuario.nombre;
  cout << "Ingrese el apellido del usuario: " << endl;
  cin >> usuario.apellido;
  cout << "Ingrese la agencia del usuario: " << endl;
  cin >> usuario.agencia;
  cout << "Ingrese la contraseña del usuario: " << endl;
  cin >> usuario.password;
  cout << endl;

  usuariosTxt = fopen("Usuarios.txt", "a");
  if (usuariosTxt == NULL) {
    return;
  }
  fwrite(&usuario, sizeof(usuario), 1, usuariosTxt);
  cout << "Usuario creado con exito" << endl;

  fclose(usuariosTxt);
}


void borrarConsola() {
  system("CLS");
}

void menu() {
  int opcion;
  do {
    cout << ("***********  M E N U ***********") << endl;
    cout << "1. Crear archivo Usuario.txt" << endl;
    cout << "2. Agregar Usuario" << endl;
    cout << "3. Mostrar Usuarios" << endl;
    cout << "4. Crear archivo Transaccion.txt" << endl;
    cout << "5. Mostrar Transacciones" << endl;
    cout << "6. Salir" << endl;
    cin >> opcion;
    switch (opcion) {
      case 1:
        crearUsuarioTxt();
        break;
      case 2:
        agregarUsuario();
        mostrarUsuarios();
        break;
      case 3:
        borrarConsola();
        mostrarUsuarios();
        break;
      case 4:
        crearTransaccionTxt();
        break;
      case 5:
        borrarConsola();
        mostrarTransacciones();
        break;
      case 6:
        break;
      default:
        cout << "Opcion no valida" << endl;
        break;
    }
  } while (opcion != 6);

}


int main() {
  menu();
  return 0;
}