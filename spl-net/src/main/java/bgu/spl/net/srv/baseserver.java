package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessageEncoderDecoderimpl;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.api.MessagingProtocolimp;
import sun.management.GcInfoBuilder;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.function.Supplier;

public abstract class BaseServer<T> implements Server<T> {

    private final int port;
    private final Supplier<MessagingProtocolimp> protocolFactory;
    private final Supplier<MessageEncoderDecoderimpl> encdecFactory;
    private ServerSocket sock;
    private ConnectionImpl connections; //i added
    private int connection_id;

    public BaseServer(
            int port,
            Supplier<MessagingProtocolimp> protocolFactory,
            Supplier<MessageEncoderDecoderimpl> encdecFactory) {

        this.port = port;
        this.protocolFactory = protocolFactory;
        this.encdecFactory = encdecFactory;
		this.sock = null;
		connection_id=0;
    }

    @Override
    public void serve() {
        connections = new ConnectionImpl();

        try (ServerSocket serverSock = new ServerSocket(port)) {
			System.out.println("Server started");

            this.sock = serverSock; //just to be able to close

            while (!Thread.currentThread().isInterrupted()) {

                Socket clientSock = serverSock.accept();

                BlockingConnectionHandler<T> handler = new BlockingConnectionHandler<T>(
                        clientSock,
                        encdecFactory.get(),
                        protocolFactory.get(),connection_id,connections);

                connections.addToConnectionMap(handler,connection_id);//add connection handler to connection map;
                connection_id++;



                execute(handler);
            }
        } catch (IOException ex) {
        }

        System.out.println("server closed!!!");
    }

    @Override
    public void close() throws IOException {
		if (sock != null)
			sock.close();
    }

    protected abstract void execute(BlockingConnectionHandler<T>  handler);

}
