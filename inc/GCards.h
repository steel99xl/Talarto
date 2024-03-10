#ifndef GCARDS_H
#define GCARDS_H
#include "TerminalGraphics/tgraphics.hpp"
#include "Cards.h"

typedef struct Hand{
    Deck D;
    // What Card in the Deck is currently selected
    int Selected;
    int UsedCardsLimit;
    int DiscardLimit;
    int HandLimit;
    int DiscardCount;
    int HandCount;
    // Start positon of player hand drawing
    graphics::Point3D<double> Start;
    int MaxX;
    int MaxY;
    graphics::Pixel Box;
    graphics::Pixel Select;
} Hand;



// The Graphical Card
typedef struct GCard{
    graphics::Pixel Face;
    graphics::Pixel Suit;
    graphics::Pixel Background;
    graphics::Point3D<double> Start;
    graphics::Point3D<double> End;
    graphics::Point3D<double> IDPos;
    int Width;
    char * buf;

    GCard(){
        this->buf = (char *)malloc(sizeof(char) * 2);
    }

    ~GCard(){
        free(this->buf);
    }

}GCard;


template <typename T>
inline void DrawHand(graphics::Display &D,Hand &H, GCard &G, MapList &M, graphics::Point3D<T> Pos, graphics::Matrix3x3<T> Scale){
    bool Scaling = true;
    while(Scaling){
    if(((H.D.Count * G.Width) * Scale.B.Y) > (H.MaxX-H.Start.X)){
        Scale.B.Y -= 0.1;
    } else {
        Scaling = false;
    }
    }

    // Draw hand of regular cards


    for(int i = 0; i < H.D.Count; i++){
        if(H.D.Cards[i].IsUsed){
            D.Rect((int)G.Start.X + Pos.X+1, (int)G.Start.Y + Pos.Y+1, (int)G.End.X + Pos.X, (int)G.End.Y + Pos.Y, H.Select,true);
        } else {
            D.Rect((int)G.Start.X + Pos.X+1, (int)G.Start.Y + Pos.Y+1, (int)G.End.X + Pos.X, (int)G.End.Y + Pos.Y, G.Background,true);
        }
        D.Rect((int)G.Start.X + Pos.X, (int)G.Start.Y + Pos.Y, (int)G.End.X + Pos.X, (int)G.End.Y + Pos.Y, H.Box);
        switch(H.D.Cards[i].Suit){
            case('S'):
            case('C'):

                D.SetPixel(G.IDPos.X + Pos.X, G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[i]), graphics::Black_On_White);
                if(graphics::GetLen(MapLookUp(M,H.D.Cards[i])) > 2){
                    D.PutText(-G.IDPos.X + Pos.X-1, -G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[i]), graphics::Black_On_White);
                } else {
                    D.SetPixel(-G.IDPos.X + Pos.X, -G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[i]), graphics::Black_On_White);
                }
                graphics::EasyChar(H.D.Cards[i].Suit, G.buf);
                D.SetPixel(-G.IDPos.X + Pos.X, G.IDPos.Y + Pos.Y, G.buf, graphics::Black_On_White);
                D.SetPixel(G.IDPos.X + Pos.X, -G.IDPos.Y + Pos.Y, G.buf, graphics::Black_On_White);

                break;


            case('H'):

            case('D'):
                D.SetPixel(G.IDPos.X + Pos.X, G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[i]), graphics::Red_On_White);
                if(graphics::GetLen(MapLookUp(M,H.D.Cards[i])) > 2){
                    D.PutText(-G.IDPos.X + Pos.X-1, -G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[i]), graphics::Red_On_White);
                } else {
                    D.SetPixel(-G.IDPos.X + Pos.X, -G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[i]), graphics::Red_On_White);
                }
                graphics::EasyChar(H.D.Cards[i].Suit, G.buf);
                D.SetPixel(-G.IDPos.X + Pos.X, G.IDPos.Y + Pos.Y, G.buf, graphics::Red_On_White);
                D.SetPixel(G.IDPos.X + Pos.X, -G.IDPos.Y + Pos.Y, G.buf, graphics::Red_On_White);
                break;
        }

        /*
        Screen.SetPixel((int)vpc.Start.X + Pos.X, (int)vpc.Start.Y + Pos.Y, "S" );
        Screen.SetPixel((int)vpc.End.X + Pos.X, (int)vpc.End.Y + Pos.Y, "E" );
        */
        Pos.X += G.Width * Scale.B.Y;
    }
    

}

template <typename T>
inline void DrawSelectedCard(graphics::Display &D,Hand &H, GCard &G, MapList &M, graphics::Point3D<T> Pos, graphics::Matrix3x3<T> Scale){

    if(H.D.Cards[H.Selected].IsUsed){
        D.Rect((int)G.Start.X + Pos.X+1, (int)G.Start.Y + Pos.Y+1, (int)G.End.X + Pos.X, (int)G.End.Y + Pos.Y, H.Select,true);
    } else {
        D.Rect((int)G.Start.X + Pos.X+1, (int)G.Start.Y + Pos.Y+1, (int)G.End.X + Pos.X, (int)G.End.Y + Pos.Y, G.Background,true);
    }

    D.Rect((int)G.Start.X + Pos.X, (int)G.Start.Y + Pos.Y, (int)G.End.X + Pos.X, (int)G.End.Y + Pos.Y, H.Box);
    switch(H.D.Cards[H.Selected].Suit){
        case('S'):
        case('C'):

            D.SetPixel(G.IDPos.X + Pos.X, G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[H.Selected]), graphics::Black_On_Blue);
            if(graphics::GetLen(MapLookUp(M,H.D.Cards[H.Selected])) > 2){
                D.PutText(-G.IDPos.X + Pos.X-1, -G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[H.Selected]), graphics::Black_On_Blue);
            } else {
                D.SetPixel(-G.IDPos.X + Pos.X, -G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[H.Selected]), graphics::Black_On_Blue);
            }
            graphics::EasyChar(H.D.Cards[H.Selected].Suit, G.buf);
            D.SetPixel(-G.IDPos.X + Pos.X, G.IDPos.Y + Pos.Y, G.buf, graphics::Black_On_Blue);
            D.SetPixel(G.IDPos.X + Pos.X, -G.IDPos.Y + Pos.Y, G.buf, graphics::Black_On_Blue);

            break;


        case('H'):

        case('D'):
            D.SetPixel(G.IDPos.X + Pos.X, G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[H.Selected]), graphics::Red_On_Blue);
            if(graphics::GetLen(MapLookUp(M,H.D.Cards[H.Selected])) > 2){
                D.PutText(-G.IDPos.X + Pos.X-1, -G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[H.Selected]), graphics::Red_On_Blue);
            } else {
                D.SetPixel(-G.IDPos.X + Pos.X, -G.IDPos.Y + Pos.Y, MapLookUp(M,H.D.Cards[H.Selected]), graphics::Red_On_Blue);
            }
            graphics::EasyChar(H.D.Cards[H.Selected].Suit, G.buf);
            D.SetPixel(-G.IDPos.X + Pos.X, G.IDPos.Y + Pos.Y, G.buf, graphics::Red_On_Blue);
            D.SetPixel(G.IDPos.X + Pos.X, -G.IDPos.Y + Pos.Y, G.buf, graphics::Red_On_Blue);
            break;
    }
}



#endif
