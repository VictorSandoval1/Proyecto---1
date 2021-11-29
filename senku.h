//
// Created by mango on 25/11/2021.
//

#ifndef SENKU_SENKU_H
#define SENKU_SENKU_H

#include <iostream>

using namespace std;

#define alive 1
#define death -1
#define blank 0

class Piece {
private:
    int x,y;
    int status;
public:
    Piece(int x, int y, int status) : x(x), y(y), status(status) {}

    int getX() const {
        return x;
    }

    void setX(int x) {
        Piece::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        Piece::y = y;
    }

    int getStatus() const {
        return status;
    }

    void setStatus(int status) {
        Piece::status = status;
    }

};

class Senku {
protected:
    int rows, columns;
    Piece** board;
    int mov_size = 4;
    int movements[8][2] = {{0,2},{0,-2},{2,0},{-2,0},{2,2},{2,-2},{-2,2},{-2,-2}};
    int inner_movements[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};


public:
    Senku()= default;

    bool move(int x, int y, int x2, int y2, bool move = true){
        //valida que este dentro del tablero
        if (x<0 || x>rows-1 || x2<0 || x>rows-1 || y<0 || y>columns-1 || y2<0 || y2>columns-1)
            return false;
        // si la pieza (x,y) que quiero mover no esta viva el movimiento es invalido
        if (board[x+y*columns]->getStatus() != alive)
            return false;

        for (int i = 0; i < mov_size; ++i) {
            // la pieza (x2,y2) a la que me quiero mover es un lugar valido
            if( (x+movements[i][0]==x2) && (y+movements[i][1]==y2) ){
                int inerX = x+inner_movements[i][0];
                int inerY = y+inner_movements[i][1];
                // me aseguro que la pieza a la que voy a saltar este muerta y que halla un pieza viva en medio
                if (board[x2+y2*columns]->getStatus()==death && board[inerX+inerY*columns]->getStatus()==alive){
                    if (move){
                        board[x+y*columns]->setStatus(death);
                        board[inerX+inerY*columns]->setStatus(death);
                        board[x2+y2*columns]->setStatus(alive);
                    }
                    return true;
                }
            }
        }
        return false;
    }

    bool isPlaying(){
//        cout << "entra a playing";
        // devuelve "true" si alguna pieza se puede mover, "false" si no
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                for (int k=0; k<mov_size; k++) {
                    bool can_move = move(i,j,i+movements[k][0],j+movements[k][1],false);
                    if (can_move) // si hay piezas que se pueden mover entonces todavia no se pierde ni se gana
                        return true;
                }
            }
        }
        return false;
    }

    bool win_or_lose(){ // 1 si ganamos 0 si perdimos
//        cout << "entra a win or lose";
        int count=0; // si hay más de una pieza viva entonces perdimos
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i + j * columns]->getStatus() == alive) { count++; }
            }
        }
        if (count==1)
            return 1;
        return 0;
    }

    void show(){
        cout << "   ";
        for (int i = 0; i < columns; ++i) {
            cout << i+1 << "  " ;
        }
        cout << '\n';
        for (int i = 0; i < rows; ++i) {
            cout << i+1 << "  ";
            for (int j = 0; j < columns; ++j) {
                switch (board[i+j*columns]->getStatus()) {
                    case alive:{
                        cout << "0";
                        break;
                    }
                    case death:{
                        cout << "+";
                        break;
                    }
                    case blank:{
                        cout << " ";
                        break;
                    }
                    default:{
                        cout << board[i+j*columns]->getStatus();
                        break;
                    }
                }
                cout << "  ";
            }
            cout << "\n";
        }
    }

};

class SAleman: public Senku{ // --> Por herencia
public:
    SAleman() {
        rows=9;
        columns=9;
        int brd[10][10] = {
                {0,0,0,1,1,1,0,0,0},
                {0,0,0,1,1,1,0,0,0},
                {0,0,0,1,1,1,0,0,0},
                {1,1,1,1,1,1,1,1,1},
                {1,1,1,1,-1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1},
                {0,0,0,1,1,1,0,0,0},
                {0,0,0,1,1,1,0,0,0},
                {0,0,0,1,1,1,0,0,0}
        };

        board = new Piece*[rows*columns];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i+j*columns]= new Piece(i,j,brd[i][j]);

    }
};

class SIngles: public  Senku{
public:
    SIngles(){
        rows=7;
        columns=7;
        int brd[7][7] = {
                {0,0,1,1,1,0,0},
                {0,0,1,1,1,0,0},
                {1,1,1,1,1,1,1},
                {1,1,1,-1,1,1,1},
                {1,1,1,1,1,1,1},
                {0,0,1,1,1,0,0},
                {0,0,1,1,1,0,0},
        };
        board = new Piece*[rows*columns];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i+j*columns]= new Piece(i,j,brd[i][j]);
    }
};

class SFrances: public  Senku{
public:
    SFrances(){
        rows=7;
        columns=7;
        int brd[7][7] = {
                {0,0,1,1,1,0,0},
                {0,1,1,1,1,1,0},
                {1,1,1,-1,1,1,1},
                {1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1},
                {0,1,1,1,1,1,0},
                {0,0,1,1,1,0,0},
        };
        board = new Piece*[rows*columns];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i+j*columns]= new Piece(i,j,brd[i][j]);
    }
};

class SDiamante: public  Senku{
public:
    SDiamante(){
        rows=9;
        columns=9;
        int brd[9][9] = {
                {0,0,0,0,1,0,0,0,0},
                {0,0,0,1,1,1,0,0,0},
                {0,0,1,1,1,1,1,0,0},
                {0,1,1,1,1,1,1,1,0},
                {1,1,1,1,-1,1,1,1,1},
                {0,1,1,1,1,1,1,1,0},
                {0,0,1,1,1,1,1,0,0},
                {0,0,0,1,1,1,0,0,0},
                {0,0,0,0,1,0,0,0,0},
        };
        board = new Piece*[rows*columns];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i+j*columns]= new Piece(i,j,brd[i][j]);
    }
};

class STriangular: public  Senku{
public:
    STriangular(){
        rows=9;
        columns=9;
        mov_size = 8;
        int brd[9][9] = {
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,-1,0,0,0,0},
                {0,0,0,1,0,1,0,0,0},
                {0,0,1,0,1,0,1,0,0},
                {0,1,0,1,0,1,0,1,0},
                {1,0,1,0,1,0,1,0,1},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0}
        };
        board = new Piece*[rows*columns];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i+j*columns]= new Piece(i,j,brd[i][j]);
    }
};

class SAsimetrico: public  Senku{
public:
    SAsimetrico(){
        rows=8;
        columns=8;
        int brd[8][8] = {
                {0,0,1,1,1,0,0,0},
                {0,0,1,1,1,0,0,0},
                {0,0,1,1,1,0,0,0},
                {1,1,1,1,1,1,1,1},
                {1,1,1,-1,1,1,1,1},
                {1,1,1,1,1,1,1,1},
                {0,0,1,1,1,0,0,0},
                {0,0,1,1,1,0,0,0},
        };
        board = new Piece*[rows*columns];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i+j*columns]= new Piece(i,j,brd[i][j]);
    }
};

#endif //SENKU_SENKU_H