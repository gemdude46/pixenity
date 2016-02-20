#define NOCLIP_SPEED                                                           1
#define WALK_SPEED                                                           0.7
#define JUMP_POWER                                                             1
#define FRICTION                                                             1.5

#define KM_UP                                                             KEY_UP
#define KM_DOWN                                                         KEY_DOWN
#define KM_LEFT                                                         KEY_LEFT
#define KM_RIGHT                                                       KEY_RIGHT
#define KM_JUMP                                                           KEY_UP

void Player::tick(World* world){
    if (this->noclip){
        this->vel=vector2df();
        if (KD(KM_UP))    this->pos+=vector2df(0,-NOCLIP_SPEED);
        if (KD(KM_DOWN))  this->pos+=vector2df(0, NOCLIP_SPEED);
        if (KD(KM_LEFT))  this->pos+=vector2df(-NOCLIP_SPEED,0);
        if (KD(KM_RIGHT)) this->pos+=vector2df(NOCLIP_SPEED, 0);
    }else{
        bool ongr = BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-3,8))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-2,8))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-1,8))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(0, 8))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(1, 8))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(2, 8))).solid;
        
        bool lsol = BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5,-7))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5,-6))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5,-5))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5,-4))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5,-3))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5,-2))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5,-1))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5, 0))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5, 1))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5, 2))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5, 3))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5, 4))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5, 5))).solid;
        
        bool rsol = BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4,-7))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4,-6))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4,-5))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4,-4))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4,-3))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4,-2))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4,-1))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4, 0))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4, 1))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4, 2))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4, 3))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4, 4))).solid ||
                    BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(4, 5))).solid;
                    
        
        if (ongr) this->vel.X/=FRICTION;
        
        if (ongr && this->vel.Y > 0) this->vel.Y = 0;
        if (!ongr) this->vel.Y += world->gravity;
        
        if (ongr && KD(KM_LEFT) && ! lsol) {
            this->vel.X = -WALK_SPEED;
            if (BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5, 7))).solid){
                this->pos.Y-=1;
                if (BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(-5, 7))).solid) this->pos.Y-=1;
            }
        }
        if (ongr && KD(KM_RIGHT) && ! rsol) {
            this->vel.X = WALK_SPEED;
            if (BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(5, 7))).solid){
                this->pos.Y-=1;
                if (BLOCK(world->getBlockAt(this->getIPos()+vector2d<s32>(5, 7))).solid) this->pos.Y-=1;
            }
        }
        if (ongr && KD(KM_JUMP)) this->vel.Y = -JUMP_POWER;
        
        if (lsol && this->vel.X < 0) this->vel.X = 0;
        if (rsol && this->vel.X > 0) this->vel.X = 0;
    }
    this->pos+=this->vel;
}
