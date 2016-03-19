#define TG_FREQ                                                           4311.0
#define TG_AMP                                                               512
#define DIRT_DEPTH                                                           100

#define COAL_ORE_FREQ                                                      140.1
#define COAL_ORE_DENSITY                                                    0.03
#define COAL_ORE_DEPTH                                                         0 
#define COAL_ORE_OFFSET                                                        6

#define GOLD_NGT_FREQ                                                       12.1
#define GOLD_NGT_DENSITY                                                    -0.5
#define GOLD_NGT_DEPTH                                                      1000
#define GOLD_NGT_OFFSET                                                       79

void Chunk::GEN(){
    int hm[CHSIZE];
    for (int i = 0; i < CHSIZE; i++) hm[i] = noiseGen.GetValue((this->pos.X*CHSIZE+i)/TG_FREQ,this->world->seed,0)*TG_AMP;
    
    
    
    for (int i = 0; i < CHSIZE*CHSIZE; i++) {
        int h = hm[i%CHSIZE], y = (i/CHSIZE)+(CHSIZE*this->pos.Y);
        if (y < h) this->blocks[i] = BLOCK_AIR;
        else if (y < h+DIRT_DEPTH) this->blocks[i] = BLOCK_DIRT;
        else {
            
            if (this->pos.Y*CHSIZE >= COAL_ORE_DEPTH &&
            noiseGen.GetValue(
                (this->pos.X*CHSIZE+(i%CHSIZE))/COAL_ORE_FREQ,
                COAL_ORE_OFFSET+0.5,
                (this->pos.Y*CHSIZE+(i/CHSIZE))/COAL_ORE_FREQ
            ) > 1-COAL_ORE_DENSITY) this->blocks[i] = BLOCK_COAL;
            
            else if (this->pos.Y*CHSIZE >= GOLD_NGT_DEPTH &&
            noiseGen.GetValue(
                (this->pos.X*CHSIZE+(i%CHSIZE))/GOLD_NGT_FREQ,
                GOLD_NGT_OFFSET+0.5,
                (this->pos.Y*CHSIZE+(i/CHSIZE))/GOLD_NGT_FREQ
            ) > 1-GOLD_NGT_DENSITY) this->blocks[i] = BLOCK_GOLD;
            
            else this->blocks[i] = BLOCK_STONE;
        }
    }
}
