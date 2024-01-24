#include <iostream>
#include <cmath>
#include <windows.h>

#include "Quaternion.h"
#include "RTX.h"
#include "Vector.h"

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006

void redraw(float pitch, float yaw, float radius)
{
    RTX raytracer;

    Vector camPos(0, 0, 0);

    const float pitchRadians = pitch * PI / 180.0f;
    const float yawRadians = yaw * PI / 180.0f;

    camPos.x(radius * std::cos(pitchRadians) * std::cos(yawRadians));
    camPos.y(radius * std::sin(pitchRadians) * std::cos(yawRadians));
    camPos.z(radius * std::sin(yawRadians));


    const Vector camDir = (-camPos).Normal();

    std::system("cls");
    raytracer.RayCast(camPos, camDir);
    raytracer.Draw();
    std::cout << "dupa debugging: [" << pitch << "; " << yaw << "; " << radius << "]\ncampos: " << camPos.ToString() << "\ncamdir: " << camDir.ToString() << std::endl;
}

int main()
{
    // Don't @ me.
    float pitch = 0.0f;
    float yaw = 0.0f;
    float radius = 10.0f;

    redraw(pitch, yaw, radius);

    // WINAPIIIIIIIIIIiiiiiiiiiii-
    HANDLE hstdin;
    DWORD mode;

    while(true)
    {
        bool dirty = false;
        hstdin = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(hstdin, &mode);
        SetConsoleMode(hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
        const int opt = std::cin.get();
        if (opt == 0x61) //a
        {
            pitch -= 5.0f;
            dirty = true;
        }
        if (opt == 0x64) //d
        {
            pitch += 5.0f;
            dirty = true;
        }
        if (opt == 0x77) //w
        {
            yaw += 5.0f;
            dirty = true;
        }
        if (opt == 0x73) //s
        {
            yaw -= 5.0f;
            dirty = true;
        }
        if (opt == 0x71) //q
        {
            radius -= 1.0f;
            dirty = true;
        }
        if (opt == 0x65) //e
        {
            radius += 1.0f;
            dirty = true;
        }

        if (dirty)
        {
            if (yaw >= 90.0f) yaw = 90.0f;
            else if (yaw < -90.0f) yaw = -90.f;

            if (pitch >= 360.0f) pitch -= 360.0f;
            else if (pitch < 0.0f) pitch += 360.0f;

            if (radius < 3.0f) radius = 2.0f; // when radius == 1.0f we get an exception -_-

            redraw(pitch, yaw, radius);
        }
    }
}