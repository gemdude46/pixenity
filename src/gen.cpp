#define TG_FREQ                                                           4311.0
#define TG_AMP                                                               512
#define DIRT_DEPTH                                                           200
#define ORE_GEN_NOISE_OFFSET                                                  42
#define COAL_ORE_FREQ                                                        0.3

void Chunk::GEN(){
    int hm[CHSIZE];
    for (int i = 0; i < CHSIZE; i++) hm[i] = noiseGen.GetValue((this->pos.X*CHSIZE+i)/TG_FREQ,this->world->seed,0)*TG_AMP;
    for (int i = 0; i < CHSIZE*CHSIZE; i++) {
        if (this->pos.Y < (TG_AMP/CHSIZE) + 1){
            int h = hm[i%CHSIZE], y = (i/CHSIZE)+(CHSIZE*this->pos.Y);
            if (y < h) this->blocks[i] = BLOCK_AIR;
            else if (y < h+DIRT_DEPTH) this->blocks[i] = BLOCK_DIRT;
            else this->blocks[i] = BLOCK_STONE;
        }
        else {
            int ore = 0;
            if(noiseGen.GetValue(this->pos.X,this->pos.Y,ORE_GEN_NOISE_OFFSET)>(1-COAL_ORE_FREQ)) ore = BLOCK_COAL;
        }
    }
}
