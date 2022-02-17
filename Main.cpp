#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

// Randomly generates travel price between each city
void travel(vector<int>& vec) {

	for (int i = 0; i < 8; i++) {
		vec.push_back(rand() % 2000 + 99);
	}

}

// A utility function to list all cities and the price of traveling to each city
void printSector(vector<vector<int>>& vec) {
	int k = 0;

	for (int i = 0; i < 8; i++) {
		cout << (char)(i + 65) << " ";
		for (int k = 0; k < 8; k++) {
			cout << vec[i][k] << " ";
		}
		cout << endl;
		k = 0;
	}
}


//Function may need to be deleted
// Prints the fitness of a genome A.K.A. the price of traveling to all cities and returning to the start
void fitnessFinder(vector<vector<int>> vvec, vector<int> vec) {
	int sum = 0;

	for (int x = 0; x < 7; x++) {
		cout << sum << " + " << vvec[vec[x]][vec[x + 1]] << " = ";
		sum += vvec[vec[x]][x + 1];
		cout << sum << endl;
		if (x == 6) {
			x++;
			cout << sum << " + " << vvec[vec[x]][0] << " = ";
			sum += vvec[vec[x]][0];
			cout << sum << endl;
		}
	}
}

//Finds the fitness of a route
int fitness(vector<vector<int>> vvec, vector<int> vec) {
	int sum = 0;

	for (int x = 0; x < 7; x++) {
		sum += vvec[vec[x]][x + 1];
		if (x == 6) {
			x++;
			sum += vvec[vec[x]][0];
		}
	}

	return sum;
}

// Sets the travel cost of going to the same city 0
void samecityRemover(vector<vector<int>>& vvec) {
	int k = 0;

	for (int i = 0; i < 8; i++) {
		for (int k = 0; k < 8; k++) {
			if (i == k) {
				vvec[i][k] = 0;
			}
		}
		k = 0;
	}
}

// Creates a grid to store the cost of travel between each city
void costCreator(vector<vector<int>>& Cities, int i) {
	srand(i);

	vector <int> A;
	travel(A);
	Cities.push_back(A);
	vector <int> B;
	travel(B);
	Cities.push_back(B);
	vector <int> C;
	travel(C);
	Cities.push_back(C);
	vector <int> D;
	travel(D);
	Cities.push_back(D);
	vector <int> E;
	travel(E);
	Cities.push_back(E);
	vector <int> F;
	travel(F);
	Cities.push_back(F);
	vector <int> G;
	travel(G);
	Cities.push_back(G);
	vector <int> H;
	travel(H);
	Cities.push_back(H);
}

//Randomizes routes and also used for scramble mutation
vector<int> Shuffle(vector<int>& Cities) {
	random_shuffle(Cities.begin(), Cities.end());
	return Cities;
}

//Creates set of 9 routes for cities
void CityInitializer(vector<vector<int>>& Population) {
	vector<int> Cities;
	vector<int> Cities2;

	Cities.push_back(0);
	for (int i = 1; i < 8; i++) {
		Cities.push_back(i);
		Cities2.push_back(i);
	}
	Cities.push_back(0);

	for (int i = 0; i < 9; i++) {

		Shuffle(Cities2);

		for (int i = 1; i < 8; i++) {
			Cities[i] = Cities2[i - 1];
		}

		Population.push_back(Cities);
	}

}

//Prints the genomes and their fitness
void PopReader(vector<vector<int>>& Population, vector<vector<int>>& CitySector) {
	cout << "Genome              " << "Fitness" << endl;
	for (int i = 0; i < 9; i++) {
		for (int k = 0; k < 9; k++) {
			cout << Population[i][k];
		}
		cout << "           " << fitness(CitySector, Population[i]) << endl;
		cout << endl;
	}
}

