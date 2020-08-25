package bgu.spl.net.Frames;

import bgu.spl.net.PassiveObjects.Book;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.api.MessagingProtocolimp;
import bgu.spl.net.api.User;
import bgu.spl.net.srv.ConnectionImpl;
import bgu.spl.net.srv.Connections;
import javafx.util.Pair;

import java.util.LinkedList;

public class SEND implements MessageIn {
    private String msg;


    public SEND(String msg) {
        this.msg = msg;
    }

    @Override
    public void process(Connections connections, MessagingProtocolimp messagingProtocolimp, int connection_id, String msg) {
        String[] str = msg.split("\n");
        String genre = str[1].split(":")[1];

        LinkedList sent_list = (LinkedList) DataStructure.topic_map.get(genre); //linked list of all subscribers to this topic
        if (sent_list!=null) {
            for (int i = 0; i < sent_list.size(); i++) {
                Pair pair = (Pair) sent_list.get(i);//this pair hold: key:connectionId, value:subscriptionId
                connections.send((Integer) pair.getKey(), new Message((String) pair.getValue(), genre, str[3])); //str[2] is the body of the message

            }
        }

    }

}
