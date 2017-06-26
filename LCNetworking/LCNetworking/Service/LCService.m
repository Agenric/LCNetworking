//
//  LCService.m
//  LCNetworking
//
//  Created by Agenric on 2017/3/2.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import "LCService.h"
#import "NSObject+LCNetworkingMethods.h"

@implementation LCService

- (instancetype)init {
    self = [super init];
    if (self) {
        if ([self conformsToProtocol:@protocol(LCServiceProtocol)]) {
            self.child = (id<LCServiceProtocol>)self;
        }
    }
    return self;
}

#pragma mark - getters and setters
- (NSString *)privateKey {
    return self.child.isOnline ? self.child.onlinePrivateKey : self.child.offlinePrivateKey;
}

- (NSString *)publicKey {
    return self.child.isOnline ? self.child.onlinePublicKey : self.child.offlinePublicKey;
}

- (NSString *)apiBaseUrl {
    return self.child.isOnline ? self.child.onlineApiBaseUrl : self.child.offlineApiBaseUrl;
}

- (NSString *)apiVersion {
    return self.child.isOnline ? self.child.onlineApiVersion : self.child.offlineApiVersion;
}


@end