//Organizes Vector from smallest(fittest) to largest(least fit)
void FitOrganizer(vector<vector<int>>& Population, vector<vector<int>>& CitySector) {
	deque<vector<int>> Population2;

	for (int i = 0; i < 9; i++) {
		if (i == 0) {
			Population2.push_back(Population[i]);
		}
		else if (fitness(CitySector, Population2[i - 1]) > fitness(CitySector, Population[i])) {
			int h = i;
			for (int k = i; k > 0; k--, h--) {
				if (fitness(CitySector, Population2[k - 1]) < fitness(CitySector, Population[i])) {
					break;
				}
			}
			deque<vector<int>>::iterator it = Population2.begin();
			for (int g = 0; g < h; g++) {
				it++;
			}
			Population2.insert(it, Population[i]);
		}
		else {
			Population2.push_back(Population[i]);
		}
	}

	for (int i = 0; i < 9; i++) {
		Population[i] = Population2[i];
	}

}


//Order Crossover Function (OX1)
vector<int> Cross(vector<int> A, vector<int> B) {
	vector<int> A2;
	vector<int> B2;
	vector<int> C1;
	for (int i = 1; i < 8; i++) {
		A2.push_back(A[i]);
		B2.push_back(B[i]);
		C1.push_back(B[i]);
	}
	int a = rand() % 7;
	int b = a + 1;
	int c = a + 2;
	int k = 1;
	int y = 0;
	if (b > 6) {
		b = b - 7;
	}
	if (c > 6) {
		c = c - 7;
	}
	for (int i = c + 1; k < 8; i++) {
		if (i == 7) {
			i = 0;
		}

		if (B2[i] != A2[a] && B2[i] != A2[b] && B2[i] != A2[c]) {
			y = c + k;
			if (y > 6) {
				y = y - 7;
			}
			C1[y] = B2[i];
			k++;
		}


		if (i == 6) {
			i = -1;
		}
	}
	C1[a] = A2[a];
	C1[b] = A2[b];
	C1[c] = A2[c];
	
	for (int i = 0; i < 7; i++) {
		A[i + 1] = C1[i];
	}
	return A;
}

//Insert mutation function
vector<int> insert(vector<int>& Pop) {
	vector<int> A;
	for (int i = 1; i < 8; i++) {
		A.push_back(Pop[i]);
	}
	int d = rand() % 7;
	int r = rand() % 6;
	int j = A[d];
	A.erase(A.begin() + d);
	A.insert(A.begin() + r, j);

	for (int i = 1; i < 8; i++) {
		Pop[i] = A[i - 1];
	}
	return Pop;
}

vector<int> swap(vector<int>& Pop) {
	vector<int> A;
	for (int i = 1; i < 8; i++) {
		A.push_back(Pop[i]);
	}
	int d = rand() % 7;
	int r = rand() % 7;

	while (d == r) {
		r = rand() % 7;
	}

	int y = A[r];
	A[r] = A[d];
	A[d] = y;

	for (int i = 1; i < 8; i++) {
		Pop[i] = A[i - 1];
	}
	return Pop;
}

vector<int> invert(vector<int>& Pop) {
	vector<int> A;
	vector<int> B;
	vector<int> C;
	for (int i = 1; i < 8; i++) {
		A.push_back(Pop[i]);
	}
	int d = rand() % 7;
	int y;

	for (int i = 0; i < 4; i++) {
		if ((d + i) > 6) {
			y = A[d + i - 7];
		}
		else {
			y = A[d + i];
		}
		B.push_back(y);
	}
	for (int i = 0; i < 4; i++) {
		y = d + i;
		if (y > 6) {
			y = y - 7;
		}
		C.push_back(y);
	}
	for (int i = 0; i < 4; i++) {
		A[C[3 - i]] = B[i];
	}
	for (int i = 1; i < 8; i++) {
		Pop[i] = A[i - 1];
	}
	return Pop;
}

vector<int> scramble(vector<int>& Pop) {
	vector<int> A;
	vector<int> B;
	vector<int> C;
	for (int i = 1; i < 8; i++) {
		A.push_back(Pop[i]);
	}

	int d = rand() % 7;
	int y;

	for (int i = 0; i < 4; i++) {
		if ((d + i) > 6) {
			y = A[d + i - 7];
		}
		else {
			y = A[d + i];
		}
		B.push_back(y);
	}
	for (int i = 0; i < 4; i++) {
		y = d + i;
		if (y > 6) {
			y = y - 7;
		}
		C.push_back(y);
	}

	Shuffle(B);

	for (int i = 0; i < 4; i++) {
		A[C[i]] = B[i];
	}
	for (int i = 1; i < 8; i++) {
		Pop[i] = A[i - 1];
	}
	return Pop;
}

