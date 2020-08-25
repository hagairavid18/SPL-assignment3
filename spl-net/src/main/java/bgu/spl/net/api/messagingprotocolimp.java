package bgu.spl.net.api;


import bgu.spl.net.Frames.*;
import bgu.spl.net.srv.Connections;

public class MessagingProtocolimp implements StompMessagingProtocol {
    private Connections connections;
    private int connection_id;
    private boolean should_terminate;


    @Override
    public void start(int connectionId, Connections<String> connections) {
        this.connections=connections;
        this.connection_id=connectionId;
        should_terminate = false;
    }

    @Override
    public void process(String msg) {
        String[] str = msg.split("\n");
        switch (str[0]) {
            case "CONNECT": {
                String versionId = str[1].split(":")[1];
                String userName = str[3].split(":")[1];
                String password = str[4].split(":")[1];
                Login login = new Login(userName, password,versionId);
                login.process(connections, this, connection_id,msg);
            }
            break;
            case "SUBSCRIBE":{
                String genre=str[1].split(":")[1];
                String receiptId=str[3].split(":")[1];
                String subscription_id = str[2].split(":")[1];
                JoinGenreClub join=new JoinGenreClub(genre,receiptId,subscription_id);
                join.process(connections,this,connection_id,msg);
            }
            break;
            case "SEND":{
                SEND send=new SEND(msg);
                send.process(connections,this,connection_id,msg);
            }
            break;

            case "UNSUBSCRIBE":{
                String genreId=str[1].split(":")[1];
                String receiptId=str[2].split(":")[1];
                ExitGenreClub exitGenreClub=new ExitGenreClub(genreId, receiptId);
                exitGenreClub.process(connections,this,connection_id,msg);

            }
            break;
            case "DISCONNECT":{
                String receipt_id = str[1].split(":")[1];
                Logout logout = new Logout(receipt_id);
                logout.process(connections,this,connection_id,msg);






            }


        }



    }

    @Override
    public boolean shouldTerminate() {
        return should_terminate;
    }


    public void setTerminate(boolean terminate){
        should_terminate = terminate;

    }
}
