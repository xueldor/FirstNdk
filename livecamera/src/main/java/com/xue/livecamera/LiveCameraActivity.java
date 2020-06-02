package com.xue.livecamera;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.PixelFormat;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.os.Bundle;
import android.view.TextureView;
import android.widget.ImageView;

import java.io.IOException;
import java.util.List;

public class LiveCameraActivity extends Activity implements TextureView.SurfaceTextureListener, Camera.PreviewCallback {

    static {
        System.loadLibrary("livecamera");
    }

    private Camera mCamera;
    private TextureView mTextureView;
    private byte[] mVideoSource;
    private ImageView mImageViewR, mImageViewG, mImageViewB;
    private Bitmap mImageR, mImageG, mImageB;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        System.out.println("onCreate livecamera");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_livecamera);
        mTextureView = (TextureView) findViewById(R.id.preview);
        mImageViewR = ((ImageView)findViewById(R.id.imageViewR));
        mImageViewG = ((ImageView)findViewById(R.id.imageViewG));
        mImageViewB = ((ImageView)findViewById(R.id.imageViewB));
        mTextureView.setSurfaceTextureListener(this);
    }


    SurfaceTexture tmpsurface;
    int tmpwidth;
    int tmpheight;
    /**
     * 开始onSurfaceTextureAvailable不回调的原因：使用AppCompatActivity，但是theme使用了android:style。统一即可
     * @param surface
     * @param width
     * @param height
     */
    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface,int width,int height) {
        System.out.println("onSurfaceTextureAvailable");
        if(checkSelfPermission("android.permission.CAMERA") == PackageManager.PERMISSION_GRANTED) {
            mCamera = Camera.open();
            try {
                mCamera.setPreviewTexture(surface);
                mCamera.setPreviewCallbackWithBuffer(this);
                mCamera.setDisplayOrientation(0);
                Camera.Size size = findBestResolution(width, height);

                PixelFormat pixelFormat = new PixelFormat();
                PixelFormat.getPixelFormatInfo(mCamera.getParameters().getPreviewFormat(), pixelFormat);
                int sourceSize = size.width * size.height * pixelFormat.bitsPerPixel / 8;

                Camera.Parameters parameters = mCamera.getParameters();
                parameters.setPreviewSize(size.width, size.height);
                parameters.setPreviewFormat(PixelFormat.YCbCr_420_SP);
                mCamera.setParameters(parameters);

                mVideoSource = new byte[sourceSize];
                mImageR = Bitmap.createBitmap(size.width, size.height,
                        Bitmap.Config.ARGB_8888);
                mImageG = Bitmap.createBitmap(size.width, size.height,
                        Bitmap.Config.ARGB_8888);
                mImageB = Bitmap.createBitmap(size.width, size.height,
                        Bitmap.Config.ARGB_8888);
                mImageViewR.setImageBitmap(mImageR);
                mImageViewG.setImageBitmap(mImageG);
                mImageViewB.setImageBitmap(mImageB);

                mCamera.addCallbackBuffer(mVideoSource);
                mCamera.startPreview();

            } catch (IOException e) {
                mCamera.release();
                mCamera = null;
                throw new IllegalStateException();
            }
        }else {
            requestPermissions(new String[]{"android.permission.CAMERA"},1);
            tmpsurface = surface;
            tmpwidth =width;
            tmpheight = height;
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if(requestCode == 1){
            if(permissions != null && permissions.length > 0 && permissions[0].equals("android.permission.CAMERA")){
                onSurfaceTextureAvailable(tmpsurface,tmpwidth,tmpheight);
            }
        }
    }

    private Camera.Size findBestResolution(int pWidth, int pHeight) {
        List<Camera.Size> sizes = mCamera.getParameters().getSupportedPreviewSizes();
        Camera.Size selectedSize = mCamera.new Size(0, 0);
        for (Camera.Size size : sizes) {
            if ((size.width <= pWidth)
                    && (size.height <= pHeight)
                    && (size.width >= selectedSize.width)
                    && (size.height >= selectedSize.height)) {
                selectedSize = size;
            }
        }
        if ((selectedSize.width == 0) || (selectedSize.height == 0)) {
            selectedSize = sizes.get(0);
        }
        return selectedSize;
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {

    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        if (mCamera != null) {
            mCamera.stopPreview();
            mCamera.release();
            mCamera = null;
            mVideoSource = null;
            mImageR.recycle(); mImageR = null;
            mImageG.recycle(); mImageG = null;
            mImageB.recycle(); mImageB = null;
        }
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {

    }

    @Override
    public void onPreviewFrame(byte[] data, Camera camera) {
        if (mCamera != null) {
            decode(mImageR, data, 0xFFFF0000);
            decode(mImageG, data, 0xFF00FF00);
            decode(mImageB, data, 0xFF0000FF);
            mImageViewR.invalidate();
            mImageViewG.invalidate();
            mImageViewB.invalidate();

            mCamera.addCallbackBuffer(mVideoSource);
        }
    }

    /**
     * YUV to RGB
     * @param pTarget
     * @param pSource
     * @param pFilter
     */
    public native void decode(Bitmap pTarget, byte[] pSource,int pFilter);
}
