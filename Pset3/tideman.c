#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) //vamos supor que o eleitor esteja digitando o 1º nome "rank[0]"
{
    //Aqui o eleitor está digitando o nome e o programa está vendo se é válido
    //Quando achar, o ranks[0] recebe i. Ou seja, a primeira opção recebe i que é o nome do candidato. A segunda opção ficará salva em ranks[1]...
    for (int i = 0; i < candidate_count; i++) { 
        if (strcmp(candidates[i], name) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //ex: Eleitor 1
    //1º Alice, 2º Charlie, 3º Bob
    //Alice > Charlie = 1 //Alice > bob = 1 // Charlie > Bob = 1
    //Eleitor 2
    //1º Bob, 2º Alice, 3º Charlie
    //Bob > Alice = 1 // Bob > Charlie = 1 // Alice > Charlie = 2
    for (int i = 0; i < candidate_count -1; i++) {
        int preferido = ranks[i];
        for (int j = i + 1; j < candidate_count; j++) {
            int contra = ranks[j];
            preferences[preferido][contra]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Percorrer cada candidato e ver através da matriz preferences[preferido][contra] se ele ganhou, perdeu ou empatou 
    //ex: Alice
    //vs Bob. Perdeu, ganhou ou empatou?
    for (int i = 0; i < candidate_count - 1; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if(preferences[i][j] != preferences[j][i]) {
                pair novo_par;
                if(preferences[i][j] > preferences[j][i]) {
                    novo_par.winner = i;
                    novo_par.loser = j;
                }
                else {
                    novo_par.winner = j;
                    novo_par.loser = i;
                }
                pairs[pair_count] = novo_par;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for(int i = 0; i < pair_count; i++)
    {
        int valor1 = preferences[pairs[i].winner][pairs[i].loser];
        for (int j = i + 1; j < pair_count; j++) {
            int valor2 = preferences[pairs[j].winner][pairs[j].loser];
            if (valor1 < valor2) {
                pair aux = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = aux;
            }
        }
    }
}

bool verificar_ciclo(int pai, int filho) 
{
    if (locked[filho][pai]) {
        return true;
    }
    
    for (int i = 0; i < candidate_count; i++) {
        if (locked[filho][i] && verificar_ciclo(pai, i)) {
            return true;
        }
    }
    
    return false;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        pair p = pairs[i];
        bool ciclo = verificar_ciclo(p.winner, p.loser);
        if (!ciclo) {
            locked[p.winner][p.loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) {
        bool fonte = true;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                fonte = false;
                break;
            }
        }
        if (fonte) {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}