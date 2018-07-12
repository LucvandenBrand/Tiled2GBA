#include "../gbaLib/types.h"
#include "mapViewer.h"
#include "../gbaLib/input/input.h"

int main()
{
    loadMap();

    BGPoint shift = {0, 0};
    while (TRUE)
    {
        videoSync();

        KeyState inputState = getInputState();
        shift.y += getYAxis(inputState);
        shift.x += getXAxis(inputState);

        shiftMap(shift);
    }

    return 0;
}
