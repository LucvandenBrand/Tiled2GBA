#include <string.h>
#include "../engine/video/background.h"
#include "assets/map.h"


/**
 * Draw the titlescreen of the game.
 * Once the player presses start, this function returns.
 */
void titleScreen() {
    //const u32 ANIM_SPEED = 0.1;

    //u32 titleSprite = loadSprite("title");
    memcpy(MEMORY_BACKGROUND_PALETTE, mapPalette, mapPaletteLength);
    memcpy(&MEMORY_CHAR_BLOCK[0][0], mapTileSet, mapTileSetLength);
    memcpy(&MEMORY_SCREEN_BLOCK[30][0], mapTileMap0, mapTileMap0Length);

    REGISTER_BACKGROUND_CONTROL[0] = FLAG_BACKGROUND_CHAR_BLOCK(0)    |
                                     FLAG_BACKGROUND_SCREEN_BLOCK(30) |
                                     FLAG_BACKGROUND_8BPP             |
                                     FLAG_BACKGROUND_REGULAR_32x32;
    REGISTER_DISPLAY_CONTROL = FLAG_MODE0 | FLAG_BACKGROUND0;

    while (TRUE) {

    }
    //drawText("Press START");
    //playMusic("titleMusic");

    //u32 titleX = SCREEN_WIDTH / 2;
    //u32 titleY = SCREEN_HEIGHT / 2;
    //u32 deltaTitleY = 0;
    //u32 button = getButton(BUTTON_START);
    //while (!button) {
    //    deltaTitleY += ANIM_SPEED;
    //    drawSprite(titleSprite, titleX, titleY + sin(deltaTitleY))
    //};

    //stopMusic();
    //playSound("start");
}
