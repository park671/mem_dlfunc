package com.park.dlfunc;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;

import androidx.annotation.Nullable;

import com.park.dlfunc.databinding.ActivityMainBinding;

import java.lang.reflect.Method;

import dalvik.system.DexFile;

public class MainActivity extends Activity {

    private static final String TAG = "MainActivity";

    private ActivityMainBinding binding;

    @Override
    protected void attachBaseContext(Context newBase) {
        super.attachBaseContext(newBase);
        try {
            Method method1 = StubArtMethodClass.class.getMethod("func1");
            Method method2 = StubArtMethodClass.class.getMethod("func2");
            if (NativeBridge.initEnv(method1, method2)) {
                Log.d(TAG, "native env init success");
            } else {
                Log.e(TAG, "native env init fail");
            }
        } catch (Throwable e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(LayoutInflater.from(this));
        binding.dynsymButton.setOnClickListener(v -> {
            if (NativeBridge.testDynSymFunc()) {
                binding.dynsymButton.setTextColor(Color.GREEN);
            } else {
                binding.dynsymButton.setTextColor(Color.RED);
            }
        });
        binding.symtabButton.setOnClickListener(v -> {
            if (NativeBridge.testNonDynSymFunc()) {
                binding.symtabButton.setTextColor(Color.GREEN);
            } else {
                binding.symtabButton.setTextColor(Color.RED);
            }
        });

        binding.invokeTargetButton.setOnClickListener(v -> {
            new Thread(() -> {
                Log.d(TAG, "target start");
                TargetClass.func0(1, 7);
                Log.d(TAG, "target finish");
            }).start();
        });
        binding.trampolineButton.setOnClickListener(v -> {
            try {
                Method func0 = TargetClass.class.getMethod("func0", int.class, int.class);
                NativeBridge.injectTrampoline(func0);
            } catch (NoSuchMethodException e) {
                throw new RuntimeException(e);
            }
        });

        binding.triggerButton.setOnClickListener(v -> {
            try {
                AssetUtils.copyAssetToFilesDir(MainActivity.this, "test.dex", null);
                String path = getFilesDir() + "/test.dex";
                DexFile.loadDex(path, null, 0);
            } catch (Throwable tr) {
                Log.e(TAG, "error", tr);
            }
        });
        setContentView(binding.getRoot());
    }
}
