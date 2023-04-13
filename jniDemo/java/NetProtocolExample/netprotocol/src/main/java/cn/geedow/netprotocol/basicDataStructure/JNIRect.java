package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIRect implements Serializable {
    public int x;
    public int y;
    public int width;
    public int height;

    public JNIRect() {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }
}
