//
//  LCLoggerConfiguration.h
//  LCNetworking
//
//  Created by Agenric on 2017/6/26.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LCAppContext.h"

@interface LCLoggerConfiguration : NSObject

/** 渠道ID */
@property (nonatomic, strong) NSString *channelID;

/** app标志 */
@property (nonatomic, strong) NSString *appKey;

/** app名字 */
@property (nonatomic, strong) NSString *logAppName;

/** 服务名 */
@property (nonatomic, assign) NSString *serviceType;

/** 记录log用到的webapi方法名 */
@property (nonatomic, strong) NSString *sendLogMethod;

/** 记录action用到的webapi方法名 */
@property (nonatomic, strong) NSString *sendActionMethod;

/** 发送log时使用的key */
@property (nonatomic, strong) NSString *sendLogKey;

/** 发送Action记录时使用的key */
@property (nonatomic, strong) NSString *sendActionKey;

- (void)configWithAppType:(LCAppType)appType;

@end
