#include <iostream>
using namespace std;

int get_min(int *, int);
void print_array(int **, int, int);
void delete_array2d(int **);
int ** create_array2d(int **, int, int);

//void copy_row(int &c, int row, int s){
//     for (size_t t=0; t!=s; ++t){
//          c[t] = row[t];
//     }
//}

void swap_min(int **mt, int m, int n) {

    int row_idx = 0;
    int new_min = 0;
    int min = get_min(mt[0], n);

    for (size_t i=1; i!=m; ++i){
        new_min = get_min(mt[i], n);
        if(new_min < min) {
             row_idx = i;
	     min = new_min;
        }        
    }
 
    if (row_idx){
           int * tmp = mt[0];
           mt[0] = mt[row_idx];
           mt[row_idx] = tmp;
	   //delete [] tmp;
    }
    print_array(mt, m, n);
}


int get_min( int * a , int s ) {    
    int r = a[0];
    for ( size_t i = 1; i != s ; ++ i ){
       if (a[i] < r){
            r = a[i];
        }
    }
    return r ;
}

int ** create_array2d(int a, int b) {
    int ** m = new int *[a];
    m[0] = new int [a*b];
    for (size_t i = 1; i!=a; ++i) {
        m[i] = m[i-1] + b;
    }
    return m;
}

void delete_array2d(int ** m){
    delete [] m[0];
    delete [] m;

}

void print_array(int ** m, int a, int b){
    for (size_t ia=0; ia != a; ++ia) {
        for (size_t ib=0; ib != b; ++ib) {
            cout << m[ia][ib] << " ";
	}
        cout << endl;
    }
}

int main() {

    int a = 3;
    int b = 3;

    int ** m = create_array2d(a, b);
    m[0][0] = 2;
    m[0][1] = 3; 
    m[0][2] = 5;
    
    m[1][0] = 7;
    m[1][1] = 0; 
    m[1][2] = 3;

    m[2][0] = 4;
    m[2][1] = 8; 
    m[2][2] = 6;

    swap_min(m, a, b);
    delete_array2d(m);
    return 0;
}

