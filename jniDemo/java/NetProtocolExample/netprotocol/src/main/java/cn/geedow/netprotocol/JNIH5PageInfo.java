package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNIH5PageInfo implements Serializable {
    public int type;
    public String url;

    public JNIH5PageInfo() {
        url = "";
    }
}
