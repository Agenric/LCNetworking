//
//  NSString+LCNetworkingMethods.m
//  LCNetworking
//
//  Created by Agenric on 2017/2/28.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import "NSString+LCNetworkingMethods.h"
#import <CommonCrypto/CommonDigest.h>
#import "NSObject+LCNetworkingMethods.h"

@implementation NSString (LCNetworkingMethods)

- (NSString *)LC_md5 {
    NSData* inputData = [self dataUsingEncoding:NSUTF8StringEncoding];
    unsigned char outputData[CC_MD5_DIGEST_LENGTH];
    CC_MD5([inputData bytes], (unsigned int)[inputData length], outputData);
    
    NSMutableString* hashStr = [NSMutableString string];
    int i = 0;
    for (i = 0; i < CC_MD5_DIGEST_LENGTH; ++i)
        [hashStr appendFormat:@"%02x", outputData[i]];
    
    return hashStr;
}

@end
