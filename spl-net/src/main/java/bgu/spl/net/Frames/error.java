package bgu.spl.net.Frames;

public class Error implements MessageOut {

    private String error_message;
    private String msgFromClient;



    public Error(String error_message, String msgFromClient) {
        this.error_message = error_message;
        this.msgFromClient = msgFromClient;
    }

    @Override
    public byte[] encode() {
        String strOutput="ERROR"+'\n'+
                "message: "+error_message+'\n'+'\n'+
                "The message:"+'\n'+
                "-----"+'\n'+
                msgFromClient+'\n'+
                "-----"+'\n'+
                '\u0000';

        return strOutput.getBytes();
    }
}
