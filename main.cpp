#include "inc/Cards.h"
#include "inc/TerminalGraphics/tgraphics.hpp"
#include "inc/SimpleRandom/simplerandom.hpp"
#include "inc/GCards.h"

// S : Spades
// H : Harts
// C : Clubs
// D : Diamonds

// Jack ID 11 Value 11
// Queen ID 12 Value 11 

void Title(graphics::Display &D){
    D.PutText((D.Width/2)-5,D.Height/2,"Talarto", graphics::Red_On_White);
    D.PutText((D.Width/2)-13,(D.Height/2)+2,"Press ANY KEY to continue", graphics::Red_On_White);
    D.PutText((D.Width/2)-13,(D.Height/2)+4,"A fan version of Balarto");
    

    D.Show();


    D.ClearPixels(graphics::LightPixel, graphics::Black);

}


void Help(graphics::Display &D){
    
    D.PutText((D.Width/2)-5,D.Height/2-4,"Help:", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2-3,"LEFT & RIGHT Arrows let you  move between cards", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2-2,"UP & DOWN Arrows let you select and un-select cards", graphics::Green);

    D.PutText((D.Width/2)-15,D.Height/2-1,"After each win you last used type 'levels up'", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2,"After every three win your 'Hands', 'Discard' and three random types 'level up'", graphics::Green, graphics::LEFT,graphics::DOWN,46);

    D.Show();
}


void RoundWin(graphics::Display &D){
    D.PutText((D.Width/2)-5,D.Height/2-4,"Round Won:", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2-3,"Press S for Shop", graphics::Green);
    D.PutText((D.Width/2)-15,D.Height/2-2,"Press N for Next Round", graphics::Green);
    D.Show();
}
template <typename T>
void GameScreen(graphics::Display &D,Hand &Player,graphics::Point3D<T> &PPos, GCard &vpc, graphics::Matrix3x3<T> &Scale, MapList &Cards, MapList &ScoreMap,int &PScore, int &TargetScore,unsigned int &WinCount){
               char *IBuff = new char[20];
               int CheckResult = QuickCheck(Player.D);
                D.PutText(D.Width*0.05,D.Height*0.3,ScoreMap.Map[CheckResult].Value);

                sprintf(IBuff, "%d", Player.DiscardCount);
                D.PutText(D.Width*0.10,D.Height*0.35,"Discards",graphics::White_On_Red);
                D.PutText(D.Width*0.20,D.Height*0.35,IBuff, graphics::White_On_Red);

                sprintf(IBuff, "%d", Player.HandCount);
                D.PutText(D.Width*0.10,D.Height*0.37,"  Hands ", graphics::White_On_Blue);
                D.PutText(D.Width*0.20,D.Height*0.37,IBuff, graphics::White_On_Blue);


                sprintf(IBuff, "%d", PScore);
                D.PutText(D.Width*0.10,D.Height*0.25,"Score : ", graphics::Yellow_On_Blue);
                D.PutText(D.Width*0.25,D.Height*0.25,IBuff, graphics::Yellow_On_Blue);

                sprintf(IBuff, "%d", TargetScore);
                D.PutText(D.Width*0.10,D.Height*0.2,"TargetScore : ", graphics::Yellow_On_Red);
                D.PutText(D.Width*0.25,D.Height*0.2,IBuff, graphics::Yellow_On_Red);


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

void Shop(graphics::Display &D, Hand &Player, MapList &Level, int &Balance, int &Cost){
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
        D.PutText((D.Width/2)-15,D.Height/2-(3-i),Level.Map[i].Value, graphics::Green);
        sprintf(IBuff, "%d", Level.Map[i].ID);
        D.PutText((D.Width/2)+1,D.Height/2-(3-i),IBuff, graphics::Green);


        D.PutText((D.Width/2)+3,D.Height/2-(3-i),Level.Map[i+1].Value, graphics::Green);
        sprintf(IBuff, "%d", Level.Map[i+1].ID);
        D.PutText((D.Width/2)+19,D.Height/2-(3-i),IBuff, graphics::Green);
    }

        D.PutText((D.Width/2)-15,D.Height/2+8,"HAND", graphics::Green);
        sprintf(IBuff, "%d", Player.HandLimit);
        D.PutText((D.Width/2)+1,D.Height/2+8,IBuff, graphics::Green);


        D.PutText((D.Width/2)+3,D.Height/2+8, "DISCARD", graphics::Green);
        sprintf(IBuff, "%d", Player.DiscardLimit);
        D.PutText((D.Width/2)+19,D.Height/2+8,IBuff, graphics::Green);
    D.Show();
}



