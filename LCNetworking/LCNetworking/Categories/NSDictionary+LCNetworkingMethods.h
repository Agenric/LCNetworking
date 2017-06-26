//
//  NSDictionary+LCNetworkingMethods.h
//  LCNetworking
//
//  Created by Agenric on 2017/2/28.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (LCNetworkingMethods)

- (NSString *)LC_urlParamsStringSignature:(BOOL)isForSignature;
- (NSString *)LC_jsonString;
- (NSArray *)LC_transformedUrlParamsArraySignature:(BOOL)isForSignature;

@end
