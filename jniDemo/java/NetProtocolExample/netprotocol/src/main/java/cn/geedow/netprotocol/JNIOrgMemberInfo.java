package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNIOrgMemberInfo implements Serializable {
    public int orgId;                               // 成员所属组织ID
    public String account;                          // 成员账号
    public String name;                             // 成员名称
	public String userIcon;							// 用户头像	
    public int status;                              // 成员状态
    public int accountType;                         // 成员账号状态
    public String serialNumber;                     // 成员序列号
    public String uuid;                             // 成员内部编号
    public long utcInviteTimeout;
    public String phone;                            // 成员手机号
    public String email;                            // 用户邮箱
    public String departFullName;                   // 部门名称全路径
    public boolean isFrequentContact;               // 是否为常用联系人

    public JNIOrgMemberInfo() {
        orgId = 0;
        account = "";
        name = "";
        userIcon = "";
        status = 0;
        accountType = 0;
        serialNumber = "";
        uuid = "";
        utcInviteTimeout = 0;
        phone = "";
        email = "";
        departFullName = "";
        isFrequentContact = false;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        JNIOrgMemberInfo that = (JNIOrgMemberInfo) o;
        return account.equals(that.account);
    }
}
