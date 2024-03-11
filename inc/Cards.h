#ifndef CARDS_H
#define CARDS_H
#include "SimpleRandom/simplerandom.hpp"
#include <stdlib.h>


const char * const CClub = "󰣎";
const char * const CHeart = "";
const char * const CSpade = "󰣑";
const char * const CDiamond = "󰣏";

typedef struct Card{
    int ID;
    int Value;
    char Suit;
    bool IsUsed;

    Card(int ID = 0, int Value = 0, char Suit = 'S', bool IsUsed = false) : ID(ID), Value(Value), Suit(Suit), IsUsed(IsUsed){
        this->IsUsed = IsUsed;
    }
}Card;

typedef struct Deck{
    int Count;
    int UsedCount;
    Card *Cards;
    Deck(int Count = 0, int UsedCount = 0, Card *Cards = NULL){
        this->Count = Count;
        this->UsedCount = UsedCount;
        if(Cards != NULL){
            this->Cards = (Card *)malloc(sizeof(Card)*Count);
        } else{
            this->Cards = Cards;
        }
    }
}Deck;


inline Card GetCard(Deck &D,int Index){
    int Temp;
    int check = Index < 0 ? -1 : 1;
    Index = Index * check;
    if(Index > (D.Count-1)){
        Temp = Index - (D.Count-1);
        if(Temp > (D.Count-1)){
            Temp = Temp%(D.Count-1);
        }

        return D.Cards[Temp];
    } else {
        return D.Cards[Index];
    }

}

inline int GetCardPos(Deck &D,int Index){
    int Temp;
    int check = Index < 0 ? -1 : 1;
    Index = Index * check;
    if(Index > (D.Count-1)){
        Temp = Index - (D.Count-1);
        if(Temp > (D.Count-1)){
            Temp = Temp%(D.Count-1);
        }
        return Temp;
    } else {
        return Index;
    }

}

inline Card *MakeEmptyDeck(int Count){
    return (Card *) malloc(sizeof(Card)*Count);
}

inline void MakeDeckStandard(Deck &D){
    D.Count = 0;
    D.UsedCount = 0;
    D.Cards = (Card *) malloc(sizeof(Card)*52);

    for(int i = 2; i < 15; i++){
        if(i <= 10){
            D.Cards[D.Count].ID = i;
            D.Cards[D.Count].Value = i;
            D.Cards[D.Count].Suit = 'S';
            D.Cards[D.Count].IsUsed = false;

            D.Cards[D.Count+1].ID = i;
            D.Cards[D.Count+1].Value = i;
            D.Cards[D.Count+1].Suit = 'H';
            D.Cards[D.Count+1].IsUsed = false;
            
            D.Cards[D.Count+2].ID = i;
            D.Cards[D.Count+2].Value = i;
            D.Cards[D.Count+2].Suit = 'C';
            D.Cards[D.Count+2].IsUsed = false;

            D.Cards[D.Count+3].ID = i;
            D.Cards[D.Count+3].Value = i;
            D.Cards[D.Count+3].Suit = 'D';
            D.Cards[D.Count+2].IsUsed = false;
        }
        if( i >= 11){
            D.Cards[D.Count].ID = i;
            D.Cards[D.Count].Value = 11;
            D.Cards[D.Count].Suit = 'S';
            D.Cards[D.Count].IsUsed = false;

            D.Cards[D.Count+1].ID = i;
            D.Cards[D.Count+1].Value = 11;
            D.Cards[D.Count+1].Suit = 'H';
            D.Cards[D.Count+1].IsUsed = false;
            
            D.Cards[D.Count+2].ID = i;
            D.Cards[D.Count+2].Value = 11;
            D.Cards[D.Count+2].Suit = 'C';
            D.Cards[D.Count+2].IsUsed = false;

            D.Cards[D.Count+3].ID = i;
            D.Cards[D.Count+3].Value = 11;
            D.Cards[D.Count+3].Suit = 'D';
            D.Cards[D.Count+3].IsUsed = false;
        }

        D.Count = D.Count +4;
    }
}

