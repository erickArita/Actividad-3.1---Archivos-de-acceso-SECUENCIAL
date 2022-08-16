#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <process.h>

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
FILE *usuariosTxt;
FILE *transaccionesTxt;

bool validaUsuario(char nombre[20], char password[20]) {

  usuariosTxt = fopen("Usuarios.txt", "r");

  if (usuariosTxt == NULL) {
    cout << "Error al abrir el archivo de clientes";
    fclose(usuariosTxt);
    return false;
  }

  fread(&usuario, sizeof(usuario), 1, usuariosTxt);


  while (!feof(usuariosTxt)) {
    if (stricmp(usuario.nombre, nombre) == 0 && stricmp(usuario.password, password) == 0) {
      cout << "Usuario valido" << endl << endl;
      cout << "-----BIENVENIDO-------" << endl;
      cout << usuario.nombre << " " << usuario.apellido << endl;
      return true;
    }
    fread(&usuario, sizeof(usuario), 1, usuariosTxt);
  }


  fclose(usuariosTxt);

  cout << "Usuario no valido" << endl << endl;
  return false;
}

void borrarConsola() {
  system("CLS");
}

void login() {
  bool usuarioValido;
  char nombre[20];
  char password[20];
  do {
    cout << ("*********** LOGIN ***********") << endl;
    cout << "Ingrese su nombre: ";
    cin >> nombre;
    cout << "Ingrese su contraseña: ";
    cin >> password;
    usuarioValido = validaUsuario(nombre, password);
    cout << "Precione cualquier tecla para continuar..." << endl;
    getch();
    borrarConsola();
    cout << endl;
  } while (!usuarioValido);

}

void crearTransaccion() {
  transaccionesTxt = fopen("Transacciones.txt", "a");

  if (transaccionesTxt == NULL) {

    cout << ("Error al abrir el archivo Transacciones.txt\n");
    fclose(transaccionesTxt);
    return;
  }
  fwrite(&transaccion, sizeof(transaccion), 1, transaccionesTxt);
  fclose(transaccionesTxt);
}

void mostrarRegistro() {
  int ganadas = 0;
  int perdidas = 0;
  int jugadas = 0;

  struct Transaccion transaccionActual;

  transaccionesTxt = fopen("Transacciones.txt", "r");

  if (transaccionesTxt == NULL) {
    cout << "Error al abrir el archivo de Transacciones.txt\n";
    fclose(transaccionesTxt);
    return;
  }
  fread(&transaccionActual, sizeof(transaccionActual), 1, transaccionesTxt);

  while (!feof(transaccionesTxt)) {
    if (transaccionActual.codigo == usuario.codigo) {
      jugadas++;
      transaccionActual.gano ? ganadas++ : perdidas++;
    }
    fread(&transaccionActual, sizeof(transaccionActual), 1, transaccionesTxt);
  }

  printf("%-15s %-15s %-15s \n", "Jugadas", "Ganadas", "Perdidas");
  printf("%-15d %-15d %-15d \n", jugadas, ganadas, perdidas);

  fclose(transaccionesTxt);
}

void juego() {
  srand(time(NULL));
  int rand1, rand2, rand3, numeroIngresado;
  bool gano;

  rand1 = rand() % 50 + 1;
  rand2 = rand() % 50 + 1;
  rand3 = rand() % 50 + 1;

  cout << "Se generaron 3 numeros ramdon intente adivinar al menos 1" << endl;
  cout << "Ingrese un numero entre 1 y 50: ";
  cin >> numeroIngresado;


  if (numeroIngresado == rand1 || numeroIngresado == rand2 || numeroIngresado == rand3) {
    gano = true;
    cout << "Felicidades, ha ganado" << endl << endl;
  } else {
    gano = false;
    cout << "Lo siento, ha perdido" << endl << endl;
  }

  transaccion.codigo = usuario.codigo;
  transaccion.numRamdon1 = rand1;
  transaccion.numRamdon2 = rand2;
  transaccion.numRamdon3 = rand3;
  transaccion.numeroIngresado = numeroIngresado;
  transaccion.gano = gano;
  crearTransaccion();
}


void menu() {
  int opcion;
  do {
    cout << ("***********  M E N U ***********") << endl;
    cout << "1. Ver registro de Usuario" << endl;
    cout << "2. Jugar" << endl;
    cout << "3. Salir" << endl;
    cin >> opcion;
    borrarConsola();
    switch (opcion) {
      case 1:
        mostrarRegistro();
        break;
      case 2:
        juego();
        break;
      case 3:
        break;
      default:
        cout << "Opcion no valida" << endl;
        break;
    }
  } while (opcion != 3);

}

int main() {
  login();
  menu();
  return 0;
}