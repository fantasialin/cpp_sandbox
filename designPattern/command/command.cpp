#include <iostream>
#include <list>
#include <string>

using namespace std;

class Command {
  public :
    virtual ~Command() {
        cout << "Command dtor" << endl;
    }
    virtual void Execute() = 0;

  protected :
    Command() {
        cout << "Command ctor" << endl;
    }
};

template <typename Receiver>
class SimpleCommand : public Command {
  public :
    typedef void (Receiver::* Action)();

    SimpleCommand(Receiver* r, Action a) : _receiver(r), _action(a) {}

    virtual void Execute();

  private :
    Action _action;
    Receiver* _receiver;

};

template <typename Receiver>
void SimpleCommand<Receiver>::Execute() {
    (_receiver->*_action)();
}


class MacroCommand : public Command {

  public :
    //MacroCommand() {}
    //virtual ~MacroCommand() {}

    virtual void Add(Command*);
    virtual void Remove(Command*);

    virtual void Execute();


  private :
    std::list<Command*> _cmds;
};

void MacroCommand::Add(Command* c) {
    _cmds.push_back(c);
}

void MacroCommand::Remove(Command* c) {
    _cmds.remove(c);
}

void MacroCommand::Execute() {
    for (auto cp : _cmds ) {
        cp->Execute();
    }
}

class MyClass1 {
  public :
    void Action() { cout << "MyClass1::Action()" << endl; }
};

class MyClass2 {
  public :
    void Action() { cout << "MyClass2::Action()" << endl; }
};

int main(int argc, char **argv){
    cout << "Command - ace SimpleCommand<> test" << endl;
    MyClass1 receiver1;
    Command* cmd1 = new SimpleCommand<MyClass1>(&receiver1, &MyClass1::Action);
    cmd1->Execute();

    MyClass2 receiver2;
    Command* cmd2 = new SimpleCommand<MyClass2>(&receiver2, &MyClass2::Action);
    cmd2->Execute();

    cout << "Command - ace MacroCommand test" << endl;
    MacroCommand macroCmd;
    macroCmd.Add(cmd1);
    macroCmd.Add(cmd2);
    macroCmd.Execute();

    macroCmd.Remove(cmd2);
    cout << " after remove cmd2" << endl;
    macroCmd.Execute();

    delete cmd1;
	delete cmd2;

    return 0;
}