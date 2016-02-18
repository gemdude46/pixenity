#define CHSIZE 128

class Chunk {
    public:
    int blocks[CHSIZE*CHSIZE];
    ITexture* sf;
    vector3d<s32> pos;
    Chunk (vector3d<s32> p) {
        for (int i = 0; i < CHSIZE*CHSIZE; i++) blocks[i] = p.Y > 0;
        sf = NULL;
        pos = p;
    }
    void updateSF(IrrlichtDevice*);
};

void Chunk::updateSF(IrrlichtDevice* device){
    if (this->sf) this->sf->drop();
    IImage* I = device->getVideoDriver()->createImage(ECF_A8R8G8B8,dimension2d<u32>(4*CHSIZE,4*CHSIZE));
    
    for (int i = 0; i < CHSIZE*CHSIZE; i++){
        SColor c = BLOCKCOLORS[this->blocks[i]%256];
        int x = (i%CHSIZE)*4, y = (i/CHSIZE)*4;
        I->setPixel(x,y,c);   I->setPixel(x+1,y,c);   I->setPixel(x+2,y,c);   I->setPixel(x+3,y,c);
        I->setPixel(x,y+1,c); I->setPixel(x+1,y+1,c); I->setPixel(x+2,y+1,c); I->setPixel(x+3,y+1,c);
        I->setPixel(x,y+2,c); I->setPixel(x+1,y+2,c); I->setPixel(x+2,y+2,c); I->setPixel(x+3,y+2,c);
        I->setPixel(x,y+3,c); I->setPixel(x+1,y+3,c); I->setPixel(x+2,y+3,c); I->setPixel(x+3,y+3,c);
    }
    
    this->sf = device->getVideoDriver()->addTexture("chunkSF",I);
    this->sf->grab();
    I->drop();
}
