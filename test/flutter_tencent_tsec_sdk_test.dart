import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_tencent_tsec_sdk/flutter_tencent_tsec_sdk.dart';
import 'package:flutter_tencent_tsec_sdk/flutter_tencent_tsec_sdk_platform_interface.dart';
import 'package:flutter_tencent_tsec_sdk/flutter_tencent_tsec_sdk_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockFlutterTencentTsecSdkPlatform
    with MockPlatformInterfaceMixin
    implements FlutterTencentTsecSdkPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final FlutterTencentTsecSdkPlatform initialPlatform = FlutterTencentTsecSdkPlatform.instance;

  test('$MethodChannelFlutterTencentTsecSdk is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelFlutterTencentTsecSdk>());
  });

  test('getPlatformVersion', () async {
    FlutterTencentTsecSdk flutterTencentTsecSdkPlugin = FlutterTencentTsecSdk();
    MockFlutterTencentTsecSdkPlatform fakePlatform = MockFlutterTencentTsecSdkPlatform();
    FlutterTencentTsecSdkPlatform.instance = fakePlatform;

    expect(await flutterTencentTsecSdkPlugin.getPlatformVersion(), '42');
  });
}
