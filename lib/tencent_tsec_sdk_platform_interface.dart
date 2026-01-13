import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'tencent_tsec_sdk_method_channel.dart';

abstract class TencentTsecSdkPlatform extends PlatformInterface {
  /// Constructs a FlutterTencentTsecSdkPlatform.
  TencentTsecSdkPlatform() : super(token: _token);

  static final Object _token = Object();

  static TencentTsecSdkPlatform _instance =
      MethodChannelFlutterTencentTsecSdk();

  /// The default instance of [TencentTsecSdkPlatform] to use.
  ///
  /// Defaults to [MethodChannelFlutterTencentTsecSdk].
  static TencentTsecSdkPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [TencentTsecSdkPlatform] when
  /// they register themselves.
  static set instance(TencentTsecSdkPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }

  Future<bool> initialize({required int channel, bool enableLog = false}) {
    throw UnimplementedError('initialize() has not been implemented.');
  }

  Future<String?> getDeviceToken() {
    throw UnimplementedError('getDeviceToken() has not been implemented.');
  }
}
