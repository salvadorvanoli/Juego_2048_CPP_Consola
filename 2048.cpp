// Perfiles

#include <iostream>
using namespace std;

// Estructuras necesarias para el sistema de perfiles y el funcionamiento del juego

struct hora{
    string hora;
    string minutos;
    string segundos;
};

struct fecha{
    string dia;
    string mes;
    string anio;
};

struct partida{
    int resultadoPartida;
    fecha fechaComienzoPartida;
    hora horaComienzoPartida;
};

struct perfil{
    string alias;
    string apellido;
    string nombre;
    fecha nacimiento;
    fecha fechaComienzoPartida;
    hora horaComienzoPartida;
    int partidaGuardada[4][4];
    int powerUps[4]={0};
    int puntajeActual=0;
    bool hayJuegoParaContinuar=false;
    int puntajeMaximo=0;
    partida partidasPerfil[100];
    int partidasJugadas=0;
};

// Variables globales necesarias para el funcionamiento de los menús, el sistema de perfiles y de juegos guardados

perfil perfilesDeshabilitados[21];
perfil perfiles[21];
int cantPerfilesHabilitados=0;
int cantPerfilesDeshabilitados=0;
int perfilActual;
bool perfil=false;
bool volverAlMenu=false;
bool primeraEjecucion=true;

// Variables globales necesarias para el funcionamiento del juego

int tablero[4][4]={0};

// Lógica de los power Ups

void powerUpGenerar256(){
    char columna, fila;
    bool bucle=true;
    while (bucle){
        cout << "Ingresa unas coordenadas validas en las que quieras colocar un 256" << endl;
        cout << "Columna: " << endl;
        cin >> columna;
        columna-='1';
        cout << "Fila: " << endl;
        cin >> fila;
        fila-='1';
        if ((columna>=0 && columna<=3) && (fila>=0 && fila<=3)){
            bucle=false;
        }
    }
    tablero[fila][columna]=256;
    return;
}

void powerUpVolverUnTurno(int tableroPrevio[4][4]){
    for(int i=0; i<=3; i++){
        for(int j=0; j<=3; j++){
            tablero[i][j]=tableroPrevio[i][j];
        }
    }
    perfiles[perfilActual].puntajeActual=0;
    return;
}

void powerUpDuplicarTablero(){
    for(int i=0; i<=3; i++){
        for(int j=0; j<=3; j++){
            tablero[i][j]*=2;
        }
    }
    return;
}

// Mostrar menu existe para no repetir código cuando quiera volver al menú

void mostrarMenu(){
    system("clear");
    cout << "----------------------------------------------------------------------------------------" << endl << 
        "|   222222222222222         0000000000000              444444          888888888       |" << endl << 
        "|  2:::::::::::::::22     00:::::::::::::00           4::::::4       88:::::::::88     |" << endl << 
        "|  2::::::222222:::::2   0:::::::::::::::::0        4::::::::4     88:::::::::::::88   |" << endl << 
        "|  2222222     2:::::2   0:::::::000:::::::0      4::::44::::4    8::::::88888::::::8  |" << endl << 
        "|              2:::::2   0::::::0   0::::::0     4::::4 4::::4    8:::::8     8:::::8  |" << endl << 
        "|              2:::::2   0:::::0     0:::::0    4::::4  4::::4    8:::::8     8:::::8  |" << endl << 
        "|           2222::::2    0:::::0     0:::::0   4::::4   4::::4     8:::::88888:::::8   |" << endl << 
        "|      22222::::::22     0:::::0 000 0:::::0  4::::444444::::4      8:::::::::::::8    |" << endl << 
        "|    22::::::::222       0:::::0     0:::::0   4:::::::::::::4     8:::::88888:::::8   |" << endl << 
        "|   2:::::22222          0:::::0     0:::::0    4444444444:::4    8:::::8     8:::::8  |" << endl << 
        "|  2:::::2               0:::::0     0:::::0              4::4    8:::::8     8:::::8  |" << endl << 
        "|  2:::::2               0::::::0   0::::::0              4::4    8:::::8     8:::::8  |" << endl << 
        "|  2:::::2       222222  0:::::::000:::::::0             4:::4    8::::::88888::::::8  |" << endl << 
        "|  2::::::2222222:::::2  0:::::::::::::::::0           4::::::4    88:::::::::::::88   |" << endl << 
        "|  2::::::::::::::::::2   00:::::::::::::00           4::::::::4     88:::::::::88     |" << endl << 
        "|  22222222222222222222     0000000000000             444444444        888888888       |" << endl << 
        "|                                                                                      |" << endl << 
        "|                                                                                      |" << endl << 
        "|                                                                                      |" << endl << 
        "|                                    1-°Nuevo juego°                                   |" << endl << 
        "|                                     2-°Continuar°                                    |" << endl <<
        "|                             3-°Estadisticas e informes°                              |" << endl <<
        "|                                      4-°Reglas°                                      |" << endl <<
        "|                                      5-°Tienda°                                      |" << endl << 
        "|                                  6-°Salir del juego°                                 |" << endl << 
        "|                                                                                      |" << endl << 
        "|                                                                                      |" << endl << 
        "----------------------------------------------------------------------------------------" << endl;
    cout << "                                 Introduzca un comando" << endl;
}

// guardarTablero existe para no repetir código, guarda el tablero de juego en el espacio de guardado del perfil seleccionado

void guardarTablero(){
    int i, j;
    for (i = 0; i <= 3; i++){
        for (j = 0; j<= 3; j++){
            perfiles[perfilActual].partidaGuardada[i][j]=tablero[i][j];
        }
    }
}

// cargarTablero existe para no repetir código, carga el tablero según el perfil seleccionado

void cargarTablero(){
    int i, j;
    for (i = 0; i <= 3; i++){
        for (j = 0; j<= 3; j++){
            tablero[i][j]=perfiles[perfilActual].partidaGuardada[i][j];
        }
    }
}

