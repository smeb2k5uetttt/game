#include <iostream>
#include <sstream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <map>
#include "sung.h"
using namespace std ;
#define pb push_back
int wdW = 1000 ;
int wdH = 600 ;
int vtStorex = 880 ;
int vtStorey = 490;
int kc = 35;
int diem = 0 ;
int kiluc ;
bool lose = false ;
SDL_Point re[26] ;
SDL_Texture * danlua = NULL ;
SDL_Texture *pic[4] ;
SDL_Texture *danxanh = NULL ;
SDL_Texture* danphao = NULL ;
Mix_Music * nhacnen = NULL;
Mix_Chunk *tiengcao = NULL;
Mix_Chunk* tiengphao = NULL ;
Mix_Chunk* tienglua = NULL ;
class sung ;
class monster;
map<pair<int, int>, int> m ;
ifstream hs ;
ofstream hss ;
void ktaongare()
{
    re[1] = {180 , 100} ;
    re[2] = {280 , 100} ;
    re[3] = {280 , 150} ;
    re[4] = {375 , 150} ;
    re[5] = {375 , 35} ;
    re[6] = {590 , 35} ;
    re[7] = {590 , 95} ;
    re[8] = {700 , 95} ;
    re[9] = {700 , 210} ;
    re[10] = {180 , 280} ;
    re[11] = {230 , 280} ;
    re[12] = {430 , 280} ;
    re[13] = {430 , 335} ;
    re[14] = {590 , 335} ;
    re[15] = {590 , 390} ;
    re[16] = {800 , 390} ;
    re[17] = {800 , 210} ;
    re[18] = {65 , 335} ;
    re[19] = {65 , 390} ;
    re[20] = {230 , 390} ;
    re[21] = {280 , 390} ;
    re[22] = {280 , 455} ;
    re[23] = {375 , 455} ;
    re[24] = {375 , 390} ;
    re[25] = {430 , 390} ;
}
//dinhdan
TTF_Font* font = NULL;
SDL_Color mau = {255, 0 ,0 } ;
int gold = 0 ;
SDL_Window * MAINWD = NULL ;
SDL_Renderer * rd = nullptr ;
void taoanhquaivat()
{
    SDL_Surface * sf = IMG_Load("mm1.png") ;
    pic[0] = SDL_CreateTextureFromSurface(rd, sf) ;
    sf = IMG_Load("mm2.png") ;
    pic[1] = SDL_CreateTextureFromSurface(rd, sf) ;
    sf = IMG_Load("mm3.png") ;
    pic[2] = SDL_CreateTextureFromSurface(rd, sf) ;
    sf = IMG_Load("mm4.png") ;
    pic[3] = SDL_CreateTextureFromSurface(rd, sf) ;
    SDL_FreeSurface(sf) ;
}
class hang
{
    private :
        bool coqv ;
        int vitrigannhat  ;
        int vitrisunggannhat  ;
        int *cacqv = NULL ;
        sung *sunggannhat ;
        monster *qvgannhat ;
    public:
        int getvtgn();
        void setvtgn(int a);
        bool coqvat();
        void setqv();
        void reset();
        void setvtsunggn(int a );
        int getvtsgn();
        void setsunggn(sung *a) ;
        sung * sunggn() ;
        void setqvgn(monster* a ) ;
        monster *qvgn() ;
};

void hang::setqvgn(monster *a)
{
    qvgannhat = a ;
}
monster*hang:: qvgn()
{
    return qvgannhat;
}
sung* hang::sunggn()
{
   return sunggannhat ;
}
void hang:: setsunggn(sung *a)
{
    sunggannhat = a ;
}
int hang::getvtgn()
{
    return vitrigannhat ;
}
void hang::setvtgn(int a)
{
    vitrigannhat = a ;
    return ;
}
bool hang:: coqvat()
{
    return coqv ;
}
void hang::setqv()
{
    coqv = true ;
}
void hang:: reset()
{
    vitrigannhat = -500 ;
    coqv = false ;
    vitrisunggannhat = 5000 ;
    sunggannhat = NULL ;
    qvgannhat = NULL ;
}
void hang::setvtsunggn(int a )
{
    vitrisunggannhat = a ;
}
int hang::getvtsgn()
{
    return vitrisunggannhat ;
}
hang row[13] ;

class textture
{
    private://dame
        SDL_Texture * tt ;
        int cao , rong ;
    public:
        textture()  ;
        ~textture() ;
        int getcao() ;
        int getrong() ;
        bool loadanh(string s ) ;
        void render(int x , int y , int w , int h  ) ;
        void freechu() ;
        bool loadchu(int a) ;
        void free()
        {
            SDL_DestroyTexture(tt) ;
            tt = NULL ;
        }
};

void textture :: freechu()
{
    SDL_DestroyTexture(tt) ;
}
class button : public textture
{
    private:
        int x , y ;
        SDL_Point vt ;


    public:
        void xuly(SDL_Event e) ;
        void getvt(int x , int y)
        {
            vt.x = x ;
            vt.y = y ;
        }
};
class shopee : public textture
{
    public:
        bool on = false ;
        bool ok = false ;
        void muado() ;
};

class monster
{
    private:

        long long  mau = 5101 ;
        long long  maucu =5101;
        int speed = 1  ;
        int xx , yy ;
        SDL_Point pos0 ;
        int k ; int i  ,j ;
        int dame = 15 ;
        int damecu = 15 ;
        string tt ; // trang thai di chuyen ngang doc
    public:
        void movee() ;
        void render() ;
        monster(int input );
        SDL_Point getpos() ;
        // them ham vitrihang o day
        void vitrihang(monster *a);
        void dinhdan(long long  x ) ;
        void checksung() ;
        void setspeed()
        {
            speed = 1 ;
        }

        long long getmau() ;
};

