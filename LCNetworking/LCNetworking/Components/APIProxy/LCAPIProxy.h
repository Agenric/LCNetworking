//
//  LCAPIProxy.h
//  LCNetworking
//
//  Created by Agenric on 2017/3/2.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LCURLResponse.h"

typedef void(^LCCallback)(LCURLResponse *response);

@interface LCAPIProxy : NSObject

+ (instancetype)sharedInstance;

- (NSInteger)callGETWithParams:(NSDictionary *)params serviceIdentifier:(NSString *)servieIdentifier methodName:(NSString *)methodName success:(LCCallback)success fail:(LCCallback)fail;
- (NSInteger)callPOSTWithParams:(NSDictionary *)params serviceIdentifier:(NSString *)servieIdentifier methodName:(NSString *)methodName success:(LCCallback)success fail:(LCCallback)fail;
- (NSInteger)callPUTWithParams:(NSDictionary *)params serviceIdentifier:(NSString *)servieIdentifier methodName:(NSString *)methodName success:(LCCallback)success fail:(LCCallback)fail;
- (NSInteger)callDELETEWithParams:(NSDictionary *)params serviceIdentifier:(NSString *)servieIdentifier methodName:(NSString *)methodName success:(LCCallback)success fail:(LCCallback)fail;


- (NSNumber *)callApiWithRequest:(NSURLRequest *)request success:(LCCallback)success fail:(LCCallback)fail;
- (void)cancelRequestWithRequestID:(NSNumber *)requestID;
- (void)cancelRequestWithRequestIDList:(NSArray *)requestIDList;

@end