inline void MarkDeckUnUsed(Deck &D){
    for(int i = 0; i < D.Count; i++){
        D.Cards[i].IsUsed = false;
    }
}

// Marks all transphers cards in origin deck to IsUsed 
inline void RandomTranspher(simplerandom &Random,Deck &D, Deck &Out){
    int Temp;
    if(D.UsedCount + Out.Count > D.Count){
        MarkDeckUnUsed(D);
    }
    for(int i = 0; i < Out.Count; i++){
        Temp = GetCardPos(D,Random.Next());

        if(D.Cards[Temp].IsUsed == false){
            Out.Cards[i] = D.Cards[Temp];
            D.Cards[Temp].IsUsed = true;
        } else {
            while(D.Cards[Temp].IsUsed == true){
                if(Temp == D.Count-1){
                    Temp = 0;
                } else {
                    Temp += 1;
                }
            }
            Out.Cards[i] = GetCard(D,Temp);
            D.Cards[Temp].IsUsed = true;
        }

        D.UsedCount += 1;

    }
}


inline void TransferDeck(Deck &D, Deck &Out){
    if(D.Count <= Out.Count){
        for(int i = 0; i < D.Count; i++){
            Out.Cards[i] = D.Cards[i];
        }
        Out.UsedCount = D.UsedCount;
    }
}



inline void RandomReplaceUsed(simplerandom &Random, Deck &D, Deck &Out){
    if(Out.UsedCount == 0){
        return;
    }

    int Temp;

    if(D.UsedCount + Out.UsedCount > D.Count){
        MarkDeckUnUsed(D);
    }
    for(int i = 0; i < Out.Count; i++){
        if(Out.Cards[i].IsUsed == true){
            Temp = GetCardPos(D,Random.Next());
            if(D.Cards[Temp].IsUsed == false){
                Out.Cards[i] = D.Cards[Temp];
                D.Cards[Temp].IsUsed = true;
            } else {
                while(D.Cards[Temp].IsUsed == true){
                    if(Temp == D.Count-1){
                        Temp = 0;
                    } else {
                        Temp += 1;
                    }
                }
                Out.Cards[i] = GetCard(D,Temp);
                D.Cards[Temp].IsUsed = true;
            }

            D.UsedCount += 1;

        }
    }

}


inline void SortDeckID(Deck &D){
    bool sorted = false;
    Card Temp = 0;

    for(int i = 0; i < D.Count; i++){
        sorted = false;
        for(int j = 0; j < D.Count -1; j++){
            if(D.Cards[j].ID > D.Cards[j+1].ID){
                Temp = D.Cards[j];
                D.Cards[j] = D.Cards[j+1];
                D.Cards[j+1] = Temp;
                sorted = true;
            }
        }
        if(!sorted){
            return;
        }
    }
}

inline void SortDeckValue(Deck &D){
    bool sorted = false;
    Card Temp = 0;

    for(int i = 0; i < D.Count; i++){
        sorted = false;
        for(int j = 0; j < D.Count -1; j++){
            if(D.Cards[j].Value > D.Cards[j+1].Value){
                Temp = D.Cards[j];
                D.Cards[j] = D.Cards[j+1];
                D.Cards[j+1] = Temp;
                sorted = true;
            }
        }
        if(!sorted){
            return;
        }
    }
}

inline void SortDeckSuit(Deck &D){
    bool sorted = false;
    Card Temp = 0;

    for(int i = 0; i < D.Count; i++){
        sorted = false;
        for(int j = 0; j < D.Count -1; j++){
            if(D.Cards[j].Suit > D.Cards[j+1].Suit){
                Temp = D.Cards[j];
                D.Cards[j] = D.Cards[j+1];
                D.Cards[j+1] = Temp;
                sorted = true;
            }
        }
        if(!sorted){
            return;
        }
    }
}


// Else high card

