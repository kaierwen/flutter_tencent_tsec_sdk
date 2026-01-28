//
//  TuringPostRule.h
//  TuringShield
//
//  Created by Sensheng Xu on 2019/8/1.
//  Copyright © 2019 Tecent Inc. All rights reserved.
//
//  $$api_level=TS_TURING_SHIELD_OPEN_API_LEVEL$$
//
//

#import <Foundation/Foundation.h>
#import "TuringServiceDefine.h"



TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING)
typedef enum : NSUInteger {
    TuringPostProtocolWUP TS_AVAILABLE_IF(TS_NETWORKING_WUP_SUPPORTS) = 1,
    TuringPostProtocolShark TS_AVAILABLE_IF(TS_NETWORKING_SHARK_SUPPORTS) = 2,
    TuringPostProtocolTMFSharkTars TS_AVAILABLE_IF(TS_NETWORKING_TMF_SHARK_SUPPORTS) = 3,
    TuringPostProtocolTMFSharkTaf TS_AVAILABLE_IF(TS_NETWORKING_TMF_SHARK_SUPPORTS) = 4,
    TuringPostProtocolTMFSharkSaaS TS_AVAILABLE_IF(TS_NETWORKING_SAAS_TMF_SUPPORTS) = 5,
} TuringPostProtocol;

@tsclass(TuringPostRule);
TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringPostRule : NSObject

+ (nonnull instancetype)postRule;
- (nonnull instancetype)init NS_UNAVAILABLE;

@property (nonatomic, assign) BOOL usesDebugServer;
@property (nonatomic, assign) TuringPostProtocol protocol;


@property (nonatomic, class) TuringPostProtocol defaultProtocol;
@property (nonatomic, class) BOOL usesDebugServerAsDefault;

@end

#define TuringDefaultAutoPostRule ([TuringAutoPostRule autoPostRule])


@tsclass(TuringAutoPostRule);
TS_AVAILABLE_IF(TS_ENABLES_DATA_SENDING)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAutoPostRule : TuringPostRule

+ (nonnull instancetype)autoPostRule;
+ (nonnull instancetype)postRule NS_UNAVAILABLE;

@property (nonatomic, assign) BOOL postsThroughWiFiOnly;
@property (nonatomic, assign) NSUInteger maximumPostsThroughCellulerPerDay;
@property (nonatomic, assign) NSUInteger maximumPostsThroughCellulerPerHour;

@property (nonatomic, assign) BOOL cachesRecordInCaseOfReachedMaximumPostsLimitation;
@property (nonatomic, assign) BOOL cachesRecordInCaseOfFailedPosting;
@property (nonatomic, assign) BOOL alsoPostsCachedRecordsIfPossible; // TODO: Havn't applied yet

@end
