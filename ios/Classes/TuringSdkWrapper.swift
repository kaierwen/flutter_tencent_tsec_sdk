import Foundation
import os.log

/// SDK Wrapper for iOS
/// - Parameters:
///   - enableLog: 是否开启日志
class TuringSdkWrapper {
    private let enableLog: Bool
    private var isInit: Bool = false
    private let tag = "TuringSdkWrapper"
    
    // 用于在后台线程执行 SDK 调用的队列
    private let queue = DispatchQueue(label: "com.tencent.tsec.sdk", qos: .utility)
    
    init(enableLog: Bool = false) {
        self.enableLog = enableLog
    }
    
    private func log(_ message: String) {
        if enableLog {
            // 使用 print 输出日志，简单可靠
            print("[\(tag)] \(message)")
        }
    }
    
    /// 获取 SDK 版本信息
    /// - Returns: SDK 版本字符串
    func getPlatformVersion() -> String {
        guard let info = TuringSdkWrapperOC.getSDKInformation() as? [String: Any],
              let version = info["version"] as? String else {
            return "iOS SDK Version - 未知"
        }
        return version
    }
    
    /// 初始化 SDK
    /// - Parameter channel: 渠道号
    /// - Returns: 初始化是否成功
    func initialize(channel: Int) -> Bool {
        return queue.sync {
            // 设置渠道号
            TuringSdkWrapperOC.setCustomChannelID(Int32(channel))
            
            // 启动风险检测服务
            guard let service = TuringSdkWrapperOC.getStandardService() else {
                log("SDK 初始化失败: 无法获取标准服务")
                isInit = false
                return false
            }
            
            TuringSdkWrapperOC.startRiskDetecting(service, withUserID: nil, withPostRule: nil)
            
            log("SDK 初始化完成，渠道号: \(channel)")
            isInit = true
            return true
        }
    }
    
    /// 获取设备 Token，在后台线程中执行
    /// - Returns: 设备 Token 字符串，如果失败返回 "errorCode: <错误码>" 或空字符串
    func getDeviceToken() -> String {
        if !isInit {
            log("SDK 未初始化，无法获取设备 Token")
            return ""
        }
        
        // 使用信号量等待异步操作完成
        let semaphore = DispatchSemaphore(value: 0)
        var tokenResult: String = ""
        var errorResult: Error?
        
        queue.async {
            guard let service = TuringSdkWrapperOC.getStandardService() else {
                self.log("获取设备 Token 失败: SDK 服务不可用")
                tokenResult = ""
                semaphore.signal()
                return
            }
            
            // 调用获取风险消息接口（设备指纹）
            TuringSdkWrapperOC.fetchUniversalRiskMessage(
                service,
                withExtractAPIChecking: nil,
                usingCachedMessage: false,
                includesOutdatedMessage: false,
                withCompletionHandler: { (message, error) in
                    if let error = error {
                        self.log("获取设备 Token 失败: \(error.localizedDescription)")
                        errorResult = error
                        tokenResult = "errorCode: \((error as NSError).code)"
                    } else if let message = message, !message.isEmpty {
                        self.log("获取设备 Token 成功: \(message)")
                        tokenResult = message
                    } else {
                        self.log("获取设备 Token 失败: 返回消息为空")
                        tokenResult = ""
                    }
                    semaphore.signal()
                }
            )
        }
        
        // 等待异步操作完成，最多等待 30 秒
        _ = semaphore.wait(timeout: .now() + 30)
        
        return tokenResult
    }
    
    /// 释放资源
    func release() {
        queue.sync {
            if let service = TuringSdkWrapperOC.getStandardService() {
                TuringSdkWrapperOC.stopRiskDetecting(service)
            }
            log("SDK Wrapper 资源已释放")
        }
    }
}