vector<int> Evolve(vector <vector<int>>& Population, vector <vector<int>> CitySector, int mute) {
	Population[5] = Cross(Population[0], Population[1]);
	Population[6] = Cross(Population[1], Population[0]);
	Population[7] = Cross(Population[2], Population[3]);
	Population[8] = Cross(Population[3], Population[2]);

	int u = 0;

	switch (mute) {
		case 1:
			for (int i = 5; i < 9; i++) {
				//50% chance of mutation
				u = rand() % 2;
				if (u == 1) {
					Population[i] = insert(Population[i]);
				}
			}
			break;
		case 2:
			for (int i = 5; i < 9; i++) {
				//50% chance of mutation
				u = rand() % 2;
				if (u == 1) {
					Population[i] = swap(Population[i]);
				}
			}
			break;
		case 3:
			for (int i = 5; i < 9; i++) {
				//50% chance of mutation
				u = rand() % 2;
				if (u == 1) {
					Population[i] = invert(Population[i]);
				}
			}
			break;
		case 4:
			for (int i = 5; i < 9; i++) {
				//50% chance of mutation
				u = rand() % 2;
				if (u == 1) {
					Population[i] = scramble(Population[i]);
				}
			}
			break;
	}

	FitOrganizer(Population, CitySector);
	PopReader(Population, CitySector);

	vector<int> fittest = Population[0];

	for (int i = 0; i < 9; i++) {
		if (fitness(CitySector, Population[i]) < fitness(CitySector, fittest)) {
			fittest = Population[i];
		}
	}
	return fittest;
}

void Breed(vector <vector<int>>& Population, vector <vector<int>> CitySector, int mute) {
	vector <vector<int>> best;
	for (int i = 1; i < 11; i++) {
		cout << "Generation " << i << endl << endl;
		best.push_back(Evolve(Population, CitySector, mute));
		cout << "Best of generation " << i << " is " ;
		for (int k = 0; k < 9; k++) {
			cout << best[i - 1][k];
		}
		cout << " with a fitness of " << fitness(CitySector, best[i - 1]) << endl << endl;
	}

	vector<int> fittest = best[0];
	int fitgen = 1;
	for (int i = 0; i < 9; i++) {
		if (fitness(CitySector, best[i]) < fitness(CitySector, fittest)) {
			fittest = best[i];
			fitgen = i + 1;
		}
	}
	cout << "Best of run solution is ";
	for (int i = 0; i < 9; i++) {
		cout << fittest[i];
	}
	cout << " from generation " << fitgen;
	cout << " with a fitness of " << fitness(CitySector, fittest) << endl << endl;
}


// Function sets and prints initial population
void CallSet(vector <vector<int>> CitySector, int mute) {
	vector <vector<int>> Population1;
	CityInitializer(Population1);
	cout << "Starting Population:" << endl;
	FitOrganizer(Population1, CitySector);
	PopReader(Population1, CitySector);
	Breed(Population1, CitySector, mute);
}

int main() {
	//Establish cost grid for travel
	vector <vector<int>> CitySector;
	costCreator(CitySector, 1);
	samecityRemover(CitySector);

	for (int i = 0; i < 3; i++) {
		cout << "Insert Mutation Set: " << i << endl;
		CallSet(CitySector, 1);
	}

	for (int i = 0; i < 3; i++) {
		cout << "Swap Mutation Set: " << i << endl;
		CallSet(CitySector, 2);
	}

	for (int i = 0; i < 3; i++) {
		cout << "Invert Mutation Set: " << i << endl;
		CallSet(CitySector, 3);
	}

	for (int i = 0; i < 3; i++) {
		cout << "Scramble Mutation Set: " << i << endl;
		CallSet(CitySector, 4);
	}
}