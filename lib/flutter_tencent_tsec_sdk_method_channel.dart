import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'flutter_tencent_tsec_sdk_platform_interface.dart';

/// An implementation of [FlutterTencentTsecSdkPlatform] that uses method channels.
class MethodChannelFlutterTencentTsecSdk extends FlutterTencentTsecSdkPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_tencent_tsec_sdk');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
