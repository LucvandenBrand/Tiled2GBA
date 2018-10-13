#include "../gbaLib/types.h"
#include "../gbaLib/input/input.h"
#include "map/map.h"
#include "sprite/sprite.h"

int main()
{
    Map map = loadMap();
    setMapOnScreen(map);

    loadSpriteSheet();
    SpriteObject spriteObjects[128];
    initializeSpriteObjectMemory(spriteObjects, 128);
    setSpritesOnScreen();

    mapObjectsToSpriteObjects(map.objects, spriteObjects, map.numObjects);
    copySpriteObjectsToMemory(spriteObjects, map.numObjects);

    const int SHIFT_SPEED = 2;
    BGPoint shift = {0, 0};
    while (TRUE)
    {
        videoSync();

        KeyState inputState = getInputState();
        shift.y += getYAxis(inputState) * SHIFT_SPEED;
        shift.x += getXAxis(inputState) * SHIFT_SPEED;

        shiftMap(map, shift);

        ObjectPoint objectShift;
        objectShift.x = - getXAxis(inputState) * SHIFT_SPEED;
        objectShift.y = - getYAxis(inputState) * SHIFT_SPEED;

        shiftMapObjects(map.objects, objectShift, map.numObjects);
        mapObjectsToSpriteObjects(map.objects, spriteObjects, map.numObjects);
        copySpriteObjectsToMemory(spriteObjects, map.numObjects);
    }
}