// huboCambio es parte de la lógica del juego, verifica que se haya hecho un movimiento efectivo, es decir que cambie en algo el tablero

bool huboCambio(int tableroPrevio[4][4]){
    int i, j;
    bool Cambio=false;
    for (i = 0; i <= 3; i++){
        for (j = 0; j <= 3; j++){
            if(tableroPrevio[i][j]!=tablero[i][j]){
                Cambio=true;
            }
        }
    }
    return Cambio;
}

// Indica hacia dónde se movió el jugador por última vez

void indicarMovimiento(int tableroPrevio[4][4], char moverHacia){
    if(huboCambio(tableroPrevio)){
        switch(moverHacia){
            case 'w':
            cout << "      Te moviste hacia arriba" << endl;
            break;
            case 's':
            cout << "      Te moviste hacia abajo" << endl;
            break;
            case 'a':
            cout << "      Te moviste hacia la izquierda" << endl;
            break;
            case 'd':
            cout << "      Te moviste hacia la derecha" << endl;
            break;
        }
    }
}

// funcionCualquierTecla existe para no repetir código

void funcionCualquierTecla(){
    char cualquierTecla=0;
    cout << " Ingresa cualquier tecla para volver atrás" << endl;
    cin >> cualquierTecla;
}

// Lógica del menú de power ups

void tiendaPowerUps(){
    system("clear");
    char introduccion;
    bool bucle=true;
    cout << "----------------------------------------------------------------------------------" << endl << endl << "                        ¡Bienvenido a la tienda de Power Ups!" << endl << " Gasta tu puntaje para comprar algunas ventajas que te pueden servir en el juego!" << endl << endl << "                      Los poderes se comparten entre perfiles" << endl << endl << "     1-Generar un 256 <1000 puntos> <un uso>" << endl << "     2-Volver un turno <5000 puntos> <infinitos usos> <reinicia el puntaje>" << endl << "     3-Duplicar el tablero <3500 puntos> <un uso>" << endl << endl << "     4-Volver al menu" << endl << endl << "----------------------------------------------------------------------------------" << endl;
    while(bucle){
        cin >> introduccion;
        switch(introduccion){
            case '1':
            if(perfiles[perfilActual].puntajeMaximo>=1000){
                bucle=false;
                perfiles[perfilActual].puntajeMaximo-=1000;
                perfiles[perfilActual].powerUps[0]++;
                cout << "--------------------------" << endl << endl << " Compra realizada con éxito" << endl << endl << "--------------------------" << endl;
                funcionCualquierTecla();
                tiendaPowerUps();
                return;
                break;
            } else {
                bucle=false;
                system("clear");
                cout << "-------------------------------------------" << endl << endl << "   Te faltan puntos para comprar esto" << endl << endl << "-------------------------------------------" << endl;
                funcionCualquierTecla();
                tiendaPowerUps();
                return;
                break;
            }
            case '2':
            if(perfiles[perfilActual].puntajeMaximo>=5000){
                bucle=false;
                perfiles[perfilActual].puntajeMaximo-=5000;
                perfiles[perfilActual].powerUps[0]++;
                cout << "--------------------------" << endl << endl << " Compra realizada con éxito" << endl << endl << "--------------------------" << endl;
                funcionCualquierTecla();
                tiendaPowerUps();
                return;
                break;
            } else {
                bucle=false;
                system("clear");
                cout << "-------------------------------------------" << endl << endl << "   Te faltan puntos para comprar esto" << endl << endl << "-------------------------------------------" << endl;
                funcionCualquierTecla();
                tiendaPowerUps();
                return;
                break;
            }
            case '3':
            if(perfiles[perfilActual].puntajeMaximo>=3500){
                bucle=false;
                perfiles[perfilActual].puntajeMaximo-=3500;
                perfiles[perfilActual].powerUps[0]++;
                cout << "--------------------------" << endl << endl << " Compra realizada con éxito" << endl << endl << "--------------------------" << endl;
                funcionCualquierTecla();
                tiendaPowerUps();
                return;
                break;
            } else {
                bucle=false;
                system("clear");
                cout << "-------------------------------------------" << endl << endl << "   Te faltan puntos para comprar esto" << endl << endl << "-------------------------------------------" << endl;
                funcionCualquierTecla();
                tiendaPowerUps();
                return;
                break;
            }
            case '4':
            bucle=false;
            mostrarMenu();
            return;
            break;
            default:
            cout << " Tecla incorrecta"  << endl;
            tiendaPowerUps();
            return;
        }
    }
    return;
}

// Guarda el puntaje en el arreglo correspondiente al perfil actual, en caso de que un puntaje nuevo mayor aparezca para el mismo perfil, lo sobrescribe

void guardarPuntajes(){
    if(perfiles[perfilActual].puntajeActual>perfiles[perfilActual].puntajeMaximo){
        perfiles[perfilActual].puntajeMaximo=perfiles[perfilActual].puntajeActual;
    }
}

// Parte de la lógica del juego, mueve los números del tablero, y en el caso de que se muevan dos números iguales en una dirección, quedando estos juntos, se suman y se elimina el número de una de las casillas.

void moverHaciaArriba(){
    int numero, i, j;
    for (i = 0; i <= 3; i++){
        for (j = 0; j <= 3; j++){
            if (tablero[i][j]!=0){
                numero = tablero[i][j];
                tablero[i][j] = 0;
                while (i > 0 && tablero[i-1][j] == 0){
                    i--;
                }
                tablero[i][j] = numero;
            }
        }
    }
    for (i = 0; i <= 3; i++){
        for (j = 0; j <= 3; j++){
            if(tablero[i+1][j]==tablero[i][j]){
                tablero[i][j]*=2;
                perfiles[perfilActual].puntajeActual+=tablero[i][j];
                tablero[i+1][j]=0;
            }
        }
    }
    for (i = 0; i <= 3; i++){
        for (j = 0; j <= 3; j++){
            if (tablero[i][j]!=0){
                numero = tablero[i][j];
                tablero[i][j] = 0;
                while (i > 0 && tablero[i-1][j] == 0){
                    i--;
                }
                tablero[i][j] = numero;
            }
        }
    }
}

