package project;

import java.io.Serializable;

class PowerUp implements Serializable {
    int x;
    int y;
    int type;

    PowerUp(){
        this.x = (30 + (int)(Math.random() * 580.0D));
        this.y = (280 + (int)(Math.random() * 80.0D));
        this.type = ((int)(Math.random() * 5.0D));  //特殊效果種類
    }
}