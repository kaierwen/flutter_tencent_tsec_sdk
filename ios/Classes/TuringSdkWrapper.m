#import <Foundation/Foundation.h>
#import "TuringShield.h"

// Objective-C 包装类，用于在 Swift 中访问 TuringShield SDK
@interface TuringSdkWrapperOC : NSObject
+ (NSDictionary *)getSDKInformation;
+ (void)setCustomChannelID:(int32_t)channelID;
+ (TuringShield *)getStandardService;
+ (void)startRiskDetecting:(TuringShield *)service withUserID:(NSString *)userID withPostRule:(id)rule;
+ (void)stopRiskDetecting:(TuringShield *)service;
+ (void)fetchUniversalRiskMessage:(TuringShield *)service
            withExtractAPIChecking:(NSArray<NSString *> *)extractAPIChecking
                 usingCachedMessage:(BOOL)shouldUseCachedMessage
            includesOutdatedMessage:(BOOL)includesOutdatedMessage
              withCompletionHandler:(void (^)(NSString *message, NSError *error))completionHandler;
@end

@implementation TuringSdkWrapperOC

+ (NSDictionary *)getSDKInformation {
    return [TuringShield information];
}

+ (void)setCustomChannelID:(int32_t)channelID {
    TuringShield.customChannelID = channelID;
}

+ (TuringShield *)getStandardService {
    return [TuringShield standardService];
}

+ (void)startRiskDetecting:(TuringShield *)service withUserID:(NSString *)userID withPostRule:(id)rule {
    [service startRiskDetectingWithUserID:userID withPostRule:rule];
}

+ (void)stopRiskDetecting:(TuringShield *)service {
    [service stopRiskDetecting];
}

+ (void)fetchUniversalRiskMessage:(TuringShield *)service
            withExtractAPIChecking:(NSArray<NSString *> *)extractAPIChecking
                 usingCachedMessage:(BOOL)shouldUseCachedMessage
            includesOutdatedMessage:(BOOL)includesOutdatedMessage
              withCompletionHandler:(void (^)(NSString *message, NSError *error))completionHandler {
    [service fetchUniversalRiskMessageWithExtractAPIChecking:extractAPIChecking
                                        usingCachedMessage:shouldUseCachedMessage
                                   includesOutdatedMessage:includesOutdatedMessage
                                     withCompletionHandler:completionHandler];
}

@end
