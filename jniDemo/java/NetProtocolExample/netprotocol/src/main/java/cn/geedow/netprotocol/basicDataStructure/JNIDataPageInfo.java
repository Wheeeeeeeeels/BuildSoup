package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIDataPageInfo implements Serializable {
    public boolean upToAll;                 //
    public int totalDatas;
    public int pageNum;
    public int pageSize;
    public int totalPages;
    public String version;

    public JNIDataPageInfo(){
        upToAll = false;
        totalDatas = 0;
        pageNum = 1;
        pageSize = 1;
        totalPages = 0;
        version = "";
    }
}
