class World {
    public:
    vector<Chunk*> chunks;
    Player player;
    World(){
        player = Player();
    }
    
    void tick();
    void blit(IrrlichtDevice*);
};

void World::tick(){}
void World::blit(IrrlichtDevice* device){
    for (int i = 0; i < this->chunks.size(); i++){
        if (this->chunks[i]->sfdirty) this->chunks[i]->updateSF(device);
        device->getVideoDriver()->draw2DImage(this->chunks[i]->sf,
        ofs+position2d<s32>(500,333)+((this->chunks[i]->pos*16)-this->player.getIPos()));
    }
}
