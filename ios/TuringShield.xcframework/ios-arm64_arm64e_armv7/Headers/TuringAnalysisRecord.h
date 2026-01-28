//
//  TuringAnalysisRecord.h
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
@tsclass(TuringAnalysisRecord);

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisRecord : NSObject

- (nonnull instancetype)init NS_UNAVAILABLE;

@property (nonatomic, assign, readonly) NSUInteger sceneID;
@property (nonatomic, nullable, copy, readonly) NSString *userID;

#if TS_ENABLES_PREDICTION_PROCEEDING && !TS_ENABLES_DATA_SENDING
- (nullable NSData *)requestDataForSharkSashimi;
#endif

- (nonnull NSString *)context;

@end

#pragma mark -
@tsclass(TuringAnalysisGameRecord);

TS_AVAILABLE_IF(TS_AGE_PROJECT)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisGameRecord : TuringAnalysisRecord
@end

#pragma mark -
@tsclass(TuringAnalysisOwnerRecord);

TS_AVAILABLE_IF(TS_OWNER_PROJECT)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisOwnerRecord : TuringAnalysisRecord
@end

#pragma mark -
@tsclass(TuringAnalysisHumanRecord);

TS_AVAILABLE_IF(TS_HUMAN_PROJECT)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisHumanRecord : TuringAnalysisRecord
@end

#pragma mark -
@tsclass(TuringAnalysisFingerprintRecord);

TS_AVAILABLE_IF(TS_ENABLES_FINGERPRINT_FEATURE)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisFingerprintRecord : TuringAnalysisRecord
@end
