package bgu.spl.net.api;

import javafx.util.Pair;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

public class DataStructure {

    //message counter is responsible to give any message an id
    public volatile static Integer message_counter= 0;

    public volatile static  ConcurrentHashMap<String,User> users_map = new ConcurrentHashMap<>();//holds user names as keys and user as value

    public volatile static ConcurrentHashMap<String, List<Pair<Integer ,String>>> topic_map = new ConcurrentHashMap<>();//for each genre holds a list of : connection id, subscription id(String),


    public static void subscribeTopic(int connection_id, String genre, String subscription_id){ // a method that subscribe a user to a topic
        if (topic_map.get(genre) ==null){
            topic_map.put(genre,new LinkedList<Pair<Integer, String>>());
        }

        if (!isSubscribing(genre,connection_id)) topic_map.get(genre).add(new Pair<>(connection_id,subscription_id));
    }
    public static void unSubscribeTopic(int connection_id, String genre){
        if(topic_map.get(genre)!=null) {
            for (Pair p : topic_map.get(genre))
                if (p.getKey().equals(connection_id)) {
                    topic_map.get(genre).remove(p);
                    break;
                }
        }
    }
    public static void unSubscribeTopicGivenSubscriptionId(int connection_id, String subscription_id){
        for(String genre:topic_map.keySet()){//check every genre in the topic map
            for(Pair p:topic_map.get(genre)){//in each genre check all subscribers
                if((p.getKey().equals(connection_id))&&(p.getValue().equals(subscription_id))){//for each subscriber compare its subscription id to input
                    topic_map.get(genre).remove(p);//if equal- remove
                    break;
                }
            }
        }
    }
    private static boolean isSubscribing(String genre, int connection_id){
        for (int i=0; i<topic_map.get(genre).size(); i++) {
            if (topic_map.get(genre).get(i).getKey() == null) {
                return true;
            }
        }
        return false;
    }
    public static User searchByConnectionId(int connection_id){
        for(User user:users_map.values()){
            if(user.getConnection_id()==connection_id)
                return user;
        }
        return null;//if user has not found
    }






}
