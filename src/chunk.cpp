#define CHSIZE                                                               128

class Chunk {
    public:
    int blocks[CHSIZE*CHSIZE];
    ITexture* sf;
    bool sfdirty;
    position2d<s32> pos;
    World* world;
    Chunk (position2d<s32> p, World* w) {
        world=w;
        sf = NULL;
        pos = p;
        sfdirty = true;
        GEN();
    }
    void updateSF(IrrlichtDevice*);
    void GEN();
    void clean(){sf->drop();}
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
