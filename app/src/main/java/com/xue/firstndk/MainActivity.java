package com.xue.firstndk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MotionEvent;

import java.io.EOFException;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        System.out.println(JniTest.getString());

        JniTest test = new JniTest();
        test.printHello();
        test.printStr("test print in cpp");
        System.out.println(test.reverseBoolean(true));
        System.out.println(test.toUpperChar('a'));
        System.out.println(test.incShort((short)3));
        System.out.println(test.createIntArr(5));
        System.out.println(test.incLong(45));
        System.out.println(test.getFloat(3.2F));
        System.out.println(test.getDouble(5.54));
        System.out.println(test.charsToString(new char[]{'a','b','c'}));

        System.out.println("-------test jni2test");
        Jni2Test jni2Test = new Jni2Test();
        jni2Test.raiseSalary(1);
        System.out.println("raise salary " + jni2Test.getSalary());
        jni2Test.raiseSalary(1);
        System.out.println("raise salary " + jni2Test.getSalary());

        jni2Test.printName();

        System.out.println("test callback");
        jni2Test.doTask();
        System.out.println("new Jni2 Obj " + Jni2Test.createInstance());

        System.out.println("-------test jni3test");
        Jni3Test jni3Test = new Jni3Test();
        try {
            jni3Test.throwEOFExpt();
        } catch (EOFException e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
        try {
            jni3Test.throwEOFExpt2();
        } catch (EOFException e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if(event.getAction() == MotionEvent.ACTION_UP){
            new Jni2Test().doTask();

            Jni3Test jni3Test = new Jni3Test();
            try {
                jni3Test.throwEOFExpt();
            } catch (EOFException e) {
                System.out.println(e);
            }
            try {

                jni3Test.throwEOFExpt2();
            } catch (EOFException e) {
                System.out.println(e.getMessage());
            }

            try {
                jni3Test.checkJavaExpt();
            }catch (Exception e){
                System.out.println("捕获异常" + e.getMessage());
            }
        }
        return true;
    }
}
