//
//  TuringShield.h
//  TuringShield
//
//  Created by Sensheng Xu on 2019/6/24.
//  Copyright © 2019 Tecent Inc. All rights reserved.
//
//  $$api_level=TS_TURING_SHIELD_OPEN_API_LEVEL$$
//  $$sdk_file_filter=$$
//  $$sdk_function_filter=$$
//
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "TuringServiceDefine.h"

#import "TuringAnalysisRecord.h"
#import "TuringAnalysisPrediction.h"
#import "TuringPostRule.h"
#import "TuringAnalysisTask.h"
#import "TuringAnalysisPolicy.h"
#import "TuringAppContext.h"



#pragma mark - Description / Documentation

/*
!!!: 一、图灵盾服务接口概览
 
 图灵盾SDK可以为你的App提供三大类型的服务：风险预测、身份识别、年龄识别
 */

/*
 !!!: 二、主要接口类介绍
 
 
        TuringShieldService
                  |
                  |          指定分析策略
                  |      +---------- TuringAnalysisPolicy
                  |      v
                  | 创建分析任务
                  v
        TuringAnalysisTask
                  |
                  | 产生记录
                  v
        TuringAnalysisRecord
                  |
                  |          指定上报策略
                  |      +---------- TuringPostRule
                  |      v
                  | 预测结果
                  v
        TuringAnalysisPrediction
 */


/*
 !!!: 三、开始使用图灵盾
 
 使用图灵盾自动采集策略，只需要在合适的位置添加一行代码（例如applicationDidFinishLaunching）即可以启动：
    [[TuringShieldService standardService] startRiskDetectingWithUserID:YOUR_USER_ID];
 
 特别的，如果你需要为特定的使用图灵盾只需要在你的代码中添加数行代码即可。以人机分析为例：
     // 1. 选择一种分析策略（以人机为例）
     TuringAnalysisPolicy *humanPolicy = [TuringAnalysisPolicy humanPolicy];
     // 2. 绑定需要跟踪的p视图（下例是点击button1时触发采集）
     humanPolicy.associatedView = self.button1;
     // 2. 创建一个分析任务
     TuringAnalysisTask *humanTask = [[TuringShieldService standardService] analysisTaskForSceneID:YOUR_SCENE_ID withUserID:YOUR_USER_ID policy:humanPolicy];
     // 3. 在任何合适的时机（例如viewDidLoad）开始任务
     [humanTask startWithPostRule:TuringDefaultAutoPostRule];
     // 4. 在任何正确的时机（例如dealloc）结束任务
     [humanTask stop];
 
 在`TuringAnalysisPolicy`中有更多的分析参数和选项可供你因应不同环境和场景而作出细微调整。
 
 |<-- 为正确显示下面的图表，请拉伸你的代码窗口以确保下面的横线显示在同一行 ----------------------------------------->|

                               +------------------+
                               |                  |
           +------------+------+      Service     +------------------------+        +------------------+
           |            |      |                  |                        |        |                  |
           |            |      +---------+--------+                        |        |  AnalysisPolicy  |
           |            |                |                                 |        |                  |
           |            |                |                                 |        +-------+----------+
           |            |                |                                 |                |
           +            |                +                                 +                |
  [PREDICTION FEATURE]  |       [RECORD MANAGEMENT]               [ANALYSING FEATURE]       v
  -predictForRecord:    |   -managedRecords              -analysisTaskForSceneID:userID:policy:
  -predictForRecords:   |   -managedRecordsForSceneID:                     +
           +            |   -removeRecords:                                |
           |            |                +                        +--------v---------+
  +--------v---------+  |                |                        |                  |
  |                  |  |                |                        |   AnalysisTask   |
  |    Prediction    |  |                |                        |                  |
  |                  |  |                |                        +--------+---------+
  +------------------+  |                |                                 |
                        |                |                                 +
                        |                |                           [TASK OPERATION]
                        |                |                         -start
                        |                |                         -startWithRecordHandler:
                        +                |                         -startWithPostRule: <------+
               [Device FP FEATURE]       |                                 +                  |
              -getDeviceFingerprint      |                                 |                  |
                        +                |                                 |         +--------+--------+
                        |                |                                 |         |                 |
                        |                |                                 |         |     PostRule    |
                        |                |                                 |         |                 |
                        |                |                                 |         +-----------------+
                        |                |                                 |
               +--------v---------+      |                        +--------v---------+
               |                  |      |                        |                  |
               |    Device FP     |      +------------------------>      Record      |
               |                  |                               |                  |
               +------------------+                               +------------------+

 */

