#include "../gbaLib/types.h"
#include "mapViewer.h"
#include "../gbaLib/input/input.h"

int main()
{
    loadMap();

    const int SHIFT_SPEED = 2;
    BGPoint shift = {0, 0};
    while (TRUE)
    {
        videoSync();

        KeyState inputState = getInputState();
        shift.y += getYAxis(inputState) * SHIFT_SPEED;
        shift.x += getXAxis(inputState) * SHIFT_SPEED;

        shiftMap(shift);
    }

    return 0;
}
