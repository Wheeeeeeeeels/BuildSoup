package cn.geedow.netprotocol.basicDataStructure;

public class JNIPushedMsg {
    public long id;
    public long timestamp;
    public int type;
    public boolean unreadFlag;
    public String content;
    public String ruid;

    public JNIPushedMsg() {
        id = 0;
        timestamp = 0;
        type = 0;
        unreadFlag = false;
        content = "";
        ruid = "";
    }

    @Override
    public String toString() {
        return "JNIPushedMsg{" +
                "id=" + id +
                ", timestamp=" + timestamp +
                ", type=" + type +
                ", unreadFlag=" + unreadFlag +
                ", content='" + content + '\'' +
                ", ruid='" + ruid + '\'' +
                '}';
    }
}
