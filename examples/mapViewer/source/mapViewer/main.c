#include "../gbaLib/types.h"
#include "../gbaLib/input/input.h"
#include "map/map.h"

int main()
{
    Map map = loadMap();
    setMapOnScreen(map);

    const int SHIFT_SPEED = 2;
    BGPoint shift = {0, 0};
    while (TRUE)
    {
        videoSync();

        KeyState inputState = getInputState();
        shift.y += getYAxis(inputState) * SHIFT_SPEED;
        shift.x += getXAxis(inputState) * SHIFT_SPEED;

        shiftMap(map, shift);
    }
}
