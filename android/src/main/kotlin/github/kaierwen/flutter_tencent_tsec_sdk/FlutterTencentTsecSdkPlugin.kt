package github.kaierwen.flutter_tencent_tsec_sdk

import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result

/** FlutterTencentTsecSdkPlugin */
class FlutterTencentTsecSdkPlugin :
    FlutterPlugin,
    MethodCallHandler {
    // The MethodChannel that will the communication between Flutter and native Android
    //
    // This local reference serves to register the plugin with the Flutter Engine and unregister it
    // when the Flutter Engine is detached from the Activity
    private lateinit var channel: MethodChannel

    private lateinit var sdkWrapper: TuringSdkWrapper

    override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
        channel = MethodChannel(flutterPluginBinding.binaryMessenger, "flutter_tencent_tsec_sdk")
        channel.setMethodCallHandler(this)
        sdkWrapper = TuringSdkWrapper(flutterPluginBinding.applicationContext)
    }

    override fun onMethodCall(
        call: MethodCall,
        result: Result
    ) {
        // 处理来自Dart的调用
    when (call.method) {
        "getPlatformVersion" -> {
          val version = sdkWrapper.getPlatformVersion()
          result.success(version)
        }
        "initialize" -> {
          val channel = call.argument<Int>("channel") ?: 0
          val success = sdkWrapper.initialize(channel)
          result.success(success)
        }
        "getDeviceToken" -> {
          val deviceToken = sdkWrapper.getDeviceToken()
          result.success(deviceToken)
        }
        else -> {
          result.notImplemented()
        }
      }
    }

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
        channel.setMethodCallHandler(null)
    }
}
