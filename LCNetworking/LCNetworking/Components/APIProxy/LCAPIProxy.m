//
//  LCAPIProxy.m
//  LCNetworking
//
//  Created by Agenric on 2017/3/2.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import "LCAPIProxy.h"
#import <AFNetworking/AFNetworking.h>
#import "LCServiceFactory.h"
#import "LCRequestGenerator.h"
#import "LCLogger.h"
#import "NSURLRequest+LCNetworkingMethods.h"

static NSString * const kLCAPIProxyDispatchItemKeyCallbackSuccess = @"kLCAPIProxyDispatchItemCallbackSuccess";
static NSString * const kLCAPIProxyDispatchItemKeyCallbackFail = @"kLCAPIProxyDispatchItemCallbackFail";

@interface LCAPIProxy ()

@property (nonatomic, strong) NSMutableDictionary *dispatchTable;
@property (nonatomic, strong) NSNumber *recordedRequestId;

//AFNetworking stuff
@property (nonatomic, strong) AFHTTPSessionManager *sessionManager;

@end

@implementation LCAPIProxy
#pragma mark - getters and setters
- (NSMutableDictionary *)dispatchTable
{
    if (_dispatchTable == nil) {
        _dispatchTable = [[NSMutableDictionary alloc] init];
    }
    return _dispatchTable;
}

- (AFHTTPSessionManager *)sessionManager
{
    if (_sessionManager == nil) {
        _sessionManager = [AFHTTPSessionManager manager];
        _sessionManager.responseSerializer = [AFHTTPResponseSerializer serializer];
        _sessionManager.securityPolicy.allowInvalidCertificates = YES;
        _sessionManager.securityPolicy.validatesDomainName = NO;
    }
    return _sessionManager;
}

#pragma mark - life cycle
+ (instancetype)sharedInstance
{
    static dispatch_once_t onceToken;
    static LCAPIProxy *sharedInstance = nil;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[LCAPIProxy alloc] init];
    });
    return sharedInstance;
}

#pragma mark - public methods
- (NSInteger)callGETWithParams:(NSDictionary *)params serviceIdentifier:(NSString *)servieIdentifier methodName:(NSString *)methodName success:(LCCallback)success fail:(LCCallback)fail
{
    NSURLRequest *request = [[LCRequestGenerator sharedInstance] generateGETRequestWithServiceIdentifier:servieIdentifier requestParams:params methodName:methodName];
    [LCLogger logDebugInfoWithRequest:request apiName:methodName service:[[LCServiceFactory sharedInstance] serviceWithIdentifier:servieIdentifier] requestParams:params httpMethod:@"GET"];
    NSNumber *requestId = [self callApiWithRequest:request success:success fail:fail];
    return [requestId integerValue];
}

- (NSInteger)callPOSTWithParams:(NSDictionary *)params serviceIdentifier:(NSString *)servieIdentifier methodName:(NSString *)methodName success:(LCCallback)success fail:(LCCallback)fail
{
    NSURLRequest *request = [[LCRequestGenerator sharedInstance] generatePOSTRequestWithServiceIdentifier:servieIdentifier requestParams:params methodName:methodName];
    [LCLogger logDebugInfoWithRequest:request apiName:methodName service:[[LCServiceFactory sharedInstance] serviceWithIdentifier:servieIdentifier] requestParams:params httpMethod:@"POST"];
    NSNumber *requestId = [self callApiWithRequest:request success:success fail:fail];
    return [requestId integerValue];
}

- (NSInteger)callPUTWithParams:(NSDictionary *)params serviceIdentifier:(NSString *)servieIdentifier methodName:(NSString *)methodName success:(LCCallback)success fail:(LCCallback)fail
{
    NSURLRequest *request = [[LCRequestGenerator sharedInstance] generatePutRequestWithServiceIdentifier:servieIdentifier requestParams:params methodName:methodName];
    [LCLogger logDebugInfoWithRequest:request apiName:methodName service:[[LCServiceFactory sharedInstance] serviceWithIdentifier:servieIdentifier] requestParams:params httpMethod:@"PUT"];
    NSNumber *requestId = [self callApiWithRequest:request success:success fail:fail];
    return [requestId integerValue];
}

- (NSInteger)callDELETEWithParams:(NSDictionary *)params serviceIdentifier:(NSString *)servieIdentifier methodName:(NSString *)methodName success:(LCCallback)success fail:(LCCallback)fail
{
    NSURLRequest *request = [[LCRequestGenerator sharedInstance] generateDeleteRequestWithServiceIdentifier:servieIdentifier requestParams:params methodName:methodName];
    [LCLogger logDebugInfoWithRequest:request apiName:methodName service:[[LCServiceFactory sharedInstance] serviceWithIdentifier:servieIdentifier] requestParams:params httpMethod:@"DELETE"];
    NSNumber *requestId = [self callApiWithRequest:request success:success fail:fail];
    return [requestId integerValue];
}

- (void)cancelRequestWithRequestID:(NSNumber *)requestID
{
    NSURLSessionDataTask *requestOperation = self.dispatchTable[requestID];
    [requestOperation cancel];
    [self.dispatchTable removeObjectForKey:requestID];
}

- (void)cancelRequestWithRequestIDList:(NSArray *)requestIDList
{
    for (NSNumber *requestId in requestIDList) {
        [self cancelRequestWithRequestID:requestId];
    }
}

/** 这个函数存在的意义在于，如果将来要把AFNetworking换掉，只要修改这个函数的实现即可。 */
- (NSNumber *)callApiWithRequest:(NSURLRequest *)request success:(LCCallback)success fail:(LCCallback)fail
{
    // 跑到这里的block的时候，就已经是主线程了。
    __block NSURLSessionDataTask *dataTask = nil;
    dataTask = [self.sessionManager dataTaskWithRequest:request completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        NSNumber *requestID = @([dataTask taskIdentifier]);
        [self.dispatchTable removeObjectForKey:requestID];
        NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse *)response;
        NSData *responseData = responseObject;
        NSString *responseString = [[NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding];
        
        if (error) {
            [LCLogger logDebugInfoWithResponse:httpResponse
                                responseString:responseString
                                       request:request
                                         error:error];
            LCURLResponse *LCResponse = [[LCURLResponse alloc] initWithResponseString:responseString requestId:requestID request:request responseData:responseData error:error];
            fail?fail(LCResponse):nil;
        } else {
            // 检查http response是否成立。
            [LCLogger logDebugInfoWithResponse:httpResponse
                                responseString:responseString
                                       request:request
                                         error:NULL];
            LCURLResponse *LCResponse = [[LCURLResponse alloc] initWithResponseString:responseString requestId:requestID request:request responseData:responseData status:LCURLResponseStatusSuccess];
            success?success(LCResponse):nil;
        }
    }];
    
    NSNumber *requestId = @([dataTask taskIdentifier]);
    
    self.dispatchTable[requestId] = dataTask;
    [dataTask resume];
    
    return requestId;
}

@end
