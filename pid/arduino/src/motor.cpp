class Motor{
    public:
        Motor(){
            // Initialize motor
        }
        void setSpeed(int speed){
            // Set speed
            this->speed = speed;
        }
        int getSpeed(){
            // Get speed
            return this->speed;
        }
    private:
        int speed;
};