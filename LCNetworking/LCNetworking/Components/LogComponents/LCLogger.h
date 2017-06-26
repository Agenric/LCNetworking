//
//  LCLogger.h
//  LCNetworking
//
//  Created by Agenric on 2017/3/2.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LCService.h"
#import "LCLoggerConfiguration.h"
#import "LCURLResponse.h"

@interface LCLogger : NSObject

@property (nonatomic, strong, readonly) LCLoggerConfiguration *configParams;

+ (void)logDebugInfoWithRequest:(NSURLRequest *)request apiName:(NSString *)apiName service:(LCService *)service requestParams:(id)requestParams httpMethod:(NSString *)httpMethod;
+ (void)logDebugInfoWithResponse:(NSHTTPURLResponse *)response responseString:(NSString *)responseString request:(NSURLRequest *)request error:(NSError *)error;
+ (void)logDebugInfoWithCachedResponse:(LCURLResponse *)response methodName:(NSString *)methodName serviceIdentifier:(LCService *)service;

+ (instancetype)sharedInstance;
- (void)logWithActionCode:(NSString *)actionCode params:(NSDictionary *)params;

@end
