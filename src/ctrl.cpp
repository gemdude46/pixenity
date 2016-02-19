#define NOCLIP_SPEED                                                           1

void Player::tick(){
    if (this->noclip){
        this->vel=vector2df();
        if (KD(KEY_UP))    this->pos+=vector2df(0,-NOCLIP_SPEED);
        if (KD(KEY_DOWN))  this->pos+=vector2df(0, NOCLIP_SPEED);
        if (KD(KEY_LEFT))  this->pos+=vector2df(-NOCLIP_SPEED,0);
        if (KD(KEY_RIGHT)) this->pos+=vector2df(NOCLIP_SPEED, 0);
    }
    this->pos+=this->vel;
}
