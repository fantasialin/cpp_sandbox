#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

class Strategy;

class TestBed
{
  public :
    enum StrategyType {
        Dummy, Left, Right, Center
    };
    TestBed() { strategy_ = nullptr; }

    //void setStrategy(StrategyType type, int width);
    void setStrategy(int type, int width);
    void DoIt();

  private :
    Strategy* strategy_;
};

class Strategy
{
  public :
    Strategy(int width) : width_(width) {}

    void format(){
        char line[80], word[30];
        ifstream inFile("quote.txt", ios::in);
        line[0] = '\0';

        inFile >> word;
        strcat(line, word);
        while (inFile >> word){
            if((strlen(line) + strlen(word) + 1) > width_){
                justify(line);
            }
            else {
                strcat(line, " ");
            }
            strcat(line, word);
        }
        justify(line);//for last paragraph
    }

  protected :
    int width_;
  private :
    virtual void justify(char* line) = 0;
};

class LeftStrategy : public Strategy
{
  public :
    LeftStrategy(int width) : Strategy(width) {}

  private :
    virtual void justify(char* line){
        cout << line << endl;
        line[0] = '\0';
    }
};

class RightStrategy : public Strategy
{
  public :
    RightStrategy(int width) : Strategy(width) {}

  private :
    virtual void justify(char* line){
        char buf[80];
        int offset = width_ - strlen(line);
        memset(buf, ' ', 80);
        strcpy(&buf[offset], line);
        cout << buf << endl;
        line[0] = '\0';
    }
};

class CenterStrategy : public Strategy
{
  public :
    CenterStrategy(int width) : Strategy(width) {}

  private :
    virtual void justify(char* line){
        char buf[80];
        int offset = (width_ - strlen(line)) / 2;
        memset(buf, ' ', 80);
        strcpy(&buf[offset], line);
        cout << buf << endl;
        line[0] = '\0';
    }
};

void TestBed::DoIt() {
    strategy_->format();
}


//void TestBed::setStrategy(StrategyType type, int width){
void TestBed::setStrategy(int type, int width){
    delete strategy_;
    if (type == Left) {
        strategy_ = new LeftStrategy(width);
    }
    else if(type == Right) {
        strategy_ = new RightStrategy(width);
    }
    else if(type == Center) {
        strategy_ = new CenterStrategy(width);
    }
}


int main(int argc, char **argv){
    cout << "Strategy - layout test" << endl;

    TestBed test;
    int answer, width;
    cout << "Exit(0), Left(1), Right(2), Center(3): ";
    cin >> answer;
    while(answer){
        cout << "Width: ";
        cin >> width;
        // set strategy & apply the strategy
        test.setStrategy(answer, width);
        test.DoIt();
        cout << "Exit(0), Left(1), Right(2), Center(3): ";
        cin >> answer;
    }
    
    return 0;
}