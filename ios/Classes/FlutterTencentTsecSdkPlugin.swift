import Flutter
import UIKit

public class FlutterTencentTsecSdkPlugin: NSObject, FlutterPlugin {
  private var sdkWrapper: TuringSdkWrapper?
  
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "flutter_tencent_tsec_sdk", binaryMessenger: registrar.messenger())
    let instance = FlutterTencentTsecSdkPlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    switch call.method {
    case "getPlatformVersion":
      // 如果 SDK 已初始化，使用 SDK 的版本信息，否则返回系统版本
      if let wrapper = sdkWrapper {
        result(wrapper.getPlatformVersion())
      } else {
        result("iOS " + UIDevice.current.systemVersion)
      }
      
    case "initialize":
      guard let args = call.arguments as? [String: Any] else {
        result(FlutterError(code: "INVALID_ARGUMENT", message: "Invalid arguments", details: nil))
        return
      }
      
      let channel = args["channel"] as? Int ?? 0
      let enableLog = args["enableLog"] as? Bool ?? false
      
      // 如果已经初始化过，先释放旧的实例
      sdkWrapper?.release()
      
      // 创建新的 SDK Wrapper 实例，传入 enableLog 参数
      sdkWrapper = TuringSdkWrapper(enableLog: enableLog)
      
      let success = sdkWrapper!.initialize(channel: channel)
      result(success)
      
    case "getDeviceToken":
      guard let wrapper = sdkWrapper else {
        result(FlutterError(
          code: "NOT_INITIALIZED",
          message: "SDK is not initialized. Call initialize() first.",
          details: nil
        ))
        return
      }
      
      let deviceToken = wrapper.getDeviceToken()
      result(deviceToken)
      
    default:
      result(FlutterMethodNotImplemented)
    }
  }
  
  // 当插件从引擎分离时调用
  public func detachFromEngine(for registrar: FlutterPluginRegistrar) {
    sdkWrapper?.release()
    sdkWrapper = nil
  }
}
