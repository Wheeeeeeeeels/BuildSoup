package cn.geedow.netprotocol.basicDataStructure;

public class JNIStreamQuality {
    public int type;
    public String resolution;
    public String videoBitRate;
    public String audioBitRate;
    public int fps;
    public double videoPacketLostRate;
    public double audioPacketLostRate;

    public JNIStreamQuality() {
        type = 0;
        resolution = "";
        videoBitRate = "";
        audioBitRate = "";
        fps = 0;
        videoPacketLostRate = 0.0D;
        audioPacketLostRate = 0.0D;
    }
}
