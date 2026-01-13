import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'tencent_tsec_sdk_platform_interface.dart';

/// An implementation of [TencentTsecSdkPlatform] that uses method channels.
class MethodChannelFlutterTencentTsecSdk extends TencentTsecSdkPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_tencent_tsec_sdk');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>(
      'getPlatformVersion',
    );
    return version;
  }

  @override
  Future<bool> initialize({required int channel}) async {
    final result = await methodChannel.invokeMethod<bool>(
      'initialize',
      <String, dynamic>{'channel': channel},
    );
    return result ?? false;
  }

  @override
  Future<String?> getDeviceToken() async {
    final result = await methodChannel.invokeMethod<String>('getDeviceToken');
    return result;
  }
}
