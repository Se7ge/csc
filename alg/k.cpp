#include <iostream>
#include <algorithm>
#include <vector>
#include <cstddef>  // size_t
using namespace std;

void print_vector(vector<int>);

void restruct(vector<int> &r){
	int trans = 0;
	int k = 0;
	for (int i=0; i!=r.size(); ++i){
		k = r.size() - i - 1;
		r[k] += trans;
		trans = 0;
		if (r[k] > 9){
			trans = r[k] / 10;
		} else if (r[k] < 0){
			trans = -1;
		}
	    r[k] -= trans * 10;
	}
	if (trans > 0){
	    r.insert(r.begin(), trans);	
	}
	
}

int get_length(vector<int> &a, vector<int> &b) {
	if (a.size() > b.size()){
		b.insert(b.begin(), a.size() - b.size(), 0);
	} else if (a.size() < b.size()){
		a.insert(a.begin(), b.size() - a.size(), 0);			
	}
	return a.size();
}

vector<int> sum_vectors(vector<int> a, vector<int> b) {
	int length = get_length(a, b);
	vector<int> res(a.begin(), a.end());
    for (int i = 0; i != length; ++i) {
		res[i] += b[i];
	}	
	restruct(res);
	return res;
}

vector<int> sub_vectors(vector<int> a, vector<int> b) {
	int length = get_length(a, b);
	vector<int> res(a.begin(), a.end());
    for (int i = 0; i != length; ++i) {
		res[i] -= b[i];
	}	
	restruct(res);
	return res;
}


vector<int> move10(vector<int> a, int num) {
	if (a.size() == 1 && a[0] == 0){
		return a;
	}
    for (int i = 0; i != num; ++i) {
		a.push_back(0);
	}
	return a;
}

void print_vector(vector<int> a){
	for (size_t i=0; i!=a.size(); ++i){
       cout << a[i] << " ";
	}
	cout << endl;
}

vector<int> karatsuba(vector<int> a, vector<int> b) {
	int length = get_length(a, b);
	//cout << "Length: " <<  length << endl;
	if (length == 0){
		vector<int> res(1, 0);		
		return res;
	 }
	if (length <= 100){		
		vector<int> res(2*length - 1, 0);
		for (int i=0; i != a.size(); ++i){
			for (int j=0; j != b.size(); ++j){
				res[i+j] += a[i] * b[j];
			}
		}
		//res.push_back(a[0]*b[0]);
		//print_vector(res);
		restruct(res);
		return res;
	}
	int floor_n_2 = length/2;
	int ceil_n_2 = length - floor_n_2;
	
	vector<int> al(a.begin(), a.begin() + ceil_n_2);
	vector<int> ar(a.begin() + ceil_n_2, a.end());	
	vector<int> bl(b.begin(), b.begin() + ceil_n_2);
	vector<int> br(b.begin() + ceil_n_2, b.end());
	
	vector<int> P1 = karatsuba(al, bl);
	vector<int> P2 = karatsuba(ar, br);
	vector<int> P3 = karatsuba(sum_vectors(al, ar), sum_vectors(bl, br));	
	
	return sum_vectors(sum_vectors(move10(P1, 2*floor_n_2), move10(sub_vectors(sub_vectors(P3, P2), P1), floor_n_2)), P2);
}

int main(){
    vector<int> a;
    vector<int> b;
    vector<int> res;
    string input;
    cin >> input;
	
    for (int i=0; i != input.size(); ++i){
		a.push_back(input[i] - '0');
	}
	
    cin >> input;
    for (int i=0; i != input.size(); ++i){
		b.push_back(input[i]- '0');
	}
	res = karatsuba(a, b);
	restruct(res);
    for (int i=0; i!=res.size(); ++i){
        cout << res[i];
	}
    return 0;
}
