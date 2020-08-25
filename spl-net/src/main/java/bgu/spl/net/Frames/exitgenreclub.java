package bgu.spl.net.Frames;

import bgu.spl.net.api.DataStructure;
import bgu.spl.net.api.MessagingProtocolimp;
import bgu.spl.net.srv.Connections;

public class ExitGenreClub implements MessageIn {
    private String subscriptionId;
    private String receipt_id;


    public ExitGenreClub(String subscriptionId, String receipt_id) {
        this.subscriptionId = subscriptionId;
        this.receipt_id = receipt_id;
    }

    @Override
    public void process(Connections connections, MessagingProtocolimp messagingProtocolimp, int connection_id, String msg) {


        DataStructure.unSubscribeTopicGivenSubscriptionId(connection_id, subscriptionId);
        connections.send(connection_id, new Receipt(receipt_id));

    }
}
