#include <stdio.h>
#include <stdlib.h>

void print_line_of_stars(int M) {

    for (int i = 0; i < M + 2; i++) {
        printf("*");
    }
    printf("\n");
}


void move_up(int *x, char *character) {
    if (*x != 1) {
        (*x)--;
        *character = '^';
    }
}


void move_left(int *y, char *character) {
    if (*y != 1) {
        (*y)--;
        *character = '<';
    }
}


void move_down(int *x, char *character, int N) {
    if (*x != N) {
        (*x)++;
        *character = 'v';
    }

}


void move_right(int *y, char *character, int M) {
    if (*y != M) {
        (*y)++;
        *character = '>';
    }

}

int calculate_distance(int x, int y, int new_l, int new_c) {
    return abs(x - new_l) + abs(y - new_c);
}
    

void calculate_obstacle_next_pos(int x, int y, int *l, int *c) {

    int new_l, new_c, value, min;

    // linia de deasupra de pe tablă
    value = calculate_distance(x, y, *l - 1, *c - 1);
    min = value;

    new_l = *l - 1;
    new_c = *c - 1;

    value = calculate_distance(x, y, *l - 1, *c);
    if (value < min) {
        min = value;
        new_l = *l - 1;
        new_c = *c;
    }

    value = calculate_distance(x, y, *l - 1, *c + 1);
    if (value < min) {
        min = value;
        new_l = *l - 1;
        new_c = *c + 1;
    }

    // linia curentă de pe tablă
    value = calculate_distance(x, y, *l, *c - 1);
    if (value < min) {
        min = value;
        new_l = *l;
        new_c = *c - 1;
    }

    value = calculate_distance(x, y, *l, *c + 1);
    if (value < min) {
        min = value;
        new_l = *l;
        new_c = *c + 1;
    }

    // linia urmatoare de pe tablă
    value = calculate_distance(x, y, *l + 1, *c - 1);
    if (value < min) {
        min = value;
        new_l = *l + 1;
        new_c = *c - 1;
    }
    value = calculate_distance(x, y, *l + 1, *c);
    if (value < min) {
        min = value;
        new_l = *l + 1;
        new_c = *c;
    }

    value = calculate_distance(x, y, *l + 1, *c + 1);
    if (value < min) {
        min = value;
        new_l = *l + 1;
        new_c = *c + 1;
    }
        
    // Modificare poziție obstacol
    *l = new_l;
    *c = new_c;
}

int move_character(int *x, int *y, int N, int M, char *character) {

    char move;
    scanf("\n%c", &move);

    switch (move) {
        case 'w': 
            move_up(x, character);
            return 0;

        case 'a':
            move_left(y, character);
            return 0;

        case 's':
            move_down(x, character, N);
            return 0;

        case 'd':
            move_right(y, character, M);
            return 0;

        case 'q':
            return 1;
    }
    return 1;
}

int is_the_game_ended(int x, int y, int N, int M) {
    return (x == N && y == M) ? 1 : 0;
}

int main() {

    int N, M, x, y, P, quit_game = 0, i, j, number_rounds = 0,
        l1 = -1, l2 = -1, l3 = -1, c1, c2, c3;

    char character = 'v', mobil = 'm', m1, m2, m3;
    
    // Citire input
    scanf("%d %d %d %d %d", &N, &M, &y, &x, &P);

    if (P >= 1) {
        scanf("%d %d %c", &l1, &c1, &m1);
    }
    if (P >= 2) {
        scanf("%d %d %c", &l2, &c2, &m2);
    }
    if (P == 3) {
        scanf("%d %d %c", &l3, &c3, &m3);
    }

    // Începerea jocului
    while (1) {

        if (quit_game) {
            break;
        }

        // Afișare tabela
        print_line_of_stars(M);

        for (i = 1; i < N + 1; i++) {

            printf("*"); // Prima stea de pe o linie

            for (j = 1; j < M + 1; j++) {

                if (i == x && j == y) {
                    printf("%c", character);

                } else if ((i == l1 && j == c1) || 
                           (i == l2 && j == c2) ||
                           (i == l3 && j == c3)) {
                    // Este cumva obstacol pe aceasta pozitie ?
                    printf("x");
                } else {
                    printf(" ");
                }
            }

            printf("*\n"); // Ultima stea de pe o linie
        }

        print_line_of_stars(M);

        if (is_the_game_ended(x, y, N, M)) {
            printf("GAME COMPLETED\n");
            break;
        }

        // Daca quit_game este 1 încheiem jocul
        quit_game = move_character(&x, &y, N, M, &character);

        number_rounds++;

        if (is_the_game_ended(x, y, N, M)) {
            // Mergem la iteratia următoare pentru că trebuie printată tabela
            // și apoi afișat mesajul GAME COMPLETED
            continue;
        }
        
        if ((x == l1 && y == c1) || 
            (x == l2 && y == c2) ||
            (x == l3 && y == c3)) {
            // Daca personajul se suprapune cu vreun obstacol inainte de 
            // mutarea acestora
            printf("GAME OVER\n");
            break;
        }

        if (number_rounds % 2 == 0) {

            // Calculez poziția următoare a obstacolelor mobile
            if (l1 != -1 && m1 == mobil)
                calculate_obstacle_next_pos(x, y, &l1, &c1);

            if (l2 != -1 && m2 == mobil) 
                calculate_obstacle_next_pos(x, y, &l2, &c2);

            if (l3 != -1 && m3 == mobil) 
                calculate_obstacle_next_pos(x, y, &l3, &c3);
        }

        if ((x == l1 && y == c1) || 
            (x == l2 && y == c2) ||
            (x == l3 && y == c3)) {
            // Daca personajul se suprapune cu vreun obstacol dupa
            // mutarea acestora
            printf("GAME OVER\n");
            break;
        } 

    }

    return 0;
}
