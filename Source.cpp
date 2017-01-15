#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

#define N 100
#define Max_length 20

int tentativi = 0;
int trovato(char population[N][N],int length_word, char word_to_find[Max_length], int a, clock_t start);

int main()
{
	clock_t start;
	start = clock();
	srand(time(nullptr));
	/*population , create a initial population and assign them a random value ( the DNA )
	  every value is a random word and so is a matrice*/
	
	char word_to_find[Max_length] = { "TesT" };
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
	//da 65 a 122 dalla A alla z
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
		trovato(population, length_word, word_to_find, a, start);
	}

	while (true)
	{
		//fitness , this increase when one of the population find a correct word 
		//   ( this is real important but wrong right now )
		/*
		ho la parola "unicorn" da trovare
		creare una ruota della fortuna con delle percentuali delle frasi in base al fitness
		io ho le parole:  unijorm , pancake , blablah , popcorn
		unijorm ha in comune 5 lettere , quindi fitness 5 ( 50% ), lo metto 5 volte
		popcorn ha in comune 4 lettere , quindi fitness 4 ( 40% ), lo metto 4 volte
		pancake ha in comune 1 lettere , quindi fitness 1 ( 10% ), lo metto 1 volta
		blablah ha in comune 0 lettere , quindi fitness 0 ( 0% ), non lo metto
		ora prendo un valore random tra 1 e 10 e vedo cosa viene
		*/
		//la proporzione si fa su la lunghezza della parola e il numero della popolazione
		int fitness[N] = { 0 };
		char word_correct[N][N] = { 0 };
		int fitness2[N] = { 0 };
		int somma = 0;
		for (int a = 0, c = 0; a < N; a++)
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
			trovato(population, length_word, word_to_find, c, start);
		}

		for (int a = 0; a < N; a++)
		{
			if (fitness[a] >= 1)
			{
				for (int b = 0; b < length_word; b++)
				{
					word_correct[a][b] = population[a][b];
					for (int c = 0; c < length_word; c++)
					{
						if (word_correct[a][b] == word_to_find[c])
						{
							fitness2[a]++;
							somma += 1;
						}	
					}
				}
			}
		}
		/*ruota della fortuna che ha N elementi ogniuno con un proprio valore, e ogni elemento ha la sua probabilità con la sua percentuale di essere preso , e la percentuale aumenta più è grande il numero al suo interno

		posso aggiungere più elementi in base al numero in proporzione al length
		in base a quanti ne ho di 1 ci faccio una certa proporzione , in base a quanti ne ho di 0 faccio un'altra proporzione
		*/



		//selection
		/*
		kill the one with 0 fitness
		pick 2 parents or 3 or more , but better 2
		make crossover and mutation
		crossover : you can mix half and half , or 4 member of one and 2 take randomly
		mutation : after the crossover if i insert the 1% mutation this mean that i have
		1% of probability to change a letter in a word with a new one
		*/
		for (int a = 0; a < somma; a++)
		{
			for (int b = 0; b < length_word; b++)
			{
				if (b <= length_word / 2)
				{
					population[a][b] = word_correct[a][b];
				}
				else
				{
					population[a][b] = (rand() % 58) + 65;
					if (!isalpha(population[a][b]))
					{
						b--;
						continue;
					}
				}
			}
			trovato(population, length_word, word_to_find, a, start);
		}
		int numero_random = 0;
		for (int a = 0; a < N; a++)
		{
			numero_random = rand() % 2;
			if (numero_random == 0)
			{
				for (int b = 0; b < length_word; b++)
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
				for (int b = 0; b < length_word; b++)
				{
					if (b >(length_word / 2))
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
	system("pause");
	return 0;
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
			cout << "\n\n\n\tWORD FIND";
			clock_t end;
			end = clock();
			cout << "\n\n\tTIME: " << ((double)(end - start)) / CLOCKS_PER_SEC;
			system("pause");
			return 0;
		}
	}
	tentativi = 0;
}