void moverHaciaIzquierda(){
    int numero, i, j;
    for (i = 0; i <= 3; i++){
        for (j = 0; j<= 3; j++){
            if (tablero[i][j]!=0){
                numero = tablero[i][j];
                tablero[i][j] = 0;
                while (j > 0 && tablero[i][j-1] == 0){
                    j--;
                }
                tablero[i][j] = numero;
            }
        }
    }
    for (j = 0; j <= 3; j++){
        for (i = 0; i <= 3; i++){
            if(tablero[i][j+1]==tablero[i][j]){
                tablero[i][j]*=2;
                perfiles[perfilActual].puntajeActual+=tablero[i][j];
                tablero[i][j+1]=0;
            }
        }
    }
    for (i = 0; i <= 3; i++){
        for (j = 0; j<= 3; j++){
            if (tablero[i][j]!=0){
                numero = tablero[i][j];
                tablero[i][j] = 0;
                while (j > 0 && tablero[i][j-1] == 0){
                    j--;
                }
                tablero[i][j] = numero;
            }
        }
    }
}

void moverHaciaAbajo(){
    int numero, i, j;
    for (i = 3; i >= 0; i--){
        for (j = 3; j >= 0; j--){
            if (tablero[i][j]!=0){
                numero = tablero[i][j];
                tablero[i][j] = 0;
                while (i < 3 && tablero[i+1][j] == 0){
                    i++;
                }
                tablero[i][j] = numero;
            }
        }
    }
    for (i = 3; i >= 0; i--){
        for (j = 3; j >= 0; j--){
            if(tablero[i-1][j]==tablero[i][j]){
                tablero[i][j]*=2;
                perfiles[perfilActual].puntajeActual+=tablero[i][j];
                tablero[i-1][j]=0;
            }
        }
    }
    for (i = 3; i >= 0; i--){
        for (j = 3; j >= 0; j--){
            if (tablero[i][j]!=0){
                numero = tablero[i][j];
                tablero[i][j] = 0;
                while (i < 3 && tablero[i+1][j] == 0){
                    i++;
                }
                tablero[i][j] = numero;
            }
        }
    }
}

void moverHaciaDerecha(){
    int numero, i, j;
    for (i = 3; i >= 0; i--){
        for (j = 3; j >= 0; j--){
            if (tablero[i][j]!=0){
                numero = tablero[i][j];
                tablero[i][j] = 0;
                while (j < 3 && tablero[i][j+1] == 0){
                    j++;
                }
                tablero[i][j] = numero;
            }
        }
    }
    for (j = 3; j >= 0; j--){
        for (i = 3; i >= 0; i--){
            if(tablero[i][j-1]==tablero[i][j]){
                tablero[i][j]*=2;
                perfiles[perfilActual].puntajeActual+=tablero[i][j];
                tablero[i][j-1]=0;
            }
        }
    }
    for (i = 3; i >= 0; i--){
        for (j = 3; j >= 0; j--){
            if (tablero[i][j]!=0){
                numero = tablero[i][j];
                tablero[i][j] = 0;
                while (j < 3 && tablero[i][j+1] == 0){
                    j++;
                }
                tablero[i][j] = numero;
            }
        }
    }
}

void mover(char moverHacia, int tableroPrevio[4][4]){
    int numero, i, j;
    switch(moverHacia){
        case 'w':
        moverHaciaArriba();
        break;
        case 'a':
        moverHaciaIzquierda();
        break;
        case 's':
        moverHaciaAbajo();
        break;
        case 'd':
        moverHaciaDerecha();
        break;
        case 'q':
        system("clear");
        volverAlMenu=true;
        perfiles[perfilActual].hayJuegoParaContinuar=true;
        guardarPuntajes();
        guardarTablero();
        mostrarMenu();
        break;
        case '1':
        if(perfiles[perfilActual].powerUps[0]>=1){
            powerUpGenerar256();
            perfiles[perfilActual].powerUps[0]--;
        }
        break;
        case '2':
        if(perfiles[perfilActual].powerUps[1]>=1){
            powerUpVolverUnTurno(tableroPrevio);
        }
        break;
        case '3':
        if(perfiles[perfilActual].powerUps[2]>=1){
            powerUpDuplicarTablero();
            perfiles[perfilActual].powerUps[2]--;
        }
        break;
    }
    return;
}


// Parte de la lógica del juego, genera un dos o cuatro de manera random en el tablero cada vez que es invocada

void generarNumero(){
    srand (time(NULL));
    char c;
    int i, j, k;
    i = rand() % 4 + 0;
    j = rand() % 4 + 0;
    if(!(perfiles[perfilActual].hayJuegoParaContinuar)){
        while (tablero[i][j]!=0){
            i = rand() % 4 + 0;
            j = rand() % 4 + 0;
        }
        k = rand() % 2;
        if(k==0){
            tablero[i][j] = 2;
        }
        if(k==1){
            tablero[i][j] = 4;
        }
    }
    perfiles[perfilActual].hayJuegoParaContinuar=false;
}

// Parte de la lógica del juego, genera dos dos(2) de manera random en el tablero al iniciar un nuevo juego

void generarIniciales(){
    srand(time(NULL));
    int contador=2;
    while(contador>0){
        int i = rand() % 4 + 0;
        int j = rand() % 4 + 0;
        while (tablero[i][j]!=0){
            i = rand() % 4 + 0;
            j = rand() % 4 + 0;
        }
        tablero[i][j] = 2;
        contador--;
    }
}

