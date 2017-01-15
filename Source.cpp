#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

#define N 100
#define Max_length 7

int tentativi = 0;
int trovato(char population[N][N], int length_word, char word_to_find[Max_length], int a, clock_t start);

int main()
{
	clock_t start;
	start = clock();
	srand(time(nullptr));
	char word_to_find[Max_length] = { "Nois" };
	cout << "\tWord to find: " << word_to_find << "\n\n";
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
			population[a][b] = (rand() % 58)+ 65;
			if (!isalpha(population[a][b]))
			{
				b--;
				continue;
			}
		}
		trovato(population, length_word, word_to_find, a, start);
	}

	while(true)
	{
		int fitness[N] = { 0 };
		for (int a = 0; a < N; a++)
		{
			for (int b = 0; b < length_word; b++)
			{
				for (int c = 0; c < length_word; c++)
				{
					if (population[a][c] == word_to_find[b])
					{
						fitness[a]++;
					}
				}
			}
		}
		int unquinto = length_word / 5;
		char word_correct[N][N] = { 0 };
		for (int a = 0; a < N; a++)
		{
			if (fitness[a] > unquinto)
			{
				for (int b = 0; b < length_word; b++)
				{
					word_correct[a][b] = population[a][b];
				}
			}
		}
		int fitness2[N] = { 0 };
		int somma = 0;
		for (int a = 0; a < N; a++)
		{
			for (int b = 0; b < length_word; b++)
			{
				for (int c = 0; c < length_word; c++)
				{
					if (population[a][b] == word_to_find[c])
					{
						fitness2[a]++;
						somma += 1;
					}
				}
			}
		}

		char word_correct2[N][N] = { 0 };
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
				}
			}
			trovato(word_correct2, length_word, word_to_find, c, start);
		}
		int numero_random = 0;
		for (int a = 0; a < N; a++)
		{
			numero_random = rand() % 2;
			if (numero_random == 0)
			{
				for (int b = 0; b < length_word/2; b++)
				{
					if (b <= (length_word / 2))
					{
						population[a][b] = word_correct2[a][b];
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
				for (int b = 0; b < length_word / 2; b++)
				{
					if (b > (length_word / 2))
					{
						population[a][b] = word_correct2[a][b];
					}
					population[a][b] = (rand() % 58) + 65;
					if (!(isalpha(population[a][b])))
					{
						b--;
						continue;
					}
				}
			}
			trovato(population, length_word, word_to_find, a, start);
		}
	}
}


int trovato(char population[N][N], int length_word, char word_to_find[Max_length], int a, clock_t start)
{
	for (int x = 0; x < length_word; x++)
	{
		if (population[a][x] == word_to_find[x])
		{
			tentativi++;
		}
		if (tentativi == length_word)
		{
			for (int x = 0; x < length_word; x++)
			{
				cout << population[a][x] << " ";
			}
			cout << "\n\n\tWORD FIND";
			clock_t end;
			end = clock();
			cout << "\n\n\tTIME: " << ((double)(end - start)) / CLOCKS_PER_SEC;
			system("pause");
			return 0;
		}
	}
	tentativi = 0;
}
