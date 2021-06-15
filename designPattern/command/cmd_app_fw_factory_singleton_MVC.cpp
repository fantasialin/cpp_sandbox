#include <iostream>
#include <list>
#include <string>
//#include <exception>

using namespace std;

class View
{
  public :
    virtual ~View() {}
    virtual void update() = 0; //virtual void update(Document* doc) = 0;
};

class Document
{
  public :
    Document(string& name ) : name(name) {
      cout << " Document ctor. name : " << name << endl;
    }

    //template method
    void Open() {
      cout << "Document::Open()" << endl;
      Serialize();
    }

    void Paste() {
      cout << "Document::Paste()" << endl;
    }

    //observer
    void Attach(View* view) {
      cout << "Document::Attach()" << endl;
      views.push_back(view);
    }

    void Detach(View* view) {
      cout << "Document::Detach()" << endl;
      views.remove(view);
    }
    
    void Notify() {
      cout << "Document::Notify()" << endl;
      if (changed) {
        for (auto v : views){
          v->update();
        }
      }
      //reset the changed state
      changed = false;
    }

    virtual void LButtonDown() = 0;

    void DataChange() {
      changed = true;
    }

    virtual Document* Serialize() = 0; //pure virtual function

  private :
    string name;
    std::list<View*> views; // observers collection
    bool changed = false;

};

class Application 
{
  public :
    void Add(Document* doc) {
      _docList.push_back(doc);
    }

    Document* GetCurrentDoc() {
      return _docList.back();
    }

    //Factory method
    virtual Document* CreateDocument(string&) = 0;

    // for singleton
  public :
    Application () {
      ++_counter_;
      if(_counter_ > 1){
        //throw std::exception();
        throw runtime_error("Application object shoule be singleton.");
      }
    }

  private :
    std::list<Document*> _docList;
    static int _counter_; // for singleton
};
// initial value = 0
int Application::_counter_ = 0;


class Command 
{
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


class MacroCommand : public Command 
{
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

// A OpenCommand must be passed a Application object as its receiver.
class OpenCommand : Command 
{
  public :
    OpenCommand(Application* app) : app(app) {
      cout << "OpenCommand ctor" << endl;
    }

    virtual void Execute();

  protected :
    virtual string AskUser() {
      cout << "OpenCommand::AskUser()" << endl;
      return string("test.txt");
    }

  private :
    Application* app;
};

void OpenCommand::Execute() {
    string name = AskUser();
    Document* doc = app->CreateDocument(name);//invoke Factory method

    app->Add(doc);
    doc->Open();
}

// A PasteCommand must be passed a Document object as its receiver.
class PasteCommand : public Command
{
  public :
    PasteCommand(Document* doc) : doc(doc) {
      cout << "PasteCommand ctor" << endl;
    }

    virtual void Execute() {
      doc->Paste();
    }

  private :
    Document* doc;
};


class MyDoc : public Document
{
  public :
    MyDoc(string& name) : Document(name), subjectState(1) {
      cout << "MyDoc ctor, i = " << subjectState << endl;
    }

    virtual Document* Serialize() override {
      cout << "MyDoc::Serialized()" << endl;
      return this;
    }
    
    virtual void LButtonDown() override {
      cout << "MyDoc::LButtonDown()" << endl;
      subjectState *= 5;
      DataChange(); // change Document's data state
      Notify(); // notify all views
    }

    int GetState() {
      return subjectState;
    }

  private :
    int subjectState;
};

class MyApp : public Application
{
  public :
    virtual Document* CreateDocument(string& name) {  //Factory method
      cout << "MyApp::CreateDocument()" << endl;
      return new MyDoc(name);
    }
};

class MyView1 : View
{
  public :
    MyView1(MyDoc* myDoc) : subject(myDoc) {
      subject->Attach(this);
    }

    virtual void update() override {
      cout << "MyView1::update() data= " << subject->GetState() << endl;
    }

  private :
    MyDoc* subject;
};

class MyView2 : View
{
  public :
    MyView2(MyDoc* myDoc) : subject(myDoc) {
      subject->Attach(this);
    }

    virtual void update() override {
      cout << "MyView2::update() data= " << subject->GetState() << endl;
    }

  private :
    MyDoc* subject;
};

class MyView3 : View
{
  public :
    MyView3(MyDoc* myDoc) : subject(myDoc) {
      subject->Attach(this);
    }

    virtual void update() override {
      cout << "MyView3::update() data= " << subject->GetState() << endl;
    }

  private :
    MyDoc* subject;
};



int main(int argc, char **argv) {
    cout << "Command - app framwork + template method + command + factory + MVC - test" << endl;

    MyApp* app = new MyApp;

    cout << "test OpenCommand" << endl;

    OpenCommand cmd1(app);
    cmd1.Execute();

    cout << "test PasteCommand" << endl;

    Document* doc = app->GetCurrentDoc();
    PasteCommand cmd2(doc);
    cmd2.Execute();

    cout << "Command - MacroCommand test" << endl;
    //MacroCommand macroCmd;
    //macroCmd.Add(&cmd1);
    //macroCmd.Add(&cmd2);
    //macroCmd.Execute();

    return 0;
}