// Parte de la lógica del juego, verifica que no se hayan cumplido las condiciones de victoria y derrota

int verificarTablero(){
    bool hayEspacio=false;
    bool hayPosibilidadDeSeguir=false;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(tablero[i][j]==2048){
                perfiles[perfilActual].partidasPerfil[perfiles[perfilActual].partidasJugadas].resultadoPartida=1;
                perfiles[perfilActual].partidasJugadas++;
                return 1;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(tablero[i][j]==0){
                hayEspacio=true;
            }
        }
    }
    if(!hayEspacio){
        for (int j = 3; j >= 0; j--){
            for (int i = 3; i >= 0; i--){
                if(tablero[i][j-1]==tablero[i][j]){
                    hayPosibilidadDeSeguir=true;
                }
            }
        }
        for (int j = 3; j >= 0; j--){
            for (int i = 3; i >= 0; i--){
                if(tablero[i][j+1]==tablero[i][j]){
                    hayPosibilidadDeSeguir=true;
                }
            }
        }
        for (int j = 3; j >= 0; j--){
            for (int i = 3; i >= 0; i--){
                if(tablero[i+1][j]==tablero[i][j]){
                    hayPosibilidadDeSeguir=true;
                }
            }
        }
        for (int j = 3; j >= 0; j--){
            for (int i = 3; i >= 0; i--){
                if(tablero[i-1][j]==tablero[i][j]){
                    hayPosibilidadDeSeguir=true;
                }
            }
        }
    }
    if(!hayEspacio && !hayPosibilidadDeSeguir){
        perfiles[perfilActual].partidasPerfil[perfiles[perfilActual].partidasJugadas].resultadoPartida=2;
        perfiles[perfilActual].partidasJugadas++;
        return 2;
    }
    return 0;
}

// Parte de la lógica del juego, muestra en cada turno el tablero, el puntaje y los controles

void mostrarTablero(){
    cout << "-----------------------------------------" << endl << "          Puntaje acutal: < " << perfiles[perfilActual].puntajeActual << " >" << endl << endl << "       ";
    for (int f=0; f < 4; f++){
        for (int c=0; c < 4; c++){
            if (tablero[f][c]==0){
                cout << "[    ] ";
            } else {
                if(tablero[f][c]<=9){
                    cout << "[ " << tablero[f][c] << "  ] ";
                }
                if(tablero[f][c]<=99 && tablero[f][c]>9){
                    cout << "[ " << tablero[f][c] << " ] ";
                }
                if(tablero[f][c]<=999 && tablero[f][c]>99){
                    cout << "[" << tablero[f][c] << " ] ";
                }
                if(tablero[f][c]<=9999 && tablero[f][c]>999){
                    cout << "[" << tablero[f][c] << "] ";
                }
            }
            if(c==3){
                cout << endl << "       ";
            }
        }
    }
    cout << endl << "Muevete con wasd | Vuelve al menú con q" << endl << "       Poderes aclarados en reglas" << endl << endl << "-----------------------------------------" << endl;
}

// Unifica la lógica del juego, uniendo las diferentes funciones y procedimientos necesarios para ejecutarlo, y permite continuar una partida empezada

void continuar(){
    char moverHacia;
    int tableroPrevio[4][4]={0};
    int i, j;
    volverAlMenu=false;
    bool primerTurno=false;
    system("clear");
    if(!perfil){
        cout << "---------------------------------------------------" << endl << endl << "     Necesitas crear un perfil en estadisticas" << endl << endl << "---------------------------------------------------" << endl << endl;
        funcionCualquierTecla();
        mostrarMenu();
        return;
    }
    if(!(perfiles[perfilActual].hayJuegoParaContinuar)){
        generarIniciales();
        primerTurno=true;
        cout << "--------------------------------------------------" << endl << endl << " Ingrese tiempo y fecha de inicio de partida para continuar" << endl << endl;
        cout << " Ingrese la hora en el siguiente orden: horas, minutos, segundos" << endl << endl << " ";
        cin >> perfiles[perfilActual].partidasPerfil[perfiles[perfilActual].partidasJugadas].horaComienzoPartida.hora;
        cout << endl << " ";
        cin >> perfiles[perfilActual].partidasPerfil[perfiles[perfilActual].partidasJugadas].horaComienzoPartida.minutos;
        cout << endl << " ";
        cin >> perfiles[perfilActual].partidasPerfil[perfiles[perfilActual].partidasJugadas].horaComienzoPartida.segundos;
        cout << endl << " ";
        cout << "Ahora ingrese la fecha en el siguiente orden: dia, mes, año" << endl << endl << " ";
        cin >>perfiles[perfilActual].partidasPerfil[perfiles[perfilActual].partidasJugadas].fechaComienzoPartida.dia;
        cout << endl << " ";
        cin >>perfiles[perfilActual].partidasPerfil[perfiles[perfilActual].partidasJugadas].fechaComienzoPartida.mes;
        cout << endl << " ";
        cin >>perfiles[perfilActual].partidasPerfil[perfiles[perfilActual].partidasJugadas].fechaComienzoPartida.anio;
        cout << endl << " ";
        cout << " Datos ingresados con éxito" << endl << endl << "--------------------------------------------------" << endl << endl;
        funcionCualquierTecla();
    }
    if(verificarTablero()!=1 && verificarTablero()!=2){
        while(!volverAlMenu && verificarTablero()!=1 && verificarTablero()!=2){
            system("clear");
            if(moverHacia!='1' && moverHacia!='2' && moverHacia!='3' && huboCambio(tableroPrevio) && !primerTurno){
               generarNumero();
            }
            mostrarTablero();
            indicarMovimiento(tableroPrevio, moverHacia);
            if(primerTurno){
                cin >> moverHacia;
                if(moverHacia=='2'){
                    do{
                        cout << "El poder volver atrás no se puede usar este turno" << endl;
                        cin >> moverHacia;
                    } while(moverHacia=='2');
                }
            }
            if(!primerTurno){
                cin >> moverHacia;
            }
            if (moverHacia=='w' || moverHacia=='a' || moverHacia=='s' || moverHacia=='d'){
                for (i = 0; i <= 3; i++){
                    for (j = 0; j <= 3; j++){
                        tableroPrevio[i][j]=tablero[i][j];
                    }
                }
            }
            mover(moverHacia, tableroPrevio);
            primerTurno=false;
        }
    }
    if(verificarTablero()==1){
        system("clear");
        cout << "-------------------------------------------------" << endl << endl <<"       Lograste formar 2048, ¡ganaste!" << endl << endl << "        Tu puntaje final fue:  <" << perfiles[perfilActual].puntajeActual << ">" << endl << endl << " Puedes empezar una nueva partida desde el menú" << endl << endl << "-------------------------------------------------" << endl << endl;
        funcionCualquierTecla();
        perfiles[perfilActual].hayJuegoParaContinuar=true;
        guardarPuntajes();
        guardarTablero();
        mostrarMenu();
        return;
    }
    if(verificarTablero()==2){
        system("clear");
        cout << "-------------------------------------------------" << endl << endl << "      Te quedaste sin opciones, ¡perdiste!" << endl << endl << "        Tu puntaje final fue:  <" << perfiles[perfilActual].puntajeActual << ">" << endl << endl << " Puedes empezar una nueva partida desde el menú" << endl << endl << "-------------------------------------------------" << endl << endl;
        funcionCualquierTecla();
        perfiles[perfilActual].hayJuegoParaContinuar=true;
        guardarPuntajes();
        guardarTablero();
        mostrarMenu();
        return;
    }
    return;
}

