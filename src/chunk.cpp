#define CHSIZE 128

class Chunk {
    public:
    int blocks[CHSIZE*CHSIZE];
    ITexture* sf;
    bool sfdirty;
    position2d<s32> pos;
    Chunk (position2d<s32> p) {
        for (int i = 0; i < CHSIZE*CHSIZE; i++) {
            if (p.Y < 0){
                blocks[i] = BLOCK_AIR;
                continue;
            }
            if (p.Y == 0){
                blocks[i] = BLOCK_DIRT;
                continue;
            }
            if (p.Y > 0){
                blocks[i] = BLOCK_STONE;
                continue;
            }
        }
        sf = NULL;
        pos = p;
        sfdirty = true;
    }
    void updateSF(IrrlichtDevice*);
};

void Chunk::updateSF(IrrlichtDevice* device){
    if (this->sf) this->sf->drop();
    IImage* I = device->getVideoDriver()->createImage(ECF_A8R8G8B8,dimension2d<u32>(4*CHSIZE,4*CHSIZE));
    
    for (int i = 0; i < CHSIZE*CHSIZE; i++){
        SColor c = BLOCK(this->blocks[i]).color;
        int x = (i%CHSIZE)*4, y = (i/CHSIZE)*4;
        I->setPixel(x,y,c);   I->setPixel(x+1,y,c);   I->setPixel(x+2,y,c);   I->setPixel(x+3,y,c);
        I->setPixel(x,y+1,c); I->setPixel(x+1,y+1,c); I->setPixel(x+2,y+1,c); I->setPixel(x+3,y+1,c);
        I->setPixel(x,y+2,c); I->setPixel(x+1,y+2,c); I->setPixel(x+2,y+2,c); I->setPixel(x+3,y+2,c);
        I->setPixel(x,y+3,c); I->setPixel(x+1,y+3,c); I->setPixel(x+2,y+3,c); I->setPixel(x+3,y+3,c);
    }
    
    this->sf = device->getVideoDriver()->addTexture("chunkSF",I);
    this->sf->grab();
    I->drop();
    this->sfdirty = false;
}
