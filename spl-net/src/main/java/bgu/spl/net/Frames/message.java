package bgu.spl.net.Frames;

import bgu.spl.net.api.DataStructure;

public class Message implements MessageOut {
    private String message_id;
    private String subscription_id;
    private String topic;
    private String body;

    public Message(String subscription_id, String topic, String body) {
        this.topic = topic;
        this.body = body;
        synchronized (DataStructure.message_counter) {
            message_id = DataStructure.message_counter.toString();
            DataStructure.message_counter++;
        }
        this.subscription_id = subscription_id;
    }

    @Override
    public byte[] encode() {
        String strOutput=
                "MESSAGE"+'\n'
                +"subscription:"+subscription_id+'\n'
                +"Message-id:"+message_id+'\n'
                +"destination:"+topic+'\n'+'\n'
                +body+'\n'
                +'\u0000';
        return strOutput.getBytes();
    }
}