#pragma mark - Main
// !!!: 主接口

/**
 图灵盾服务
 主要功能：
 1. 提供预测能力
 2. 提供记录管理的能力
 3. 分析任务的管理能力
 */
@tsclass(TuringShield);

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringShield : NSObject

+ (nullable instancetype)standardService;
- (nonnull instancetype)init NS_UNAVAILABLE;

+ (nonnull NSDictionary *)information;

@end

#pragma mark - Device Risk
// !!!: 设备风险接口

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringShield (DeviceRisk)

- (void)startRiskDetectingWithUserID:(nullable NSString *)userID withPostRule:(nullable TuringPostRule *)rule TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING);

- (void)startHumanServiceWithUserID:(nullable NSString *)userID withPostRule:(nullable TuringPostRule *)rule TS_AVAILABLE_IFS(TS_ENABLES_DATA_SENDING, TS_HUMAN_PROJECT);

- (void)startFingerprintServiceWithUserID:(nullable NSString *)userID withPostRule:(nullable TuringPostRule *)rule TS_AVAILABLE_IFS(TS_ENABLES_DATA_SENDING, TS_ENABLES_FINGERPRINT_FEATURE);

- (void)startRiskDetectingWithUserID:(nullable NSString *)userID withRecordHandler:(nullable TuringAnalysisRecordHandler)recordHandler TS_AVAILABLE_IFS(__TS_NOT(TS_ENABLES_DATA_SENDING), TS_ENABLES_PREDICTION_PROCEEDING);

- (void)stopRiskDetecting TS_AVAILABLE_IF(TS_ENABLES_PREDICTION_PROCEEDING);

- (void)stopFingerprintService TS_AVAILABLE_IFS(TS_ENABLES_DATA_SENDING, TS_ENABLES_FINGERPRINT_FEATURE);

@property (class, nonnull, nonatomic, readonly) TuringAppContext *appContext TS_AVAILABLE_IFS(TS_ENABLES_DATA_SENDING, TS_ENABLES_FINGERPRINT_FEATURE);

+ (void)setupAppContext:(nullable TuringAppContext *)context 
    TS_MSG_DEPRECATED("Use class property `appContext` instead");

- (void)setupAppContext:(nonnull TuringAppContext *)context 
    TS_MSG_DEPRECATED("Use class property `appContext` instead");

#define getFingerprintWithCompletionHandler fetchTuringMessageTicket

- (BOOL)getFingerprintWithCompletionHandler:(nonnull void(^)(TuringDeviceFingerprint *_Nullable fingerprint))handler TS_AVAILABLE_IFS(TS_ENABLES_DATA_SENDING, TS_ENABLES_FINGERPRINT_FEATURE);

#define getOfflineFingerprint                     getCachedTuringMessageTicket
#define getCachedFingerprintIncludingOudatedData  getCachedTuringMessageTicketIncludingOudatedData

- (nullable TuringDeviceFingerprint *)getCachedFingerprintIncludingOudatedData TS_AVAILABLE_IFS(TS_ENABLES_DATA_SENDING, TS_ENABLES_FINGERPRINT_FEATURE);

- (void)fetchRiskMessageUsingCacheWithExtractAPIChecking:(nullable NSArray<NSString *> *)extractAPIChecking 
                                   withCompletionHandler:(nullable void(^)(NSString *_Nullable message, NSError *_Nullable error))completionHandler
    TS_AVAILABLE_IF(TS_ENABLES_RISK_DETECT_FEATURE);

