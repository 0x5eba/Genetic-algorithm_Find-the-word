#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>

using namespace std;

//"N" is the total population
//"N" must be over a number a few up "M" , otherwise it will uselessly take more time 
int M = 0;
int N = 0;
//"Prob_mutation" maximum is 100 ( raccomand keep it down of the 10 ) , is in percentage
const int Prob_mutation = 5;

string phrase = "";
int word_correct = 0;
int completed = 0;
int sum = 0;
clock_t start;

void Random_population(vector<vector<char>> &population);
void Fitness(vector<vector<char>> &population, vector<int> &fitness);
void Sorting(vector<vector<char>> &population, vector<int> &fitness);
void Crossover(vector<vector<char>> &population);
void Mutation(vector<vector<char>> &population, int a, int b);
void Find(vector<vector<char>> &population, int a);

int main() 
{
	start = clock();
	srand(time(NULL));

    cout << "Insert the phrase to generate: ";
    getline(cin, phrase);
    M = phrase.length();
    N = M + 30 + M*0.35;

	vector<vector<char>> population(N, vector<char>(M));
    vector<int> fitness(N, 0);

	cout << "\nPopulation: " << N << "\n";
	cout << "Mutation: " << Prob_mutation << "%\n";

	Random_population(population);

	while (true){
		Fitness(population, fitness);

		Sorting(population, fitness);

		Crossover(population);

		if (completed == 1)
            return 0;
		sum = 0;
	}
	return 0;
}


void Random_population(vector<vector<char>> &population)
{
	for (int a = 0; a < N; a++){
		for (int b = 0; b < M; b++){
			Mutation(population, a, b);
		}
	}
}

void Fitness(vector<vector<char>> &population, vector<int> &fitness)
{
	for (int a = 0; a < N; a++)
		fitness[a] = 0;

	for (int a = 0; a < N; a++){
		for (int b = 0; b < M; b++){
			if (population[a][b] == phrase[b])
				fitness[a]++;
		}
	}
}

void Sorting(vector<vector<char>> &population, vector<int> &fitness)
{
	int max_fitness = fitness[0];
	for (int a = 0; a < N; a++){
		for (int b = a; b < N; b++){
			if (max_fitness < fitness[b])
				max_fitness = b;
		}
		if (max_fitness > 0)
		{
			for (int c = 0; c < M; c++){
				int temp = population[max_fitness][c];
				population[max_fitness][c] = population[a][c];
				population[a][c] = temp;
			}
			int temp = fitness[a];
			fitness[a] = fitness[max_fitness];
			fitness[max_fitness] = temp;
			sum++;
		}
		max_fitness = 0;
	}
	if (sum > N / 2)
		sum = N / 2;
}

void Crossover(vector<vector<char>> &population)
{
	for (int a = 0; a < sum; a++){
		int random_mating = rand() % 101;
		if (random_mating >= 50){
			
            int random_mate = rand() % sum;
			for (int b = 0; b < M; b++)
			{
				//MUTATION
				int random_Prob_mutation = rand() % 101;
				if (random_Prob_mutation <= Prob_mutation){
					Mutation(population, a, b);
					continue;
				}

				int random = rand() % 101;
				if (random < 50){
					population[sum + a][b] = population[a][b];
				}
				else {
					population[sum + a][b] = population[random_mate][b];
				}
			}
		}
		Find(population, a);
        if (completed == 1)
            break;
	}
}

void Mutation(vector<vector<char>> &population, int a, int b)
{
    population[a][b] = rand() % 127;
	// do {
	// 	population[a][b] = (rand() % 58) + 65;
	// } while (population[a][b] > 90 && population[a][b] < 97);
}

void Find(vector<vector<char>> &population, int a)
{
    for (int x = 0; x < M; x++){
		if (population[a][x] == phrase[x])
			word_correct++;
		if (word_correct == M) {
			cout << "\n\tPhrase find: ";
			for (int x = 0; x < M; x++){
				cout << population[a][x];
			}
			clock_t end;
			end = clock();
			cout << "\n\nIn " << ((double)(end - start)) / CLOCKS_PER_SEC << " seconds\n\n";
			completed = 1;
			break;
		}
	}
	word_correct = 0;
}