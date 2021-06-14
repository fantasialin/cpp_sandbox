#include <iostream>
#include <list>
#include <string>

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

  private :
    std::list<Document*> _docList;
};


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

    return 0;
}