- (void)fetchRiskMessageWithExtractAPIChecking:(nullable NSArray<NSString *> *)extractAPIChecking
                            usingCachedMessage:(BOOL)shouldUseCachedMessage
                         withCompletionHandler:(nullable void(^)(NSString *_Nullable message, NSError *_Nullable error))completionHandler
    TS_AVAILABLE_IF(TS_ENABLES_RISK_DETECT_FEATURE);

- (void)fetchUniversalRiskMessageWithExtractAPIChecking:(nullable NSArray<NSString *> *)extractAPIChecking
                                     usingCachedMessage:(BOOL)shouldUseCachedMessage
                                includesOutdatedMessage:(BOOL)includesOutdatedMessage
                                  withCompletionHandler:(nonnull void (^)(NSString *_Nullable message, NSError *_Nullable error))completionHandler
    TS_AVAILABLE_IF(TS_ENABLES_UNIVERSAL_TOKEN);

- (void)fetchRiskMessageWithExtractAPIChecking:(nullable NSArray<NSString *> *)extractAPIChecking
                            usingCachedMessage:(BOOL)shouldUseCachedMessage
                       includesOutdatedMessage:(BOOL)includesOutdatedMessage
                       alsoRequiringDeviceInfo:(BOOL)includesDeviceInfo
                         withCompletionHandler:(nonnull void(^)(NSString *_Nullable message, NSError *_Nullable error))completionHandler
    TS_AVAILABLE_IF(__TS_AND_3(TS_ENABLES_RISK_DETECT_FEATURE, TS_SIGNING_TOKEN_FEATURE, TS_ENABLES_DEVICE_INFO_ACCESS));

- (void)fetchUniversalRiskMessageWithExtractAPIChecking:(nullable NSArray<NSString *> *)extractAPIChecking
                                     usingCachedMessage:(BOOL)shouldUseCachedMessage
                                includesOutdatedMessage:(BOOL)includesOutdatedMessage
                                alsoRequiringDeviceInfo:(BOOL)includesDeviceInfo
                                  withCompletionHandler:(nonnull void (^)(NSString *_Nullable message, NSError *_Nullable error))completionHandler
    TS_AVAILABLE_IF(__TS_AND_3(TS_ENABLES_UNIVERSAL_TOKEN, TS_SIGNING_TOKEN_FEATURE,  TS_ENABLES_DEVICE_INFO_ACCESS));

- (void)fetchRiskMessageWithExtractAPIChecking:(nullable NSArray<NSString *> *)extractAPIChecking
                         withCompletionHandler:(nullable void(^)(NSString *_Nullable message, NSError *_Nullable error))completionHandler
TS_MSG_DEPRECATED("Use `-fetchRiskMessageUsingCacheWithExtractAPIChecking:withCompletionHandler:`"
                  " or `-fetchRiskMessageWithExtractAPIChecking:usingCachedMessage:withCompletionHandler:` instead");

- (void)startUserInteractionDetecting;
- (void)stopUserUserInteractionDetecting;

- (void)startSimulatedGeoDetecting TS_AVAILABLE_IFS(TS_ENABLES_FAKE_LOCATION_DETECTING, TS_ENABLES_RISK_DETECT_FEATURE);
- (void)stopSimulatedGeoDetecting TS_AVAILABLE_IFS(TS_ENABLES_FAKE_LOCATION_DETECTING, TS_ENABLES_RISK_DETECT_FEATURE);

@end

#pragma mark - Task Management
// !!!: 任务管理

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringShield (TaskManagement)

- (nullable TuringAnalysisTask *)analysisTaskForSceneID:(NSUInteger)sceneID withUserID:(nonnull NSString *)userID policy:(nonnull TuringAnalysisPolicy *)policy;
- (nullable TuringAnalysisTask *)managedAnalysisTaskForSceneID:(NSUInteger)sceneID;

@end

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@protocol TuringShieldServiceTaskDelegate <NSObject>

@optional
- (void)turingShieldService:(nonnull TuringShield *)service task:(nonnull TuringAnalysisTask *)task didReceiveRecord:(nonnull TuringAnalysisRecord *)record;
- (void)turingShieldService:(nonnull TuringShield *)service task:(nullable TuringAnalysisTask *)task didPostRecord:(nonnull TuringAnalysisRecord *)record withPrediction:(nonnull __kindof TuringAnalysisPrediction *)prediction TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING);

