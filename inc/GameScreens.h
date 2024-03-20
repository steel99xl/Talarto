#ifndef GAMESCREENS_H
#define GAMESCREENS_H
#include "Cards.h"
#include "TerminalGraphics/tgraphics.hpp"
#include "SimpleRandom/simplerandom.hpp"
#include "GCards.h"


inline void Title(graphics::Display &D){
    D.PutText((D.Width/2)-5,D.Height/2,"Talarto", graphics::Red_On_White);
    D.PutText((D.Width/2)-13,(D.Height/2)+2,"Press ANY KEY to continue", graphics::Red_On_White);
    D.PutText((D.Width/2)-13,(D.Height/2)+4,"A fan version of Balarto");
    

    D.Show();


    D.ClearPixels(graphics::LightPixel, graphics::Black);

}


inline void Help(graphics::Display &D){
    
    D.PutText((D.Width/2)-5,D.Height/2-4,"Help:", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2-3,"LEFT & RIGHT Arrows let you  move between cards", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2-2,"UP & DOWN Arrows let you select and un-select cards", graphics::Green);

    D.PutText((D.Width/2)-15,D.Height/2-1,"After each win you last used type 'levels up'", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2,"After every three win your 'Hands', 'Discard' and three random types 'level up'", graphics::Green, graphics::LEFT,graphics::DOWN,46);

    D.Show();
}


inline void RoundWin(graphics::Display &D){
    D.PutText((D.Width/2)-5,D.Height/2-4,"Round Won:", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2-3,"Press S for Shop", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2-2,"Press N for Next Round and 2X Money", graphics::Green);
    D.Show();   
}

template <typename T>
inline void GameScreen(graphics::Display &D,Hand &Player,graphics::Point3D<T> &PPos, GCard &vpc, graphics::Matrix3x3<T> &Scale, MapList &Cards, MapList &ScoreMap,int &PScore, int &TargetScore, int &OldTargetScore,unsigned int &WinCount, SimpleHand &Enamy){
               char *IBuff = new char[20];
               int CheckResult = QuickCheck(Player.D);
                D.PutText(D.Width*0.05,D.Height*0.35,ScoreMap.Map[CheckResult].Value);

                sprintf(IBuff, "%d", Player.DiscardCount);
                D.PutText(D.Width*0.10,D.Height*0.4,"Discards",graphics::White_On_Red);
                D.PutText(D.Width*0.20,D.Height*0.4,IBuff, graphics::White_On_Red);

                sprintf(IBuff, "%d", Player.Health);
                D.PutText(D.Width*0.10,D.Height*0.43," Health ", graphics::White_On_Blue);
                D.PutText(D.Width*0.20,D.Height*0.43,"   ", graphics::White_On_Blue);
                if(Player.Health*3 == Player.HealthLimit){
                    D.PutText(D.Width*0.20,D.Height*0.43,IBuff, graphics::Red_On_Blue);
                } else {
                    D.PutText(D.Width*0.20,D.Height*0.43,IBuff, graphics::White_On_Blue);
                }

                sprintf(IBuff, "%d", Player.Shild);
                D.PutText(D.Width*0.10,D.Height*0.51," Shields", graphics::White_On_Blue);
                D.PutText(D.Width*0.20,D.Height*0.51,"   ", graphics::White_On_Blue);
                if(Player.Shild == 0){
                    D.PutText(D.Width*0.20,D.Height*0.51,IBuff, graphics::Red_On_Blue);
                } else { 
                    D.PutText(D.Width*0.20,D.Height*0.51,IBuff, graphics::White_On_Blue);
                }

                sprintf(IBuff, "%d", PScore);
                D.PutText(D.Width*0.10,D.Height*0.3,"Score       :", graphics::Yellow_On_Blue);
                D.PutText(D.Width*0.26,D.Height*0.3,"   ", graphics::Yellow_On_Blue);
                D.PutText(D.Width*0.26,D.Height*0.3,IBuff, graphics::Yellow_On_Blue);

                sprintf(IBuff, "%d", TargetScore);
                D.PutText(D.Width*0.10,D.Height*0.25,"TargetScore :", graphics::Yellow_On_Red);
                D.PutText(D.Width*0.26,D.Height*0.25,"   ", graphics::Yellow_On_Red);
                D.PutText(D.Width*0.26,D.Height*0.25,IBuff, graphics::Yellow_On_Red);

                sprintf(IBuff, "%d", OldTargetScore);
                D.PutText(D.Width*0.10,D.Height*0.2,"PastScore   :", graphics::Yellow_On_Red);
                D.PutText(D.Width*0.26,D.Height*0.2,"   ", graphics::Yellow_On_Red);
                D.PutText(D.Width*0.26,D.Height*0.2,IBuff, graphics::Yellow_On_Red);

                sprintf(IBuff, "%d", Enamy.Health);
                D.PutText(D.Width*0.10,D.Height*0.15,"Enamy Health : ", graphics::Yellow_On_Red);
                D.PutText(D.Width*0.28,D.Height*0.15,"   ", graphics::Yellow_On_Red);
                D.PutText(D.Width*0.28,D.Height*0.15,IBuff, graphics::Yellow_On_Red);


                D.PutText(D.Width*.8,D.Height*0.10,"HAND    : Z");
                D.PutText(D.Width*.8,D.Height*0.15,"DISCARD : X");
                D.PutText(D.Width*.8,D.Height*0.20,"HELP    : H");
                D.PutText(D.Width*.8,D.Height*0.25,"QUIT    : Q");


                D.PutText(D.Width/2-11,D.Height-1,"Sort Value : o");
                D.PutText(D.Width/2+6,D.Height-1,"Sort Suit : O");
                // Visual win counter        
                sprintf(IBuff, "%d", WinCount);
                D.PutText(1,D.Height,IBuff);


                // Draw Cards
                PPos.X = Player.Start.X;
                DrawHand(D,Player,vpc,Cards,PPos,Scale);

                // Draw currently selected Card
                PPos.X = Player.Start.X;//(vpc.Width * Player.Selected);
                DrawSelectedCard(D,Player,vpc,Cards,PPos,Scale);

                D.Show();
}

