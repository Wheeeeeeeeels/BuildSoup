package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;


public class JNICompanyInfo implements Serializable {
    public String name;
    public String code;
    public int randomRoomCapacity;
    public boolean isExpired;
    public String expireDate;       // 企业服务过期时间
    public int daysToExpiredDate;
    public int surplusConversationHours;
    public int surplusConversationMins;
    public int surplusConversationDuration;
    public String cloudRecordUsedSpace;
    public String cloudRecordTotalSpace;
    public int fixedMeetingRoomCount;

    public JNICompanyInfo() {
        name = "";
        code = "";
        randomRoomCapacity = 0;
        isExpired = false;
        expireDate = "";
        daysToExpiredDate = 0;
        surplusConversationHours = 0;
        surplusConversationMins = 0;
        surplusConversationDuration = 0;
        cloudRecordUsedSpace = "";
        cloudRecordTotalSpace = "";
        fixedMeetingRoomCount = 0;
    }
}