@end

#pragma mark - Record Management
// !!!: 记录管理

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringShield (RecordManagement)

- (nullable NSArray<TuringAnalysisRecord *> *)cachedRecords;
- (nullable NSArray<TuringAnalysisRecord *> *)cachedRecordsForSceneID:(NSUInteger)sceneID;
- (void)removeRecords:(nonnull NSArray<TuringAnalysisRecord *> *)records;

- (TuringPostIdentifier)postRecord:(nonnull TuringAnalysisRecord *)record forRule:(nullable TuringPostRule *)rule TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING);
- (TuringPostIdentifier)postRecords:(nonnull NSArray<TuringAnalysisRecord *> *)records forRule:(nullable TuringPostRule *)rule TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING);
- (void)cancelPostForID:(TuringPostIdentifier)postID TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING);

- (void)addDelegate:(nonnull id<TuringShieldServiceTaskDelegate>)delegate;
- (void)removeDelegate:(nonnull id<TuringShieldServiceTaskDelegate>)delegate;

@end

#pragma mark - Token Signature
// !!!: 风险验签接口

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
TS_AVAILABLE_IF(TS_SIGNING_TOKEN_FEATURE)
@interface TuringShield (TokenSignature)

/// 激活验签
/// - Parameter token: 验签票据
/// - Parameter error: 返回的错误信息
/// - Returns 成功时返回YES，否则返回NO
- (BOOL)activateSignatureToken:(nonnull NSString *)token error:(NSError *__autoreleasing _Nullable *_Nullable)error;

/// 请求签名
/// - Parameter data: 被签名的数据块
/// - Parameter error: 返回的错误信息
/// - Returns 成功时返回签名信息，否则返回空
- (nullable NSString *)getSignatureForData:(nonnull NSData *)data error:(NSError *__autoreleasing _Nullable *_Nullable)error;

@end

#pragma mark - Advance
// !!!: 高级接口，一般不建议使用

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringShield (Advance)

@property (nonatomic) BOOL disablesPrivacySensitiveFingerprintData TS_MSG_DEPRECATED("use `-blockPrivacySensitiveData:lowPerformanceData:` instead");

- (void)blockPrivacySensitiveData:(BOOL)privacySensable lowPerformanceData:(BOOL)performanceSensble TS_AVAILABLE_IFS(TS_ENABLES_DATA_SENDING, TS_ENABLES_FINGERPRINT_CONFIG_CONTROL);

@property (class, nonatomic, nullable) NSString *customClientVersion TS_AVAILABLE_IF(TS_ENABLES_CUSTOM_CLIENT_VERSION);
@property (class, nonatomic) int32_t customChannelID TS_AVAILABLE_IF(TS_ENABLES_CUSTOM_CHANNEL_ID);

- (TuringPostIdentifier)postRecords:(nonnull NSArray<TuringAnalysisRecord *> *)records forRule:(nullable TuringPostRule *)rule withCompletionHandler:(nonnull TuringPostResponseHandler)handler TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING);

@property (class, nonatomic) NSTimeInterval requestTimeout TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING);
+ (void)resetDefaultRequestTimeout TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING);

@property (class, nonatomic) BOOL enablesFingerprintConfigFailingSimulation TS_AVAILABLE_IFS(TS_ENABLES_FINGERPRINT_CONFIG_CONTROL, TS_ENABLES_FINGERPRINT_CONFIG_TEST);

@end

TS_AVAILABLE_IF(TS_NETWORKING_TMF_SHARK_SUPPORTS)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringShield (TMFSharkNetworking)

