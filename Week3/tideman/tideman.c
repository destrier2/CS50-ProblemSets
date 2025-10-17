#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
} pair;

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
int checkCycle(void);
int checkColumn(void);

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
bool vote(int rank, string name, int ranks[])
{
    // TODO - Done

    for(int i = 0; i < candidate_count; i++) {
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
    // TODO - Done
    for(int i = 0; i < candidate_count; i++) { //For each person in the rank
        for(int j = i+1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }    
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO - Done
    for(int i = 0; i < candidate_count; i++) {
        for(int j = i; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            } else if (preferences[j][i] > preferences[i][j]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            } //If equal, do nothing
        }    
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO - Done
    //Using bubble sort because I'm lazy
    int count = 2;
    while (count > 0) {
        count = 0;
        for(int i = 0; i < pair_count-1; i++) {
            for (int j = i+1; j < pair_count; j++) {
                if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser]) {
                    //swap
                    int tempWin = pairs[i].winner;
                    int templose = pairs[i].loser;
                    pairs[i].winner = pairs[j].winner;
                    pairs[i].loser = pairs[j].loser;
                    pairs[j].winner = tempWin;
                    pairs[j].loser = templose;
                    count++;
                }
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for(int i = 0; i < pair_count; i++) {
        //There must still be at least one column that is empty
        if (checkCycle() > 1) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        } else if (checkCycle() == 1) {
            if (checkColumn() != pairs[i].winner) {
                locked[pairs[i].winner][pairs[i].loser] = true;
            } //Else, skip
        }
    }
    return;
}

int checkColumn(void) {
    for(int i = 0; i < candidate_count; i++) {
        bool works = true;
        for(int j = 0; j < candidate_count; j++) {
            if (locked[i][j] == true) {
                works = false;
            }
        }
        if (works) {
            return i;
        }
    }
}

int checkCycle(void) {
    int count = 0;
    for(int i = 0; i < candidate_count; i++) {
        bool works = true;
        for(int j = 0; j < candidate_count; j++) {
            if (locked[i][j] == true) {
                works = false;
            }
        }
        if (works) {
            count++;
        }
    }
    return count;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    /*if (checkCycle() != 1) {
        printf("Error, you messed up somewhere");
    } else {
        int count = 0;
        int index = -1;
        for(int i = 0; i < candidate_count; i++) {
            int wins = 0;
            for(int j = 0; j < candidate_count; j++) {
                if (locked[i][j] == true) {
                    wins++;
                }
            }
            if (wins > count) {
                index = i;
                count = wins;
            }
        }
        printf("%s\n", candidates[index]);
    }*/
    for(int i = 0; i < candidate_count; i++) {
        int falseCount = 0;
        for (int j = 0; j < candidate_count; j++) {
            if (!locked[j][i]) {
                falseCount++;
            }
        }
        if (falseCount == candidate_count) {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
