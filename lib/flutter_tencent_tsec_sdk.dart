
import 'flutter_tencent_tsec_sdk_platform_interface.dart';

class FlutterTencentTsecSdk {
  Future<String?> getPlatformVersion() {
    return FlutterTencentTsecSdkPlatform.instance.getPlatformVersion();
  }
}
