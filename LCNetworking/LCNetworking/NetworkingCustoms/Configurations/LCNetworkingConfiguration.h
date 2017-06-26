//
//  LCNetworkingConfiguration.h
//  LCNetworking
//
//  Created by Agenric on 2017/3/1.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#ifndef LCNetworkingConfiguration_h
#define LCNetworkingConfiguration_h

typedef NS_ENUM(NSInteger, LCAppType) {
    LCAppTypexxx
};

typedef NS_ENUM(NSUInteger, LCURLResponseStatus)
{
    LCURLResponseStatusSuccess, //作为底层，请求是否成功只考虑是否成功收到服务器反馈。至于签名是否正确，返回的数据是否完整，由上层的LCAPIBaseManager来决定。
    LCURLResponseStatusErrorTimeout,
    LCURLResponseStatusErrorNoNetwork // 默认除了超时以外的错误都是无网络错误。
};

static NSString *LCKeychainServiceName = @"xxxxx";
static NSString *LCUDIDName = @"xxxx";
static NSString *LCPasteboardType = @"xxxx";

static BOOL kLCShouldCache = YES;
static BOOL kLCServiceIsOnline = NO;
static NSTimeInterval kLCNetworkingTimeoutSeconds = 20.0f;
static NSTimeInterval kLCCacheOutdateTimeSeconds = 300; // 5分钟的cache过期时间
static NSUInteger kLCCacheCountLimit = 1000; // 最多1000条cache

// services
extern NSString * const kLCServiceGDMapV3;
extern NSString * const kLeCarSharePortalV3;

#endif /* LCNetworkingConfiguration_h */
