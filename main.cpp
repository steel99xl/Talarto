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
    vpc.Start.X = -3.0;
    vpc.Start.Y = -3.0;
    vpc.Start.Z = 1.0;

    vpc.IDPos.X = -2.0;
    vpc.IDPos.Y = -2.0;
    vpc.IDPos.Z = 1.0;

    vpc.End.X = 3.0;
    vpc.End.Y = 3.0;
    vpc.End.Z = 1.0;
    vpc.Width = 7;

    graphics::Matrix3x3<double> Scale(1.0,1.0,1.0);

    graphics::Point3D<double> Pos(Player.Start.X, Player.Start.Y);

    char *IBuff = new char[20];

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
    int TargetScore = 300;
    double TMut = 1.5;


    unsigned int WinCount = 0;


    Title(Screen);


    graphics::Input InputManager;
    InputManager.Init();
    InputManager.IO_BLOCK();
    char Input;


    int CheckResult = 0;


    bool isRunning = true;


    Player.D.UsedCount = 0;

    while(isRunning){
        Input = InputManager.SmartInput();

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

            case('d'):
                RandomTranspher(Random,D,Player.D);
                Player.D.UsedCount = 0;
                break;

            // Discard and draw
            case('x'):
                if(Player.DiscardCount > 0 && Player.D.UsedCount > 0){
                    RandomReplaceUsed(Random,D,Player.D);
                    Player.D.UsedCount = 0;
                    Player.DiscardCount = Player.DiscardCount -1;
                    CheckResult = 0;
                }
                break;

            case('o'):
                SortDeckID(Player.D);
                break;

            case('O'):
                SortDeckSuit(Player.D);
                break;

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
                }

                break;
            case('q') :
                isRunning = false;
                break;
        }


        if(PScore >= TargetScore){
            Screen.PutText(Screen.Width*0.25,Screen.Height*0.25,"            ", graphics::Black);
            PScore = 0;
            TargetScore = TargetScore * TMut;
            if(WinCount%3 == 0 && WinCount >= 3){
                ScoreMap.Map[CheckResult].ID = ScoreMap.Map[Random.RangedNext(1,10)].ID + Random.RangedNext(2,10);
                ScoreMap.Map[CheckResult].ID = ScoreMap.Map[Random.RangedNext(1,10)].ID + Random.RangedNext(2,10);
                ScoreMap.Map[CheckResult].ID = ScoreMap.Map[Random.RangedNext(1,10)].ID + Random.RangedNext(2,10);
                Player.DiscardLimit += Random.RangedNext(1,3);
                Player.HandLimit += Random.RangedNext(1,3);
            } else {
                ScoreMap.Map[CheckResult].ID = ScoreMap.Map[Random.RangedNext(1,10)].ID + Random.RangedNext(2,10);
            }
            Player.DiscardCount = Player.DiscardLimit;
            Player.HandCount = Player.HandLimit;
        }


        if(Player.HandCount == 0){
                isRunning = false;
        }





        // Draw UI
        

        CheckResult = QuickCheck(Player.D);
        Screen.PutText(Screen.Width*0.05,Screen.Height*0.3,ScoreMap.Map[CheckResult].Value);

        sprintf(IBuff, "%d", Player.DiscardCount);
        Screen.PutText(Screen.Width*0.10,Screen.Height*0.35,"Discards",graphics::White_On_Red);
        Screen.PutText(Screen.Width*0.20,Screen.Height*0.35,IBuff, graphics::White_On_Red);

        sprintf(IBuff, "%d", Player.HandCount);
        Screen.PutText(Screen.Width*0.10,Screen.Height*0.37,"  Hands ", graphics::White_On_Blue);
        Screen.PutText(Screen.Width*0.20,Screen.Height*0.37,IBuff, graphics::White_On_Blue);


        sprintf(IBuff, "%d", PScore);
        Screen.PutText(Screen.Width*0.10,Screen.Height*0.25,"Score : ", graphics::Yellow_On_Blue);
        Screen.PutText(Screen.Width*0.25,Screen.Height*0.25,IBuff, graphics::Yellow_On_Blue);

        sprintf(IBuff, "%d", TargetScore);
        Screen.PutText(Screen.Width*0.10,Screen.Height*0.2,"TargetScore : ", graphics::Yellow_On_Red);
        Screen.PutText(Screen.Width*0.25,Screen.Height*0.2,IBuff, graphics::Yellow_On_Red);

        Pos.X = Player.Start.X;
        DrawHand(Screen,Player,vpc,Map,Pos,Scale);

        Pos.X = Player.Start.X+(vpc.Width * Player.Selected);

        DrawSelectedCard(Screen,Player,vpc,Map,Pos,Scale);

        Screen.Show();

    }

    InputManager.Restore();
    puts(graphics::Color_Off);
    puts("");

    return 0;
}