inline int IsPair(Deck &D,int IDSkip = 0){
    Card A;
    if(IDSkip == -1){
        return -1;
    }
    if(D.UsedCount < 2){
        return -1;
    }
    for(int i = 0; i < D.Count; i++){
        if(D.Cards[i].IsUsed && D.Cards[i].ID != IDSkip){
            A = D.Cards[i];
            for(int j = 0; j < D.Count; j++){
                if(i != j && D.Cards[j].IsUsed){
                    if(D.Cards[j].ID == A.ID){
                        return A.ID;
                    }
                }
            }
        }

    }
    return -1;
}


inline int IsThree(Deck &D,int IDSkip = 0){
    Card A,B;
    if(IDSkip == -1){
        return -1;
    }
    if(D.UsedCount < 3){
        return -1;
    }
    for(int a = 0; a < D.Count; a++){
        if(D.Cards[a].IsUsed && D.Cards[a].ID != IDSkip){
            A = D.Cards[a];
            for(int b = a; b < D.Count; b++){
                if(D.Cards[b].IsUsed && b != a){
                    B = D.Cards[b];
                    for(int c = b; c < D.Count; c++){
                        if(D.Cards[c].IsUsed && b != c && b != a){
                            if(A.ID == D.Cards[c].ID && B.ID == D.Cards[c].ID){
                            return B.ID;
                            }
                        }
                    }
                }
            }
        }

    }
    return -1;
}

inline int IsTwoPair(Deck &D){
    if(D.UsedCount < 4){
        return -1;
    }
    if(IsPair(D,IsPair(D)) > -1){
        return 1;
    }
    return -1;
}

inline int IsFlush(Deck &D){
    Card A;
    int Count = 0;
    if(D.UsedCount < 5){
        return -1;
    }
    for(int i = 0; i < D.Count; i++){
        if(D.Cards[i].IsUsed){
            A = D.Cards[i];
            Count = 1;
            for(int j = 0; j < D.Count; j++){
                if(D.Cards[j].IsUsed && j != i){
                    if(A.Suit == D.Cards[j].Suit){
                        Count +=1;
                        if(Count == 5){
                            return A.Suit;
                        }
                    }
                }
            }
            // should not need to loop hole deck more than once
            Count = 0;
        }

    }
    return -1;
}

inline int IsStraight(Deck &D){
    Card A;
    Deck Temp;
    Temp.Count = D.Count;
    Temp.Cards = MakeEmptyDeck(Temp.Count);
    TransferDeck(D,Temp);
    SortDeckID(Temp);
    int Count = 0;
    if(D.UsedCount < 5){
        return -1;
    }
        
    for(int i = 0; i < Temp.Count; i++){
        if(D.Cards[i].IsUsed){
            A = Temp.Cards[i];
            Count = 1;
            for(int j = 0; j < Temp.Count; j++){
                if(Temp.Cards[j].IsUsed && j != i){
                    if(A.ID == Temp.Cards[j].ID - Count || A.ID == Temp.Cards[j].ID + Count ){
                        Count = Count + 1;
                    } else if(A.ID == Temp.Cards[Temp.Count-j].ID - Count || A.ID == Temp.Cards[Temp.Count-j].ID + Count ){
                        Count = Count + 1;
                    }

                    if(Count == 5){
                        return A.ID;
                    }
                }
            }
            // should not need to loop hole deck more than once
            Count = 0;
        }

    }

    
    return -1;
}


// not perfect , lol
inline int IsFullHouse(Deck &D){
    int C;
    C = IsThree(D);
    if(C == -1){
        return -1;
    }
    if(IsPair(D,IsThree(D)) > -1){
        return 1;
    }
    return -1;
}

