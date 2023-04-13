package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNIServerInfo implements Serializable {
    public boolean isProxy;                         // 是否为代理服务器
    public String host;                             // 服务器地址
    public int httpPort;                            // 服务器HTTP端口
    public int httpsPort;                           // 服务器HTTPS端口

    public JNIServerInfo() {
        isProxy = false;
        host = "";
        httpPort = 0;
        httpsPort = 0;
    }
}
