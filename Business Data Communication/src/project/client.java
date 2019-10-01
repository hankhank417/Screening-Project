package project;

import java.io.*;
import java.net.Socket;
import java.util.*;

public class client{
    public static void main( String[] args ) throws IOException{
        String host;
        int port = 5987;
        Socket socket = null;
        Scanner consoleInput = new Scanner( System.in );
        System.out.println("請輸入Server端位址");
        host = consoleInput.nextLine();
        try{
            socket = new Socket( host, port );
            ObjectInputStream input = null;
            ObjectOutputStream output = null;
            try{
                input = new ObjectInputStream( new BufferedInputStream(socket.getInputStream()) );
                output = new ObjectOutputStream( new BufferedOutputStream(socket.getOutputStream()) ); output.flush();
                System.out.println( input.readUTF() );
                game gg = (game) input.readObject();
                gg.set();
                while (true){
                    gg.x[0] = input.readInt();
                    gg.y[0] = input.readInt();
                    gg.s[0] = input.readBoolean();
                    gg.c[0] = input.readInt();
                    gg.v[0] = (boolean[]) input.readObject();
                    gg.hp[0] = input.readInt();
                    if (gg.hp[0] == 0) break;
                    gg.time[0] = input.readInt();
                    gg.pt[0] = input.readInt();
                    gg.bullets = (ArrayList<Bullet>) input.readObject();
                    gg.player = input.readInt();

                    output.writeInt(gg.x[1]);
                    output.writeInt(gg.y[1]);
                    output.writeBoolean(gg.s[1]);
                    output.writeInt(gg.c[1]);
                    output.writeObject(gg.v[1]);
                    output.writeInt(gg.hp[1]); output.flush();
                    if (gg.hp[1] == 0) break;
                    output.writeInt(gg.time[1]);
                    output.writeInt(gg.pt[1]);
                    output.writeInt(gg.pc);
                    output.writeObject(gg.powerup); output.flush();

                    gg.run();
                }
                gg.dispose();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }catch ( IOException e ){
            e.printStackTrace();
        }finally{
            if ( socket != null ) socket.close();
            consoleInput.close();
        }
    }
}