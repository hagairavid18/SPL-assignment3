package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessageEncoderDecoderimpl;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.api.MessagingProtocolimp;
import bgu.spl.net.impl.rci.ObjectEncoderDecoder;
import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) {
        int port = Integer.parseInt(args[0]);
        String serverType = args[1];


        if (serverType.equals("tpc")) {

            Server.threadPerClient(
                    port, //port
                    MessagingProtocolimp::new, //protocol factory
                    MessageEncoderDecoderimpl::new //message encoder decoder factory
            ).serve();
        }

        if (serverType.equals("reactor")) {

            Server.reactor(
                    10, port,//port
                    MessagingProtocolimp::new, //protocol factory
                    MessageEncoderDecoderimpl::new //message encoder decoder factory
            ).serve();


        }

    }
}
