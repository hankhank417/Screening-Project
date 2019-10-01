package project;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;

import javax.swing.JFrame;

public class game extends JFrame{
    private static final long serialVersionUID = 1;
    int[] x;//玩家x座標
    int[] y;//玩家y座標
    boolean[] s;//發射與否
    int[] c;//子彈冷卻時間
    boolean[][] v;//移動與否
    int[] hp;//血量
    int[] time;//特殊效果剩餘時間
    int[] pt;//特殊效果種類
    int pc;//特殊效果出現的剩餘時間
    ArrayList<Bullet> bullets = new ArrayList<>();//儲存子彈的陣列
    PowerUp powerup;//特殊效果
    int player;//玩家人數

    void setClient(){
        setSize(640, 640);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setLocationRelativeTo(null);
        setFocusable(true);
        repaint();
    }

    void set(){ //程式初始化
        setSize(640, 640);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setLocationRelativeTo(null);
        setFocusable(true);

        addKeyListener(new KeyListener() {
            public void keyTyped(KeyEvent e) {}
            public void keyPressed(KeyEvent e) {
                int k = e.getKeyCode();
                requestFocus();
                switch(k){
                    case KeyEvent.VK_UP: v[0][0]=true; break;
                    case KeyEvent.VK_DOWN: v[0][1]=true; break;
                    case KeyEvent.VK_LEFT: v[0][2]=true; break;
                    case KeyEvent.VK_RIGHT: v[0][3]=true; break;
                    case KeyEvent.VK_SLASH: s[0]=true; break;

                    case KeyEvent.VK_W: v[1][0]=true; break;
                    case KeyEvent.VK_S: v[1][1]=true; break;
                    case KeyEvent.VK_A: v[1][2]=true; break;
                    case KeyEvent.VK_D: v[1][3]=true; break;
                    case KeyEvent.VK_Q: s[1]=true; break;

                    case KeyEvent.VK_Y: v[2][0]=true; break;
                    case KeyEvent.VK_H: v[2][1]=true; break;
                    case KeyEvent.VK_G: v[2][2]=true; break;
                    case KeyEvent.VK_J: v[2][3]=true; break;
                    case KeyEvent.VK_T: s[2]=true; break;

                    case KeyEvent.VK_P: v[3][0]=true; break;
                    case KeyEvent.VK_SEMICOLON : v[3][1]=true; break;
                    case KeyEvent.VK_L: v[3][2]=true; break;
                    case 222: v[3][3]=true; break;
                    case KeyEvent.VK_O: s[3]=true; break;

                    case KeyEvent.VK_2: gameset(2); break;
                    case KeyEvent.VK_3: gameset(3); break;
                    case KeyEvent.VK_4: gameset(4); break;
                }
            }

            public void keyReleased(KeyEvent e) {
                int k = e.getKeyCode();
                requestFocus();
                switch(k){
                    case KeyEvent.VK_UP: v[0][0]=false; break;
                    case KeyEvent.VK_DOWN: v[0][1]=false; break;
                    case KeyEvent.VK_LEFT: v[0][2]=false; break;
                    case KeyEvent.VK_RIGHT: v[0][3]=false; break;
                    case KeyEvent.VK_SLASH: s[0]=false; break;

                    case KeyEvent.VK_W: v[1][0]=false; break;
                    case KeyEvent.VK_S: v[1][1]=false; break;
                    case KeyEvent.VK_A: v[1][2]=false; break;
                    case KeyEvent.VK_D: v[1][3]=false; break;
                    case KeyEvent.VK_Q: s[1]=false; break;

                    case KeyEvent.VK_Y: v[2][0]=false; break;
                    case KeyEvent.VK_H: v[2][1]=false; break;
                    case KeyEvent.VK_G: v[2][2]=false; break;
                    case KeyEvent.VK_J: v[2][3]=false; break;
                    case KeyEvent.VK_T: s[2]=false; break;

                    case KeyEvent.VK_P: v[3][0]=false; break;
                    case KeyEvent.VK_SEMICOLON : v[3][1]=false; break;
                    case KeyEvent.VK_L: v[3][2]=false; break;
                    case 222: v[3][3]=false; break;
                    case KeyEvent.VK_O: s[3]=false; break;
                }
            }
        });
    }

