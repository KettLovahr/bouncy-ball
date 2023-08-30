#include <raylib.h>

typedef struct {
    int x;
    int y;
    float xspeed;
    float yspeed;
    float r;
    float bounciness;
    Color color;
    int streak;
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
    b.streak = 1;
    return b;
}
