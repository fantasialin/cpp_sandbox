#include <iostream>
#include <string>

using namespace std;

class Game
{
  public :
    explicit Game(int Num_of_players) : number_of_players (Num_of_players) {}

    // this is template method to invoke derived class's functions
    void run(){

        start();
        while(!have_winner()){
            take_turn();
        }

        cout << "Player : " << get_winner() << " wins." << endl;
    }

  protected :
    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;

    int current_player { 0 };
    int number_of_players;
};

class Chess : public Game
{
  public :
    explicit Chess() : Game {2} {}

  protected :
    void start() override {
        cout << "Starting a chess game with " << number_of_players << " players" << endl;
    }

    bool have_winner() override {
        return turns >= max_turns;
    }

    void take_turn() override {
        cout << " Turn " << turns << " taken by player " << current_player << endl;
        turns++;
        current_player = (current_player + 1) % number_of_players;
    }

    int get_winner() override {
        return current_player;
    }

  private :
    int turns { 0 }, max_turns { 10 };
};


int main(int argc, char **argv){
    cout << "Template Method test" << endl;
    Chess chessGame;
    //invoke Template method
    chessGame.run();

    getchar();
    return 0;
}