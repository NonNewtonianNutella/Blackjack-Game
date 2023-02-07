// Jeremy Zheng - ICS4U1-1 - Final Summative
//header file
#include <vector>
#include <iostream>
using namespace std;

//function prototypes

//PARENT CLASS
class Deck{
  public:
    vector<string>hand;
    string drawCard(vector<string>& deck);
    int getPoints();
    void getValue(string card);
};


//CHILD CLASSES
class Player: public Deck{
  private:
    int bet;
  public:
    //Player bet constructor
    Player(int bet) : bet(bet){}
    
    int getBet(int bet);
    string getMove(int turn);
};

class Dealer: public Deck{
  public:
};

class Blackjack: public Deck{
  public:
    vector<string>deck;
    void setDeck();
    void displayHands(Player &a,Dealer &b,bool showDealerHand=false);
    void displayCards(vector<string>a);
    void startGame(Blackjack &game, Player &a, Dealer &b);
    //Blackjack Constructors
    Blackjack(vector<string>deck) : deck(deck){}
    Blackjack(){}
};