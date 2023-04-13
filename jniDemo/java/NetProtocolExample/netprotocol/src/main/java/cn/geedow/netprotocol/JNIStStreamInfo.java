package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNIStStreamInfo implements Serializable {
    public String id;
    public int type;
    public boolean hasVideo;
    public boolean hasAudio;
    public int pushStreamStatus;		// 推流状态
    public int pullStreamStatus;		// 拉流状态

    public JNIStStreamInfo() {
        id = "";
        type = 0;
        hasVideo = false;
        hasAudio = false;
        pushStreamStatus = 1;
        pullStreamStatus = 1;
    }
}
