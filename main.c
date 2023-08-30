#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.c"

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Kett's Raylib Test");

    GameState game = create_gamestate();
    Ball* ball = create_ball(&game, 100, 100, 50, RED);
    Ball* ball2 = create_ball(&game, 300, 300, 50, BLUE);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_Q)) {
            TakeScreenshot("screenshot.png");
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            get_ball_click(&game, GetMousePosition());
        }

        game_loop(&game);

        BeginDrawing();
        ClearBackground(BLACK);
        draw_loop(&game);

        update_score(&game);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
