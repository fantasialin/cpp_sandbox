#include <iostream>
#include <list>
#include <string>
//#include <exception>

using namespace std;

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

    virtual Document* Serialize() = 0; //pure virtual function

  private :
  string name;
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
    MyDoc(string& name) : Document(name) {
      cout << "MyDoc ctor" << endl;
    }

    virtual Document* Serialize() override {
      cout << "MyDoc::Serialized()" << endl;
      return this;
    }
};

class MyApp : public Application
{
  public :
    virtual Document* CreateDocument(string& name) {  //Factory method
      cout << "MyApp::CreateDocument()" << endl;
      return new MyDoc(name);
    }
};

// for test singleton Application object
class MyApp2 : public Application
{
  public :
    virtual Document* CreateDocument(string& name) {  //Factory method
      cout << "MyApp2::CreateDocument()" << endl;
      return new MyDoc(name);
    }
};


int main(int argc, char **argv) {
    cout << "Command - app framwork + template method + command + factory - test" << endl;

    MyApp* app = new MyApp;

    cout << "test OpenCommand" << endl;

    OpenCommand cmd1(app);
    cmd1.Execute();

    cout << "test PasteCommand" << endl;

    Document* doc = app->GetCurrentDoc();
    PasteCommand cmd2(doc);
    cmd2.Execute();

    cout << "test Singleton of Application object" << endl;
    //MyApp* app_1 = new MyApp; //Error
    //MyApp* app_2 = new MyApp2; //Error

    return 0;
}