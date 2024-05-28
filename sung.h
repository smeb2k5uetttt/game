#ifndef SUNG_H
#define SUNG_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

class sung
{
protected:
    int mau  ;
    int i = 0;
    int k = 0;
    SDL_Texture *plant;
    int giatri;
    SDL_Rect pos;
    int hang;
    SDL_Rect vitridan;
    int vtdanbandau;
    bool tralaivitritrongcay = true ;
public:
    void ban(); // ham de ban sung
    sung(string s);
    void render();
    void setmau(int a) ;
    void setpos(int x, int y, int w, int h);
    int getposX();
    void sethang(int _hang);
    int gethang();
    void setvtdan(int x, int y);
    void matmau(int dame);
    bool hetmau() ;
    int getmau() ;
    void tralaivitrim() ;
    bool checkcheck() ;
};

#endif // SUNG_H
