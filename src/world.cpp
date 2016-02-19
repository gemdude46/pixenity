#define MAXTICKS                                                           16384

class World {
    public:
    vector<Chunk*> chunks;
    queue<vector2d<s32>> blockupdates;
    Player player;
    World(){
        player = Player();
    }
    
    int  getBlockAt(vector2d<s32>);
    int  getBlockAtForce(vector2d<s32>);
    void setBlockAt(vector2d<s32>,int);
    void setBlockAtForce(vector2d<s32>,int);
    void tick();
    void blit(IrrlichtDevice*);
    void genChunkAt(vector2d<s32> p, bool update = true){
        chunks.push_back(new Chunk(p));
        if (update) for(s32 i = 0; i < CHSIZE; i++) for(s32 j = 0; j < CHSIZE; j++) blockupdates.push(vector2d<s32>(i,j)+(p*16));
    }
    Chunk* getChunkAt(vector2d<s32> p){
        for (int i = 0; i < chunks.size(); i++) if(chunks[i]->pos == p) return chunks[i]; return NULL;
    }
    void requireChunkAt(vector2d<s32> p){
        if (!getChunkAt(p)) genChunkAt(p);
    }
    bool tickBlockAt(vector2d<s32> p, int b){
        if (b==BLOCK_SAND){
            if (!BLOCK(getBlockAt(p+vector2d<s32>(0,1))).solid){
                setBlockAt(p,BLOCK_AIR);
                setBlockAt(p+vector2d<s32>(0,1),BLOCK_SAND);
                return true;
            }
            return false;
        }
        return false;
    }
};

int World::getBlockAt(vector2d<s32> p){
    Chunk* c = this->getChunkAt(vector2d<s32>(pdiv(p.X,CHSIZE),pdiv(p.Y,CHSIZE)));
    if (c) return c->blocks[pmod(p.X,CHSIZE)+(CHSIZE*pmod(p.Y,CHSIZE))];
    return BLOCK_ERROR;
}

int World::getBlockAtForce(vector2d<s32> p){
    vector2d<s32> cp = vector2d<s32>(pdiv(p.X,CHSIZE),pdiv(p.Y,CHSIZE));
    this->requireChunkAt(cp);
    return this->getChunkAt(cp)->blocks[pmod(p.X,CHSIZE)+(CHSIZE*pmod(p.Y,CHSIZE))];
}

void World::setBlockAt(vector2d<s32> p, int n){
    Chunk* c = this->getChunkAt(vector2d<s32>(pdiv(p.X,CHSIZE),pdiv(p.Y,CHSIZE)));
    if (c) {c->blocks[pmod(p.X,CHSIZE)+(CHSIZE*pmod(p.Y,CHSIZE))]=n;
    c->sfdirty = true;}
}

void World::setBlockAtForce(vector2d<s32> p, int n){
    vector2d<s32> cp = vector2d<s32>(pdiv(p.X,CHSIZE),pdiv(p.Y,CHSIZE));
    this->requireChunkAt(cp);
    Chunk* c = this->getChunkAt(cp);
    c->blocks[pmod(p.X,CHSIZE)+(CHSIZE*pmod(p.Y,CHSIZE))]=n;
    c->sfdirty = true;
}

void World::tick(){
    
    if (this->blockupdates.size()>MAXTICKS)
    clog << "Too many updates! (" << this->blockupdates.size() << '/' << MAXTICKS << ") Was some terrain generated?" << endl;
    
    for (int i = 0; i < MAXTICKS && ! this->blockupdates.empty(); i++){
        vector2d<s32> bl = this->blockupdates.front();
        if (this->tickBlockAt(bl,this->getBlockAt(bl))) {
            this->blockupdates.push(bl+vector2d<s32>(0,1));
            this->blockupdates.push(bl+vector2d<s32>(0,-1));
            this->blockupdates.push(bl+vector2d<s32>(1,0));
            this->blockupdates.push(bl+vector2d<s32>(-1,0));
        }
        this->blockupdates.pop();
    }
    
    vector2d<s32> cp = this->player.getChunkPos();
    requireChunkAt(cp+vector2d<s32>(-1,-1)); requireChunkAt(cp+vector2d<s32>(0,-1)); requireChunkAt(cp+vector2d<s32>(1,-1));
    requireChunkAt(cp+vector2d<s32>(-1,0));  requireChunkAt(cp);                     requireChunkAt(cp+vector2d<s32>(1,0));
    requireChunkAt(cp+vector2d<s32>(-1,1));  requireChunkAt(cp+vector2d<s32>(0,1));  requireChunkAt(cp+vector2d<s32>(1,1));
}

void World::blit(IrrlichtDevice* device){
    device->getVideoDriver()->draw2DRectangle(SColor(255,0,255,255),rect<s32>(ofs,dimension2d<s32>(1000,666)));
    for (int i = 0; i < this->chunks.size(); i++){
        if (this->chunks[i]->sfdirty) this->chunks[i]->updateSF(device);
        device->getVideoDriver()->draw2DImage(this->chunks[i]->sf,
        ofs+position2d<s32>(500,333)+((this->chunks[i]->pos*CHSIZE*4)-(this->player.getIPos()*4)),
        rect<s32>(0,0,CHSIZE*4,CHSIZE*4),NULL,WHITE,true);
    }
    device->getVideoDriver()->draw2DImage(device->getVideoDriver()->getTexture("assets/images/player.png"),ofs+position2d<s32>(484,301),
    rect<s32>(0,0,32,64),NULL,WHITE,true);
}