    void gameset(int t){ //每場遊戲的初始化
        player=t;
        x=new int[player];
        y=new int[player];
        hp=new int[player];
        for(int i=0; i<player; i++){
            if(player<i+3 && i<2) x[i]=320;
            else if(i<2) x[i]=160;
            else x[i]=480;
            y[i] = (i%2==0 ? 220:420);
            hp[i]=100;
        }
        bullets.clear();
        s=new boolean[player];
        c=new int[player];
        v=new boolean[player][4];
        time=new int[player];
        pt=new int[player];
        pc=200;
        powerup=new PowerUp();
    }

    void run(){ //遊戲執行緒
        if(pc==0){
            powerup=new PowerUp();
            pc=-1;
        }
        else if(pc!=-1)pc--;

        for(int i=0; i<player; i++){
            int d=5;
            if(pt[i]==3 && time[i]!=0) d = 8;
            int a = x[i];
            if(v[i][2]) a-=d;
            if(v[i][3]) a+=d;
            int b = y[i];
            if(v[i][0]) b-=d;
            if(v[i][1]) b+=d;
            if( a>25 && a<615 ) x[i] = a;
            if(b>(i%2==0? 25: 345) && b<(i%2==0? 295: 615)) y[i] = b;
            if(c[i]<=0){
                if(s[i] && hp[i]>0){
                    bullets.add(new Bullet(x[i],y[i]+(i%2==0?25:-25),i));
                    if(pt[i]==2&&time[i]!=0){
                        bullets.add(new Bullet(x[i]-40,y[i]+(i%2==0?25:-25),i));
                        bullets.add(new Bullet(x[i]+40,y[i]+(i%2==0?25:-25),i));
                    }
                    c[i]=20;
                }
            } else c[i]--;

            if(time[i]!=0){
                switch(pt[i]){
                    case 0: hp[i]+=30; break;
                    case 1: c[i]-=3; break;
                }
                time[i]--;
            }
        }

        for(Bullet bu:bullets){
            if(bu.t%2==1)bu.y-=20; else bu.y+=20;
            for(int i=0;i<player;i++){
                if(bu.t%2==i%2||hp[i]<=0) continue;
                if(Math.abs(bu.x-x[i])<25 && Math.abs(bu.y-y[i])<25){
                    if(pt[i]!=4||time[i]==0)hp[i]-=10;
                    bu.dead=true;
                }
            }
            if(Math.abs(bu.x-powerup.x)<10 && Math.abs(bu.y-powerup.y)<10 && pc==-1){
                bu.dead=true;
                pc=100+(int)(Math.random()*200);
                switch(powerup.type){
                    case 0: time[bu.t]=1; break;
                    case 1: time[bu.t]=200; break;
                    case 2: time[bu.t]=200; break;
                    case 3: time[bu.t]=500; break;
                    case 4: time[bu.t]=300; break;
                }
                pt[bu.t]=powerup.type;
            }
        }
        for(int i=0;i<bullets.size();i++){
            if(bullets.get(i).y<-100||bullets.get(i).y>740||bullets.get(i).dead){
                bullets.remove(i);
                i--;
            }
        }
        repaint();
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void paint(Graphics paint){
        Image offscreen = createImage(640, 640);
        Graphics2D g = (Graphics2D)offscreen.getGraphics();

        g.fillRect(0, 0, getWidth(), getHeight());
        g.setColor(Color.magenta);
        for(int i=0;i<player;i++)if(pt[i]==4&&time[i]!=0)g.fillRect(x[i]-30, y[i]-30, 60, 60);
        for(int i=0;i<player;i++){
            g.setColor(new Color[]{Color.green,Color.blue,Color.orange,Color.cyan}[i]);
            if(hp[i]>0)g.fillRect(x[i]-25, y[i]-25, 50, 50);
        }
        g.setColor(Color.red);
        for(Bullet b:bullets)g.fillOval(b.x-5, b.y-5, 10, 10);
        g.setColor(Color.white);
        g.setFont(new Font(null, Font.PLAIN, 15));
        for(int i=0;i<player;i++)if(hp[i]>0)g.drawString(hp[i]+"", x[i]-14, y[i]-33);
        g.setColor(Color.yellow);
        if(pc==-1)g.fillRect(powerup.x-10, powerup.y-10, 20, 20);
        g.setColor(Color.red);
        g.setFont(new Font(null, Font.PLAIN, 150));

        paint.drawImage(offscreen, 0, 0, getWidth(), getHeight(),null);
    }
}