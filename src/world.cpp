class World {
    public:
    vector<Chunk*> chunks;
    Player player;
    World(){
        player = Player();
    }
    
    void tick();
    void blit();
};

void World::tick(){}
void World::blit(){}