// nuevoJuego restablece las variables relacionadas a puntaje y el tablero para dar paso al juego

void nuevoJuego(){
    system("clear");
    if(perfiles[perfilActual].hayJuegoParaContinuar){
        perfiles[perfilActual].partidasPerfil[perfiles[perfilActual].partidasJugadas].resultadoPartida=3;
        perfiles[perfilActual].partidasJugadas++;
    }
    if(!perfil){
        cout << "---------------------------------------------------" << endl << endl << "     Necesitas crear un perfil en estadisticas" << endl << endl << "---------------------------------------------------" << endl << endl;
        funcionCualquierTecla();
        mostrarMenu();
        return;
    }
    perfiles[perfilActual].puntajeActual=0;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            tablero[i][j]=0;
        }
    }
    perfiles[perfilActual].hayJuegoParaContinuar=false;
    continuar();
    return;
}

// Es la opción del menu que permite acceder a las reglas

void reglas(){
    char cualquierTecla=0;
    system("clear");
        cout << "----------------------------------------------------------------------------------------" << endl << 
        "|                                                                                      |" << endl << 
        "|                                       °Reglas°                                       |" << endl << 
        "|                                                                                      |" << endl << 
        "| Tienes un tablero de 4x4 donde se generan dos y cuatros de manera aleatoria, debes   |" << endl <<
        "| utilizar las teclas de movimiento w,a,s,d para mover los números en el tablero. Si   |" << endl <<
        "| dos números iguales se juntan, se sumarán. Tu objetivo es sumar 2048 en un espacio   |" << endl <<
        "| para ganar. Si se llena el tablero y no tienes posibilidad de mover, pierdes.        |" << endl <<
        "|                                                                                      |" << endl <<
        "| Además, tienes un set de poderes que puedes comprar con puntos obtenidos jugando.    |" << endl <<
        "| Estos poderes pueden usarse con 1, 2 y 3. Con uno usas un poder que genera un 248    |" << endl <<
        "| en el lugar del tablero que elijas. Con dos usas un poder que te vuelve un turno     |" << endl <<
        "| atrás, este poder es desbloqueable, por lo que, una vez que lo compres lo podrás usar|" << endl <<
        "| infinitas veces, aunque con cuidado, ¡porque reinicia el puntaje!. Con tres usas un  |" << endl <<
        "| poder que duplica todos los números que hayan en el tablero.                         |" << endl <<
        "|                                                                                      |" << endl <<
        "|                  °Ingresa cualquier caracter para volver al menú°                    |" << endl << 
        "|                                                                                      |" << endl << 
        "|                                                                                      |" << endl << 
        "----------------------------------------------------------------------------------------" << endl;
    cin >> cualquierTecla;
    mostrarMenu();
    return;
}

// estadisticas sirve para guardar o eliminar perfiles, puntajes y partidas. Es necesario un perfil para iniciar el juego

