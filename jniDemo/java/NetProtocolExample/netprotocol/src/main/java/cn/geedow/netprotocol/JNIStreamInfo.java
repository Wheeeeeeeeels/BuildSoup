package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNIStreamInfo implements Serializable {
    public String id;
    public int type;
    public boolean hasVideo;
    public boolean hasAudio;

    public JNIStreamInfo() {
        id = "";
        type = 0;
        hasVideo = false;
        hasAudio = false;
    }
}
