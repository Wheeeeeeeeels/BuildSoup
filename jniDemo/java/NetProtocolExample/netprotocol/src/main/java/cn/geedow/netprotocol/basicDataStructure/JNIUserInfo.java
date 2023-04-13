package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIUserInfo implements Serializable {
    public String account;					        // 平台生成的用户唯一标识
    public String name;					            // 昵称
    public String icon;					            // 头像

    public String department;					    // 所属部门，游客为空
    public int departmentId;                        // 部门id

    public int accountType;					        // 账号类型
    public int terminalType;			            // 终端类型

    public String serialNumber;					    // 设备序列号
    public String deviceModel;					    // 硬终端型号

    public String phone;					        // 手机号
    public String email;					        // 邮箱

    @Override
    public String toString() {
        return "JNIUserInfo{" +
                "account='" + account + '\'' +
                ", name=" + name +
                ", department=" + department +
                ", icon=" + icon +
                ", accountType=" + accountType +
                ", terminalType=" + terminalType +
                ", serialNumber=" + serialNumber +
                ", deviceModel=" + deviceModel +
                ", phone=" + phone +
                ", email=" + email +
                '}';
    }

    public JNIUserInfo(){
        account = "";
        name = "";
        icon = "";

        department = "";
        departmentId = -1;

        accountType = 0;
        terminalType = 7;

        serialNumber = "";
        deviceModel = "";

        phone = "";
        email = "";
    }
}
