class Player {
    public:
    vector2df pos, vel;
    vector2d<s32> getIPos(){
        return vector2d<s32>((s32)pos.X,(s32)pos.Y);
    }
};