void estadisticas(){
    system("clear");
    cout << "---------------------------------------------------------------" << endl << endl << "                  °Selecciona una opción°" << endl << endl << "   1-Crear perfil" << endl << "   2-Listado de perfiles" << endl << "   3-Cargar perfil" << endl << "   4-Deshabilitar/habilitar perfil" << endl << "   5-Historial de partidas" << endl << endl << "   6-Volver al menú" << endl << endl << "---------------------------------------------------------------" << endl << endl;
    int seleccionarOpcion;
    char elegirOpcion;
    char cualquierTecla=0;
    cin >> elegirOpcion;
    if(elegirOpcion>=49 && elegirOpcion<=54){
        seleccionarOpcion=elegirOpcion-48;
    }
    if(seleccionarOpcion==6){
        mostrarMenu();
        return;
    } else {
        guardarTablero();
        if(seleccionarOpcion==1){
            for(int i=19; i>=0; i--){
                if(perfiles[i].nombre=="*"){
                    perfilActual=i;
                }
            }
            system("clear");
            cout << "---------------------------------------------" << endl << endl << " Establece un nombre, un apellido, un alias y una fecha de nacimiento" << endl << endl << "---------------------------------------------" << endl << endl;
            cout << " Ingresa un nombre" << endl << endl << " ";
            cin >> perfiles[perfilActual].nombre;
            cout << endl;
            cout << " Ingresa un apellido" << endl << endl << " ";
            cin >> perfiles[perfilActual].apellido;
            cout << endl;
            cout << " Ingresa un alias" << endl << endl << " ";
            bool distintoAfuera;
            do{
                distintoAfuera=true;
                cin >> perfiles[perfilActual].alias;
                for(int j=(perfilActual+1); j<20; j++){
                    if(perfiles[perfilActual].alias==perfiles[j].alias || perfiles[perfilActual].alias==perfilesDeshabilitados[j].alias){
                        distintoAfuera=false;
                        cout << " Ya existe un usuario con ese alias" << endl << " ";
                    }
                }
                for(int j=0; j<(perfilActual); j++){
                    if(perfiles[perfilActual].alias==perfiles[j].alias || perfiles[perfilActual].alias==perfilesDeshabilitados[j].alias){
                        distintoAfuera=false;
                        cout << " Ya existe un usuario con ese alias" << endl << " ";
                    }
                }
            }while(!distintoAfuera);
            cout << endl;
            cout << " Ingresa tu fecha de nacimiento: día/mes/año" << endl << endl << " ";
            cin >> perfiles[perfilActual].nacimiento.dia;
            cout << " ";
            cin >> perfiles[perfilActual].nacimiento.mes;
            cout << " ";
            cin >> perfiles[perfilActual].nacimiento.anio;
            perfiles[perfilActual].hayJuegoParaContinuar=false;
            perfil=true;
            system("clear");
            cout << "-------------------------------------------------------------------------------" << endl << endl << " El perfil " << perfiles[perfilActual].alias << " tiene una puntuación máxima de " << perfiles[perfilActual].puntajeMaximo << " y ha sido creado y cargado con éxito" << endl << endl << "-------------------------------------------------------------------------------" << endl << endl;
            cantPerfilesHabilitados++;
            funcionCualquierTecla();
            cargarTablero();
            mostrarMenu();
            return;
        }
        if(seleccionarOpcion==2){
            system("clear");
            cout << "--------------------------------" << endl << endl << " °Lista de perfiles°" << endl;
            for(int i=0; i<20; i++){
                if(perfiles[i].nombre!="*"){
                    cout << endl << " --------- PERFIL " << (i+1) << " ---------" << endl << " Nombre: " << perfiles[i].nombre << endl << " Apellido: " << perfiles[i].apellido << endl << " Alias: " << perfiles[i].alias << endl << " Fecha de nacimiento: " << perfiles[i].nacimiento.dia << "/" << perfiles[i].nacimiento.mes << "/" << perfiles[i].nacimiento.anio <<  endl << " Puntaje maximo: " << perfiles[i].puntajeMaximo << endl << " ----------------------------" << endl;
                }
            }
            cout << endl << endl << endl;
            funcionCualquierTecla();
            estadisticas();
            return;
        }
        if(seleccionarOpcion==3){
            system("clear");
            cout << "--------------------------------------------------------------------------" << endl << endl << " Elige el perfil que deseas cargar" << endl << endl;
            for(int i=0; i<20; i++){
                if(perfiles[i].nombre!="*"){
                    cout << " ----- PERFIL " << (i+1) << " -----" << endl << " Nombre: " << perfiles[i].nombre << endl << " Apellido: " << perfiles[i].apellido << endl << " Alias: " << perfiles[i].alias << endl << " Puntaje maximo: " << perfiles[i].puntajeMaximo << endl << "------------------" << endl; 
                }
            }
            cout << endl << " Selecciona un perfil para volver a estadísticas" << endl << endl << "--------------------------------------------------------------------------" << endl << endl;
            int seleccionar=0;
            cin >> seleccionar;
            if(perfiles[seleccionar-1].nombre!="*"){
                perfilActual=seleccionar-1;
                perfil=true;
                cargarTablero();
                cout << "----------------------------------------------" << endl << "El perfil ha sido cargado con éxito" << endl << "----------------------------------------------" << endl;
            } else {
                cout << "----------------------------------------------" << endl << "El perfil seleccionado no existe" << endl << "----------------------------------------------" << endl;
            }
            funcionCualquierTecla();
            estadisticas();
            return;
        }
        if(seleccionarOpcion==4){
            system("clear");
            char opcionTemp;
            cout << "----------------------------------------" << endl << endl << " 1-Habilitar un perfil deshabilitado" << endl << " 2-Deshabilitar un perfil habilitado" << endl << endl << " 3-Volver a estadisticas" << endl << endl << "----------------------------------------" << endl << endl;
            while(opcionTemp!='1' && opcionTemp!='2' && opcionTemp!='3'){
                cin >> opcionTemp;
            }
            if(opcionTemp=='3'){
                system("clear");
                estadisticas();
                return;
            }
            if(opcionTemp=='2'){
                system("clear");
                int eliminarTemp=21;
                for(int i=0; i<20; i++){
                    if(perfiles[i].nombre!="*"){
                        cout << " ----- PERFIL " << (i+1) << " -----" << endl << " Nombre: " << perfiles[i].nombre << endl << " Apellido: " << perfiles[i].apellido << endl << " Alias: " << perfiles[i].alias << endl << " Fecha de nacimiento: " << perfiles[i].nacimiento.dia << "/" << perfiles[i].nacimiento.mes << "/" << perfiles[i].nacimiento.anio << endl << " Puntaje maximo: " << perfiles[i].puntajeMaximo << endl << endl; 
                    }
                }
                cout << endl << " Selecciona un perfil para volver a estadísticas" << endl << endl << "--------------------------------------------------------------------------" << endl << endl;
                while(eliminarTemp<1 || eliminarTemp>20){
                    cin >> eliminarTemp;
                }
                eliminarTemp--;
                if(perfiles[eliminarTemp].nombre=="*" || perfiles[eliminarTemp].nombre==""){
                    cout << " El perfil elegido no existe" << endl;
                    funcionCualquierTecla();
                    estadisticas();
                    return;
                }
                perfilesDeshabilitados[cantPerfilesDeshabilitados]=perfiles[eliminarTemp];
                perfilActual=21;
                cantPerfilesHabilitados--;
                cantPerfilesDeshabilitados++;
                perfil=false;
                perfiles[eliminarTemp].nombre="*";
                for(int i=0; i<20; i++){
                    if(perfiles[i].nombre=="*" && perfiles[i+1].nombre!="*"){
                        perfiles[i]=perfiles[i+1];
                        perfiles[i+1].nombre="*";
                    }
                }
                cout << endl << "----------------------------------------------" << endl << "El perfil ha sido deshabilitado con éxito" << endl << "----------------------------------------------" << endl;
                funcionCualquierTecla();
                estadisticas();
                return;
            }
            if(opcionTemp=='1'){
                system("clear");
                int eliminarTemp2=21;
                for(int i=0; i<20; i++){
                    if(perfilesDeshabilitados[i].nombre!="*"){
                        cout << " ----- PERFIL " << (i+1) << " -----" << endl << " Nombre: " << perfilesDeshabilitados[i].nombre << endl << " Apellido: " << perfilesDeshabilitados[i].apellido << endl << " Alias: " << perfilesDeshabilitados[i].alias << endl << " Fecha de nacimiento: " << perfilesDeshabilitados[i].nacimiento.dia << "/" << perfilesDeshabilitados[i].nacimiento.mes << "/" << perfilesDeshabilitados[i].nacimiento.anio << endl << " Puntaje maximo: " << perfilesDeshabilitados[i].puntajeMaximo << endl << endl << " Este perfil está deshabilitado" << endl; 
                    }
                }
                cout << endl << " Selecciona un perfil para volver a estadísticas" << endl << endl << "--------------------------------------------------------------------------" << endl << endl;
                while(eliminarTemp2<1 || eliminarTemp2>20){
                    cin >> eliminarTemp2;
                }
                eliminarTemp2--;
                if(cantPerfilesHabilitados>=20){
                    cout << "---------------------------------------------------" << endl << endl << "Cantidad máxima de perfiles habilitados alcanzada" << endl << endl << "---------------------------------------------------" << endl << endl;
                    funcionCualquierTecla();
                    estadisticas();
                    return;
                }
                if(perfilesDeshabilitados[eliminarTemp2].nombre=="*" || perfilesDeshabilitados[eliminarTemp2].nombre==""){
                    cout << " El perfil elegido no existe" << endl;
                    funcionCualquierTecla();
                    estadisticas();
                    return; 
                }
                perfiles[cantPerfilesHabilitados]=perfilesDeshabilitados[eliminarTemp2];
                perfilActual=cantPerfilesHabilitados;
                cantPerfilesHabilitados++;
                cantPerfilesDeshabilitados--;
                perfilesDeshabilitados[eliminarTemp2].nombre="*";
                for(int i=0; i<20; i++){
                    if(perfilesDeshabilitados[i].nombre=="*" && perfilesDeshabilitados[i+1].nombre!="*"){
                        perfilesDeshabilitados[i]=perfilesDeshabilitados[i+1];
                        perfilesDeshabilitados[i+1].nombre="*";
                    }
                }
                perfil=true;
                cout << endl << "----------------------------------------------" << endl << "El perfil ha sido habilitado con éxito" << endl << "----------------------------------------------" << endl;
                funcionCualquierTecla();
                estadisticas();
                return;
            }
            funcionCualquierTecla();
            estadisticas();
            return;
        }
        if(seleccionarOpcion==5){
            system("clear");
            char opcion;
            string introduccion1;
            string buscarDia, buscarMes, buscarAnio;
            int cantidadPartidas=0;
            cout << "--------------------------------------" << endl << " 1-Filtrar partidas por usuario" << endl << endl << " 2-Filtrar partidas por fecha" << endl << endl << " 3-Mostrar todas las partidas jugadas" << endl << "--------------------------------------" << endl << endl << " " ;
            do{
                cin >> opcion;
            }while(opcion!='1' && opcion!='2' && opcion!='3');
            if (opcion == '1'){
                system("clear");
                cout << " Ingrese el alias del usuario" << endl << endl << " ";
                cin >> introduccion1;
                cantidadPartidas=0;
                system("clear");
                for (int i=0; i<20; i++){
                    if (perfiles[i].alias==introduccion1 && perfiles[i].nombre!="*"){
                        cout << endl << " ------------------------- PERFIL " << (i+1) << " -------------------------" << endl;
                        for(int j=0; j<20; j++){
                            if(perfiles[i].partidasPerfil[j].resultadoPartida!=0 && perfiles[i].partidasPerfil[j].fechaComienzoPartida.dia!=""){
                                cout << " Resultado de la partida número " << (cantidadPartidas+1) << " fue: ";
                                if(perfiles[i].partidasPerfil[j].resultadoPartida==1){
                                    cout << "Victoria" << endl;
                                }
                                if(perfiles[i].partidasPerfil[j].resultadoPartida==2){
                                    cout << "Derrota" << endl;
                                }
                                if(perfiles[i].partidasPerfil[j].resultadoPartida==3){
                                    cout << "Abortó" << endl;
                                }
                                cout << " Esta partida se jugó en la hora " << perfiles[i].partidasPerfil[j].horaComienzoPartida.hora << ":" << perfiles[i].partidasPerfil[j].horaComienzoPartida.minutos << ":" << perfiles[i].partidasPerfil[j].horaComienzoPartida.segundos << ", del día " << perfiles[i].partidasPerfil[j].fechaComienzoPartida.dia << "/" << perfiles[i].partidasPerfil[j].fechaComienzoPartida.mes << "/" << perfiles[i].partidasPerfil[j].fechaComienzoPartida.anio << endl << endl;
                                cantidadPartidas++;
                            }
                        }
                    cout << " ------------------------------------------------------------" << endl;
                    }
                }
            funcionCualquierTecla();
            estadisticas();
            return;
            }
            if (opcion == '2'){
                cantidadPartidas=0;
                cout << " Ingrese la fecha en el siguiente orden: dia, mes, año" << endl << endl << " ";
                cin >> buscarDia;
                cout << " ";
                cin >> buscarMes;
                cout << " ";
                cin >> buscarAnio;
                system("clear");
                for (int i=0; i<20; i++){
                    if (perfiles[i].nombre!="*"){
                        for (int j=0; j<100; j++){
                            if(perfiles[i].partidasPerfil[j].fechaComienzoPartida.dia==buscarDia && perfiles[i].partidasPerfil[j].fechaComienzoPartida.mes==buscarMes && perfiles[i].partidasPerfil[j].fechaComienzoPartida.anio==buscarAnio){
                                cout << " ------------------------------------------------------------" << endl;
                                if(perfiles[i].partidasPerfil[j].resultadoPartida!=0 && perfiles[i].partidasPerfil[j].fechaComienzoPartida.dia!=""){
                                    cout << " Resultado de la partida número " << (cantidadPartidas+1) << " fue: ";
                                    if(perfiles[i].partidasPerfil[j].resultadoPartida==1){
                                        cout << "Victoria" << endl;
                                    }
                                    if(perfiles[i].partidasPerfil[j].resultadoPartida==2){
                                        cout << "Derrota" << endl;
                                    }
                                    if(perfiles[i].partidasPerfil[j].resultadoPartida==3){
                                        cout << "Abortó" << endl;
                                    }
                                    cout << " Esta partida se jugó en la hora " << perfiles[i].partidasPerfil[j].horaComienzoPartida.hora << ":" << perfiles[i].partidasPerfil[j].horaComienzoPartida.minutos << ":" << perfiles[i].partidasPerfil[j].horaComienzoPartida.segundos << ", del día " << perfiles[i].partidasPerfil[j].fechaComienzoPartida.dia << "/" << perfiles[i].partidasPerfil[j].fechaComienzoPartida.mes << "/" << perfiles[i].partidasPerfil[j].fechaComienzoPartida.anio << endl << endl;
                                    cantidadPartidas++;
                                }
                            }
                        }
                        cout << " ------------------------------------------------------------" << endl;
                    }
                }
            funcionCualquierTecla();
            estadisticas();
            return;
            }
            if (opcion == '3'){
                system("clear");
                cantidadPartidas=0;
                for(int i=0; i<20; i++){
                    if(perfiles[i].nombre!="*"){
                        cout << endl << " ------------------------- PERFIL " << (i+1) << " -------------------------" << endl;
                        cout << " Alias del jugador: " << perfiles[i].alias << endl << endl;
                        for(int j=0; j<20; j++){
                            if(perfiles[i].partidasPerfil[j].resultadoPartida!=0 && perfiles[i].partidasPerfil[j].fechaComienzoPartida.dia!=""){
                                cout << " Resultado de la partida número " << (cantidadPartidas+1) << " fue: ";
                                if(perfiles[i].partidasPerfil[j].resultadoPartida==1){
                                    cout << "Victoria" << endl;
                                }
                                if(perfiles[i].partidasPerfil[j].resultadoPartida==2){
                                    cout << "Derrota" << endl;
                                }
                                if(perfiles[i].partidasPerfil[j].resultadoPartida==3){
                                    cout << "Abortó" << endl;
                                }
                                cout << " Esta partida se jugó en la hora " << perfiles[i].partidasPerfil[j].horaComienzoPartida.hora << ":" << perfiles[i].partidasPerfil[j].horaComienzoPartida.minutos << ":" << perfiles[i].partidasPerfil[j].horaComienzoPartida.segundos << ", del día " << perfiles[i].partidasPerfil[j].fechaComienzoPartida.dia << "/" << perfiles[i].partidasPerfil[j].fechaComienzoPartida.mes << "/" << perfiles[i].partidasPerfil[j].fechaComienzoPartida.anio << endl << endl;
                                cantidadPartidas++;
                            }
                        }
                    cout << " ------------------------------------------------------------" << endl;
                    }
                }
            cout << endl << endl;
            funcionCualquierTecla();
            estadisticas();
            return;
            }
        }
    }
    if(seleccionarOpcion>6 || seleccionarOpcion<1){
        cout << "Introduzca un valor correcto" << endl << "Pulsa cualquier tecla para volver a intentarlo" << endl;
        cin >> cualquierTecla;
        estadisticas();
        return;
    }
}

// menu es la lógica del menu principal

void menu(){
    if(primeraEjecucion){
        for(int i=0; i<21; i++){
            perfiles[i].nombre="*";
            perfilesDeshabilitados[i].nombre="*";
        }
    }
    primeraEjecucion=false;
    char introduccion=0;
    bool introduccionCorrecta=false;
    mostrarMenu();
    while(!introduccionCorrecta){
        cin >> introduccion;
        switch (introduccion){
            case '1':
            nuevoJuego();
            break;
            case '2':
            continuar();
            break;
            case '3':
            estadisticas();
            break;
            case '4':
            reglas();
            break;
            case '5':
            tiendaPowerUps();
            break;
            case '6':
            return;
            break;
            default:
            system("clear");
            mostrarMenu();
            break;
        }
    }
}

int main(){
    menu();
}
