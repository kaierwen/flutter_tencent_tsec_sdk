-keepattributes JavascriptInterface
-keepattributes *Annotation*

# native方法
-keep class com.**.TNative$aa { public *; }
-keep class com.**.TNative$aa$bb { public *; }
-keep class com.**.TNative$bb { *; }
-keep class com.**.TNative$bb$I { *; }

# JavascriptInterface
-keep class com.**.TuringWebInterface {
    @android.webkit.JavascriptInterface <methods>;
}
# Automatically generated file. DO NOT MODIFY
-keepclassmembers public final class com.tencent.turingfd.sdk.tianyu.** {
    public <init>(...);
}
