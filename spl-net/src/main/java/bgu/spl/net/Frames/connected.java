package bgu.spl.net.Frames;

public class Connected implements MessageOut {
    String version_id;

    public Connected(String version_id) {
        this.version_id = version_id;
    }

    @Override
    public byte[] encode() {
        String strOutput =
                "CONNECTED" + '\n'
                        + "version:" + version_id + '\n' + '\n'
                        + '\u0000';
        return strOutput.getBytes();
    }


}