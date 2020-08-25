package bgu.spl.net.PassiveObjects;

public class Genre {
    private String genre_name;
    private String subscription_id;

    public Genre(String genre_name, String subscription_id) {
        this.genre_name = genre_name;
        this.subscription_id = subscription_id;
    }

    public String getGenre_name() {
        return genre_name;
    }

    public String getSubscription_id() {
        return subscription_id;
    }
}
