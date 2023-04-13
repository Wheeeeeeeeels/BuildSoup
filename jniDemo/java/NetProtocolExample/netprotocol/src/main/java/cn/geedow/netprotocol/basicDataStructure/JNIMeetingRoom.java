package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIMeetingRoom implements Serializable {
    public int type;					    // 会议室类型
    public String id;					    // 会议室ID
    public String name;			            // 会议室名称
    public int status;                      // 会议室状态
    public int capacity;					// 会议室方数
    public String shortNum;				    // 内部呼叫短号
    public String expiredDate;			    // 会议室到期时间
    public String roomIcon;				    // 会议室头像
    public boolean hasAdminRights;          // true表示有管理员权限

    public JNIMeetingRoom() {
        type = -1;
        id = "";
        name = "";
        status = 0;
        capacity = 0;
        shortNum = "";
        expiredDate = "";
        roomIcon = "";
        hasAdminRights = false;
    }
}
