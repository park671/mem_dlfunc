package com.park.dlfunc;

import android.content.Context;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class AssetUtils {

    private static final String TAG = "AssetUtils";

    public static String copyAssetToFilesDir(Context context, String assetFileName, String outputDirName) {
        File outputDir = (outputDirName != null) ?
                new File(context.getFilesDir(), outputDirName) :
                context.getFilesDir();
        if (!outputDir.exists()) {
            outputDir.mkdirs();
        }
        File outputFile = new File(outputDir, assetFileName);
        try (InputStream inputStream = context.getAssets().open(assetFileName);
             FileOutputStream outputStream = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[1024];
            int length;
            while ((length = inputStream.read(buffer)) > 0) {
                outputStream.write(buffer, 0, length);
            }
            outputStream.flush();
            return outputFile.getAbsolutePath();
        } catch (IOException e) {
            Log.e(TAG, "", e);
            return null;
        }
    }

    public static boolean isFileAlreadyCopied(Context context, String assetFileName, String outputDirName) {
        File outputDir = (outputDirName != null) ?
                new File(context.getFilesDir(), outputDirName) :
                context.getFilesDir();
        File outputFile = new File(outputDir, assetFileName);
        return outputFile.exists();
    }
}

