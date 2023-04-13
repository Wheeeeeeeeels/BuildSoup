package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNIConfRoomInfo implements Serializable {
    public int id;                 // 会议室id
    public int userId;                //登录用户id
    public String roomSubject;             // 会议室主题
    public String roomId;                // 会议室id
    public int roomCapacity;           //会议室容量
    public String  password;      //入会密码
    public String  moderatorPassword;  //主持人密码
    public String  micStatus;    //入会静音模式（全部静音：on，不静音：off）
    public String  videoStatus;   //入会视频状态（开启：on，关闭：off）
    public String  sharePower;    //开启：on，关闭：off
    public String allowPartOperMic;  //是否允许用户操作静音模式（是：on，否：off）
    public String allowPartOperShare;  //（开启：on，关闭：off）

    public JNIConfRoomInfo() {
        id = 0;
        userId = 0;
        roomSubject = "";
        roomId = "";
        roomCapacity = 0;
        password = "";
        moderatorPassword = "";
        micStatus = "";
        videoStatus = "";
        sharePower = "";
        allowPartOperMic = "";
        allowPartOperShare = "";
    }
}
