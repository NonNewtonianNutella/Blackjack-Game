// Jeremy Zheng - ICS4U1-1 - Final Summative
//function file
#include <algorithm>  
#include <vector>
#include <iostream>
#include <iomanip>
#include <unordered_map>

#include "header.h"
using namespace std;

//resets deck vector
void Blackjack::setDeck(){
  //standard deck values and suits
  vector<string>cardType {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
  vector<string>suitType {"C","D","H","S"};
  deck.resize(52);
  //populate vector
  int x=0;
  int y=0;
  for(int i=0;i<52;i++){
    deck[i] = cardType[x] + suitType[y];
    if((i+1)%4==0){
      x++;
      y = 0;
    }else{
      y++;
    }
  }
}
//draw random card from deck
string Deck::drawCard(vector<string>& deck){
  srand(time(NULL));
  int size = deck.size();
  int i = rand()%size;
  //swap random card with last card
  swap(deck[i], deck.back());
  string card = deck.back();
  //remove last card
  deck.pop_back();
  return card;
}

//player starts game with 2 cards
//dealer starts with 1 card face-down
void Blackjack::startGame(Blackjack &game, Player &a, Dealer &b){
  
  a.hand = {drawCard(deck), drawCard(deck)};
  b.hand = {"BACKSIDE" + drawCard(deck), drawCard(deck)};
  //show initial hand
  displayHands(a, b, false);
}

//show both hands
void Blackjack::displayHands(Player &a,Dealer &b,bool showDealerHand){
  //final turn (dealer reveals face-down card)
  if(showDealerHand){
    for(int i=0;i<b.hand.size();i++){
      if(b.hand[i].substr(0,8) == "BACKSIDE"){
        b.hand[i] = b.hand[i].substr(8);
      }
    }
    //reveal dealer points
    cout << "Dealer Points: " << b.getPoints() << endl;
    displayCards(b.hand);

  //show both hands
  }else{
    cout << "\nDealer: ???\n";
    displayCards(b.hand);
  }
  cout << "Player Points: " << a.getPoints() << endl;
  displayCards(a.hand);
}

//format and display cards
void Blackjack::displayCards(vector<string>hand){

  //array for hand cards
  string rows[5] = {"", "", "", "", ""};
  
  for(int i=0;i<hand.size();i++){
    rows[0] += " ___  ";
    //if not final turn
    //dealer card is face-down
    if(hand[i].substr(0,8) == "BACKSIDE"){
      rows[1] += "|## | ";
      rows[2] += "|###| ";
      rows[3] += "|_##| ";

    //get cardType and suitType
    }else{
      string rank; char suit;
      if(hand[i].size()==3){
        rank = "10";
        suit = hand[i][2];
      }else{
      stringstream ss; ss << hand[i][0];
      ss >> rank;
      ss.clear();
      suit = hand[i][1];
      }
      //map for card suits
      unordered_map<char,string>map{{'C',"♣"},{'D',"♦"},{'H',"♥"},{'S',"♠"}};
      string sym = map[suit];

      //formatting card
      stringstream ss;
      ss << "|" << left << setw(2) << rank << " | ";
      string top = ss.str();
      ss.str("");
      ss << "|_" << right << setw(2) << rank << "| ";
      string bottom = ss.str();
      ss.str("");
      rows[1] += top;
      rows[2] += "| " + sym + " | ";
      rows[3] += bottom;
    }
  }
  //output cards
  for(string row : rows){
    cout << row << endl;
  }
}

//get player hand value
int Deck::getPoints(){
  int points = 0;
  int numAces = 0;
  string faceDown;
  
  char arr[] = {'J','Q','K'};
  for(int i=0;i<hand.size();i++){

    char rank = hand[i][0];
    
    if(hand[i].substr(0,8) == "BACKSIDE"){
      faceDown = hand[i].substr(8);
      rank = faceDown[0];
    }

    //count number of aces
    if(rank == 'A'){
      numAces++;
    }
    //count number of face cards
    if(find(begin(arr),end(arr),rank) != end(arr)){
      points += 10;
    }
    //count number of numbered cards
    if(isdigit(rank)){
      int n = rank - '0';
      if(n > 1){
        points += n;
      }else{
        points += 10;
      }
    }
  }
  points += numAces;
  for(int i=0;i<numAces;i++){
    if((points + 10) <= 21){
      points += 10;
    }
  }
  return points;
}

//output value of card
void Deck::getValue(string card){
    unordered_map<char,string>suits{{'C',"CLOVERS"},{'D',"DIAMONDS"},{'H',"HEARTS"},{'S',"SPADES"}};
    unordered_map<char,string>faces{{'A',"ACE"},{'K',"KING"},{'Q',"QUEEN"},{'J',"JACK"}};
    string rank; string sym; char suit;
    if(card.size()==3){
      rank = "10";
      sym = suits[card[2]];
    }else if(isalpha(card[0])){
      rank = faces[card[0]];
      sym = suits[card[1]];
    }else{
      stringstream ss;
      ss << card[0];
      rank = ss.str();
      sym = suits[card[1]];
    }
    //output cardType and suitType
    cout << "You drew " << rank << " of " << sym << "\n";
    
}
//get user input for bonusBet amount
int Player::getBet(int max){
  if(max == 0){
    return 0;
  }
  while(true){
    cout << "How much do you bet? ($1 - $" << max << ")\n";
    int bet; cin >> bet;
    if(0<=bet<=max){
      return bet;
    }else{
      cout << "Invalid bet.\n";
      continue;
    }
  }
}

//action move input 
string Player::getMove(int turn){
    while(true){
      string move;
      //can only double down on first turn
      if(turn==0 && hand.size()==2){
        cout << "Enter Action: (H)it, (S)tand, (D)ouble down\n";
        cin >> move;
        
      }else{
        cout << "Enter Action: (H)it, (S)tand\n";
        cin >> move;
      }
      //input validation
      if(cin.fail() || ((move == "d" || move == "D") && hand.size() != 2)){
        cin.clear();
        cin.ignore(100,'\n');
        cout << "Invalid Move\n";
      }else{
        return move;
      }
    }
}