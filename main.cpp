//
//Created by mango on 25/11/2021.
//

#include "senku.h"
#include <iostream>
using namespace std;

#define frances 1
#define aleman 2
#define asimetrico 3
#define ingles 4
#define diamante 5
#define triangular 6

string menu =
        "   Menu - Juego Senku   \n"
        "------------------------\n"
        "1. Estilo frances\n"
        "2. Estilo aleman\n"
        "3. estilo asimetrico\n"
        "4. estilo ingles\n"
        "5. estilo diamante\n"
        "6. estilo triangular\n"
        "------------------------\n"
        "0. Salir del programa\n";

int main() {
    int opt ;
    Senku *senku;

    cout << menu;
    cout << "Seleccionar la opcion:";
    cin >> opt ;

    switch (opt) {
        case 0:{
            return 0;
            break;
        }
        case frances:{
            senku = new SFrances();
            break;
        }
        case aleman:{
            senku = new SAleman(); // Aleman_t
            break;
        }
        case asimetrico:{
            senku = new SAsimetrico();
            break;
        }
        case ingles:{
            senku = new SIngles();
            break;
        }
        case diamante:{
            senku = new SDiamante();
            break;
        }
        case triangular:{
            senku = new STriangular();
            break;
        }

    }

    senku->show();

    do{
        int i,j,i2,j2;
        cout << "Ingrese la posicion de origen (fila, columna):";cin >> i >> j;
        cout << "Ingrese la posicion de destino (fila, columna):";cin >> i2 >> j2;
        bool can_move = senku->move(i-1,j-1,i2-1,j2-1);
        if (can_move){
            cout << "puede moverse.\n";
        }else{
            cout << " No puede moverse.\n";

        }
        senku->show();
    }while (senku->isPlaying());
    bool win_or_lose = senku->win_or_lose();
    //cout << "win_or_lose: " << win_or_lose << '\n';
    if(win_or_lose){
        cout << "Ganaste! :)";
    }else{
        cout << "Perdiste! :(";
    }

    return 0;
}
