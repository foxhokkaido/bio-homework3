#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int Count(string s, int t) {
	struct cout {
		char key;
		int n;
	};
	struct cout *arr = new struct cout[t];
	for (int i = 0; i < t; i++) {
		arr[i].n = 0;
		for (int j = 0; j < t; j++)
		{
			if (s[i] == s[j]) {
				arr[i].key = s[i];
				arr[i].n++;
			}
		}
	}
	int max_count = 0;
	for (int i = 0; i < t; i++) {
		if (arr[i].n > max_count) {
			max_count = arr[i].n;
		}
	}
	return max_count;
}

int Score(int *s, string *dna, int l, int t) {
	string *alignment_matrix = new string[t];
	for (int i = 0; i < t; i++) {
		alignment_matrix[i] = dna[i].substr(s[i], l);//составляем матрицу substr - возвращает подстроку с s[i] позиции, l - количество символов
	}
	string *t_matrix = new string[l]; 
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < t; j++) {
			t_matrix[i] += alignment_matrix[j].substr(i, 1); //транспонированная матрица
		}
		
	}
	int score = 0;
	for (int i = 0; i < l; i++) {
		score = score + Count(t_matrix[i], t);
	}
	return score;
}

int* Next_Leaf(int* a, int l, int k) {
	for (int i = l - 1; i >= 0; i--) {
		if (a[i] < k-1) {
			a[i]++;
			return a;
		}
		a[i] = 0;
	}
	return a;
}

void All_Leaves(int l, int k) {
	int *s = new int[l];
	for (int i = 0; i < l; i++) {
		s[i] = 0;
	}
	for (;;) {
		for (int i = 0; i < l; i++) {
			cout << s[i];
		}
		cout << endl;
		s = Next_Leaf(s, l, k);
		int n;
		for (n = 0; n < l && s[n] == 0; n++) {
			;
		}
		if (n == l) return;

	}
}

string* Motifs(int* s, string* dna, int t, int l) {
	string* best_motifs = new string[t];
	for (int i = 0; i < t; i++) {
		best_motifs[i] = dna[i].substr(s[i], l);
	}
	return best_motifs;
}

string* BruteForceMotifSearch(string *dna, int t, int n, int l) {
	string *best_motifs = new string[t];
	int *s = new int[t];
	int *best_s = new int[t];
	for (int i = 0; i < t; i++) {
		s[i] = 0;
	}
	int best_score = Score(s, dna, l, t);
	for (;;) {
		s = Next_Leaf(s, t, n - l + 1 );

		if ((Score(s, dna, l, t)) >= best_score) {
			best_score = Score(s, dna, l, t);
			for (int i = 0; i < t; i++) {
				best_s[i] = s[i];
			}

		}
		int n;
		for (n = 0; n < t && s[n] == 0; n++) {
			;
		}
		if (n == t) {
			best_motifs = Motifs(best_s, dna, t, l);
			return best_motifs;
		}
	}

}


int main() {
	ifstream fin("input.txt");

	if (!fin.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		int l;//размер шаблона
		int t;//число последовательностей 

		fin >> l; 

		fin >> t; 

		string *arr_str = new string[t];

		for (int i = 0; i < t; i++) {
			fin >> arr_str[i];
		}
		int n = arr_str[0].length();

		string* best_motifs = new string[t];

		best_motifs = BruteForceMotifSearch(arr_str, t, n, l);

		
		ofstream fout("output.txt");

		for (int i = 0; i < t; i++) {
			fout << best_motifs[i] << endl;
		}
		

		fin.close();
		fout.close();

	}
	return 0;
}
