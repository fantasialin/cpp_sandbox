#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount 
{
  public :
    BankAccount() { cout << "BankAccount ctor" << endl; }
    ~BankAccount() { cout << "BankAccount dtor" << endl; }

    void deposit(int amount) {
        balance += amount;
        cout << "deposited : " << amount << ", blance now : " << balance << endl;
    }

    void withdraw(int amount) {
        if((balance - amount) >= overdraft_limit) {
            balance -= amount;
            cout << "withdrew : " << amount << ", blance now : " << balance << endl;
        }
    }

    void show_balance(){
        cout << "current balance : " << balance << endl;
    }

  private :
    int balance = 0;
    int overdraft_limit = -500;
};

class Command
{
  public :
    virtual ~Command() = default;
    virtual void call() const = 0;
    virtual void undo() const = 0;

};

class BankAccountCommand : Command
{
  public :
    enum Action { deposit, withdraw } action;

    BankAccountCommand(BankAccount& account, const Action action, const int amount) 
        : account(account), action(action), amount(amount) {}

    virtual void call() const override {
        switch(action){
          case deposit :
            account.deposit(amount);
            break;
          case withdraw :
            account.withdraw(amount);
            break;
          default :
            break;
        }
    }

    virtual void undo() const override {
        switch(action){
          case withdraw :
            account.deposit(amount);
            break;
          case deposit :
            account.withdraw(amount);
            break;
          default :
            break;
        }
    }

 private :
    BankAccount& account;
    int amount;
};


// vector doesn't have virtual dtor, but who cares ?
class CompositeBankAccountCommand : vector<BankAccountCommand>, Command
{
  public :
    CompositeBankAccountCommand(const initializer_list<value_type>& items)
        : vector<BankAccountCommand>(items) {}
    
    virtual void call() const override {
        for ( auto& cmd : *this)
            cmd.call();
    }

    virtual void undo() const override {
        for ( auto& cmd : *this)
            cmd.undo();
    }

};

int main(int argc, char **argv){
    cout << "Command - Bank account command test" << endl;

    BankAccount ba;

    BankAccountCommand cmd1 { ba, BankAccountCommand::deposit, 100};
    BankAccountCommand cmd2 { ba, BankAccountCommand::withdraw, 200};

    ba.show_balance();

    cmd1.call();//deposit 100
    cmd2.call();//withdraw 200

    cmd2.undo();//undo withdraw 200
    cmd1.undo();//undo deposit 100

    /*vector<BankAccountCommand> commands{*/
    CompositeBankAccountCommand commands {
        BankAccountCommand{ba, BankAccountCommand::deposit, 100},
        BankAccountCommand{ba, BankAccountCommand::withdraw, 200}
    };

    ba.show_balance();

    commands.call();

    ba.show_balance();

    commands.undo();

    ba.show_balance();





    return 0;
}