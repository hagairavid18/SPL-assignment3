package bgu.spl.net.srv;

import bgu.spl.net.Frames.Message;
import bgu.spl.net.api.DataStructure;
import javafx.util.Pair;

import java.awt.*;
import java.util.LinkedList;
import java.util.concurrent.ConcurrentHashMap;

public class ConnectionImpl<T> implements Connections<T> {
    private ConcurrentHashMap<Integer, ConnectionHandler<T>> connection_map;

    public ConnectionImpl(){
        connection_map = new ConcurrentHashMap<>();
    }



    @Override
    public boolean send(int connectionId, Object msg) {
        synchronized (connection_map.get(connectionId)) {//prevent somone from logout and and get message the same time
            if (connection_map.get(connectionId) != null)
                connection_map.get(connectionId).send((T) msg);
        }
        return false;
    }

    @Override
    public void send(String channel, T msg) {
        LinkedList sent_list = (LinkedList) DataStructure.topic_map.get(channel); //linked list of all subscribers to this topic
        if (sent_list!=null) {
            for (int i = 0; i < sent_list.size(); i++) {
                Pair pair = (Pair) sent_list.get(i);//this pair hold: key:connectionId, value:subscriptionId
                send((Integer) pair.getKey(), msg); //str[2] is the body of the message
            }
        }
    }

    @Override
    public void disconnect(int connectionId) {
        synchronized (connection_map.get(connectionId)) {//prevent somone from logout and and get message the same time
            connection_map.remove(connectionId);
        }
    }

    public ConcurrentHashMap<Integer, ConnectionHandler<T>> getConnection_map() {
        return connection_map;
    }

    public void addToConnectionMap(ConnectionHandler connectionHandler,int connection_id){

            connection_map.put(connection_id, connectionHandler);
        }





}
