package bgu.spl.net.impl.rci;

import bgu.spl.net.api.MessagingProtocolimp;
import bgu.spl.net.srv.Connections;

import java.io.Serializable;

public interface Command<T> extends Serializable {

    Serializable execute(T arg);
}
