#include <iostream>

using namespace std;

class Airplane {
  private :
    struct AirPlaneRep {
        unsigned long miles;
        char type;
    };

  private :
    union {
        AirPlaneRep rep;
        Airplane* next;
    };

  public :
    unsigned long getMiles() { return rep.miles; }
    char getType() { return rep.type; }
    void set(unsigned long m, char t) {
        rep.miles = m;
        rep.type = t;
    }

  public :
    static void* operator new(size_t size);
    static void operator delete(void* deadObject, size_t size);

  private :
    static const int BLOCK_SIZE;
    static Airplane* headOfFreeList;
};

Airplane* Airplane::headOfFreeList;
const int Airplane::BLOCK_SIZE = 512;

void* Airplane::operator new(size_t size) {

    if( size != sizeof(Airplane)) {//inheritance case
        return ::operator new(size);
    }

    Airplane* p = headOfFreeList;
    if(p){
        //cout << "get a block from pool" << endl;
        headOfFreeList = p->next;
    }
    else{
        //free list empty, allocate another pool
        //cout << "allocate a pool" << endl;
        Airplane* newBlock = static_cast<Airplane*> (::operator new(BLOCK_SIZE * sizeof(Airplane)));

        //slice pool to a small block as free list
        for(int i = 1; i< BLOCK_SIZE -1; ++i){
            newBlock[i].next = &newBlock[i+1];
        }
        newBlock[BLOCK_SIZE - 1].next = 0; //end of free list
        p = newBlock;
        headOfFreeList = &newBlock[1];
    }
    return p;
}

void Airplane::operator delete(void* deadObject, size_t size) {
    if (deadObject == 0) return;
    if (size != sizeof(Airplane)) {
        ::operator delete(deadObject);
        return;
    }

    Airplane* carcass = static_cast<Airplane*>(deadObject);

    carcass->next = headOfFreeList;
    headOfFreeList = carcass;
    return;
}


int main(int argc, char **argv){
    cout << "allocator test" << endl;

    cout << "size of Airplane = " << sizeof(Airplane) << endl;
    size_t const N = 100;
    Airplane* p[N]; //100 pointer of Airplane

    for (int i = 0; i < N; ++i){
        p[i] = new Airplane;
    }

    p[0]->set(9999, 'A');
    p[1]->set(1000, 'A');
    p[2]->set(2000, 'B');
    p[3]->set(50000, 'C');

    for (int i = 0; i < 10; ++i){
        cout << p[i] << p[i]->getType() << " " << p[i]->getMiles() << endl;
    }

    for (int i = 0; i < N; ++i){
        delete p[i];
    }

    return 0;
}
