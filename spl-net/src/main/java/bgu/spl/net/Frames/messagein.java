package bgu.spl.net.Frames;

import bgu.spl.net.api.MessagingProtocolimp;
import bgu.spl.net.srv.ConnectionImpl;
import bgu.spl.net.srv.Connections;

public interface MessageIn {


    public void process(Connections connections, MessagingProtocolimp messagingProtocolimp, int connection_id, String msg);

}
