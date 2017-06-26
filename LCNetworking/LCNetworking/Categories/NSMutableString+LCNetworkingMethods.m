//
//  NSMutableString+LCNetworkingMethods.m
//  LCNetworking
//
//  Created by Agenric on 2017/2/28.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import "NSMutableString+LCNetworkingMethods.h"
#import "NSObject+LCNetworkingMethods.h"

@implementation NSMutableString (LCNetworkingMethods)

- (void)LC_appendURLRequest:(NSURLRequest *)request {
    [self appendFormat:@"\n\nHTTP URL:\n\t%@", request.URL];
    [self appendFormat:@"\n\nHTTP Header:\n%@", request.allHTTPHeaderFields ? request.allHTTPHeaderFields : @"\t\t\t\t\tN/A"];
    [self appendFormat:@"\n\nHTTP Body:\n\t%@", [[[NSString alloc] initWithData:request.HTTPBody encoding:NSUTF8StringEncoding] LC_defaultValue:@"\t\t\t\tN/A"]];
}

@end
