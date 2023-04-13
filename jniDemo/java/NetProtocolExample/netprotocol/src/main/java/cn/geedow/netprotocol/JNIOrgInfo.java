package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNIOrgInfo implements Serializable {
    public int orgId;                               // 组织ID
    public String orgName;                          // 组织名称
    public int parentId;                            // 父组织ID
    public boolean hasChild;                        // 是否有子组织
    public boolean hasMember;                       // 是否有成员
    public int numOfEmp;                            // 部门成员人数

    public JNIOrgInfo() {
        orgId = 0;
        orgName = "";
    }

    @Override
    public String toString() {
        return "orgId:" + String.valueOf(orgId) + " orgName:" + orgName +
                " parentId:" + String.valueOf(parentId) + " hasChild:" + String.valueOf(hasChild)+
                " hasMemeber:" + String.valueOf(hasMember);
    }
}
