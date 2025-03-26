class WorldObject {
    public:
      float* x;
      float* y;
      float* rotation;
      float* width;
      float* height;

      WorldObject() {
         this->x = 0;
         this->y = 0;
         this->rotation = 0;
         this->width = 0;
         this->height = 0;
      }

      void render();
};