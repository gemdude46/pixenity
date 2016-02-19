
struct Block {
    SColor color;
    bool solid;
    Block(SColor c, bool s) : color(c), solid(s) {}
    Block(){}
};

#define BLOCK_ERROR                                                          255

#define BLOCK_AIR                                                              0
#define BLOCK_STONE                                                            1
#define BLOCK_DIRT                                                             2
#define BLOCK_SAND                                                             3
#define BLOCK_COAL                                                             4

Block BLOCKS[256];
void INITBLOCKS(){
    BLOCKS[BLOCK_AIR]                    = Block(SColor(0,0,0,0),false);
    BLOCKS[BLOCK_STONE]                  = Block(SColor(255,128,128,128),true);
    BLOCKS[BLOCK_DIRT]                   = Block(SColor(255,120,72,0),true);
    BLOCKS[BLOCK_SAND]                   = Block(SColor(255,194,178,128),true);
    BLOCKS[BLOCK_COAL]                   = Block(SColor(255,10,10,10),true);
    
    BLOCKS[BLOCK_ERROR]                  = Block(SColor(255,255,0,0),true);
}

Block BLOCK(int i){
    return BLOCKS[i%256];
}
