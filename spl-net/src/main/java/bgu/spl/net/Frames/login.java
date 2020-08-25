package bgu.spl.net.Frames;

import bgu.spl.net.api.DataStructure;
import bgu.spl.net.api.MessagingProtocolimp;
import bgu.spl.net.api.User;
import bgu.spl.net.srv.Connections;

public class Login implements MessageIn {
    private  String userName;
    private String password;
    private String version_id;

    public Login(String userName, String password, String version_id) {
        this.userName = userName;
        this.password = password;
        this.version_id = version_id;
    }

    public String getUserName() {
        return userName;
    }

    public String getPassword() {
        return password;
    }

    @Override
    public void process(Connections connections, MessagingProtocolimp messagingProtocolimp, int connection_id, String msg) {

        if (DataStructure.users_map.get(userName)==null) { //in case the connection was successful but the user dose'nt exist
            User user = new User(userName,password,true, connection_id);
            DataStructure.users_map.put(userName,user);
            connections.send(connection_id,new Connected(version_id));

        }else {
            if (DataStructure.users_map.get(userName).isOnline()) {//in case user is exist, but already logged in
                DataStructure.users_map.get(userName).setOnline(false);
                connections.send(connection_id, new Error("User already logged in", msg));
                connections.disconnect(connection_id); //remove from connection map;
                messagingProtocolimp.setTerminate(true);
            }
            else if (!DataStructure.users_map.get(userName).getPassword().equals(password)) { //in case the the password is invalid
                DataStructure.users_map.get(userName).setOnline(false);
                connections.send(connection_id, new Error("Wrong password", msg));
                connections.disconnect(connection_id); //remove from connection map;

                messagingProtocolimp.setTerminate(true);
            }
            else if (!DataStructure.users_map.get(userName).isOnline() & DataStructure.users_map.get(userName).getPassword().equals(password)){ //in case user exist, password valid and he is offline
                DataStructure.users_map.get(userName).setConnection_id(connection_id); //update connection id, in case someone connected from another computer' update this
                DataStructure.users_map.get(userName).setOnline(true);
                connections.send(connection_id,new Connected(version_id));
            }
        }



    }
}
