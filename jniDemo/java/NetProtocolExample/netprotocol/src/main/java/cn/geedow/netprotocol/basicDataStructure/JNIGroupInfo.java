package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIGroupInfo implements Serializable {
    public int groupId;						// 群组ID
    public String groupName;					    // 群组名称
    public int numOfPeople;					// 组内人数
    public String groupIcon;				// 群组头像
    public int type;					    // 群组类型

    public JNIGroupInfo(){
        groupId = 0;
        groupName = "";
        numOfPeople = 0;
        groupIcon = "";
        type = 0;
    }
}
