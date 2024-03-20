#include "inc/Cards.h"
#include "inc/TerminalGraphics/tgraphics.hpp"
#include "inc/SimpleRandom/simplerandom.hpp"
#include "inc/GCards.h"
#include "inc/GameScreens.h"

// S : Spades
// H : Harts
// C : Clubs
// D : Diamonds

// Jack ID 11 Value 11
// Queen ID 12 Value 11 

enum Mode{GAME,STORE,PICKER,LOSE};

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

    Player.HealthLimit = 100;
    Player.DiscardLimit = 4;
    Player.Shild = 0;
    Player.DiscardCount = Player.DiscardLimit;
    Player.Health = Player.HealthLimit;

    SimpleHand Enamy;
    Enamy.D.Count = 8;
    // Will alway use all cards
    Enamy.D.Cards = MakeEmptyDeck(Enamy.D.Count);
    RandomTranspher(Random,D,Enamy.D);

    Enamy.D.UsedCount = 8;
    Enamy.HealthLimit = 100;
    Enamy.Health = Enamy.HealthLimit;

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



    MapList EnamyScoreMap;
    EnamyScoreMap.Count = 11;
    EnamyScoreMap.Map = (Mapping *)malloc(sizeof(Mapping)*EnamyScoreMap.Count);
    EnamyScoreMap.Map[0] = Mapping(0,"                ");
    EnamyScoreMap.Map[1] = Mapping(1,"    High Card   ");
    EnamyScoreMap.Map[2] = Mapping(1,"      Pair      ");
    EnamyScoreMap.Map[3] = Mapping(1,"     Triple     ");
    EnamyScoreMap.Map[4] = Mapping(1,"     Two Pair   ");
    EnamyScoreMap.Map[5] = Mapping(1,"     Straight   ");
    EnamyScoreMap.Map[6] = Mapping(1,"      Flush     ");
    EnamyScoreMap.Map[7] = Mapping(1,"    Full House  ");
    EnamyScoreMap.Map[8] = Mapping(1,"      Four      ");
    EnamyScoreMap.Map[9] = Mapping(1," Straight Flush ");
    EnamyScoreMap.Map[10] = Mapping(1,"  Royal Flush   ");

    int PScore = 0;
    // a balance?
    int Balance = 0;
    // will be set when a round it won and unset when the next one is started
    bool isWon = false;

    // Enamy Score
    int TargetScore = 300;
    double TMut = 1.5;

    int OldTargetScore = Random.RangedNext(1,500);


    int Cost = 150;
    double CostMut = 1.75;
    int ShopSelect = 1;
    int ShopSelectLimit = 12;


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
    
    MarkDeckUsed(Enamy.D);
    CheckResult = QuickCheck(Enamy.D);
    TargetScore = ScoreDeck(Enamy.D,EnamyScoreMap,CheckResult);

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
                        

                        if(WinCount%3==0){
                            Enamy.HealthLimit = Enamy.HealthLimit * TMut;
                            EnamyScoreMap.Map[Random.RangedNext(1,10)].ID += 1;
                            EnamyScoreMap.Map[Random.RangedNext(1,10)].ID += 1;
                            EnamyScoreMap.Map[Random.RangedNext(1,10)].ID += 1;
                        }

                        Enamy.Health = Enamy.HealthLimit;
                            
                        OldTargetScore = TargetScore;
                        RandomReplaceUsed(Random,D,Enamy.D);
                        MarkDeckUsed(Enamy.D);
                        CheckResult = QuickCheck(Enamy.D);
                        TargetScore = ScoreDeck(Enamy.D,EnamyScoreMap,CheckResult);
                        //TargetScore = TargetScore * TMut;
                        Player.DiscardCount = Player.DiscardLimit;
                        //Player.Health = Player.HealthLimit;
                        Balance = Balance *2;
                        
                        GameState = GAME;
                        GameScreen(Screen,Player,Pos,vpc,Scale,Map,ScoreMap,PScore,TargetScore,OldTargetScore,WinCount, Enamy);

                        break;
                    case('s'):
                        if(isWon){
                            GameState = STORE;
                            Shop(Screen, Player, ScoreMap, Balance, Cost,ShopSelect);
                        }
                        break;
                }
                break;

            case(LOSE):
                LoseScreen(Screen);
                switch(Input){
                    case('r'):
                        // Reset Player Stats
                        Player.DiscardLimit = 4;
                        Player.DiscardCount = Player.DiscardLimit;
                        Player.Health = Player.HealthLimit;
                        Player.Shild = 0;

                        RandomTranspher(Random,D,Player.D);
                        MarkDeckUnUsed(Player.D);

                        Balance = 0;
                        PScore = 0;
                        OldTargetScore = 0;
                        Cost = 150;
                        SetMapAllMapIDs(ScoreMap,1);
                        SetMapAllMapIDs(EnamyScoreMap,1);

                        RandomReplaceUsed(Random,D,Enamy.D);
                        MarkDeckUsed(Enamy.D);
                        CheckResult = QuickCheck(Enamy.D);
                        TargetScore = ScoreDeck(Enamy.D,EnamyScoreMap,CheckResult);

                        GameState = GAME;
                        Screen.ClearPixels(graphics::LightPixel, graphics::Black);
                        GameScreen(Screen,Player,Pos,vpc,Scale,Map,ScoreMap,PScore,TargetScore,OldTargetScore,WinCount, Enamy);
                        break;
                }

                // Show Lose Screen
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
                        if(Player.Health > 0 && Player.D.UsedCount > 0){
                            // Simple Battle Logic
                            //Score Function (will take check result)

                            PScore = ScoreDeck(Player.D, ScoreMap,CheckResult);
                            if(TargetScore > PScore){
                                if(Player.Shild > 0){
                                    Player.Shild = Player.Shild - 1;
                                } else {
                                    Player.Health = Player.Health - (TargetScore - PScore);
                                }
                            } else {
                                Enamy.Health = Enamy.Health - (PScore -TargetScore);
                                Balance = Balance + (PScore -TargetScore);
                            }

                            OldTargetScore = TargetScore;
                            RandomReplaceUsed(Random,D,Enamy.D);
                            MarkDeckUsed(Enamy.D);

                            CheckResult = QuickCheck(Enamy.D);
                            TargetScore = ScoreDeck(Enamy.D,EnamyScoreMap,CheckResult);


                            RandomReplaceUsed(Random,D,Player.D);
                            Player.D.UsedCount = 0;
                            //Player.Health = Player.Health -1;
                            CheckResult = 0;
                            MarkDeckUnUsed(Player.D);
                        }

                        break;
                }
                if(!isWon){
                    if(Enamy.Health <= 0){
                        isWon = true;
                        WinCount = WinCount +1;
                        Screen.PutText(Screen.Width*0.25,Screen.Height*0.25,"            ", graphics::Black);
                        Balance += PScore;
                        RoundWin(Screen);
                        GameState = PICKER;
                    }
                }


                CheckResult = QuickCheck(Player.D);
                GameScreen(Screen,Player,Pos,vpc,Scale,Map,ScoreMap,PScore,TargetScore,OldTargetScore,WinCount, Enamy);

                if(!isWon){
                    if(Player.Health <= 0){
                        GameState = LOSE;
                        LoseScreen(Screen);

                    }
                }

                // Base Game Function
                break;
            case(STORE):
                switch(Input){

                    case('W') :
                        if(ShopSelect <= 2){
                            ShopSelect = (ShopSelectLimit - 2) + ShopSelect;
                        } else {
                            ShopSelect = ShopSelect - 2;
                        }
                        break;

                    case('S') :
                        if(ShopSelect >= ShopSelectLimit - 1){
                            ShopSelect = ShopSelect - (ShopSelectLimit-2);
                        } else {
                            ShopSelect = ShopSelect + 2;
                        }
                        if(ShopSelect > ShopSelectLimit){
                            ShopSelect = 1;
                        }

                        break;

                    case('A') :
                        if(ShopSelect%2==2){
                            ShopSelect = ShopSelect + 1;
                        } else {
                            ShopSelect = ShopSelect - 1;
                        }
                        if(ShopSelect == 0){
                            ShopSelect = 1;
                        }
                        break;

                    case('D') :
                        if(ShopSelect%2==2){
                            ShopSelect = ShopSelect - 1;
                        } else {
                            ShopSelect = ShopSelect + 1;
                        }
                        if(ShopSelect >= ShopSelectLimit){
                            ShopSelect = ShopSelectLimit;
                        }
                        break;

                    case('z'):
                        if(Balance >= Cost){
                            Balance = Balance - Cost;
                            switch(ShopSelect){
                                case(1):
                                        ScoreMap.Map[1].ID  = ScoreMap.Map[1].ID + 1;
                                    break;

                                case(2):
                                        ScoreMap.Map[2].ID  = ScoreMap.Map[2].ID + 1;
                                    break;

                                case(3):
                                        ScoreMap.Map[3].ID  = ScoreMap.Map[3].ID + 1;
                                    break;
                                case(4):
                                        ScoreMap.Map[4].ID  = ScoreMap.Map[4].ID + 1;
                                    break;
                                case(5):
                                        ScoreMap.Map[5].ID  = ScoreMap.Map[5].ID + 1;
                                    break;
                                case(6):
                                        ScoreMap.Map[6].ID  = ScoreMap.Map[6].ID + 1;
                                    break;
                                case(7):
                                        ScoreMap.Map[7].ID  = ScoreMap.Map[7].ID + 1;
                                    break;
                                case(8):
                                        ScoreMap.Map[8].ID  = ScoreMap.Map[8].ID + 1;
                                    break;
                                case(9):
                                        ScoreMap.Map[9].ID  = ScoreMap.Map[9].ID + 1;
                                    break;

                                case(10):
                                        ScoreMap.Map[10].ID  = ScoreMap.Map[10].ID + 1;
                                    break;
                                case(11):
                                    Player.Shild = Player.Shild + 1;
                                    break;
                                case(12):
                                    Player.DiscardLimit = Player.DiscardLimit + 1;
                                    break;
                            }

                            Cost = Cost * CostMut;
                        }
                        break;

                    case('x'):
                        if(Balance >= Cost){
                            Balance = Balance - Cost;
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
                        //TargetScore = TargetScore * TMut;
                        Player.DiscardCount = Player.DiscardLimit;


                        if(WinCount%3==0){
                            Enamy.HealthLimit = Enamy.HealthLimit * TMut;
                            EnamyScoreMap.Map[Random.RangedNext(1,10)].ID += 1;
                            EnamyScoreMap.Map[Random.RangedNext(1,10)].ID += 1;
                            EnamyScoreMap.Map[Random.RangedNext(1,10)].ID += 1;
                        }

                        Enamy.Health = Enamy.HealthLimit;
                        OldTargetScore = TargetScore;
                        RandomReplaceUsed(Random,D,Enamy.D);
                        MarkDeckUsed(Enamy.D);
                        CheckResult = QuickCheck(Enamy.D);
                        TargetScore = ScoreDeck(Enamy.D,EnamyScoreMap,CheckResult);

                        GameState = GAME;
                        GameScreen(Screen,Player,Pos,vpc,Scale,Map,ScoreMap,PScore,TargetScore,OldTargetScore,WinCount, Enamy);

                        break;
                }
                if(GameState == STORE){
                    Shop(Screen, Player, ScoreMap, Balance, Cost, ShopSelect);
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
