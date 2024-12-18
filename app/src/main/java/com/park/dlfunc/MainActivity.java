package com.park.dlfunc;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;

import androidx.annotation.Nullable;

import com.park.dlfunc.databinding.ActivityMainBinding;

public class MainActivity extends Activity {

    private ActivityMainBinding binding;

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
        setContentView(binding.getRoot());
    }
}
