class World {
    public:
    vector<Chunk*> chunks;
    Player player;
    World(){
        player = Player();
    }
    
    void tick();
    void blit(IrrlichtDevice*);
    void genChunkAt(vector2d<s32> p){
        chunks.push_back(new Chunk(p));
    }
    Chunk* getChunkAt(vector2d<s32> p){
        for (int i = 0; i < chunks.size(); i++) if(chunks[i]->pos == p) return chunks[i]; return NULL;
    }
    void requireChunkAt(vector2d<s32> p){
        if (!getChunkAt(p)) genChunkAt(p);
    }
};

void World::tick(){
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
}
