#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

#define N 20
#define Max_length 20
#define Mutation 1
#define nFitness 0

int tentativi = 0;
int finito = 0;
clock_t start;
int trovato(char population[N][N],int length_word, char word_to_find[Max_length], int a);

int main()
{
	start = clock();
	srand(time(nullptr));
	
	char word_to_find[Max_length] = { "Test" };
	cout << "\tWord to find: " << word_to_find << "\n";
	cout << "\nPopulation: " << N << "\n";
	cout << "Mutation: " << Mutation << "%\n";
	cout << "\n(More letters , more waiting)\n\n";
	int length_word = 0;
	for (int a = 0; a < Max_length; a++)
	{
		if (isalpha(word_to_find[a]))
		{
			length_word++;
		}
	}

	char population[N][N] = { 0 };
	for (int a = 0; a < N; a++)
	{
		for (int b = 0; b < length_word; b++)
		{
			//posso aggiungere di mettere anche lo spazio tra gli elementi random
			population[a][b] = (rand() % 58) + 65;
			if (!isalpha(population[a][b]))
			{
				b--;
				continue;
			}
		}		
		trovato(population, length_word, word_to_find, a);
		if (finito == 1) { system("pause"); return 0; }
	}

	int fitness[N] = { 0 };
	char word_correct[N][N] = { 0 };
	char word_correct2[N][N] = { 0 };
	int somma = 0; 
	while (finito == 0)
	{
		somma = 0;
	
		//FITNESS
		for (int a = 0; a < N; a++)
		{
			fitness[a] = 0;
		}
		for (int a = 0; a < N; a++)
		{
			for (int b = 0; b < length_word; b++)
			{
				for (int c = 0; c < length_word; c++)
				{
					//potrei sistemare se ci sono più lettere uguali ( doppioni o più ) che hanno la parola in comune con word_to_find
					if (population[a][c] == word_to_find[b])
					{
						fitness[a]++;
					}
				}
			}
			if (fitness[a] > nFitness)
			{
				for (int c = 0; c < length_word; c++)
				{
					word_correct[a][c] = population[a][c];
				}
			}
		}

		for (int a = 0, c = 0; a < N; a++)
		{
			for (int b = 0, d = 0; b < length_word; b++)
			{
				if (isalpha(word_correct[a][b]))
				{
					word_correct2[c][d] = word_correct[a][b];
					d++;
					if (d == length_word)
					{
						d = 0;
						c += 1;
					}
					if (fitness[a] > nFitness)
					{
						somma += 1;
					}
				}
			}
			trovato(word_correct2, length_word, word_to_find, c);
			if (finito == 1) { system("pause"); return 0; }
		}
		somma /= length_word;

		//CROSSOVER
		int numero_random = 0;
		int mutation = 0;
		for (int a = 0; a < N; a++)
		{
			//primo metodo
			numero_random = rand() % 2;
			mutation = 0;
			if (numero_random == 0)
			{
				for (int b = 0; b < length_word; b++)
				{
					//MUTATION
					mutation = rand() % 101;
					if (mutation <= Mutation)
					{
						population[a][b] = (rand() % 58) + 65;
						if (!(isalpha(population[a][b])))
						{
							b--;
							continue;
						}
						continue;
					}
					if (b <= (length_word / 2) && a < somma)
					{
						population[a][b] = word_correct2[a][b];
						continue;
					}
					population[a][b] = (rand() % 58) + 65;
					if (!(isalpha(population[a][b])))
					{
						b--;
						continue;
					}
				}
			}
			if (numero_random == 1)
			{
				for (int b = 0; b < length_word; b++)
				{
					mutation = rand() % 101;
					if (mutation <= Mutation)
					{
						population[a][b] = (rand() % 58) + 65;
						if (!(isalpha(population[a][b])))
						{
							b--;
							continue;
						}
						continue;
					}
					if (b > (length_word / 2) && a < somma)
					{
						population[a][b] = word_correct2[a][b];
						continue;
					}
					population[a][b] = (rand() % 58) + 65;
					if (!(isalpha(population[a][b])))
					{
						b--;
						continue;
					}
				}
			}
			//secondo metodo
			/*numero_random = rand() % length_word;
			mutation = 0;
			for (int b = 0; b < length_word; b++)
			{	
				if (a < somma)
				{
					if (b <= numero_random)
					{
						population[a][b] = word_correct2[a][b];
						continue;
					}
					if (b > numero_random)
					{
						if (a == somma - 1)
						{
							population[a][b] = word_correct2[a - 1][b];
							continue;
						}
						population[a][b] = word_correct2[a+1][b];
						continue;
					}
				}
				if (a >= somma)
				{
					//MUTATION
					mutation = rand() % 100;
					if (mutation <= Mutation)
					{
						population[a][b] = (rand() % 58) + 65;
					if (!(isalpha(population[a][b])))
					{
						b--;
						continue;
					}
					continue;
					}
					population[a][b] = (rand() % 58) + 65;
					if (!(isalpha(population[a][b])))
					{
						b--;
						continue;
					}
				}	
			}*/
			trovato(population, length_word, word_to_find, a);
			if (finito == 1) { system("pause"); return 0; }
		}
		numero_random = 0;			
	}
	return 0;
}

int trovato(char population[N][N], int length_word, char word_to_find[Max_length], int a)
{
	for (int x = 0; x < length_word; x++)
	{
		if (population[a][x] == word_to_find[x])
		{
			tentativi++;
		}
		if (tentativi == length_word)
		{
			cout << "\n\tWORD FIND:   ";
			for (int x = 0; x < length_word; x++)
			{
				cout << population[a][x] << " ";
			}
			clock_t end;
			end = clock();
			cout << "\n\n\tTime: " << ((double)(end - start)) / CLOCKS_PER_SEC << " seconds\n";
			finito = 1;
			return finito;
		}
	}
	tentativi = 0;
}
