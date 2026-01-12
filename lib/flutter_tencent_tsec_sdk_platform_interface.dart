import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'flutter_tencent_tsec_sdk_method_channel.dart';

abstract class FlutterTencentTsecSdkPlatform extends PlatformInterface {
  /// Constructs a FlutterTencentTsecSdkPlatform.
  FlutterTencentTsecSdkPlatform() : super(token: _token);

  static final Object _token = Object();

  static FlutterTencentTsecSdkPlatform _instance = MethodChannelFlutterTencentTsecSdk();

  /// The default instance of [FlutterTencentTsecSdkPlatform] to use.
  ///
  /// Defaults to [MethodChannelFlutterTencentTsecSdk].
  static FlutterTencentTsecSdkPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FlutterTencentTsecSdkPlatform] when
  /// they register themselves.
  static set instance(FlutterTencentTsecSdkPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
