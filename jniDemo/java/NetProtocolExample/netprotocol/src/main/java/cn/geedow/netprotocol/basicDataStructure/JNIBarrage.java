package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIBarrage implements Serializable {

    public String content;
    public int position;
    public int displayMode;
    public int fontSize;
    public String bgColor;
    public float opacity;

    public JNIBarrage() {
        content = "";
        position = 0;
        displayMode = 0;
        fontSize = 0;
        bgColor = "";
        opacity = 0;
    }
}
