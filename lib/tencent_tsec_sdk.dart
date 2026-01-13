import 'tencent_tsec_sdk_platform_interface.dart';

/// 腾讯天御设备安全SDK
/// [文档](https://cloud.tencent.com/document/product/1628)
class TencentTsecSdk {
  /// 获取SDK版本号
  /// @return SDK版本号字符串, 例如："v2.92.3 (2121586C4F8ED095, tianyu, 6171e17, rs, tmfshark, compiled 2025_12_12_17_12_11) [url(https://tdid.m.qq.com/tmf);c(1)]"
  Future<String?> getPlatformVersion() {
    return TencentTsecSdkPlatform.instance.getPlatformVersion();
  }

  /// 初始化SDK
  /// @param channel 渠道号, 参考[快速入门 - 步骤5：生成 SDK_channel](https://cloud.tencent.com/document/product/1628/79610#cee40935-2ef8-4500-bb4e-f6c0a5742c34)
  /// @param enableLog 是否开启日志, 默认为 false
  /// @return 初始化是否成功
  Future<bool> initialize({required int channel, bool enableLog = false}) {
    return TencentTsecSdkPlatform.instance.initialize(
      channel: channel,
      enableLog: enableLog,
    );
  }

  /// 获取设备Token
  /// @return 设备Token 字符串, 如果获取失败, 返回 "errorCode: <错误码>"
  Future<String?> getDeviceToken() {
    return TencentTsecSdkPlatform.instance.getDeviceToken();
  }
}
