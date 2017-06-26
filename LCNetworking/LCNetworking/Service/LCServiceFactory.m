//
//  LCServiceFactory.m
//  LCNetworking
//
//  Created by Agenric on 2017/3/2.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import "LCServiceFactory.h"

#import "LECarShareUserService.h"

/*************************************************************************/

// service name list
NSString * const kLECarShareUserV3 = @"kLECarShareUserV3";

@interface LCServiceFactory ()

@property (nonatomic, strong) NSMutableDictionary *serviceStorage;

@end

@implementation LCServiceFactory

#pragma mark - getters and setters
- (NSMutableDictionary *)serviceStorage
{
    if (_serviceStorage == nil) {
        _serviceStorage = [[NSMutableDictionary alloc] init];
    }
    return _serviceStorage;
}

#pragma mark - life cycle
+ (instancetype)sharedInstance
{
    static dispatch_once_t onceToken;
    static LCServiceFactory *sharedInstance;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[LCServiceFactory alloc] init];
    });
    return sharedInstance;
}

#pragma mark - public methods
- (LCService<LCServiceProtocol> *)serviceWithIdentifier:(NSString *)identifier
{
    if (self.serviceStorage[identifier] == nil) {
        self.serviceStorage[identifier] = [self newServiceWithIdentifier:identifier];
    }
    return self.serviceStorage[identifier];
}

#pragma mark - private methods
- (LCService<LCServiceProtocol> *)newServiceWithIdentifier:(NSString *)identifier {
    if ([identifier isEqualToString:kLECarShareUserV3]) {
        return [[LECarShareUserService alloc] init];
    }
    
    return nil;
}

@end
