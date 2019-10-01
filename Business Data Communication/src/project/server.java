package project;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static java.lang.System.out;

public class server{
    private static final int LISTEN_PORT = 5987;

    public static void main( String[] args ){
        server server = new server();
        server.listenRequest();
    }

    private void listenRequest() {
        ServerSocket serverSocket = null;
        ExecutorService threadExecutor = Executors.newCachedThreadPool();
        try{
            serverSocket = new ServerSocket( LISTEN_PORT );
            out.println("Server listening requests...");
            while ( true ){
                Socket socket = serverSocket.accept();
                threadExecutor.execute( new RequestThread( socket ) );
            }
        }
        catch ( IOException e ){
            e.printStackTrace();
        }finally{
            threadExecutor.shutdown();
            if ( serverSocket != null )
                try{
                    serverSocket.close();
                }catch ( IOException e ){
                    e.printStackTrace();
                }
        }
    }

    class RequestThread implements Runnable{
        private Socket clientSocket;
        RequestThread(Socket clientSocket)
        {
            this.clientSocket = clientSocket;
        }
        public void run(){
            out.printf("有%s連線進來!\n", clientSocket.getRemoteSocketAddress() );
            ObjectOutputStream output = null;
            ObjectInputStream input = null;
            try{
                output = new ObjectOutputStream( new BufferedOutputStream(this.clientSocket.getOutputStream()) ); output.flush();
                input = new ObjectInputStream( new BufferedInputStream(this.clientSocket.getInputStream()) );
                output.writeUTF( String.format("Hi, %s!\n", clientSocket.getRemoteSocketAddress() ) ); output.flush();
                game g=new game();
                g.set();
                g.gameset(2);
                output.writeObject(g); output.flush();
                while (true){
                    output.writeInt(g.x[0]);
                    output.writeInt(g.y[0]);
                    output.writeBoolean(g.s[0]);
                    output.writeInt(g.c[0]);
                    output.writeObject(g.v[0]);
                    output.writeInt(g.hp[0]);
                    if (g.hp[0] == 0) break;
                    output.writeInt(g.time[0]);
                    output.writeInt(g.pt[0]);
                    output.writeObject(g.bullets);
                    output.writeInt(g.player); output.flush();

                    g.x[1] = input.readInt();
                    g.y[1] = input.readInt();
                    g.s[1] = input.readBoolean();
                    g.c[1] = input.readInt();
                    g.v[1] = (boolean[]) input.readObject();
                    g.hp[1] = input.readInt();
                    if (g.hp[1] == 0) break;
                    g.time[1] = input.readInt();
                    g.pt[1] = input.readInt();
                    g.pc = input.readInt();
                    g.powerup = (PowerUp) input.readObject();
                    g.run();
                }
                g.dispose();
            }catch ( IOException | ClassNotFoundException e ){
                e.printStackTrace();
            } finally{
                try{
                    if ( this.clientSocket != null && !this.clientSocket.isClosed() ) this.clientSocket.close();
                }catch ( IOException e ){
                    e.printStackTrace();
                }
            }
        }
    }
}