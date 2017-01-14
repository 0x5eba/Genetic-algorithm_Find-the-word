#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

#define N 100
//#define N 10
#define Max_length 20

int tentativi = 0;
bool trovato = false;

int main()
{
	clock_t start, end;
	double tempo;
	start = clock();
	srand(time(nullptr));
	//population , create a initial population and assign them a random value ( the DNA )
	//every value is a random word and so is a matrice
	
	char word_to_find[Max_length] = { "FreDi" };
	cout << "\tWord to find: " << word_to_find << "\n\n";
	int length_word = 0;
	for (int a = 0; a < Max_length; a++)
	{
		if (isalpha(word_to_find[a]))
		{
			length_word++;
		}
	}

	char start_population[N][N] = { 0 };
	//da 65 a 122 dalal A alla z
	for (int a = 0; a < N; a++)
	{
		for (int b = 0; b < length_word; b++)
		{
			start_population[a][b] = (rand() % 58);
			start_population[a][b] += 65;
			if (!isalpha(start_population[a][b]))
			{
				b--;
				continue;
			}
			//cout << start_population[a][b] << " ";
		}
		for (int x = 0; x < length_word; x++)
		{
			if (start_population[a][x] == word_to_find[x])
			{
				tentativi++;
			}
			if (tentativi == length_word)
			{
				for (int x = 0; x < length_word; x++)
				{
					cout << start_population[a][x];
				}
				trovato = true;
				cout << "\n\n\n\tWORD FIND";
				end = clock();
				cout << "\n\n\t" << ((double)(end - start)) / CLOCKS_PER_SEC;
				system("pause");
				return 0;
			}
		}
		tentativi = 0;
		//cout << endl;
	}
	

	char new_population[N][N] = { 0 };
	int not_start = 0;
	do {
		if (not_start != 0)
		{
			for (int a = 0; a < N; a++)
			{
				for (int b = 0; b < length_word; b++)
				{
					start_population[a][b] = new_population[a][b];
				}
				for (int x = 0; x < length_word; x++)
				{
					if (start_population[a][x] == word_to_find[x])
					{
						tentativi++;
					}
					if (tentativi == length_word)
					{
						for (int x = 0; x < length_word; x++)
						{
							cout << start_population[a][x];
						}
						trovato = true;
						cout << "\n\n\n\tWORD FIND1";
						end = clock();
						cout << "\n\n\t" << ((double)(end - start)) / CLOCKS_PER_SEC;
						system("pause");
						return 0;
					}
				}
				tentativi = 0;
			}
		}
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
		int fitness[N] = { 0 };
		for (int a = 0; a < N; a++)
		{
			for (int b = 0; b < length_word; b++)
			{
				//int sotract = 0;
				for (int c = 0; c < length_word; c++)
				{
					//funziona solo con i doppioni

					/*int conta = 0;
					while (sotract == 0)
					{
					for (int d = 0; d < length_word; d++)
					{
					if (start_population[a][b] == start_population[a][d])
					{
					conta++;
					}
					}
					if (conta != 1)
					{
					sotract++;
					break;
					fitness[a]--;
					}
					}*/
					if (start_population[a][b] == word_to_find[c])
					{
						fitness[a]++;
					}
				}
			}
		}
		int unsettimo = length_word / 7;
		char word_correct[N][N] = { 0 };
		for (int a = 0; a < N; a++)
		{
			if (fitness[a] > unsettimo)
			{
				for (int b = 0; b < length_word; b++)
				{
					word_correct[a][b] = start_population[a][b];
					//cout << word_correct[a][b] << " ";
				}
				//cout << endl;
			}
		}
		//calcolo il fitness di nuovo , in base al numero del fitness lo metto tante volte quante il numero dentro un array
		int fitness2[N] = { 0 };
		int somma = 0;
		for (int a = 0; a < N; a++)
		{
			for (int b = 0; b < length_word; b++)
			{
				for (int c = 0; c < length_word; c++)
				{
					if (start_population[a][b] == word_to_find[c])
					{
						fitness2[a]++;
						somma += 1;
					}
				}
			}
		}
		/*for (int a = 0; a < N; a++)
		{
			cout << fitness2[a] <<" ";
		}
		cout << endl;*/

		/*ruota della fortuna che ha N elementi ogniuno con un proprio valore, e ogni elemento ha la sua probabilità con la sua percentuale di essere preso , e la percentuale aumenta più è grande il numero al suo interno

		posso aggiungere più elementi in base al numero in proporzione al length
		in base a quanti ne ho di 1 ci faccio una certa proporzione , in base a quanti ne ho di 0 faccio un'altra proporzione
		*/



		//selection
		/*
		idk (kill the one with 0 fitness)
		pick 2 parents or 3 or more , but better 2
		make crossover and mutation
		crossover : you can mix half and half , or 4 member of one and 2 take randomly
		mutation : after the crossover if i insert the 1% mutation this mean that i have
		1% of probability to change a letter in a word with a new one
		*/

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
			for (int x = 0; x < length_word; x++)
			{
				if (word_correct2[c][x] == word_to_find[x])
				{
					tentativi++;
				}
				if (tentativi == length_word)
				{
					for (int x = 0; x < length_word; x++)
					{
						cout << word_correct2[a][x] << " ";
					}
					trovato = true;
					cout << "\n\n\n\tWORD FIND2";
					end = clock();
					cout << "\n\n\t" << ((double)(end - start)) / CLOCKS_PER_SEC;
					system("pause");
					return 0;
				}
			}
			tentativi = 0;
		}
		for (int a = 0; a < N; a++)
		{
			for (int b = 0; b < length_word; b++)
			{
				//cout << word_correct2[a][b] << " ";
			}
			//cout << endl;
		}
		new_population[N][N] = { 0 };
		//cout << "\n\n";
		int numero_random = 0;
		for (int a = 0; a < somma; a++)
		{
			for (int b = 0; b < length_word; b++)
			{
				numero_random = rand() % length_word;
				if (b <= length_word / 2)
				{
					new_population[a][numero_random] = word_correct2[a][b];
				}
				else
				{
					new_population[a][numero_random] = (rand() % 58);
					new_population[a][numero_random] += 65;
					if (!isalpha(new_population[a][numero_random]))
					{
						b--;
						continue;
					}
				}
				//cout << new_population[a][b] << " ";
			}
			//cout << endl;
			for (int x = 0; x < length_word; x++)
			{
				if (new_population[a][x] == word_to_find[x])
				{
					tentativi++;
				}
				if (tentativi == length_word)
				{
					for (int x = 0; x < length_word; x++)
					{
						cout << new_population[a][x];
					}
					trovato = true;
					cout << "\n\n\n\tWORD FIND3";
					end = clock();
					cout << "\n\n\t" << ((double)(end - start)) / CLOCKS_PER_SEC;
					system("pause");
					return 0;
				}
			}
			tentativi = 0;
			//cout << endl;
		}

		/*for (int a = 0; a < somma; a++)
		{
		for (int b = 0; b < length_word; b++)
		{
		cout << new_population[a][b] << " ";
		}
		cout << endl;
		}*/
		numero_random = 0;
		for (int a = somma; a < N; a++)
		{
			for (int b = 0; b < length_word; b++)
			{
				numero_random = rand() % length_word;
				new_population[a][numero_random] = (rand() % 58);
				new_population[a][numero_random] += 65;
				if (!isalpha(new_population[a][numero_random]))
				{
					b--;
					continue;
				}
				//cout << new_population[a][b] << " ";
			}
			for (int x = 0; x < length_word; x++)
			{
				if (new_population[a][x] == word_to_find[x])
				{
					tentativi++;
				}
				if (tentativi == length_word)
				{
					for (int x = 0; x < length_word; x++)
					{
						cout << new_population[a][x];
					}
					trovato = true;
					cout << "\n\n\n\tWORD FIND4";
					end = clock();
					cout << "\n\n\t" << ((double)(end - start)) / CLOCKS_PER_SEC;
					system("pause");
					return 0;
				}
			}
			tentativi = 0;
			//cout << endl;
		}
		not_start++;
	}while (trovato == false);
	system("pause");
	return 0;
}
