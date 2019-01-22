#include "main.h"
#include "./input/input.h"

int main()
{
    Map map = loadMap();
    setMapOnScreen(map);

    loadSpriteSheet();
    OBJ_ATTR spriteObjects[128];
    initializeSpriteObjectMemory(spriteObjects, 128);
    showMapObjects(&map, spriteObjects);
    setSpritesOnScreen();

    const int SHIFT_SPEED = 2;
    BackgroundPoint backgroundShift = {0, 0};
    while (TRUE)
    {
        vid_vsync();

        KeyState inputState = getInputState();
        backgroundShift.y += getYAxis(inputState) * SHIFT_SPEED;
        backgroundShift.x += getXAxis(inputState) * SHIFT_SPEED;
        shiftMap(map, backgroundShift);

        ObjectPoint objectShift = {0, 0};
        objectShift.x = getXAxis(inputState) * SHIFT_SPEED;
        objectShift.y = getYAxis(inputState) * SHIFT_SPEED;
        shiftMapObjects(map.objects, objectShift, map.numObjects);
        showMapObjects(&map, spriteObjects);
    }
}
