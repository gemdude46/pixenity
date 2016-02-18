#define BLOCK_AIR                                                              0
#define BLOCK_STONE                                                            1
#define BLOCK_DIRT                                                             2

SColor BLOCKCOLORS[256];
void INITBLOCKCOLORS(){
    BLOCKCOLORS[BLOCK_AIR]                            = SColor(0,0,0,0);
    BLOCKCOLORS[BLOCK_STONE]                          = SColor(255,128,128,128);
    BLOCKCOLORS[BLOCK_DIRT]                           = SColor(255,209,105,10);
}
