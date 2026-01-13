package github.kaierwen.flutter_tencent_tsec_sdk

import android.content.Context
import android.util.Log
import com.tencent.turingfd.sdk.tianyu.TuringRiskService
import com.tencent.turingfd.sdk.tianyu.TuringSDK
import java.util.concurrent.Callable
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors
import java.util.concurrent.Future

/**
 * SDK Wrapper
 * @param context
 * @param enableLog 是否开启日志
 */
class TuringSdkWrapper(private val context: Context, private val enableLog: Boolean = true) {
    private val TAG = "TuringSdkWrapper"
    private var isInit = false

    // 创建单线程执行器，用于在后台线程执行 SDK 调用
    private val executor: ExecutorService = Executors.newSingleThreadExecutor()

    private fun log(message: String) {
        if (enableLog) {
            Log.d(TAG, message)
        }
    }

    fun getPlatformVersion(): String = TuringSDK.getVersionInfo()

    // 初始化SDK
    fun initialize(channel: Int): Boolean {
        return try {
            // 这里是模拟调用，你需要根据SDK的真实API进行替换
            val ret = TuringSDK.createConf(context) {
                true
            }
                .channel(channel)
                .enableClickRisk()
                .enableWiFiRisk()
                .build()
                .init()
            log("SDK 初始化完成，返回码: $ret")
            isInit = true
            true
        } catch (e: Exception) {
            log("SDK 初始化失败: $e")
            isInit = false
            false
        }
    }

    /**
     * 获取设备 Token，在子线程中执行
     * @return 设备 Token 字符串
     */
    fun getDeviceToken(): String {
        if (!isInit) {
            log("SDK 未初始化，无法获取设备 Token")
            return ""
        }

        try {
            // 在子线程中执行 SDK 调用
            val future: Future<String> = executor.submit(Callable {
                try {
                    val resp = TuringRiskService.reqRiskDetectV3(false)
                    // 根据实际返回类型处理响应
                    // 假设 resp 有 toString() 或类似方法返回 token
                    if (resp.errorCode == 0L) {
                        val token = resp.deviceToken
                        log("获取设备 Token 成功: $token")
                        token
                    } else {
                        log("获取设备 Token 失败: ${resp.errorCode}")
                        "errorCode: ${resp.errorCode}"
                    }
                } catch (e: Exception) {
                    log("获取设备 Token 失败: ${e.message}")
                    ""
                }
            })
            // 等待子线程执行完成并返回结果
            return future.get()
        } catch (e: Exception) {
            log("执行获取设备 Token 任务失败: ${e.message}")
            return ""
        }
    }

    /**
     * 释放资源，关闭线程池
     */
    fun release() {
        executor.shutdown()
    }
}