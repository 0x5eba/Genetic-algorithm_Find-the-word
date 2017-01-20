#include <iostream>
#include <ctime>
#include <stdlib.h>

//"N" is the total population
//"N" must be over a number a few up "M" , otherwise it will uselessly take more time 
#define N 60
//"M" is the length of "Word"
#define M 30
//"Word" accept only the alphabetic character ( uppercase and lowercase ), the space and nothing else
#define Word "MayBe SoMEThiNg MoRe DIffiCUlT"
//"Prob_mutation" maximum is 100 ( raccomand keep it down of the 10 ) , is in percentage
#define Prob_mutation 5

int word_correct = 0;
int completed = 0;
clock_t start;
int Random_population(char population[N][M]);
int Fitness(char population[N][M], int fitness[N]);
int Crossover(char population[N][M], int sum);
int Find(char population[N][M], int a);

int main()
{
	start = clock();
	srand(time(NULL));
	char population[N][M] = { 0 };
	int fitness[N] = { 0 };
	int sum = 0;

	std::cout << "\n\tWord to find: " << Word << "\n";
	std::cout << "\npopulation: " << N << "\n";
	std::cout << "Prob_mutation: " << Prob_mutation << "%\n";
	
	Random_population(population);
	while (true)
	{
		//FITNESS
		Fitness(population, fitness);
		
		//SORTING
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
		//CROSSOVER
		Crossover(population, sum);
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
			population[a][b] = (rand() % 58) + 65;
			if (!isalpha(population[a][b]))
			{
				b--;
				continue;
			}
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

int Crossover(char population[N][M], int sum)
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
					if (random_Prob_mutation < 2)//per lo spazio
					{
						population[a][b] = 32;
						continue;
					}
					population[a][b] = (rand() % 58) + 65;
					if (population[a][b] > 90 || population[a][b] < 97)
					{
						b--;
						continue;
					}
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
		}
	}
	word_correct = 0;
}
