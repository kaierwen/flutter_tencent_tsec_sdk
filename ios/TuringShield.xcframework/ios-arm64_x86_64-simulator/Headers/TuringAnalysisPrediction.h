//
//  TuringAnalysisPrediction.h
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


#pragma mark -
@tsclass(TuringAnalysisPrediction);

TS_AVAILABLE_IF(TS_ENABLES_PREDICTION_PROCEEDING)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisPrediction : NSObject <NSCopying>

- (nonnull instancetype)init NS_UNAVAILABLE;

@property (nonatomic, assign, readonly)   BOOL advice;
@property (nonatomic, assign, readonly)   float posibility;
@property (nonatomic, nullable, readonly) NSError *error;
@property (nonatomic, nonnull, readonly)  NSMutableDictionary *externals;

@end

#pragma mark -
@tsclass(TuringAnalysisGamePrediction);

TS_AVAILABLE_IFS(TS_ENABLES_PREDICTION_PROCEEDING, TS_AGE_PROJECT)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisGamePrediction : TuringAnalysisPrediction

@property (nonatomic, assign, getter=advice, readonly) BOOL isTeeny;
@property (nonatomic, assign, getter=posibility, readonly) float teenyPosibility;

@end

@tsclass(TuringAnalysisOwnerPrediction);
TS_AVAILABLE_IFS(TS_ENABLES_PREDICTION_PROCEEDING, TS_OWNER_PROJECT)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisOwnerPrediction : TuringAnalysisPrediction

@property (nonatomic, assign, getter=advice, readonly) BOOL isOwner;
@property (nonatomic, assign, getter=posibility, readonly) float ownerPosibility;

@end

#pragma mark -
@tsclass(TuringAnalysisHumanPrediction);

TS_AVAILABLE_IFS(TS_ENABLES_PREDICTION_PROCEEDING, TS_HUMAN_PROJECT)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisHumanPrediction : TuringAnalysisPrediction

- (BOOL)advice NS_UNAVAILABLE;

@property (nonatomic, assign, getter=posibility, readonly) float machinePosibility;

@end


#pragma mark -

typedef enum : NSInteger {
    TuringDeviceFingerprintConditionNone        = -1,
    TuringDeviceFingerprintConditionNew         = 0,
    TuringDeviceFingerprintConditionRecall      = 1,
    TuringDeviceFingerprintConditionUpdate      = 2,
    TuringDeviceFingerprintConditionDelete      = 3,
    TuringDeviceFingerprintConditionQuery       = 4,
    TuringDeviceFingerprintConditionEmulator    = 5,
    TuringDeviceFingerprintConditionOnLineCache = 6,
    TuringDeviceFingerprintConditionOutdated    = 254,
    TuringDeviceFingerprintConditionCache       = 255,
} TuringDeviceFingerprintCondition;

//@tsclass(TuringDeviceFingerprint);
@tsswiftclass(TuringDeviceFingerprint, TuringMessageTicket);

TS_AVAILABLE_IFS(TS_ENABLES_PREDICTION_PROCEEDING, TS_ENABLES_FINGERPRINT_FEATURE)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringDeviceFingerprint : TuringAnalysisPrediction <NSCopying, NSSecureCoding>

- (BOOL)advice NS_UNAVAILABLE;

@property (nonatomic, readonly, nullable) NSString *ticket;
@property (nonatomic, readonly, getter=posibility) float confidence;
@property (nonatomic, readonly, assign) NSInteger condition;

@property (nonatomic, nullable, readonly) NSString *analysisTicket TS_AVAILABLE_IF(__TS_OR(TS_ACT_AS_TAID_ADVERTISER, TS_ACT_AS_TAID_PROVIDER));

@end

#pragma mark -

typedef enum : NSInteger {
    TuringDeviceRiskConditionNone        = -1,
    TuringDeviceRiskConditionUpdated     = 253,
    TuringDeviceRiskConditionOutdated    = 254,
    TuringDeviceRiskConditionCache       = 255,
} TuringDeviceRiskCondition;

//@tsclass(TuringDeviceRisk);
@tsswiftclass(TuringDeviceRisk, TuringRiskToken);

TS_AVAILABLE_IF(TS_ENABLES_RISK_DETECT_FEATURE)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringDeviceRisk : TuringAnalysisPrediction <NSCopying, NSSecureCoding>

- (BOOL)advice NS_UNAVAILABLE;
- (float)posibility NS_UNAVAILABLE;

@property (nonatomic, readonly, nullable) NSString *message;
@property (nonatomic, readonly, nullable) NSDate *outdateDate;
@property (nonatomic, readonly, assign)   NSInteger condition;
@property (nonatomic, readonly, nullable) NSString *signKey TS_AVAILABLE_IF(TS_SIGNING_TOKEN_FEATURE);

@end

#pragma mark -

TS_AVAILABLE_IF(TS_ENABLES_PREDICTION_PROCEEDING)
@interface NSError (tsclassname(TuringErrorType))

#define isValuableForReposting tsmethodname(isValuableForReposting)
- (BOOL)isValuableForReposting;

#define isAlreadyPostToServer  tsmethodname(isAlreadyPostToServer)
- (BOOL)isAlreadyPostToServer;

@end
