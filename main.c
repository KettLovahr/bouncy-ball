#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.c"

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
                ball.streak += 1;

                game.score += abs((int)ball.xspeed) * ball.streak;

                if (ball.r < 10) {
                    ball.r = 10;
                }
                if (ball.r > 100) {
                    ball.r = 100;
                }
            }
        }

        physics_loop(&ball);

        BeginDrawing();
        ClearBackground(BLACK);
        draw_loop(&ball);

        sprintf(game.score_str, "Score: %d", game.score);
        DrawText(game.score_str, 20, 20, 20, WHITE);
        EndDrawing();
    }
}
