// Jeremy Zheng - ICS4U1-1 - Final Summative
//main file

#include <thread>  // std::this_thread::sleep_for
#include <chrono>  // std::chrono::seconds

#include <algorithm>  //std::find
#include <vector>     //std::vector
#include <iostream>
#include "header.h"
using namespace std;

int main(){
  //Player Winnings
  int money = 5000;
  int winnings = 0;
  while(true){

    if(money <= 0){
      cout << "You are out of money!\n";
      cout << "Thanks for playing.\n";
      return 0;
    }

    //get betting amount
    
    cout << "--------------------------------------------\n";
    cout << " ~WELCOME TO BLACKJACK~                    /\n\n";
    cout << "Current Wallet: $" << money << "\n";
    cout << "Enter Betting Amount($1 - $ " << money << ")\n";
    int bet; cin >> bet;
    while(cin.fail() || bet > money || bet < 0){
      cout << "Error: Not A Valid Option\n";
      cin.clear();
      cin.ignore(100,'\n');
      cout << "Enter Betting Amount($1 - $ " << money << ")\n";
      cin >> bet;
    }
    cout << "                                           /\n";
    cout << "--------------------------------------------\n";
    

    //create class objects
    Player p1(bet);
    Dealer d1;
    vector<string>deck;
    Blackjack game(deck);
    //reset deck 
    game.setDeck();
    //start game
    //2 cards each
    game.startGame(game, p1, d1);
    int points = p1.getPoints();
    int i=0;
    //MAIN GAME LOOP
    while(points < 21){
      
    
      //user input for action move
      string move = p1.getMove(i);
      
      //DOUBLE DOWN
      if(move == "D" || move == "d"){
        //get betting amount
        int maxBet = min(bet, (money-bet));
        if(maxBet == 0){
          cout << "You have bet the max amount\n";
          i++;
          continue;
        }
        int bonusBet = p1.getBet(maxBet);
        bet += bonusBet;
        cout << "Bet increased to " << bet << "\n";
        this_thread::sleep_for(chrono::seconds(2));
      }
      system("clear");
      //HIT & DOUBLE DOWN
      string arr1[] = {"H","h","D","d"};
      if(find(begin(arr1),end(arr1),move) != end(arr1)){
        //draw card
        string card = p1.drawCard(game.deck);
        p1.getValue(card);
        p1.hand.push_back(card);
        //output current hand and points
        cout << "Player Points: " << p1.getPoints() << endl;
        game.displayCards(p1.hand);

        if(p1.getPoints() > 21){
          break;
        }

      }

      //STAND & DOUBLE DOWN
      string arr2[] = {"S","s","D","d"};
      if(find(begin(arr2),end(arr2),move) != end(arr2)){
        break;
      }

      //count number of actions
      i++;
    }
    this_thread::sleep_for(chrono::seconds(2));
    //dealer action moves
    if(p1.getPoints() <= 21){
      
      //DEALER ACTION LOOP
      while(true){
        cout << "Dealer hits...\n";

        if(d1.getPoints() >= 17){
          break;
        }
        
        string card = d1.drawCard(game.deck);
        d1.hand.push_back(card);
      
        game.displayHands(p1, d1, false);
        this_thread::sleep_for(chrono::seconds(4));
        system("clear");
      }
      cin.ignore();
      cout << "Press Enter to Continue...";
      cin.get();
      
      system("clear");
    }
    game.displayHands(p1,d1,true);
    
    //FINAL TURN
    //GET TOTAL POINT VALUE OF HAND
    int playerPoints = p1.getPoints();
    int dealerPoints = d1.getPoints();
    if(dealerPoints > 21){
      cout << "Dealer busts! You win $" << bet << "!\n";
      winnings += bet;
    }else if(playerPoints > 21 || playerPoints < dealerPoints){
      cout << "You lost!\n";
      winnings -= bet;
    }else if(playerPoints > dealerPoints){
      cout << "You won $" << bet << "!\n";
      winnings += bet;
    }else if(playerPoints == dealerPoints){
      cout << "It's a tie, the bet is returned\n";
    }



    //ASK IF USER WOULD LIKE TO QUIT
    cout << "Would you like to continue playing?\n"; 
    money += winnings;
    char choice; cin >> choice;
    if(choice == 'Y' || choice == 'y'){
      system("clear");
      continue;
    }else{
      //show total winnings
      cout << "Final Wallet: $" << money << endl;
      cout << "Total Winnings: $" << winnings << endl;
      cout << "THANKS FOR PLAYING!";
      return 0;
    }
  }
  

}