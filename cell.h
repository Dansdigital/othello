#include <string>
using namespace std;
class Cell
{
public:
    Cell(string s = " ", int i = 0) { state = s; id = i;}
    string get_state() const { return state; }
    int get_id()const{return id;}
    void heart_state() {state = "\xe2\x99\xa5"; id = 1;}
    void ace_state() {state = "\xe2\x99\xa4"; id = 2;}

    void cell_restart(){state = " "; id = 0;}
    void flip();
    friend ostream& operator <<(ostream& outs, Cell c){outs << c.state; return outs;}

private:
    string state;
    int id;
};

// |---|
// | X |
// |---|

