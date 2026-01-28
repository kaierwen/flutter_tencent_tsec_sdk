#import <Foundation/Foundation.h>

// Objective-C 包装类，用于在 Swift 中访问 TuringShield SDK
@interface TuringSdkWrapperOC : NSObject
+ (NSDictionary *)getSDKInformation;
+ (void)setCustomChannelID:(int32_t)channelID;
+ (id)getStandardService;
+ (void)startRiskDetecting:(id)service withUserID:(NSString *)userID withPostRule:(id)rule;
+ (void)stopRiskDetecting:(id)service;
+ (void)fetchUniversalRiskMessage:(id)service
            withExtractAPIChecking:(NSArray<NSString *> *)extractAPIChecking
                 usingCachedMessage:(BOOL)shouldUseCachedMessage
            includesOutdatedMessage:(BOOL)includesOutdatedMessage
              withCompletionHandler:(void (^)(NSString * _Nullable message, NSError * _Nullable error))completionHandler;
@end
