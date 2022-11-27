
using namespace std;

int King::checkMove(int target){
    int dir = target - this.getPos();
    bool pseudo;
    bool legal;
    for(int i = 0; i < 8; i++){
        if(dir == direction[i]){
            pseudo = true;
            break;
        }
    }
    if(pseudo){
        
    }
}



