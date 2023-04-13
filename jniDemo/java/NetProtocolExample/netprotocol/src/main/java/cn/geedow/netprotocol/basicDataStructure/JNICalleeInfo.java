package cn.geedow.netprotocol.basicDataStructure;

public class JNICalleeInfo {
    public JNIUserInfo userInfo;
    public long expireTime;

    public JNICalleeInfo() {
        userInfo = new JNIUserInfo();
        expireTime = 0;
    }
}