+ (void)setupTMFAppID:(nonnull NSString *)appID forRSAPublicKey:(nonnull NSString *)RSAPublicKey TS_AVAILABLE_IF(__TS_OR(TS_NETWORKING_PRI_TMF_SUPPORTS, TS_NETWORKING_OS_TMF_SUPPORTS));
+ (void)setupTMFHTTPServer:(nonnull NSString *)serverURLString TS_AVAILABLE_IF(__TS_OR(TS_NETWORKING_PRI_TMF_SUPPORTS, TS_NETWORKING_OS_TMF_SUPPORTS));
+ (void)setupTMFHTTPServers:(nonnull NSArray<NSString *> *)serverURLStrings TS_AVAILABLE_IF(__TS_OR(TS_NETWORKING_PRI_TMF_SUPPORTS, TS_NETWORKING_OS_TMF_SUPPORTS));

+ (void)setupTMFHTTPPostCallback:(nullable BOOL(^)(NSMutableURLRequest *_Nonnull request))callback TS_AVAILABLE_IF(__TS_AND(TS_NETWORKING_TMF_SHARK_SUPPORTS, TS_ALLOWS_HTTP_POST_HANDLING));

@end

#define TuringCustomFeatureKey           tsclassname(TuringCustomFeatureKey)
#define TuringCustomFeatureIDFA          tsclassname(TuringCustomFeatureIDFA)
#define TuringCustomFeatureDeviceName    tsclassname(TuringCustomFeatureDeviceName)
#define TuringCustomFeatureDeviceNameMD5 tsclassname(TuringCustomFeatureDeviceNameMD5)

typedef NSString *TuringCustomFeatureKey NS_TYPED_ENUM;

NS_ASSUME_NONNULL_BEGIN
/// 使用自定义的IDFA作为特征数据。
/// @discussion `-insertCustomFeatureForKey:withValue:`。其value须为NSString *类型。
FOUNDATION_EXTERN TuringCustomFeatureKey TuringCustomFeatureIDFA;

/// 使用自定义的设备名称作为特征数据。
/// @discussion `-insertCustomFeatureForKey:withValue:`。其value须为NSString *类型。
FOUNDATION_EXTERN TuringCustomFeatureKey TuringCustomFeatureDeviceName;

/// 使用自定义的设备名称的MD5作为特征数据。
/// @discussion `-insertCustomFeatureForKey:withValue:`。其value须为NSString *类型。
FOUNDATION_EXTERN TuringCustomFeatureKey TuringCustomFeatureDeviceNameMD5;

NS_ASSUME_NONNULL_END

TS_AVAILABLE_IF(TS_ENABLES_FINGERPRINT_FEATURE)
@interface TuringShield (CustomFeatureExtension)


/// 添加一个自定义的特征数据
/// @param key 特征的键值。可用的键值，请参阅`TSTuringCustomFeatureKey`和其枚举值的定义。
/// @param value 特征的值。特征的值类型，请参阅`TSTuringCustomFeatureKey`和其枚举值的定义。
/// @discussion 当value为nil时，将清空该自定义值。
+ (void)setCustomFeatureForKey:(nonnull TuringCustomFeatureKey)key withValue:(nullable id)value;

/// 读取已经设置过的自定义特征数据
/// @param key 特征的键值。可用的键值，请参阅`TSTuringCustomFeatureKey`和其枚举值的定义。
+ (nullable id)customFeatureValueForKey:(nonnull TuringCustomFeatureKey)key;

@end


TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
NSString *_Nullable TuringShieldEnvironmentGetVPNAddress(void);

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
NSString *_Nullable TuringShieldEnvironmentGetProxyAddress(void);

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
BOOL TuringShieldEnvironmentGetJailbrokenStatus(void);

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
TS_AVAILABLE_IF(TS_ENABLES_DEVICE_INFO_ACCESS)
void TuringShieldEnvironmentGetReadyForDeviceInfo(dispatch_block_t _Nonnull whenReady);

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
TS_AVAILABLE_IF(TS_ENABLES_DEVICE_INFO_ACCESS)
NSDictionary<NSNumber *, NSString *> *_Nullable TuringShieldEnvironmentGetDeviceInfo(void);

TS_AVAILABLE_IF(TS_NETWORKING_TMF_SHARK_SUPPORTS)
BOOL TuringShieldPostTMFSharkData(NSInteger commandId, NSData *_Nonnull postingData, void(^_Nonnull resposeHandler)(NSData *_Nullable responsedData, NSError *_Nullable error)) ;


