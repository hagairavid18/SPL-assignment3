package bgu.spl.net.api;

public class User {
    private String user_name;
    private String password;
    //private List<Genre> subscribed_genres;//holds a list with Genres which the user subscribed
    private boolean isOnline;
    //private ConcurrentHashMap<String,LinkedList<Book>> inventory;// the inventory will hold a map of genres
    private int connection_id;

    public User(String user_name, String password, boolean isOnline, int connection_id) {
        this.user_name = user_name;
        this.password = password;
        this.isOnline = isOnline;
        this.connection_id = connection_id;
    }

    public void setOnline(boolean online) {
        isOnline = online;
    }

    public boolean isOnline() {
        return isOnline;
    }
    public String getUser_name() {
        return user_name;
    }

    public String getPassword() {
        return password;
    }
    public int getConnection_id() {
        return connection_id;
    }

    public void setConnection_id(int connection_id) {
        this.connection_id = connection_id;
    }


}
