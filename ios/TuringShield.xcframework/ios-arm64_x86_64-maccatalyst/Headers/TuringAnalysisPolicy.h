//
//  TuringAnalysisPolicy.h
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
#import <UIKit/UIKit.h>


#pragma mark -

TS_AVAILABLE_IF(__TS_OR_3(TS_OWNER_PROJECT, TS_AGE_PROJECT, TS_HUMAN_PROJECT))
@interface UIView (TSGetSystemKeyboardView)

+ (nullable UIView *)getSystemKeyboardView;
+ (nullable UIView *)getApplicationRootView;

@end

#pragma mark -
@tsclass(TuringAnalysisPolicy);

TS_VISIBLE_LEVEL(TS_TURING_SHIELD_OPEN_API)
@interface TuringAnalysisPolicy : NSObject

- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 创建一个基于自由输入的游戏类型的采集策略
 @discussion 针对随机输入的特性，用于识别成年人/未成年人的采集策略，为性能要求特别优化。
 */
+ (nonnull instancetype)gamePolicy TS_AVAILABLE_IF(TS_AGE_PROJECT);

/**
创建一个基于自由输入的主人身份识别类型的采集策略
@discussion 针对随机输入的特性，用于识别主人身份的采集策略，为性能要求特别优化。
*/
+ (nonnull instancetype)ownerPolicy TS_AVAILABLE_IF(TS_OWNER_PROJECT);

/**
创建一个基于键盘输入的主人身份识别类型的采集策略
@discussion 针对键盘输入的特性，用于识别主人身份的采集策略，为密码敏感性特别优化。
*/
+ (nonnull instancetype)ownerSecurityInputPolicy TS_AVAILABLE_IF(TS_OWNER_PROJECT);

/**
创建一个基于手势密码输入的主人身份识别类型的采集策略
@discussion 针对手势密码输入的特性，用于识别主人身份的采集策略，为密码敏感性特别优化。
*/
+ (nonnull instancetype)ownerSecurityPatternPolicy TS_AVAILABLE_IF(TS_OWNER_PROJECT);

/**
创建一个风险识别类型的采集策略
@discussion 针对点击和划动输入的我，用于人机识别和风险识别的采集策略，为快速采集特别优化。
*/
+ (nonnull instancetype)humanPolicy TS_AVAILABLE_IF(TS_HUMAN_PROJECT);

/**
 为策略指定采集的目标视图
 @discussion
    * 对 `gamePolicy` 和 `ownerPolicy` 而言一般不需要指定，默认会进行全屏幕采集；
    * 对 `ownerSecurityInputPolicy` 和 `ownerSecurityPatternPolicy` 而言，如果使用
    了系统标准键盘，则需要设定为输入密码的文本框（或其它支持UIKeyInput或
    UITextInput协议的UIView），但如果使用了自定义的键盘View，则需要设定为该
    键盘的view。
    * 对于 `humanPolicy` 而言，一般都需要指定被点击的对象，例如一个按钮。
    
 */
@property (nonatomic, weak, nullable) UIView *associatedView;

/**
 为策略指定传感器采样的时间间隔。因为不同的策略类型可能对采样率的要求不同且
 已预设了一个相对合理的值，因而通常不需要手动设置该选项。
 */
@property (nonatomic, assign) NSTimeInterval motionSamplingInterval;

/**
 期望采集时长
 @discussion 如果不知道用途则不要轻易改变此参数
 */
@property (nonatomic, assign) NSTimeInterval expectedTotalTrackingTime;

/**
延时结束采集，每次采集结束后额外增加的采集时长
@discussion 如果不知道用途则不要轻易改变此参数
*/
@property (nonatomic, assign) NSTimeInterval extraTrackingTime;

/**
 每天（按最近24小时计算）最大采集次数
*/
@property (nonatomic, assign) NSUInteger maximumNumberOfAlysisRecordsPerDay;
/**
 每小时（按最近60分钟内计算）最大采集次数
 */
@property (nonatomic, assign) NSUInteger maximumNumberOfAlysisRecordsPerHour;

/**
 每次创建任务最大采集次数
 */
@property (nonatomic, assign) NSUInteger maximumNumberOfAlysisRecordsPerTask;

/**
 每次采集之间间隔的时间，单位为秒
 */
@property (nonatomic, assign) NSTimeInterval intervalBetweenRecords;

@end