long long monster::getmau()
{
    return mau ;
}
void monster:: dinhdan(long long x)
{
    if(x == -1)
    {
        mau = -1 ;
    }
    else
    {
        mau -= x ;
    }
    if(mau <=0)
    {
        gold += 1 ;
        diem += 1 ;
        cout << diem ;
        mau = maucu+ 4000 ;
        maucu = mau ;
        dame = damecu + 5;
        damecu = dame ;
        xx = -100;
        yy = (j ==1) ? 335 : 100 ;
        speed = 1 ;
    }
}
void monster :: checksung()
{
    if(mau > 0 )
    {
        if(xx >= 0 && xx <= 280 && yy == 100)
    {
        if(xx == row[1].getvtsgn()-kc)
        {
            if(row[1].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[1].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }

        }
        else
        {
            speed = 1 ;
        }
        return ;
    }
    if(xx >= 280 && xx <= 375 && yy == 150)
    {
        if(xx == row[2].getvtsgn()-kc)
        {
            if(row[2].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[2].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }
        }
        else
        {
            speed = 1 ;
        }
        return ;
    }
    if(xx >= 375  && xx <= 590 && yy == 35)
    {
        if(xx== row[3].getvtsgn() - kc)
        {
            if(row[3].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[3].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }

        }
        else
            {
                speed = 1 ;
            }
        return ;
    }
    if(xx >= 590 && xx <= 700 && yy == 95 )
    {
        if(xx == row[4].getvtsgn()-kc)
        {
            if(row[4].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[4].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }

        }
        else
            {//ban
                speed = 1 ;
            }
        return ;
    }
    if(xx >= 700 && xx <= 910 && yy == 210 )
    {
        if(xx == row[5].getvtsgn()-kc)
        {
            if(row[5].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[5].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }
        }
        else
            {
                speed = 1 ;
            }
        return ;
    }
    if(xx >= 590 && xx <= 800 && yy == 390)
    {
        if(xx == row[6].getvtsgn()-kc)
        {
            if(row[6].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[6].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }

        }
        else
        {
            speed = 1 ;
        }
        return ;
    }
    if(xx >= 430 && xx <= 590 && yy == 335)
    {
        if(xx == row[7].getvtsgn()-kc)
        {
            if(row[7].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[7].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }
        }
        else
            {
                speed = 1 ;
            }
        return ;
    }
    if(xx>= 375  && xx<= 430 && yy == 390)
    {
        if(xx == row[8].getvtsgn()-kc)
        {
            if(row[8].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[8].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }

        }
        else
            {
                speed = 1 ;
            }
        return ;
    }
    if(xx >= 280 && xx <= 375 && yy== 455)
    {
        if(xx == row[9].getvtsgn()-kc)
        {
            if(row[9].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[9].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }
        }
        else
            {
                speed = 1 ;
            }
        return ;
    }
    if(xx >= 65 && xx<= 280 && yy == 390)
    {
        if(xx== row[10].getvtsgn()-kc)
        {
            if(row[10].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[10].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }
        }
        else
            {
                speed = 1 ;
            }
        return ;
    }
    if(xx >= 180 && xx <= 430 && yy == 280)
    {
        if(xx == row[11].getvtsgn()-kc)
        {
            if(row[11].sunggn()->getmau() >=0)
            {
                speed = 0 ;
                row[11].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }
        }
        else
            {
                speed = 1 ;
            }
        return ;
    }
    if(xx>= 0 && xx <= 65 &&yy == 335)
    {
        if(xx == row[12].getvtsgn()-kc )
        {
            if(row[12].sunggn()->getmau() >= 0)
            {
                speed = 0 ;
                row[12].sunggn()->matmau(dame) ;
                Mix_PlayChannel( -1, tiengcao, 0 );
            }
        }
        else
            {
                speed = 1 ;
            }
        return ;
    }
    }
}
void monster :: vitrihang(monster *a)
{
    if(mau > 0 )
    {
        if(xx >= 0 && xx <= 280 && yy == 100)
    {
        row[1].setqv() ;
        if(xx > row[1].getvtgn())
        {
            row[1].setvtgn(xx) ;
            row[1].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 280 && xx <= 375 && yy == 150)
    {
        row[2].setqv() ;
        if(xx > row[2].getvtgn())
        {
            row[2].setvtgn(xx) ;
            row[2].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 375  && xx<= 590 && yy == 35)
    {
        row[3].setqv() ;
        if(xx > row[3].getvtgn())
        {
            row[3].setvtgn(xx) ;
            row[3].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 590 && xx <= 700 && yy == 95 )
    {
        row[4].setqv() ;
        if(xx > row[4].getvtgn())
        {
            row[4].setvtgn(xx) ;
            row[4].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 700 && xx <= 910 && yy == 210 )
    {
       row[5].setqv() ;
       if(xx > row[5].getvtgn())
        {
            row[5].setvtgn(xx) ;
            row[5].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 590 && xx<= 800 && yy == 390)
    {
        row[6].setqv() ;
        if(xx > row[6].getvtgn())
        {
            row[6].setvtgn(xx) ;
            row[6].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 430 && xx <= 590 && yy == 335)
    {
        row[7].setqv() ;
        if(xx > row[7].getvtgn())
        {
            row[7].setvtgn(xx) ;
            row[7].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 375  &&xx <= 430 && yy == 390)
    {
        row[8].setqv() ;
        if(xx > row[8].getvtgn())
        {
            row[8].setvtgn(xx) ;
            row[8].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 280 && xx <= 375 && yy == 455)
    {
        row[9].setqv() ;
        if(xx > row[9].getvtgn())
        {
            row[9].setvtgn(xx) ;
            row[9].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 65 && xx<= 280 && yy == 390)
    {
        row[10].setqv() ;
        if(xx > row[10].getvtgn())
        {
            row[10].setvtgn(xx) ;
            row[10].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 180 && xx <= 430 && yy == 280)
    {
        row[11].setqv() ;
        if(xx > row[11].getvtgn())
        {
            row[11].setvtgn(xx) ;
            row[11].setqvgn(a) ;
        }
        return ;
    }
    if(xx >= 0 && xx <= 65 && yy == 335)
    {
        row[12].setqv() ;
        if(xx > row[12].getvtgn())
        {
            row[12].setvtgn(xx) ;
            row[12].setqvgn(a) ;
        }
        return ;
    }
    }
}
//ham vi tri hang() ktaorow

void sung::matmau(int dame )
{
    mau -= dame ;
}
bool sung::checkcheck()
{
    return tralaivitritrongcay ;
}
bool sung::hetmau()
{
    return this->mau <= 0 ;
}
void sung::setmau(int a)
{
    mau = a ;
}
int sung::getposX()
{
    return pos.x ;
}
void sung:: setvtdan(int x , int y)
{
    vitridan.x = x ;
    vitridan.y = y ;
    vitridan.w = 40 ;
    vitridan.h = 20 ;
    vtdanbandau = x ;
}
int sung :: gethang()
{
    return hang ;
}
// matmau
void sung :: sethang(int _hang)
{
    hang = _hang ;
}
sung :: sung(string s )
{
    SDL_Surface* sf = IMG_Load(s.c_str()) ;
    plant = SDL_CreateTextureFromSurface(rd, sf) ;
    SDL_FreeSurface(sf) ;
}
int sung::getmau()
{
    return mau;
}
void sung:: setpos(int x , int y , int w ,int h )
{
    cout << x << " " << y << " " << w  << " " << h << endl ;
    pos.x = x ; pos.y = y ; pos.w = w ; pos.h = h ;
}
void sung :: render()
{
    SDL_RenderCopy(rd, plant ,NULL , &pos ) ;
}
void sung::tralaivitrim()
{
    for(int i = pos.x - 65 ; i <= pos.x + 65 ; i++)
    {
        for(int j = pos.y-20 ; j <= pos.y + 20 ; j++)
        {
            m[{i,j}] = 0 ;
        }
    }
    tralaivitritrongcay = false ;
}
class sunglua : public sung
{
    private:
        int tien =5 ;
    public:
        sunglua(string s ) : sung(s){
            cout << "SL" << endl;
        } ;
        void ban() ;
        bool dutien() ;
};
class sunggai : public sung
{
    private :
        int tien = 2 ;
    public:
        sunggai(string s ) : sung(s)
        {
            cout << "SG" <<endl ;
        } ;
        void ban() ;
        bool dutien() ;
};
class bongma : public sung
{
    private:
        int tien =3  ;
        int posx1 , posy1 ;
        int i = 0 ; int k = 0 ;

    public:
        bongma(string s ) : sung(s)
        {
            cout << "BM" <<endl ;
        } ;
        void ban() ;
        bool dutien() ;
        void setpos1(int x , int y ) ;
        void tralaivitrimm() ;
};
void bongma::setpos1(int x , int y )
{
    posx1 = x ; posy1 = y ;
}
void bongma :: tralaivitrimm()
{
    for(int i = posx1 - 65 ; i <= posx1 + 65 ; i++)
    {
        for(int j = posy1-20 ; j <= posy1 + 20 ; j++)
        {
            m[{i,j}] = 0 ;
        }
    }
    tralaivitritrongcay = false ;
}
class cotdinh : public sung
{
    private:
        int tien = 3 ;
    public:
        cotdinh(string s ) : sung(s)
        {
            cout << "CD" <<endl ;
        } ;
        void ban() ;
        bool dutien() ;
};

class sungphao : public sung
{
    private:
        int tien = 3 ;
    public:
        sungphao(string s ) : sung(s)
        {
            cout << "SP" <<endl ;
        } ;
        void ban() ;
        bool dutien() ;
};
bool sunglua :: dutien()
{
    if(gold >= tien) return true ;
    return false ;
}
bool sungphao:: dutien()
{
    if(gold >= tien ) return true ;
    return false ;
}
bool sunggai:: dutien()
{
    if(gold >= tien ) return true ;
    return false ;
}
bool bongma:: dutien()
{
    if(gold >= tien ) return true ;
    return false ;
}
bool cotdinh:: dutien()
{
    if(gold >= tien ) return true ;
    return false ;
}
void sunglua :: ban()
{
    if(pos.x > row[gethang()].getvtgn())
    {
        if(vitridan.x <= row[gethang()].getvtgn()+20)
        {
            vitridan.x = vtdanbandau ;
            int * dame = new int ;
            *dame = 6000 ;
            //cout << row[gethang()].qvgn()->getmau() << endl ;
            if(*dame >= row[gethang()].qvgn()->getmau())
            {
                *dame = -1 ;
            }
            row[gethang()].qvgn()->dinhdan(*dame) ;
            delete dame ;
        }
        if(vitridan.x == vtdanbandau)
        {
            Mix_PlayChannel( -1, tienglua, 0 );
        }
        SDL_RenderCopy(rd,danlua,NULL ,&vitridan ) ;

        if(i == 8  )
        {
            vitridan.x -=15 ;
            i = 0 ;
        }
        i++ ;
        return ;
    }
}
void sunggai :: ban()
{
    if(pos.x > row[gethang()].getvtgn())
    {
        if(vitridan.x <= row[gethang()].getvtgn()+20)
        {
            vitridan.x = vtdanbandau ;
            int * dame = new int ;
            *dame = 1000 ;
            //cout << row[gethang()].qvgn()->getmau() << endl ;
            if(*dame >= row[gethang()].qvgn()->getmau())
            {
                *dame = -1 ;
            }
            row[gethang()].qvgn()->dinhdan(*dame) ;
            delete dame ;
        }
        if(vitridan.x == vtdanbandau)
        {
            Mix_PlayChannel( -1, tienglua, 0 );
        }
        SDL_RenderCopy(rd,danxanh,NULL ,&vitridan ) ;

        if(i == 8  )
        {
            vitridan.x -=15 ;
            i = 0 ;
        }
        i++ ;
        return ;
    }
}
void sungphao :: ban()
{
    if(pos.x > row[gethang()].getvtgn())
    {
        if(vitridan.x <= row[gethang()].getvtgn()+20)
        {
            vitridan.x = vtdanbandau ;
            int *dame = new int ;
            *dame = 3000 ;
            //cout << row[gethang()].qvgn()->getmau() << endl ;
            if(*dame >= row[gethang()].qvgn()->getmau())
            {
                *dame = -1 ;
            }
            delete dame ;
            row[gethang()].qvgn()->dinhdan(*dame) ;
        }
        if(vitridan.x == vtdanbandau )
        {
            Mix_PlayChannel( -1, tiengphao, 0 );
        }
        SDL_RenderCopy(rd,danphao,NULL ,&vitridan ) ;

        if(i == 8  )
        {
            vitridan.x -=15 ;
            i = 0 ;
        }
        i++ ;
        return ;
    }
}
void bongma :: ban()
{
    if(pos.x > row[gethang()].getvtgn())
    {
        if(pos.x <= row[gethang()].getvtgn()+20)
        {
            mau = 0  ;
            row[gethang()].qvgn()->dinhdan(-1) ;
        }
        if(i == 20  )
        {
            pos.x -=15 ;
            i = 0;
        }
        i++ ;
        return ;
    }
}

void resetrow()
{
    for(int i = 1 ; i<= 12 ; i++ )
    {
        row[i].reset() ;
    }
}
textture map1 ;
textture youlose ;
textture kyluc ;
textture xu ;
textture chu ;
textture cupvang ;
button store ;
textture score;
shopee shop ;
textture picsunggai ; //a?nh sung' gai
textture picsungphao ;
textture picsunglua ;
textture piccotdinh ;
textture picbongma ;
textture fsl ;
textture fsg ;
textture fbm ;
textture fcd ;
textture fsp ;

//matmau
int x , y ; // vi tri chuot
vector<sunglua* > SL ;
vector<sungphao* > SP;
vector<cotdinh*> CD ;
vector<bongma* > BM  ;
vector<sunggai*> SG ;

 monster :: monster(int input)
{
    k = 0 ; i = 0 ;
    tt = "ngang" ;
    j = input ;
    if(j == 0 )
    {
        xx = -100 ;
        pos0.x = -100 ;
        yy =  100 ;
        pos0.y = 100 ;
    }
    else if(j ==1 )
    {
        xx = -100 ;
        yy = 335 ;
        pos0.x = -100 ;
        pos0.y = 335 ;
    }
}

bool checkpos(int &x , int &y, sung &a )
{
    if(m[{x,y}] == 0)
    {
        if(x >= 0 && x <= 280 && y >= 85 && y <= 125 )
        {
            y = 105 ;
            for(int i = x - 65 ; i <= x + 65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            if( x <row[1].getvtsgn())
            {
                row[1].setvtsunggn(x) ;
                sung* p = &a ;
            }
            a.sethang(1) ;
            return true  ;
        }
        else if(x>=325 && x <= 400 && y>=140 && y <=170)
        {
            y = 155 ;
            for(int i = x -65 ; i <= x + 65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            if( x <row[2].getvtsgn())
            {
                row[2].setvtsunggn(x) ;
                sung* p = &a ;
                //row[2].setsunggn(p ) ;
            }
            a.sethang(2) ;
            return true ;
        }
        else if(x>= 420 && x <= 615 && y >= 30 && y <= 55)
        {
            y = 40 ;
            for(int i = x - 65 ; i<= x+65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(3) ;
            if( x <row[3].getvtsgn())
            {
                row[3].setvtsunggn(x) ;
                sung* p = &a ;
                //row[3].setsunggn(p ) ;
            }
            return true ;
        }
        else if(x>=635 && x <=735 && y >=90 && y <= 115 )
        {
            y = 105 ;
            for(int i = x - 65 ; i <= x+65 ;i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(4) ;
            if( x <row[4].getvtsgn())
            {
                row[4].setvtsunggn(x) ;
                sung* p = &a ;
                //row[4].setsunggn(p ) ;
            }
            return true ;
        }
        else if(x>= 745 && x <= 950 && y >= 200 && y <= 230 )
        {
            y = 220 ;
            for(int i = x -65 ; i <= x +65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(5) ;
            if( x <row[5].getvtsgn())
            {
                row[5].setvtsunggn(x) ;
                sung* p = &a ;
                //row[5].setsunggn(p ) ;
            }
            return true ;
        }
        else if(x>= 635 && x <= 825 && y>=380 && y <= 410)
        {
            y = 400 ;
            for(int i = x -65 ; i <=x+65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(6) ;
            if( x <row[6].getvtsgn())
            {
                row[6].setvtsunggn(x) ;
                sung* p = &a ;
                //row[6].setsunggn(p ) ;
            }
            return true ;
        }
        else if(x>= 475 && x <= 615 && y >=320 && y <= 350 ) //13
        {
            y = 340 ;
            for(int i = x-65 ; i <= x+65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(7) ;
            if( x <row[7].getvtsgn())
            {
                row[7].setvtsunggn(x) ;
                sung* p = &a ;
                //row[7].setsunggn(p ) ;
            }
            return true ;
        }
        else if(x>=225 && x <=455 && y>= 265 && y <= 295)
        {
            y = 285 ;
            for(int i = x-65 ; i <= x+65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(11) ;
            if( x <row[11].getvtsgn())
            {
                row[11].setvtsunggn(x) ;
                sung* p = &a ;
                //row[1].setsunggn(p ) ;
            }
            return true ;
        }

        else if(x>=400 && x <=440 && y>= 375 && y <= 405)
        {
            x = 445 ;
            y = 400 ;
            for(int i = x-65 ; i <= x+65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(8) ;
            if( x <row[8].getvtsgn())
            {
                row[8].setvtsunggn(x) ;
                sung* p = &a ;
                //row[8].setsunggn(p ) ;
            }
            return true ;
        }
        else if(x>=325 && x <=400 && y>= 440 && y <= 460)
        {
            y = 455 ;
            for(int i = x-65 ; i <= x+65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(9) ;
            if( x <row[9].getvtsgn())
            {
                row[9].setvtsunggn(x) ;
                sung* p = &a ;
                //row[9].setsunggn(p ) ;
            }
            return true ;
        }
        else if(x>=110 && x <=305 && y>= 375 && y <= 405)
        {
            y = 395 ;
            for(int i = x-65 ; i <= x+65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(10) ;
            if( x <row[10].getvtsgn())
            {
                row[10].setvtsunggn(x) ;
                sung* p = &a ;
                //row[10].setsunggn(p ) ;
            }
            return true ;
        }
        else if(x>=0 && x <=90 && y>= 320 && y <= 350)
        {
            y = 340 ;
            for(int i = x-65 ; i <= x+65 ; i++)
            {
                for(int j = y-20 ; j <= y+20 ; j++)
                {
                    m[{i,j}] = 1 ;
                }
            }
            a.sethang(12) ;
            if( x <row[12].getvtsgn())
            {
                row[12].setvtsunggn(x) ;
                sung* p = &a ;
                //row[12].setsunggn(p ) ;
            }
            return true ;
        }
    }
    return false  ;
}

void monster :: movee()
{
    if(mau > 0 )
    {
        if(tt == "ngang")
    {
        if(k == 5 )
        {
            i++ ;
            k = 0 ;
            xx += speed  ;
        }
    }
    else if( tt == "docd")
    {
        if(k ==5)
        {
            i++;
            yy += speed  ;
            k = 0 ;
        }
    }
    else if(tt == "docu")
    {
        if(k ==5 )
        {
            i++;
            yy -= speed ;
            k = 0 ;
        }
    }
    if(xx >= 950)
    {
        lose = true ;
        return ;
    }
    for(int i = 1; i <= 25 ;i++)
    {
        if(xx == re[i].x && yy == re[i].y)
        {
            if(i == 1 )
            {
                int m = rand() % 2 ;
                if( m == 0)
                {
                    tt = "ngang";
                }
                else
                {
                    tt = "docd" ;
                }
            }
            else if( i ==2)
            {
                tt = "docd" ;
            }
            else if( i == 3 )
            {
                tt ="ngang" ;
            }
            else if( i== 4 )
            {
                tt = "docu" ;
            }
            else if( i == 5 )
            {
                tt = "ngang" ;
            }
            else if( i == 6)
            {
                tt = "docd" ;
            }
            else if( i == 7 )
            {
                tt = "ngang" ;
            }
            else if(i == 8 )
            {
                tt = "docd" ;
            }
            else if(i== 9 )
            {
                tt = "ngang" ;
            }
            else if(i == 17)
            {
                tt = "ngang" ;
            }
            else if( i == 16)
            {
                tt = "docu" ;
            }
            else if( i == 15)
            {
                tt = "ngang" ;
            }
            else if( i == 14)
            {
                tt = "docd" ;
            }
            else if( i == 13)
            {
                tt = "ngang" ;
            }
            else if( i == 12)
            {
                tt = "docd" ;
            }
            else if( i == 11)
            {
                int m = rand() % 2 ;
                if(m ==1)
                {
                    tt = "ngang" ;
                }
                else
                {
                    tt = "docd" ;
                }
            }
            else if( i == 10)
            {
                tt = "ngang" ;
            }
            else if( i == 18)
            {
                tt = "docd" ;
            }
            else if( i == 19)
            {
                tt = "ngang" ;
            }
            else if( i == 20)
            {
                int m = rand()%2 ;
                if(m==1)
                {
                    tt = "docu";
                }
                else
                {
                    tt ="ngang" ;
                }
            }
            else if( i == 21)
            {
                tt = "docd" ;
            }
            else if( i == 22)
            {
                tt = "ngang" ;
            }
            else if( i == 23)
            {
                tt = "docu" ;
            }
            else if( i == 24)
            {
                tt = "ngang" ;
            }
            else if( i == 25)
            {
                tt = "docu" ;
            }
        }
    }
    }
}
//hoisiinh
void monster:: render()
{
    if(mau > 0 )
    {
        SDL_Rect x = {xx, yy , 95 ,96 } ;
    SDL_RenderCopy(rd, pic[i/4] ,NULL , &x ) ;
    if(i >=16)
    {
        i= 0 ;
    }
    k++ ;
    }
}
bool init()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO |SDL_INIT_AUDIO ) < 0 )
	{
		cout <<  "ko khoi tao dc SDL " << SDL_GetError() << endl ;
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			cout << "loi sethind(sdl_hint_render " << endl ;
		}

		MAINWD = SDL_CreateWindow( "23021531 LE_HONG_DUC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wdW, wdH , SDL_WINDOW_SHOWN );
		if( MAINWD == NULL )
		{
			cout <<  "ko create dc cua so? " <<  SDL_GetError() << endl ;
			success = false;
		}
		else
		{
			rd = SDL_CreateRenderer( MAINWD, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( rd == NULL )
			{
				cout <<  "ko tao dc renderer"<<  SDL_GetError() ;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( rd, 0xFF, 0xFF, 0xFF, 0xFF );
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					cout <<  "ko khoi tao dc sdl_image "<<  IMG_GetError() << endl ;
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					cout << "ko khoi toa dc font chu" << TTF_GetError() << endl ;
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					cout << "ko ktao dc cai mixer" << Mix_GetError() << endl ;
					success = false;
				}
			}
		}
	}
	return success;
}

void textture:: render(int x , int y , int w , int h   )
{

    if(x == -1)
    {
        SDL_RenderCopy (rd , tt , NULL , NULL ) ;
    }
    else
    {
        SDL_Rect rec =  {x , y , w , h} ;
        SDL_RenderCopy (rd , tt , NULL , &rec ) ;
    }
}

bool textture::loadchu(int a)
{

    string s = to_string(a) ;
	SDL_Surface* sss = TTF_RenderText_Solid( font, s.c_str() , mau );
	if( sss == NULL )
	{
		cout <<"loi la gi:" << TTF_GetError() << endl ;
	}
	else
	{
        tt   = SDL_CreateTextureFromSurface( rd, sss );
		if( tt == NULL )
		{
			cout << "loi:" << SDL_GetError() <<endl ;
		}
        //SDL_DestroyTexture(tt) ;
		SDL_FreeSurface( sss );
	}

	return tt != NULL;
}

void button :: xuly(SDL_Event e)
{
    bool inside = true;
    if( e.type == SDL_MOUSEBUTTONUP )
    {
        int x , y ;
        SDL_GetMouseState( &x, &y );

        if( x < vt.x )
		{
			inside = false;
		}

		else if( x > vt.x + 100 )
		{
			inside = false;
		}

		else if( y < vt.y )
		{
			inside = false;
		}

		else if( y > vt.y + 100 )
		{
			inside = false;
		}
		if(inside && !shop.on  )
        {
            //cout <<"trong" <<endl;
            shop.on = true ;
            shop.ok = true ;
        }
        else if(inside && shop.on)
        {
            //cout << "ngoai" << endl ;
            shop.on = false ;
            shop.ok = false ;
        }

    }
    else if(e.type == SDL_KEYDOWN)
    {
        if(e.key.keysym.sym == SDLK_q)
        {
            if(inside && !shop.on  )
            {
                //cout <<"trong" <<endl;
                shop.on = true ;
                shop.ok = true ;
            }
            else if(inside && shop.on)
            {
                //cout << "ngoai" << endl ;
                shop.on = false ;
                shop.ok = false ;
            }
        }
    }

}
int muasung(SDL_Event e  )
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {

        SDL_GetMouseState(&x, & y ) ;
        if(x>=265 && x <=265+90 && y>=475 && y <= 475+110)
        {
            return 1 ;
        }
        else if(x>=360 && x <=360+90 && y>=475 && y <= 475+110)
        {
            return 2 ;
        }
        else if(x>=455 && x <=455+90 && y>=475 && y <= 475+110)
        {
            return 3 ;
        }
        else if(x>=550 && x <=550+90 && y>=475 && y <= 475+110)
        {
            return 4 ;
        }
        else if(x>=645 && x <=645+90 && y>=475 && y <= 475+110)
        {
            return 5 ;
        }
    }
    return 0 ;
}
void fmakegun()
{
    fsl.loadanh("sunglua.png") ;
    fsp.loadanh("sungphao.png") ;
    fsg.loadanh("sunggai.png") ;
    fbm.loadanh("bongma.png") ;
    fcd.loadanh("cotdinh.png") ;
}

textture :: textture()
{
    cao = 0 ;
    rong = 0 ;
    tt = NULL ;
}
textture :: ~textture()
{
    SDL_DestroyTexture(tt) ;
    tt = NULL ;
    cao = 0 ;
    rong = 0 ;
}

int textture :: getcao()
{
    return cao ;
}
int textture:: getrong()
{
    return rong ;
}
bool textture :: loadanh(string s )
{

    SDL_Surface * sf = IMG_Load(s.c_str()) ;
    if(sf == NULL)
    {
        cout <<"ko load dc surface" << endl ;
        return false ;

    }
    else
    {
        tt = SDL_CreateTextureFromSurface(rd, sf) ;
        SDL_FreeSurface(sf) ;
        if(tt == NULL)
        {
            cout << "ko load dc texture " << SDL_GetError() << endl;
            return false ;
        }
    }

    return tt != NULL  ;
}
//checkpos
bool loadmedia()
{
    bool flag = true  ;
    SDL_Surface * sf = IMG_Load("bul3.png") ;
    if(sf != NULL)
    {
        danlua = SDL_CreateTextureFromSurface(rd, sf) ;
        if(danlua == NULL)
        {
            flag = false ;
        }
    }
    sf = IMG_Load("danxanh.png") ;
    if(sf != NULL)
    {
        danxanh = SDL_CreateTextureFromSurface(rd, sf) ;
        if(danxanh == NULL)
        {
            flag = false ;
        }
    }
    sf = IMG_Load("danphao.png") ;
    if(sf != NULL)
    {
        danphao = SDL_CreateTextureFromSurface(rd, sf) ;
        if(danphao == NULL)
        {
            flag = false ;
        }
    }
    SDL_FreeSurface(sf) ;
    nhacnen = Mix_LoadMUS("nhacnen.wav") ;
    if(nhacnen == NULL)
    {
        cout << "ko load dc nhac nen" << endl ;
        flag = false ;
    }
    tiengcao = Mix_LoadWAV("tiengcao.wav") ;
    if(tiengcao == NULL)
    {
        cout << "ko co tieng cao" << endl ;
        flag = false ;
    }
    tiengphao = Mix_LoadWAV("phaosound.wav") ;
    if(tiengphao == NULL)
    {
        cout << "ko co tieng phao" << endl ;
        flag = false ;
    }
    tienglua = Mix_LoadWAV("tienglua.wav") ;
    if(tienglua == NULL)
    {
        cout << "ko co tieng lua" << endl ;
        flag = false ;
    }
    if(!map1.loadanh("mm.png"))
    {
        cout << "ko load dc map" << endl ;
        flag = false ;
    }
    if(!youlose.loadanh("gameover.png"))
    {
        cout <<"ko load dc anh khi thua"  << endl ;
        flag = false ;
    }
    if(!store.loadanh("st2.png"))
    {
        cout << "ko load dc store :<" << endl ;
        flag = false ;
    }
    else
    {
        store.getvt(vtStorex, vtStorey) ;
    }
    if(!shop.loadanh("gg.png"))
    {
        cout <<"ko load dc anh bang? go~" ;
        flag = false ;
    }
    if(!xu.loadanh("xu.png"))
    {
        cout << "ko load dc anh xu" << endl ;
        flag =false ;
    }
    if(!cupvang.loadanh("cupvang.png"))
    {
        cout <<"ko load dc anh cup vang" << endl;
        flag = false ;
    }
    if(!picsunggai.loadanh("picsunggai.png"))
    {
        cout <<"ko load dc anhr sung gai" << endl ;
        flag = false ;
    }
    if(!picsungphao.loadanh("picsungphao.png"))
    {
        cout <<"ko load dc anhr sung phao" << endl ;
        flag = false ;
    }
    if(!picsunglua.loadanh("picsunglua.png"))
    {
        cout <<"ko load dc anhr sung lua" << endl ;
        flag = false ;
    }
    if(!piccotdinh.loadanh("piccotdinh.png"))
    {
        cout <<"ko load dc anhr sung cot dinh" << endl ;
        flag = false ;
    }
    if(!picbongma.loadanh("picbongma.png"))
    {
        cout <<"ko load dc anh bong ma" << endl ;
        flag = false ;
    }
    font = TTF_OpenFont( "VeraSeBd.ttf", 50) ;
    if( font == NULL )
	{
		cout <<"ko load dc font chu" << endl ;
		flag = false ;
	}

    return flag ;
}

void close()
{

	map1.free();
	xu.free();
	cupvang.free() ;
	youlose.free() ;
	SDL_DestroyRenderer( rd );
	TTF_CloseFont(font) ;
	SDL_DestroyWindow( MAINWD );
	SDL_DestroyTexture(danlua) ;
	danlua = NULL ;
	MAINWD = NULL;
	rd = NULL;
    Mix_FreeChunk( tiengcao );
	Mix_FreeChunk( tienglua );
	Mix_FreeChunk( tiengphao );
	tiengcao = NULL;
	tienglua = NULL;
	tiengphao = NULL;

	//Free the music
	Mix_FreeMusic( nhacnen );
	nhacnen = NULL;
	int sls = SL.size() ;
    int sgs =SG.size() ;
    int sps = SP.size() ;
    int bms = BM.size() ;
    int cds = CD.size() ;
    for(int i = 0 ; i < sls ; i++)
    {
        delete SL[i] ;
    }
    for(int i = 0 ; i < sgs ; i++)
    {
        delete SG[i] ;
    }
    for(int i = 0 ; i < sps ; i++)
    {
        delete SP[i] ;
    }
    for(int i = 0 ; i < bms ; i++)
    {
        delete BM[i] ;
    }
    for(int i = 0 ; i < cds ; i++)
    {
        delete CD[i] ;
    }
    for(int i = 0 ; i < 4 ; i++)
    {
        SDL_DestroyTexture(pic[i]) ;
    }
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
// speed
monster *r11 = new monster(1) ;
monster *r12 = new monster(0) ;
monster *r21 = new monster(1) ;
monster *r22 = new monster(0) ;
monster *r31 = new monster(1);
monster *r32 = new monster(0) ;
monster *r41 = new monster(1);
monster *r42 = new monster(0) ;
/*void hoisiinh()
{
    if(SDL_GetTicks() >= 3000)
    {

            (*r11).hoisinh() ;


            (*r12).hoisinh() ;

        if((*r21).hetmau()) (*r21).hoisinh() ;
        if((*r22).hetmau()) (*r22).hoisinh() ;
        if((*r31).hetmau()) (*r31).hoisinh() ;
        if((*r32).hetmau()) (*r32).hoisinh() ;
        if((*r41).hetmau()) (*r41).hoisinh() ;
        if((*r42).hetmau()) (*r42).hoisinh() ;
    }
}*/
void bansung()
{
    int sls = SL.size() ;
    int sgs = SG.size() ;
    int sps = SP.size() ;
    int bms = BM.size() ;//bongma
    int cds = CD.size() ;
    if(sls > 0 )
        {
            for(int i = 0 ; i < sls; i++)
            {
                if(!(*SL[i]).hetmau())
                {

                    if(row[(*SL[i]).gethang()].coqvat())
                    {
                        (*SL[i]).ban() ;
                    }
                }
            }
        }
        if(sgs > 0 )
        {
            for(int i = 0 ; i < sgs; i++)
            {
                if(!(SG[i]->hetmau()))
                {

                    if(row[(*SG[i]).gethang()].coqvat())
                    {
                        (*SG[i]).ban() ;
                    }
                }
            }
        }
        if(sps > 0 )
        {
            for(int i = 0 ; i < sps; i++)
            {
                if(!(*SP[i]).hetmau())
                {
                    if(row[(*SP[i]).gethang()].coqvat())
                    {
                        (*SP[i]).ban() ;
                    }
                }
            }
        }
        if(bms > 0 )
        {
            for(int i = 0 ; i < bms; i++)
            {
                if(!(*BM[i]).hetmau())
                {
                    if(row[(*BM[i]).gethang()].coqvat())
                    {
                        (*BM[i]).ban() ;
                    }
                }
            }
        }
}
void rendersung()
{
    int sls = SL.size() ;
        int sgs = SG.size() ;
        int sps = SP.size() ;
        int bms = BM.size() ;//bongma
        int cds = CD.size() ;
    if(sls > 0 )
        {
            for(int i = 0 ; i < sls; i++)
            {
                if(!(*SL[i]).hetmau())
                {
                    (*SL[i]).render() ;
                    if((*SL[i]).getposX() < row[(*SL[i]).gethang()].getvtsgn())
                    {
                        sung * p = SL[i] ;
                        row[(*SL[i]).gethang()].setsunggn(p) ;
                        row[(*SL[i]).gethang()].setvtsunggn((*SL[i]).getposX()) ;
                    }
                }
                else
                {
                    if((*SL[i]).checkcheck())
                    {
                        (*SL[i]).tralaivitrim() ;
                    }
                }
            }
        }
        if(sgs > 0 )
        {
            for(int i = 0 ; i < sgs; i++)
            {
                if(!(SG[i]->hetmau()))
                {
                    (*SG[i]).render() ;

                    if((*SG[i]).getposX() < row[(*SG[i]).gethang()].getvtsgn())
                    {
                        sung * p = SG[i] ;
                        row[(*SG[i]).gethang()].setsunggn(p)  ;
                        row[(*SG[i]).gethang()].setvtsunggn((*SG[i]).getposX()) ;
                    }
                }
                else
                {
                    if((*SG[i]).checkcheck())
                    {
                        (*SG[i]).tralaivitrim() ;
                    }
                }
            }
        }
        if(sps > 0 )
        {
            for(int i = 0 ; i < sps; i++)
            {
                if(!(*SP[i]).hetmau())
                {
                    (*SP[i]).render() ;

                    if((*SP[i]).getposX() < row[(*SP[i]).gethang()].getvtsgn())
                    {
                        sung * p = SP[i] ;
                        row[(*SP[i]).gethang()].setsunggn(p) ;
                        row[(*SP[i]).gethang()].setvtsunggn((*SP[i]).getposX()) ;
                    }
                }
                else
                {
                    if((*SP[i]).checkcheck())
                    {
                        (*SP[i]).tralaivitrim() ;
                    }
                }
            }
        }
        if(bms > 0 )
        {
            for(int i = 0 ; i < bms; i++)
            {
                if(!(*BM[i]).hetmau())
                {
                    (*BM[i]).render() ;

                    if((*BM[i]).getposX() < row[(*BM[i]).gethang()].getvtsgn())
                    {
                        sung * p = BM[i] ;
                        row[(*BM[i]).gethang()].setsunggn(p) ;
                        row[(*BM[i]).gethang()].setvtsunggn((*BM[i]).getposX()) ;
                    }
                }
                else
                {
                    if((*BM[i]).checkcheck())
                    {
                        cout << "gg" << endl ;
                        (*BM[i]).tralaivitrimm() ;
                    }
                }
            }
        }
        if(cds > 0 )
        {
            for(int i = 0 ; i < cds ; i++)
            {
                if(!(*CD[i]).hetmau())
                {
                    (*CD[i]).render() ;
                    if((*CD[i]).getposX() < row[(*CD[i]).gethang()].getvtsgn())
                    {
                        sung * p = CD[i] ;
                        row[(*CD[i]).gethang()].setsunggn(p) ;
                        row[(*CD[i]).gethang()].setvtsunggn((*CD[i]).getposX()) ;
                    }
                }
                else
                {
                    if((*CD[i]).checkcheck())
                    {
                        cout << "gg" << endl ;
                        (*CD[i]).tralaivitrim() ;
                    }
                }
            }
        }
}
int main(int argc , char *args[])
{

    if(!init())
    {
        cout << "khong khoi tao duoc" ;
        return 0 ;
    }
    else
    {
        if(!loadmedia())
        {
            cout << "ko load media dc :))" << endl ;
            return 0 ;
        }
    }
    Mix_PlayMusic( nhacnen, -1 );
    bool quit = false ;
    int demvang = 0 ;
    SDL_Event e ;
    ktaongare() ;
    fmakegun() ;
    taoanhquaivat() ;
    SDL_Rect vt ;
    int check ;
    bool nha = true ;
    hs.open("kiluc.txt" ) ;
    hs >> kiluc ;
    hs.close() ;
    hss.open("kiluc.txt" , ios::trunc) ;
    while(!quit)
    {
        if(SDL_PollEvent(&e) != 0 )
        {
            if(e.type == SDL_QUIT)
            {
                quit = true ;
            }
            store.xuly(e) ;
            if(shop.ok)
            {
                check = muasung(e) ;
                if(check >=1 && check <= 5 )
                {
                    nha = false ;
                }
            }
            if(!nha)
            {
                SDL_GetMouseState(&x , &y) ;
                vt.x = x - 60 ;
                vt.y = y -65 ;


                shop.ok = false ;
                if(e.type == SDL_MOUSEBUTTONUP)
                {

                    cout << vt.x << " " << vt.y << endl ;

                    switch(check)
                    {
                        case 1:
                        {
                            sunglua* a = new sunglua ("sunglua.png") ;
                            if((*a).dutien()&& checkpos(vt.x , vt.y , (*a)))
                            {
                                (*a).setpos(vt.x, vt.y, 61, 85 ) ;
                                SL.pb(a) ;
                                (*a).setmau(3000) ;
                                (*a).setvtdan(vt.x -3  , vt.y + 35  ) ;
                                gold -= 5 ;
                            }
                            else delete a ;
                        }
                        break ;
                        case 2 :
                        {
                            sunggai *a = new sunggai ("sunggai.png") ;
                            if((*a).dutien() && checkpos(vt.x , vt.y, (*a)))
                            {
                                (*a).setpos(vt.x, vt.y, 61, 85 ) ;
                                SG.pb(a) ;
                                (*a).setmau(1300) ;
                                (*a).setvtdan(vt.x -3  , vt.y + 28  ) ;
                                gold -= 2 ;
                            }
                            else delete a ;
                        }
                        break ;
                        case 3 :
                        {
                            sungphao* a = new sungphao("sungphao.png") ;
                            if((*a).dutien()&& checkpos(vt.x , vt.y, (*a)))
                            {
                                (*a).setpos(vt.x, vt.y, 61 , 85 ) ;
                                SP.pb(a) ;
                                (*a).setmau(2000) ;
                                (*a).setvtdan(vt.x -3  , vt.y + 28  ) ;
                                gold -= 3 ;
                            }
                            else delete a ;
                        }
                        break ;
                        case 4 :
                        {
                            bongma *a = new bongma("bongma.png") ;
                            if((*a).dutien()&& checkpos(vt.x , vt.y, (*a)))
                            {
                                (*a).setpos(vt.x, vt.y, 61, 85 ) ;
                                BM.pb(a) ;
                                (*a).setmau(10000) ;
                                (*a).setpos1(vt.x , vt.y) ;
                                gold -= 3 ;
                            }
                            else delete a ;
                        }
                        break ;
                        case 5 :
                        {
                            cotdinh *a  = new cotdinh("cotdinh.png") ;
                            if((*a).dutien()&& checkpos(vt.x , vt.y, (*a)))
                            {
                                (*a).setpos(vt.x, vt.y, 61 , 85 ) ;
                                CD.pb(a) ;
                                (*a).setmau(13000) ;
                                gold -= 3 ;
                            }
                            else delete a ;
                        }
                    }
                    cout <<SL.size() <<endl << SG.size() <<endl  << SP.size() << endl << BM.size() <<endl << CD.size() << endl ;
                    cout <<"------" << endl ;
                    nha= true ;
                    check = 0 ;
                }
            }
        }
        SDL_RenderClear(rd) ;
        SDL_SetRenderDrawColor(rd, 0xFF, 0xFF, 0xFF, 0xFF );
        map1.render(-1 , -1 , -1 , -1 ) ;
        if(!lose)
        {
            if(SDL_GetTicks() >=1000)
            {
                (*r11).vitrihang(r11) ;
                (*r12).vitrihang(r12) ;
            }
            if(SDL_GetTicks() >=10000)
            {
                (*r21).vitrihang(r21) ;
                (*r22).vitrihang(r22) ;
            }
            if(SDL_GetTicks() >= 17000)
            {
                (*r31).vitrihang(r31) ;
                (*r32).vitrihang(r32) ;
            }
        if(SDL_GetTicks() >= 25000)
        {
            (*r41).vitrihang(r41) ;
            (*r42).vitrihang(r42) ;
        }
        rendersung() ;
        if(demvang == 550 )
        {
            gold++ ;
            demvang = 0 ;
        }

        if(SDL_GetTicks() >=1000)
        {
            (*r11).movee() ;
            (*r11).render() ;
            (*r11).checksung() ;
            (*r12).movee() ;
            (*r12).render() ;
            (*r12).checksung();
        }
        if(SDL_GetTicks() >=10000)
        {
            (*r21).movee()   ;
            (*r21).render() ;
            (*r21).checksung() ;
            (*r22).movee()   ;
            (*r22).render() ;
            (*r22).checksung() ;
        }
        if(SDL_GetTicks() >=17000)
        {
            (*r31).movee() ;
            (*r31).render() ;
            (*r31).checksung() ;
            (*r32).movee() ;
            (*r32).render() ;
            (*r32).checksung();
        }
        if(SDL_GetTicks() >=25000)
        {
            (*r41).movee() ;
                (*r41).render() ;
                (*r41).checksung() ;


                (*r42).movee() ;
                (*r42).render() ;
                (*r42).checksung();

        }
        bansung() ;


        cupvang.render(20,20,45,50);
        xu.render(850,30,50,50) ;
        chu.loadchu(gold) ;
        chu.render(905,30, 50, 50 ) ; // dong` nay co' loi~
        chu.freechu() ;
        score.loadchu(diem) ;
        score.render(70,20 ,50 ,50) ;
        score.freechu() ;
        if(shop.ok)
        {
            shop.render(250,470,500, 120) ;
            picsunglua.render(265 , 475 , 90,110 )  ;
            picsunggai.render(360,475, 90 ,110)    ;
            picsungphao.render(455 , 475 , 90 , 110) ;
            picbongma.render(550 , 475 , 90 ,110 ) ;
            piccotdinh.render(645 , 475 , 90 , 110)  ;
        }

        if(check >=1 && check <=5)
        {
        //cout << "behon" <<endl ;
        switch(check)
        {
            case 1 :
                    fsl.render(vt.x  ,vt.y , 61 , 85 ) ;
                    break ;
            case 2 :
                    fsg.render(vt.x ,vt.y , 61 , 85 ) ;
                    break ;
            case 3 :
                    fsp.render(vt.x ,vt.y , 61 , 85 ) ;
                    break ;
            case 4 :
                    fbm.render(vt.x ,vt.y , 61 , 85 ) ;
                    break ;
            case 5 :
                    fcd.render(vt.x ,vt.y , 61 , 85 ) ;
                    break ;
        }
        }
        store.render(vtStorex, vtStorey ,100,100)   ;
        }
        else
        {
            if(diem > kiluc )
            {
                kiluc = diem ;
                cout << "cos" << endl ;
                cout << kiluc << endl ;
                hss << kiluc ;
                hss.close() ;
            }

            youlose.render(250,60,500, 313) ;
            cupvang.render(350,340,100,100);
            score.loadchu(diem) ;
            score.render(460,340 ,100 ,100) ;
            score.freechu() ;
            kyluc.loadchu(kiluc) ;
            kyluc.render(460,470, 100 ,100 ) ;
            kyluc.freechu() ;
            hs.close() ;
        }


        SDL_RenderPresent(rd) ;
        demvang ++ ;

        resetrow() ;
    }
    close() ;
    return 0 ;
}
