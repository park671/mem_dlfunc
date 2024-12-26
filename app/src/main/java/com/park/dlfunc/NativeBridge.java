package com.park.dlfunc;

import java.lang.reflect.Method;

public class NativeBridge {

    static {
        System.loadLibrary("dlfunc");
    }

    public static native boolean testDynSymFunc();

    public static native boolean testNonDynSymFunc();

    public static native boolean initEnv(Method m1, Method m2);

    public static native boolean injectTrampoline(Method method);
}
