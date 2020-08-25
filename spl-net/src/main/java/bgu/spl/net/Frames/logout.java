package bgu.spl.net.Frames;

import bgu.spl.net.api.DataStructure;
import bgu.spl.net.api.MessagingProtocolimp;
import bgu.spl.net.api.User;
import bgu.spl.net.srv.ConnectionImpl;
import bgu.spl.net.srv.Connections;

import java.util.Iterator;
import java.util.LinkedList;

public class Logout implements MessageIn {
    String receipt_id;

    public Logout(String receipt_id) {
        this.receipt_id = receipt_id;
    }

    @Override
    public void process(Connections connections, MessagingProtocolimp messagingProtocolimp, int connection_id,String msg) {
        for(String genre:DataStructure.topic_map.keySet()){//unsubscribe the client from all topics
            //if the client isn't subscribing one of the topics then the call will change nothing
            DataStructure.unSubscribeTopic(connection_id,genre);
        }
        User userToLogOut=DataStructure.searchByConnectionId(connection_id);
        userToLogOut.setOnline(false);
        connections.send(connection_id,new Receipt(receipt_id));
        userToLogOut.setConnection_id(0);
        connections.disconnect(connection_id);
        messagingProtocolimp.setTerminate(true);


    }
}
