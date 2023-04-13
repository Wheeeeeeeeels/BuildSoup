package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;
import java.util.ArrayList;

public class JNIAllMeetingRooms implements Serializable {
    public ArrayList<JNIMeetingRoom> fixedMeetingRooms;            // 固定会议室信息

    public JNIAllMeetingRooms() {
        fixedMeetingRooms = new ArrayList<>();
    }
}