enum Mode{GAME,STORE,PICKER};

int main(int argc, char** argv){

    int twidth, theight;
    if(argc == 3){
        twidth = std::atoi(argv[1]);
        theight = std::atoi(argv[2]); 
    } else {
        twidth = 79;
        theight = 22;
    }

    graphics::Display Screen(twidth,theight);

    Screen.ClearPixels(graphics::LightPixel, graphics::Black);

    simplerandom Random;

    Deck D;
    Hand Player;
    Player.D.Count = 8;
    Player.D.UsedCount = 0;
    Player.D.Cards = MakeEmptyDeck(Player.D.Count);
    Player.Start.X = Screen.Width*0.25;
    Player.Start.Y = Screen.Height*0.8;

    Player.MaxX = Screen.Width;
    Player.MaxY = Screen.Height*0.9;
    graphics::EasyBody(graphics::MidPixel,Player.Box.Body);
    graphics::EasyColor(graphics::Green,Player.Box.Color);

    graphics::EasyBody(graphics::MidPixel,Player.Select.Body);
    MakeDeckStandard(D);

    RandomTranspher(Random,D,Player.D);

    Player.Selected = 2;
    Player.UsedCardsLimit = 5;

    Player.HandLimit = 4;
    Player.DiscardLimit = 4;
    Player.DiscardCount = Player.DiscardLimit;
    Player.HandCount = Player.HandLimit;


    GCard vpc;
    // For Suit printint
    vpc.Start.X = -4.0;
    vpc.Start.Y = -3.0;
    vpc.Start.Z = 1.0;

    vpc.IDPos.X = -3.0;
    vpc.IDPos.Y = -2.0;
    vpc.IDPos.Z = 1.0;

    vpc.End.X = 4.0;
    vpc.End.Y = 3.0;
    vpc.End.Z = 1.0;
    vpc.Width = 9;

    graphics::Matrix3x3<double> Scale(1.0,1.0,1.0);

    graphics::Point3D<double> Pos(Player.Start.X, Player.Start.Y);

    // Card Mappings
    MapList Map;
    Map.Count = 13;
    Map.Map = (Mapping*) malloc(sizeof(Mapping)*Map.Count);
    Map.Map[0] = Mapping(2,"2");
    Map.Map[1] = Mapping(3,"3");
    Map.Map[2] = Mapping(4,"4");
    Map.Map[3] = Mapping(5,"5");
    Map.Map[4] = Mapping(6,"6");
    Map.Map[5] = Mapping(7,"7");
    Map.Map[6] = Mapping(8,"8");
    Map.Map[7] = Mapping(9,"9");
    Map.Map[8] = Mapping(10,"10");
    Map.Map[9] = Mapping(11,"J");
    Map.Map[10]= Mapping(12,"Q");
    Map.Map[11]= Mapping(13,"K");
    Map.Map[12]= Mapping(14,"A");

    // To keep the names and Levels in one place
    // Mapp of level and scoreing types
    // DO NOT USE MAP FUNCTIONS WITH THIS MAP and expext usefull reselts
    MapList ScoreMap;
    ScoreMap.Count = 11;
    ScoreMap.Map = (Mapping *)malloc(sizeof(Mapping)*ScoreMap.Count);
    ScoreMap.Map[0] = Mapping(0,"                ");
    ScoreMap.Map[1] = Mapping(1,"    High Card   ");
    ScoreMap.Map[2] = Mapping(1,"      Pair      ");
    ScoreMap.Map[3] = Mapping(1,"     Triple     ");
    ScoreMap.Map[4] = Mapping(1,"     Two Pair   ");
    ScoreMap.Map[5] = Mapping(1,"     Straight   ");
    ScoreMap.Map[6] = Mapping(1,"      Flush     ");
    ScoreMap.Map[7] = Mapping(1,"    Full House  ");
    ScoreMap.Map[8] = Mapping(1,"      Four      ");
    ScoreMap.Map[9] = Mapping(1," Straight Flush ");
    ScoreMap.Map[10] = Mapping(1,"  Royal Flush   ");

    int PScore = 0;
    // a balance?
    int TotalScore = 0;
    // will be set when a round it won and unset when the next one is started
    bool isWon = false;
    int TargetScore = 300;
    double TMut = 1.5;


    int Cost = 150;
    double CostMut = 1.75;


    unsigned int WinCount = 0;

    Title(Screen);

    bool HelpScreen = true;



    graphics::Input InputManager;
    InputManager.Init();
    InputManager.IO_BLOCK();
    char Input;


    int CheckResult = 0;


    bool isRunning = true;

    // Mark all cards as unused
    Player.D.UsedCount = 0;
    MarkDeckUnUsed(Player.D);

    Mode GameState = GAME;

    while(isRunning){

        Input = InputManager.SmartInput();

        switch(Input){
            case('q') :
                isRunning = false;
                break;
        }


        switch(GameState){
            case(PICKER):
                switch(Input){
                    case('n'):
                        Screen.ClearPixels(graphics::LightPixel, graphics::Black);
                        //Screen.PutText(Screen.Width*0.25,Screen.Height*0.25,"            ", graphics::Black);
                        RandomTranspher(Random,D,Player.D);
                        MarkDeckUnUsed(Player.D);
                        isWon = false;
                        PScore = 0;
                        TargetScore = TargetScore * TMut;
                        Player.DiscardCount = Player.DiscardLimit;
                        Player.HandCount = Player.HandLimit;
                        
                        GameState = GAME;
                        GameScreen(Screen,Player,Pos,vpc,Scale,Map,ScoreMap,PScore,TargetScore,WinCount);

                        break;
                    case('s'):
                        if(isWon){
                            GameState = STORE;
                            Shop(Screen, Player, ScoreMap, TotalScore, Cost);
                        }
                        break;
                }
                break;

            case(GAME):

                switch(Input){
                    case('W') :
                        if(Player.D.UsedCount < Player.UsedCardsLimit && Player.D.Cards[Player.Selected].IsUsed == false){
                            Player.D.Cards[Player.Selected].IsUsed = true;
                            Player.D.UsedCount +=1;
                        }
                        break;

                    case('S') :

                        if(Player.D.UsedCount > 0 && Player.D.Cards[Player.Selected].IsUsed == true){
                            Player.D.Cards[Player.Selected].IsUsed = false;
                            Player.D.UsedCount -=1;
                        }
                        break;

                    case('A') :
                        Player.Selected -=1;
                        if(Player.Selected < 0){
                            Player.Selected = Player.D.Count-1;
                        }
                        break;

                    case('D') :
                        Player.Selected +=1;
                        if(Player.Selected == Player.D.Count){
                            Player.Selected = 0;
                        }
                        break;

                        // Discard and draw
                    case('x'):
                        if(Player.DiscardCount > 0 && Player.D.UsedCount > 0){
                            RandomReplaceUsed(Random,D,Player.D);
                            Player.D.UsedCount = 0;
                            Player.DiscardCount = Player.DiscardCount -1;
                            CheckResult = 0;
                            MarkDeckUnUsed(Player.D);
                        }
                        break;

                    case('o'):
                        SortDeckID(Player.D);
                        break;

                    case('O'):
                        SortDeckSuit(Player.D);
                        break;

                    case('h'):
                        if(HelpScreen){
                            Help(Screen);
                        } else {
                            Screen.ClearPixels(graphics::LightPixel, graphics::Black,Screen.Width/2-15,Screen.Height/2-4, Screen.Width/2+50, Screen.Height/2+2);
                        }
                        HelpScreen = !HelpScreen;

                        break;

                        // Hand
                    case('z'):
                        if(Player.HandCount > 0 && Player.D.UsedCount > 0){
                            //Score Function (will take check result)
                            PScore += ScoreDeck(Player.D, ScoreMap,CheckResult);
                            RandomReplaceUsed(Random,D,Player.D);
                            Player.D.UsedCount = 0;
                            Player.HandCount = Player.HandCount -1;
                            CheckResult = 0;
                            MarkDeckUnUsed(Player.D);
                        }

                        break;
                }
                if(!isWon){
                    if(PScore >= TargetScore){
                        isWon = true;
                        WinCount = WinCount +1;
                        Screen.PutText(Screen.Width*0.25,Screen.Height*0.25,"            ", graphics::Black);
                        TotalScore += PScore;
                        RoundWin(Screen);
                        GameState = PICKER;
                    }
                }

                if(!isWon){
                    if(Player.HandCount == 0){
                        isRunning = false;
                    }
                }
                CheckResult = QuickCheck(Player.D);
                GameScreen(Screen,Player,Pos,vpc,Scale,Map,ScoreMap,PScore,TargetScore,WinCount);


                // Draw UI


                // Base Game Function
                break;
            case(STORE):
                switch(Input){
                    case('1'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[1].ID  = ScoreMap.Map[1].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;

                    case('2'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[2].ID  = ScoreMap.Map[2].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;

                    case('3'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[3].ID  = ScoreMap.Map[3].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;
                    case('4'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[4].ID  = ScoreMap.Map[4].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;
                    case('5'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[5].ID  = ScoreMap.Map[5].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;
                    case('6'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[6].ID  = ScoreMap.Map[6].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;
                    case('7'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[7].ID  = ScoreMap.Map[7].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;
                    case('8'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[8].ID  = ScoreMap.Map[8].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;
                    case('9'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[9].ID  = ScoreMap.Map[9].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;

                    case('0'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            ScoreMap.Map[10].ID  = ScoreMap.Map[10].ID + 1;
                            Cost = Cost * CostMut;
                        }
                        break;

                    case('z'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            Player.HandLimit = Player.HandLimit + 1;
                            Cost = Cost * CostMut;
                        }
                        break;

                    case('x'):
                        if(TotalScore >= Cost){
                            TotalScore = TotalScore - Cost;
                            Player.DiscardLimit = Player.DiscardLimit + 1;
                            Cost = Cost * CostMut;
                        }
                        break;

                    
                    case('n'):
                        Screen.ClearPixels(graphics::LightPixel, graphics::Black);
                        //Screen.PutText(Screen.Width*0.25,Screen.Height*0.25,"            ", graphics::Black);
                        RandomTranspher(Random,D,Player.D);
                        MarkDeckUnUsed(Player.D);
                        isWon = false;
                        PScore = 0;
                        TargetScore = TargetScore * TMut;
                        Player.DiscardCount = Player.DiscardLimit;
                        Player.HandCount = Player.HandLimit;
                        
                        GameState = GAME;
                        GameScreen(Screen,Player,Pos,vpc,Scale,Map,ScoreMap,PScore,TargetScore,WinCount);

                        break;
                }
                if(GameState == STORE){
                    Shop(Screen, Player, ScoreMap, TotalScore, Cost);
                }
                break;
        }


        // end of general inputs


    }

    InputManager.Restore();
    puts(graphics::Color_Off);
    puts("");

    return 0;
}
