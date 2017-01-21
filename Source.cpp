#include <iostream>
#include <ctime>
#include <stdlib.h>

//"N" is the total population
//"N" must be over a number a few up "M" , otherwise it will uselessly take more time 
#define N 40
//"M" is the length of "Word"
#define M 19
//"Word" accept the alphabetic character ( uppercase and lowercase ), the space and the numbers
#define Word "Jus7 M0re D1ffIcul7"
//"Prob_mutation" maximum is 100 ( raccomand keep it down of the 10 ) , is in percentage
#define Prob_mutation 5

int word_correct = 0;
int completed = 0;
int sum = 0;

clock_t start;

char List[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 abcdefghijklmnopqrstuvwxyz";
int Random_population(char population[N][M]);
int Fitness(char population[N][M], int fitness[N]);
int Sorting(char population[N][M], int fitness[N]);
int Crossover(char population[N][M]);
int Find(char population[N][M], int a);

int main()
{
	start = clock();
	srand(time(NULL));

	char population[N][M] = { 0 };
	int fitness[N] = { 0 };

	std::cout << "\n\tWord to find: " << Word << "\n";
	std::cout << "\nPopulation: " << N << "\n";
	std::cout << "Mutation: " << Prob_mutation << "%\n";
	
	Random_population(population);

	while (true)
	{
		Fitness(population, fitness);

		Sorting(population, fitness);

		Crossover(population);

		if (completed == 1) { system("pause"); return 0; }
		sum = 0;
	}
	return 0;
}


int Random_population(char population[N][M])
{
	for (int a = 0; a < N; a++)
	{
		for (int b = 0; b < M; b++)
		{
			int random = rand() % 64;
			population[a][b] = List[random];
		}
	}
	return population[N][M];
}

int Fitness(char population[N][M], int fitness[N])
{
	for (int a = 0; a < N; a++)
	{
		fitness[a] = 0;
	}

	for (int a = 0; a < N; a++)
	{
		for (int b = 0; b < M; b++)
		{
			if (population[a][b] == Word[b])
				fitness[a]++;
		}
	}
	return fitness[N];
}

int Sorting(char population[N][M], int fitness[N])
{
	int max_fitness = fitness[0];
	for (int a = 0; a < N; a++)
	{
		for (int b = a; b < N; b++)
		{
			if (max_fitness < fitness[b])
			{
				max_fitness = b;
			}
		}
		if (max_fitness >= 1)
		{
			for (int c = 0; c < M; c++)
			{
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
	return population[N][M];
}

int Crossover(char population[N][M])
{
	for (int a = 0; a < sum; a++)
	{
		int random_mating = rand() % 101;
		if (random_mating >= 50)
		{
			int random_mate = rand() % sum;
			for (int b = 0; b < M; b++)
			{
				//MUTATION
				int random_Prob_mutation = rand() % 101;
				if (random_Prob_mutation <= Prob_mutation)
				{
					int random = rand() % 64;
					population[a][b] = List[random];
					continue;
				}

				int random = rand() % 101;
				if (random < 50)
				{
					population[sum + a][b] = population[a][b];
				}
				else {
					population[sum + a][b] = population[random_mate][b];
				}
			}
		}
		Find(population, a);
	}
	return population[N][M];
}

int Find(char population[N][M], int a)
{
	for (int x = 0; x < M; x++)
	{
		if (population[a][x] == Word[x])
		{
			word_correct++;
		}
		if (word_correct == M)
		{
			std::cout << "\n\n\tWORD FIND:   ";
			for (int x = 0; x < M; x++)
			{
				std::cout << population[a][x] << " ";
			}
			clock_t end;
			end = clock();
			std::cout << "\n\n\t\tTime: " << ((double)(end - start)) / CLOCKS_PER_SEC << " seconds\n\n";
			completed = 1;
			return completed;
			break;
		}
	}
	word_correct = 0;
}
