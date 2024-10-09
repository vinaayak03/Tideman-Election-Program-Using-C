#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct {
    int winner;
    int loser;
} pair;

int preferences[MAX][MAX];
int locked[MAX][MAX];
pair pairs[MAX * (MAX - 1) / 2];

char candidates[MAX][50];
int pair_count;
int candidate_count;

void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int is_cycle(int winner, int loser);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [candidate ...]\n", argv[0]);
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++) {
        strcpy(candidates[i], argv[i + 1]);
    }

    pair_count = 0;
    memset(preferences, 0, sizeof(preferences));
    memset(locked, 0, sizeof(locked));

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    for (int i = 0; i < voter_count; i++) {
        int ranks[MAX];
        printf("Rank the candidates (0 is highest):\n");
        for (int j = 0; j < candidate_count; j++) {
            printf("Rank %d: ", j);
            scanf("%d", &ranks[j]);
        }
        record_preferences(ranks);
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}

void record_preferences(int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void) {
    for (int i = 0; i < pair_count - 1; i++) {
        for (int j = i + 1; j < pair_count; j++) {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser]) {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
}

void lock_pairs(void) {
    for (int i = 0; i < pair_count; i++) {
        if (!is_cycle(pairs[i].winner, pairs[i].loser)) {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }
    }
}

int is_cycle(int winner, int loser) {
    if (loser == winner) {
        return 1;
    }

    for (int i = 0; i < candidate_count; i++) {
        if (locked[loser][i] && is_cycle(winner, i)) {
            return 1;
        }
    }

    return 0;
}

void print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        int found = 0;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
