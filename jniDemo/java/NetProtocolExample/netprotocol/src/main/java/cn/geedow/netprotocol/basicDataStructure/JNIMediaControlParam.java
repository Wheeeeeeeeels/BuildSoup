package cn.geedow.netprotocol.basicDataStructure;

public class JNIMediaControlParam {
    public String account;      // 码流所属用户账号
    public int streamType;      // 码流类型
    public int mediaType;       // 0:audio 1:video

    public JNIMediaControlParam(){
        account = "";
        streamType = 0;
        mediaType = 1;
    }

    public JNIMediaControlParam(String account_, int streamType_, int mediaType_){
        account = account_;
        streamType = streamType_;
        mediaType = mediaType_;
    }
}
