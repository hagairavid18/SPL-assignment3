package bgu.spl.net.Frames;

import bgu.spl.net.api.DataStructure;
import bgu.spl.net.api.MessagingProtocolimp;
import bgu.spl.net.api.User;
import bgu.spl.net.srv.ConnectionImpl;
import bgu.spl.net.srv.Connections;

public class JoinGenreClub implements MessageIn {
    private String genre_to_join;
    private String subscription_id;
    private String receipt_id;

    public JoinGenreClub(String genre_to_join,String receipt_id, String subscription_id) {
        this.genre_to_join = genre_to_join;
        this.receipt_id = receipt_id;
        this.subscription_id = subscription_id;

    }

    @Override
    public void process(Connections connections, MessagingProtocolimp messagingProtocolimp, int connection_id, String msg) {


        DataStructure.subscribeTopic(connection_id,genre_to_join,subscription_id);
        connections.send(connection_id,new Receipt(receipt_id));




    }
}
