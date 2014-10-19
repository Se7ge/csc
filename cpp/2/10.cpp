#include <iostream>
#include <cstddef>  // size_t
using namespace std;

int get_min(int *, int);
void print_array(int **, int, int);
void delete_array2d(int **);
int ** create_array2d(size_t, size_t);


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

int ** transpose(const int * const * m, size_t r, size_t c) {
    int ** res = create_array2d(c, r);
    for (size_t i=0; i != c; ++i){
		for (size_t j=0; j != r; ++j){
				res[i][j] = m[j][i];
		}
	}
	return res;
}

int ** create_array2d(size_t a, size_t b) {
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

    size_t a = 3;
    size_t b = 4;
    int ** m = create_array2d(a, b);
    m[0][0] = 1;
    m[0][1] = 2; 
    m[0][2] = 3;
    m[0][3] = 4;
    
    m[1][0] = 5;
    m[1][1] = 6; 
    m[1][2] = 7;
    m[1][3] = 8;

    m[2][0] = 9;
    m[2][1] = 10; 
    m[2][2] = 11;
    m[2][3] = 12;

    int ** res = transpose(m, a, b);
    print_array(res, b, a);
    delete_array2d(m);
    delete_array2d(res);
    return 0;
}

