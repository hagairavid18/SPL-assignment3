package bgu.spl.net.impl.echo;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class EchoClient {

    public static void main(String[] args) throws IOException {

        if (args.length == 0) {
            args = new String[]{"localhost", "hello"};
        }

        if (args.length < 2) {
            System.out.println("you must supply two arguments: host, message");
            System.exit(1);
        }

        //BufferedReader and BufferedWriter automatically using UTF-8 encoding
        try (Socket sock = new Socket(args[0], 7777);
                BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()))) {

            String msg1 = "CONNECT" + '\n' + "accept-version:1.2" + '\n' + "host:stomp.cs.bgu.ac.il" + '\n' +"login:bob" + '\n' + "passcode:alice" + '\n' + '\n' + "\u0000";





            String msg2 = "SUBSCRIBE" + '\n' + "destination:sci-fi" + '\n' + "id:78" + '\n' +"receipt:77" + '\n' +  '\n' + "\u0000";
            String msg3 = "SUBSCRIBE" + '\n' + "destination:drama" + '\n' + "id:78" + '\n' +"receipt:77" + '\n' +  '\n' + "\u0000";
            String msg4 = "SEND" + '\n' + "destination:drama" +  '\n' +  '\n' + "Bob has added the book Foundation" +  "\u0000";
            String msg5 = "DISCONNECT" + '\n' + "receipt:78" +  '\n' +  '\n'  +  "\u0000";



            out.write(msg1);
            out.write(msg2);
            out.write(msg3);
            out.write(msg4);
            out.write(msg5);
            out.flush();

            System.out.println("awaiting response");
            String answer = " ";



            while (answer!=null){
                answer=in.readLine();
                    System.out.println(answer);
            }



//            System.out.println("sending message to server");
//            out.write(args[1]);
//            out.newLine();
//            out.flush();
//
//            System.out.println("awaiting response");
//            String line = in.readLine();
//            System.out.println("message from server: " + line);
        }



    }
}
