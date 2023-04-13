package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNICommType implements Serializable {
    public int number;
    public String str;
    public long longNumber;
    public boolean boolVar;
    public double doubleNumber;

    public JNICommType(){
        number = 0;
        str = "";
        longNumber = 0;
        boolVar = false;
        doubleNumber = 0.0;
    }
}
