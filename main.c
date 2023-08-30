#include <raylib.h>

#define WIDTH 800
#define HEIGHT 600

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
    }
    if (b->y + b->r > HEIGHT || b->y - b->r < 0) {
        b->yspeed = -b->yspeed * b->bounciness;
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

    Ball ball = create_ball(100, 100, 50, RED);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_Q)) {
            TakeScreenshot("screenshot.png");
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointCircle(GetMousePosition(), (Vector2){ball.x, ball.y}, ball.r)) {
                ball.yspeed = -50;
                ball.r -= 1;
            }
        }

        physics_loop(&ball);

        BeginDrawing();
        ClearBackground(BLACK);
        draw_loop(&ball);
        EndDrawing();
    }
}
