#include "../gbaLib/types.h"
#include "mapViewer.h"

int main()
{
    loadMap();

    BGPoint shift = {0, 0};
    while (TRUE)
    {
        videoSync();
        shift.y += 1;
        shiftMap(shift);
    }

    return 0;
}
