package bgu.spl.net.PassiveObjects;

import java.util.Stack;

public class Book {
    private String name;
    private String genre;
    private Stack<String> holders;//will hold all the user names that had hold this book before the current holder

    public Book(String name, String genre) {
        this.name = name;
        this.genre = genre;
        this.holders = new Stack<>();
    }

    public String getName() {
        return name;
    }

    public String getGenre() {
        return genre;
    }

    public Stack<String> getHolders() {
        return holders;
    }

    public void addHolder(String userName){
        holders.push(userName);
    }
}