inline void Shop(graphics::Display &D, Hand &Player, MapList &Level, int &Balance, int &Cost, int &ShopSelect){
   // Print Level mappings
   // print controls for mappings and other upgrade options along with the N next option to start the next round
   // Length 16

    D.ClearPixels(graphics::MidPixel, graphics::Green, (D.Width/2)-17,(D.Height/2)-5, D.Width/2+22, D.Height);

    char *IBuff = new char[20];
    D.PutText((D.Width/2)-3,D.Height/2-4,"   SHOP   ", graphics::Green);

    //D.PutText((D.Width/2)-15,D.Height/2-2,"Press N for Next Round", graphics::Green);
    sprintf(IBuff, "%d", Cost);
    D.PutText((D.Width/2)-15,D.Height/2-3,"Cost :", graphics::Green);
    D.PutText((D.Width/2)-10,D.Height/2-3,IBuff, graphics::Green);

    sprintf(IBuff, "%d", Balance);
    D.PutText((D.Width/2)+3,D.Height/2-3,"Balance :", graphics::Green);
    D.PutText((D.Width/2)+11,D.Height/2-3,IBuff, graphics::Green);


    for(int i = 1; i < Level.Count; i = i+2){
        if(i == ShopSelect){
            D.PutText((D.Width/2)-15,D.Height/2-(3-i),Level.Map[i].Value, graphics::Green_On_White);
            sprintf(IBuff, "%d", Level.Map[i].ID);
            D.PutText((D.Width/2)+1,D.Height/2-(3-i),IBuff, graphics::Green_On_White);
        } else {
            D.PutText((D.Width/2)-15,D.Height/2-(3-i),Level.Map[i].Value, graphics::Green);
            sprintf(IBuff, "%d", Level.Map[i].ID);
            D.PutText((D.Width/2)+1,D.Height/2-(3-i),IBuff, graphics::Green);
        }

        if(i+1 == ShopSelect){
            D.PutText((D.Width/2)+3,D.Height/2-(3-i),Level.Map[i+1].Value, graphics::Green_On_White);
            sprintf(IBuff, "%d", Level.Map[i+1].ID);
            D.PutText((D.Width/2)+19,D.Height/2-(3-i),IBuff, graphics::Green_On_White);
        } else {
            D.PutText((D.Width/2)+3,D.Height/2-(3-i),Level.Map[i+1].Value, graphics::Green);
            sprintf(IBuff, "%d", Level.Map[i+1].ID);
            D.PutText((D.Width/2)+19,D.Height/2-(3-i),IBuff, graphics::Green);
        }


    }
        if(ShopSelect == 11){
            D.PutText((D.Width/2)-15,D.Height/2+8,"SHIELD", graphics::Green_On_White);
            sprintf(IBuff, "%d", Player.Shild);
            D.PutText((D.Width/2)+1,D.Height/2+8,IBuff, graphics::Green_On_White);
        } else {
            D.PutText((D.Width/2)-15,D.Height/2+8,"SHIELD", graphics::Green);
            sprintf(IBuff, "%d", Player.Shild);
            D.PutText((D.Width/2)+1,D.Height/2+8,IBuff, graphics::Green);
        }
    
        if(ShopSelect == 12){
            D.PutText((D.Width/2)+3,D.Height/2+8, "DISCARD", graphics::Green_On_White);
            sprintf(IBuff, "%d", Player.DiscardLimit);
            D.PutText((D.Width/2)+19,D.Height/2+8,IBuff, graphics::Green_On_White);
        } else{
            D.PutText((D.Width/2)+3,D.Height/2+8, "DISCARD", graphics::Green);
            sprintf(IBuff, "%d", Player.DiscardLimit);
            D.PutText((D.Width/2)+19,D.Height/2+8,IBuff, graphics::Green);
        }


        D.PutText(D.Width*.8,D.Height*0.10,"BUY     : Z");
        D.PutText(D.Width*.8,D.Height*0.15,"NEXT    : N");

    D.Show();
}

inline void LoseScreen(graphics::Display &D){
    D.ClearPixels(graphics::MidPixel, graphics::Red, (D.Width/2)-17,(D.Height/2)-5, D.Width/2+22, D.Height);
    D.ClearPixels(graphics::MidPixel, graphics::Black, (D.Width/2)-16,(D.Height/2)-4, D.Width/2+21, D.Height-1);
    D.PutText((D.Width/2)-3,D.Height/2-4,"   LOSE   ", graphics::Black_On_Red);


    D.PutText((D.Width/2)-7,D.Height/2-(2),"Press R to Restart", graphics::Black_On_Red);
    D.PutText((D.Width/2)-6,D.Height/2,"Press Q to Quit", graphics::Black_On_Red);

    D.Show();
}




#endif
