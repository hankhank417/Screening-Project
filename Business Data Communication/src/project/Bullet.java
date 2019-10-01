package project;

class Bullet {
    int x,y,t;
    boolean dead=false;

    Bullet(int x, int y, int t){
        this.x=x;
        this.y=y;
        this.t=t;//子彈屬於哪隊的
    }
}