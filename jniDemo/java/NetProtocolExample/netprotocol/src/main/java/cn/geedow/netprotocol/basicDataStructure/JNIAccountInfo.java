package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIAccountInfo implements Serializable {

    public String phone;					// 手机号
    public String email;					// 邮箱
    public String username;				    // 用户昵称
    public String userOrgName;			    // 用户所属组织名
    public String userIcon;				    // 用户头像

    public JNIAccountInfo(){
        phone = "";
        email = "";
        username = "";
        userOrgName = "";
        userIcon = "";
    }
}
