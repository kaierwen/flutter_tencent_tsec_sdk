# flutter_tencent_tsec_sdk
腾讯云T-Sec设备安全SDK的Flutter插件，仅支持安卓和iOS（iOS未实现）

文档：https://cloud.tencent.com/document/product/1628

## 使用

### 1. 添加依赖
```dart
dependencies:
  flutter_tencent_tsec_sdk: ^0.0.1
```

### 2. 初始化SDK
需要传入【渠道号】, 参考[快速入门 - 步骤5：生成 SDK_channel](https://cloud.tencent.com/document/product/1628/79610#cee40935-2ef8-4500-bb4e-f6c0a5742c34)
```dart
final tsecSdk = TencentTsecSdk();
final bool success = await tsecSdk.initialize(channel: [渠道号]);
if (success) {
  final version = await tsecSdk.getPlatformVersion();
  debugPrint(version);
} else {
  debugPrint('初始化失败');
}
```

### 3. 获取设备Token
返回值：
- 成功：设备Token字符串
- 失败："errorCode: <错误码>"
```dart
final token = await tsecSdk.getDeviceToken();
if (token != null && token.isNotEmpty) {
  if (token.startsWith('errorCode:')) {
    setState(() {
      _errorMessage = '获取设备Token失败: $token';
      _deviceToken = token;
    });
  } else {
    setState(() {
      _deviceToken = token;
      _errorMessage = null;
    });
  }
} else {
  setState(() {
    _errorMessage = '获取设备Token失败';
    _deviceToken = null;
  });
}
```

### 4. 安卓添加混淆
参考[混淆配置](/example/android/app/proguard-rules.pro)
```
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

```