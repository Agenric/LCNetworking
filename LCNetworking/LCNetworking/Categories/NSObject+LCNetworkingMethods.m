//
//  NSObject+LCNetworkingMethods.m
//  LCNetworking
//
//  Created by Agenric on 2017/2/28.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import "NSObject+LCNetworkingMethods.h"

@implementation NSObject (LCNetworkingMethods)

- (id)LC_defaultValue:(id)defaultData {
    if (![defaultData isKindOfClass:[self class]]) {
        return defaultData;
    }
    
    if ([self LC_isEmptyObject]) {
        return defaultData;
    }
    
    return self;
}

- (BOOL)LC_isEmptyObject {
    if ([self isEqual:[NSNull null]]) {
        return YES;
    }
    
    if ([self isKindOfClass:[NSString class]]) {
        if ([(NSString *)self length] == 0) {
            return YES;
        }
    }
    
    if ([self isKindOfClass:[NSArray class]]) {
        if ([(NSArray *)self count] == 0) {
            return YES;
        }
    }
    
    if ([self isKindOfClass:[NSDictionary class]]) {
        if ([(NSDictionary *)self count] == 0) {
            return YES;
        }
    }
    
    return NO;
}

@end
