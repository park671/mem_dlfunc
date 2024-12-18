package com.park.dlfunc;

public class NativeBridge {

    static {
        System.loadLibrary("dlfunc");
    }

    public static native boolean testDynSymFunc();
    public static native boolean testNonDynSymFunc();


}
