package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNIConferenceRecordInfo implements Serializable {
    public String recordName;   //文件名
    public long recordSize;       //文件大小(byte)
    public String thumbnailUrl;   //缩略图地址
    public long id;    //会议录制记录id
    public long startTime;   //文件录制开始时间
    public long endTime;    //文件录制结束时间
    public long requestStartTime;   //开始录制时间

    public JNIConferenceRecordInfo() {
        recordName = "";
        recordSize = 0;
        thumbnailUrl = "";
        id = 0;
        startTime = 0;
        endTime = 0;
        requestStartTime = 0;
    }
}
