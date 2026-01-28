//
//  TuringAppContext.h
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


@tsclass(TuringAppContext);

TS_AVAILABLE_IF(TS_ENABLES_FINGERPRINT_FEATURE)
TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAppContext : NSObject <NSCopying>

@property (nonatomic, copy, nullable) NSString *channel;
@property (nonatomic, copy, nullable) NSString *licenseCode;
@property (nonatomic, copy, nullable) NSString *version;
@property (nonatomic, assign) NSUInteger build;
@property (nonatomic, copy, nullable) NSString *metaData;
@property (nonatomic, copy, nullable) NSDictionary<NSNumber *, NSString *> *parameters;

@end

