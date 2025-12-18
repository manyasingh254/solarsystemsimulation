#include "raylib.h"
#include <math.h>
typedef struct Planet
{
    char name[20];
    float baseDistance;
    float radius;
    float speed;
    float angle;
    Color color;
} Planet;
int main(void)
{
    InitWindow(0, 0, "Solar System - Full Screen");
    ToggleFullscreen();
    SetTargetFPS(60);
    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2;
    Vector2 sunPos = {(float)centerX, (float)centerY};
    Planet planets[] = {
        {"Mercury", 80.0f, 6.0f, 2.0f, 0.0f, LIGHTGRAY},
        {"Venus", 130.0f, 10.0f, 1.5f, 0.0f, ORANGE},
        {"Earth", 180.0f, 11.0f, 1.0f, 0.0f, BLUE},
        {"Mars", 230.0f, 9.0f, 0.8f, 0.0f, RED},
        {"Jupiter", 320.0f, 25.0f, 0.4f, 0.0f, BEIGE},
        {"Saturn", 420.0f, 22.0f, 0.3f, 0.0f, GOLD},
        {"Uranus", 510.0f, 18.0f, 0.2f, 0.0f, SKYBLUE},
        {"Neptune", 590.0f, 18.0f, 0.1f, 0.0f, DARKBLUE}};
    int planetsCount = sizeof(planets) / sizeof(planets[0]);
    float moonAngle = 0.0f;
    while (!WindowShouldClose())
    {
        for (int i = 0; i < planetsCount; i++)
        {
            planets[i].angle += planets[i].speed;
        }
        moonAngle += 3.0f;
        BeginDrawing();
        ClearBackground(BLACK);
        for (int k = 0; k < 400; k++)
        {
            DrawPixel((k * 37) % GetScreenWidth(), (k * k * 7) % GetScreenHeight(), Fade(WHITE, 0.5f));
        }
        DrawCircleV(sunPos, 40.0f, ORANGE);
        DrawCircleV(sunPos, 25.0f, YELLOW);
        DrawText("SUN", sunPos.x - 10, sunPos.y - 5, 10, BLACK);
        for (int i = 0; i < planetsCount; i++)
        {
            float radianAngle = planets[i].angle * (PI / 180.0f);
            float x = sunPos.x + cos(radianAngle) * planets[i].baseDistance;
            float y = sunPos.y + sin(radianAngle) * planets[i].baseDistance;
            Vector2 currentPos = {x, y};
            DrawRing(sunPos, planets[i].baseDistance - 0.5f, planets[i].baseDistance + 0.5f, 0, 360, 0, Fade(WHITE, 0.15f));
            DrawCircleV(currentPos, planets[i].radius, planets[i].color);
            DrawText(planets[i].name, (int)x - 20, (int)y + (int)planets[i].radius + 10, 10, WHITE);
            if (i == 2)
            {
                float moonRad = moonAngle * (PI / 180.0f);
                DrawCircle(x + cos(moonRad) * 25, y + sin(moonRad) * 25, 4.0f, LIGHTGRAY);
            }
            if (i == 5)
            {
                DrawRing(currentPos, planets[i].radius + 8.0f, planets[i].radius + 12.0f, 0, 360, 0, Fade(BEIGE, 0.6f));
            }
        }
        DrawText("Press ESC to Exit", 20, 20, 20, GREEN);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