inline int IsFour(Deck &D, int IDSkip = 0){
    Card A,B,C;
    if(IDSkip == -1){
        return -1;
    }
    if(D.UsedCount < 4){
        return -1;
    }
    for(int a = 0; a < D.Count; a++){
        if(D.Cards[a].IsUsed && D.Cards[a].ID != IDSkip){
            A = D.Cards[a];
            for(int b = a; b < D.Count; b++){
                if(D.Cards[b].IsUsed && b != a){
                    B = D.Cards[b];
                    for(int c = b; c < D.Count; c++){
                        if(D.Cards[c].IsUsed && b != c && b != a){
                            if(A.ID == D.Cards[c].ID && B.ID == D.Cards[c].ID){
                                C = D.Cards[c];
                                for(int d = c; d < D.Count; d++){
                                    if(D.Cards[d].IsUsed && d != c){
                                        if(C.ID == D.Cards[d].ID){
                                            return D.Cards[d].ID;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    return -1;
}

inline int IsStraightFlush(Deck &D){
    if(IsStraight(D) > -1 && IsFlush(D) > -1){
        return 1;
    }
    return -1;
}

inline int IsRoyalFlush(Deck &D, int HighCard = 15){
    // 15 is the default mapping for a Ace
    if(IsStraight(D) == HighCard && IsFlush(D) > -1){
        return 1;
    }
    return -1;
}


inline int QuickCheck(Deck &D){
    int check = 0;

    if(D.UsedCount < 1){
        return 0;
    }

    check = IsRoyalFlush(D);
    if(check > -1){
        return 10;
    }

    check = IsStraightFlush(D);
    if(check > -1){
        return 9;
    }
    
    check = IsFour(D);
    if(check > -1){
        return 8;
    }
    
    check = IsFullHouse(D);
    if(check > -1){
        return 7;
    }

    check = IsFlush(D);
    if(check > -1){
        return 6;
    }

    check = IsStraight(D);
    if(check > -1){
        return 5;
    }

    check = IsTwoPair(D);
    if(check  > -1){
        return 4;
    }

    check = IsThree(D);
    if(check > -1){
        return 3;
    }

    check = IsPair(D);
    if(check > -1){
        return 2;
    }

    return 1;
}


typedef struct Mapping{
    int ID;
    const char *Value;
    Mapping(int ID, const char *Value) : ID(ID), Value(Value){}
    ~Mapping(){
    }
} Mapping;

typedef struct MapList{
    int Count;
    Mapping *Map;
} MapList;


inline const char* MapLookUp(MapList &M, Card &C){
    for(int i = 0; i < M.Count; i++){
        if(M.Map[i].ID == C.ID){
            return M.Map[i].Value;
        }
    }
    return "";
}


// So we dont sort the deck
inline int ScoreDeck(Deck D,MapList SLMap, int QCResult = -1){
    int Score = 0;
    int BaseScore = 10;
    double BaseMut = 1.0;

    int tmp = 0;
    if(QCResult == -1){
        return -1;
    }

    switch(QCResult){
        case(1):
            for(int i = D.Count; i > 0; i--){
                if(D.Cards[i].IsUsed){
                    tmp = D.Cards[i].Value;
                    for(int j = D.Count; j > 0; j--){
                        if(D.Cards[j].IsUsed && D.Cards[j].Value > tmp){
                            tmp = D.Cards[i].Value;
                        }
                    }
                }

                Score = tmp + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
                break;
            }
            break;
        case(2):
            Score = (QCResult * IsPair(D)) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            break;
        case(3):
            Score = (QCResult * IsThree(D)) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            break;
        case(4):
            tmp = IsPair(D);
            Score = (QCResult * IsPair(D)) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            Score = 2 * (Score  + (QCResult * IsPair(D,tmp)) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID));
            break;
        case(5):
            for(int i = 0; i < D.Count; i++){
                Score = Score + D.Cards[i].Value;
            }
            Score = (Score * 3)  + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            break;
        case(6):
            for(int i = 0; i < D.Count; i++){
                Score = Score + D.Cards[i].Value;
            }
            Score = (Score*3) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            break;
        case(7):
            tmp = IsThree(D);
            Score = (QCResult * IsThree(D)) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            Score = (Score*4) + (QCResult * IsPair(D,tmp)) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            break;
        case(8):
            Score = 5 * (QCResult * IsFour(D)) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            break;
        case(9):
            for(int i = 0; i < D.Count; i++){
                Score = Score + D.Cards[i].Value;
            }
            Score = (Score * 5) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            break;
        case(10):
            Score = (111 * IsRoyalFlush(D)) + (BaseScore*SLMap.Map[QCResult].ID ) * (BaseMut + SLMap.Map[QCResult].ID);
            break;
    }

    return Score;
}


#endif

