#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

#define N 20
#define Word "Tests"
#define Mutation 1
#define minFitness 0

int tentativi = 0;
int finito = 0;
clock_t start;
int trovato(char population[N][N], int *length_word, int *a);

int main()
{
	start = clock();
	srand(time(NULL));
	char population[N][N] = { 0 };
	int fitness[N] = { 0 };
	char word_correct[N][N] = { 0 };
	int sum = 0;
	int copy_a = 0;

	cout << "\n\tWord to find: " << Word << "\n";
	cout << "\npopulation: " << N << "\n";
	cout << "mutation: " << Mutation << "%\n";
	cout << "minimum fitness: " << minFitness << "\n\n";
	//cout << "\n(More letters , more waiting)\n\n";
	int length_word = strlen(Word);
	
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
		trovato(population, &length_word, &a);
		if (finito == 1) { system("pause"); return 0; }
	}

	while (finito == 0)
	{
		sum = 0;
		//FITNESS
		for (int a = 0; a < N; a++) //azzero per ogni ciclo
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
					if (population[a][c] == Word[b])//aumento il fitness di una parola ( casuale ) in base a quante parole ha in comune con "Word"
						fitness[a]++;
				}
			}
			//SELECTION
			if (fitness[a] > minFitness)//tengo solo le parole con un certo fitness ( in media maggiore di 0 )
			{
				copy_a++;
				for (int c = 0; c < length_word; c++)//copio ed elimino se ci sono spazi vuoti in più
				{
					word_correct[copy_a][c] = population[a][c];
				}
				sum += 1;//tengo conto di quante parole ci sono sono in tutto corrette
			}
			trovato(word_correct, &length_word, &copy_a);
			if (finito == 1) { system("pause"); return 0; }
		}
		copy_a = 0;

		//CROSSOVER
		int random_number = 0;
		int random_mutation = 0;
		for (int a = 0; a < N; a++)
		{
			//primo metodo
			random_number = rand() % 2;
			random_mutation = 0;
			if (random_number == 0)//prendo in considerazione ( delle parole corrette ) le lettere inferirori o uguali a "b" , e le metto nella nuova popolazione , le restanti sono casuali
			{
				for (int b = 0; b < length_word; b++)
				{
					//random_mutation
					random_mutation = rand() % 101;
					if (random_mutation <= Mutation)//se il valore random tra 0 e 100 è minore o uguale alla percentuale di mutazione , che abbiamo scelto all'inizio , genera un valore casuale
					{
						population[a][b] = (rand() % 58) + 65;
						if (!(isalpha(population[a][b])))
						{
							b--;
							continue;
						}
						continue;
					}
					if (b <= (length_word / 2) && a < sum)
					{
						population[a][b] = word_correct[a][b];
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
			if (random_number == 1)//prendo in considerazione ( delle parole corrette ) le lettere maggiori a "b" , e le metto nella nuova popolazione , le restanti sono casuali
			{
				for (int b = 0; b < length_word; b++)
				{
					random_mutation = rand() % 101;
					if (random_mutation <= Mutation)
					{
						population[a][b] = (rand() % 58) + 65;
						if (!(isalpha(population[a][b])))
						{
							b--;
							continue;
						}
						continue;
					}
					if (b > (length_word / 2) && a < sum)
					{
						population[a][b] = word_correct[a][b];
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
			/*random_number = rand() % length_word;
			random_mutation = 0;
			for (int b = 0; b < length_word; b++)
			{
			if (a < sum)
			{
			if (b <= random_number)
			{
			population[a][b] = word_correct[a][b];
			continue;
			}
			if (b > random_number)
			{
			if (a == sum - 1)
			{
			population[a][b] = word_correct[a - 1][b];
			continue;
			}
			population[a][b] = word_correct[a+1][b];
			continue;
			}
			}
			if (a >= sum)
			{
			//random_mutation
			random_mutation = rand() % 100;
			if (random_mutation <= random_mutation)
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
			trovato(population, &length_word, &a);
			if (finito == 1) { system("pause"); return 0; }
		}
		random_number = 0;
	}
	return 0;
}

int trovato(char population[N][N], int *length_word, int *a)
{
	for (int x = 0; x < *length_word; x++)
	{
		if (population[*a][x] == Word[x])//controllo se tutte le lettere in sequenza sono uguali alla parola da trovare
		{
			tentativi++;
		}
		if (tentativi == *length_word)
		{
			cout << "\tWORD FIND:   ";
			for (int x = 0; x < *length_word; x++)//stampo le parole trovate per vedere se effettivamente è corretto
			{
				cout << population[*a][x] << " ";
			}
			clock_t end;
			end = clock();
			cout << "\n\n\tTime: " << ((double)(end - start)) / CLOCKS_PER_SEC << " seconds\n\n";
			finito = 1;
			return finito;
		}
	}
	tentativi = 0;
}
