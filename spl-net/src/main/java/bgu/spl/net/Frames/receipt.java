package bgu.spl.net.Frames;

public class Receipt implements MessageOut {
    private String id;


    public Receipt(String id) {
        this.id = id;
    }

    @Override
    public byte[] encode() {
        String strOutput=
                "RECEIPT"+'\n'+
                "receipt-id:"+this.id+'\n'+'\n'+
                '\u0000';
        return strOutput.getBytes();
    }
}
