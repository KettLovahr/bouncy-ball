#include "ball.c"

#define WIDTH 800
#define HEIGHT 600


typedef struct {
    int score;
    char score_str[15];
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

void physics_loop(Ball *b) {
    b->yspeed++;
    b->x += b->xspeed;
    b->y += b->yspeed;

    //Check collision against screen edges
    if (b->x + b->r > WIDTH || b->x - b->r < 0) {
        b->xspeed = -b->xspeed * b->bounciness;
        b->r += 1;
    }
    if (b->y + b->r > HEIGHT || b->y - b->r < 0) {
        b->yspeed = -b->yspeed * b->bounciness;
        b->r += 1;
        b->streak = 1;
    }

    //Clamp to screen
    b->x = clamp(b->x, 0 + b->r, WIDTH - b->r);
    b->y = clamp(b->y, 0 + b->r, HEIGHT - b->r);
}

void draw_loop(Ball *b) {
    DrawCircle(b->x, b->y, b->r, b->color);
}


