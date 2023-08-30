#include "ball.c"

#define WIDTH 800
#define HEIGHT 600


typedef struct {
    int score;
    char score_str[15];
    int ballc;
    Ball ballv[50];
} GameState;

int clamp(int x, int min, int max) {
    if (x < min) {
        return min;
    } else if (x > max) {
        return max;
    } else {
        return x;
    }
}

GameState create_gamestate() {
    GameState game;
    game.score = 0;
    game.ballc = 0;
    return game;
}

void game_loop(GameState *game) {
    for (int i = 0; i < game->ballc; i++) {
        game->ballv[i].yspeed++;
        game->ballv[i].x += game->ballv[i].xspeed;
        game->ballv[i].y += game->ballv[i].yspeed;

        //Check collision against screen edges
        if (game->ballv[i].x + game->ballv[i].r > WIDTH || game->ballv[i].x - game->ballv[i].r < 0) {
            game->ballv[i].xspeed = -game->ballv[i].xspeed * game->ballv[i].bounciness;
            game->ballv[i].r += 1;
        }
        if (game->ballv[i].y + game->ballv[i].r > HEIGHT || game->ballv[i].y - game->ballv[i].r < 0) {
            game->ballv[i].yspeed = -game->ballv[i].yspeed * game->ballv[i].bounciness;
            game->ballv[i].r += 1;
            game->ballv[i].streak = 1;
        }

        //Clamp position to screen space
        game->ballv[i].x = clamp(game->ballv[i].x, game->ballv[i].r, WIDTH - game->ballv[i].r);
        game->ballv[i].y = clamp(game->ballv[i].y, game->ballv[i].r, HEIGHT - game->ballv[i].r);


        game->ballv[i].r = clamp(game->ballv[i].r, 10, 100);
    }
}

void draw_loop(Ball *b) {
    DrawCircle(b->x, b->y, b->r, b->color);
}

Ball* create_ball(GameState *game, int x, int y, float r, Color color) {
    Ball b;
    b.x = x;
    b.y = y;
    b.r = r;
    b.color = color;

    b.xspeed = 5;
    b.yspeed = 0;
    b.bounciness = 0.9;
    b.streak = 1;

    game->ballv[game->ballc] = b;
    return &game->ballv[game->ballc++];
}
