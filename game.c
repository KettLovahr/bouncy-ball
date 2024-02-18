#include "ball.c"
#include <raylib.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 800


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
            game->ballv[i].xspeed *= -1.0 * game->ballv[i].bounciness;
        }
        if (game->ballv[i].y + game->ballv[i].r > HEIGHT || game->ballv[i].y - game->ballv[i].r < 0) {
            game->ballv[i].yspeed *= -1.0 * game->ballv[i].bounciness;
            game->ballv[i].streak = 1;
        }

        //Clamp position to screen space
        game->ballv[i].x = clamp(game->ballv[i].x, game->ballv[i].r, WIDTH - game->ballv[i].r);
        game->ballv[i].y = clamp(game->ballv[i].y, game->ballv[i].r, HEIGHT - game->ballv[i].r);


        game->ballv[i].r = clamp(game->ballv[i].r, 10, 100);
    }
}

void draw_loop(GameState *game) {
    for (int i = 0; i < game->ballc; i++) {
        DrawCircle(game->ballv[i].x, game->ballv[i].y, game->ballv[i].r, game->ballv[i].color);
    }
}

Ball* create_ball(GameState *game, int x, int y, float r, Color color) {
    Ball b;
    b.x = x;
    b.y = y;
    b.r = r;
    b.color = color;

    b.xspeed = 5;
    b.yspeed = 0;
    b.bounciness = 0.8;
    b.streak = 1;

    game->ballv[game->ballc] = b;
    return &game->ballv[game->ballc++];
}

void get_ball_click(GameState *game, Vector2 mouse_position) {
    for (int i = 0; i < game->ballc; i++) {
        if (CheckCollisionPointCircle(mouse_position, (Vector2){game->ballv[i].x, game->ballv[i].y}, game->ballv[i].r)) {
            game->ballv[i].yspeed = -20;
            game->ballv[i].xspeed += (game->ballv[i].xspeed > 0) ? 2 : -2;
            game->ballv[i].r -= 3;

            game->score += 1 * game->ballv[i].streak++;
        }
    }

}

void update_score(GameState *game) {
    sprintf(game->score_str, "Score: %d", game->score);
    DrawText(game->score_str, 20, 20, 20, WHITE);
}
