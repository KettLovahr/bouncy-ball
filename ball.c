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
