#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    int score;
    char score_str[10];
} GameState;

typedef struct {
    int x;
    int y;
    float xspeed;
    float yspeed;
    float r;
    float bounciness;
    Color color;
} Ball;

Ball create_ball(int x, int y, float r, Color color) {
    Ball b;
    b.x = x;
    b.y = y;
    b.r = r;
    b.color = color;

    b.xspeed = 5;
    b.yspeed = 0;
    b.bounciness = 0.9;
    return b;
}

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
    }

    //Clamp to screen
    b->x = clamp(b->x, 0 + b->r, WIDTH - b->r);
    b->y = clamp(b->y, 0 + b->r, HEIGHT - b->r);
}

void draw_loop(Ball *b) {
    DrawCircle(b->x, b->y, b->r, b->color);
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Kett's Raylib Test");

    GameState game = {0, ""};
    Ball ball = create_ball(100, 100, 50, RED);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_Q)) {
            TakeScreenshot("screenshot.png");
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointCircle(GetMousePosition(), (Vector2){ball.x, ball.y}, ball.r)) {
                ball.yspeed = -20;
                ball.xspeed = (ball.xspeed > 0) ? ball.xspeed + 2 : ball.xspeed - 2;
                ball.r -= 3;

                game.score += abs((int)ball.xspeed);

                if (ball.r < 10) {
                    ball.r = 10;
                }
            }
        }

        physics_loop(&ball);

        BeginDrawing();
        ClearBackground(BLACK);
        draw_loop(&ball);

        sprintf(game.score_str, "%d", game.score);
        DrawText(game.score_str, 20, 20, 20, WHITE);
        EndDrawing();
    }
}
