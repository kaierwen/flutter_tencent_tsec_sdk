package github.kaierwen.flutter_tencent_tsec_sdk

import android.content.Context
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

    private var sdkWrapper: TuringSdkWrapper? = null
    private var applicationContext: Context? = null

    override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
        channel = MethodChannel(flutterPluginBinding.binaryMessenger, "flutter_tencent_tsec_sdk")
        channel.setMethodCallHandler(this)
        applicationContext = flutterPluginBinding.applicationContext
    }

    override fun onMethodCall(
        call: MethodCall,
        result: Result
    ) {
        // 处理来自Dart的调用
    when (call.method) {
        "getPlatformVersion" -> {
          val version = sdkWrapper?.getPlatformVersion() ?: ""
          result.success(version)
        }
        "initialize" -> {
          val channel = call.argument<Int>("channel") ?: 0
          val enableLog = call.argument<Boolean>("enableLog") ?: false
          val context = applicationContext
          if (context == null) {
            result.error("INIT_ERROR", "Application context is not available", null)
            return
          }
          // 如果已经初始化过，先释放旧的实例
          sdkWrapper?.release()
          // 创建新的 SDK Wrapper 实例，传入 enableLog 参数
          sdkWrapper = TuringSdkWrapper(context, enableLog)
          val success = sdkWrapper!!.initialize(channel)
          result.success(success)
        }
        "getDeviceToken" -> {
          if (sdkWrapper == null) {
            result.error("NOT_INITIALIZED", "SDK is not initialized. Call initialize() first.", null)
            return
          }
          val deviceToken = sdkWrapper!!.getDeviceToken()
          result.success(deviceToken)
        }
        else -> {
          result.notImplemented()
        }
      }
    }

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
        channel.setMethodCallHandler(null)
        sdkWrapper?.release()
        sdkWrapper = null
        applicationContext = null
    }
}
