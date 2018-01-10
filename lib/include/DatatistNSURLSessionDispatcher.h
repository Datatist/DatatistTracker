//
//  DatatistNSURLSessionDispatcher.h
//  DatatistTracker
//
//  Created by Mattias Levin on 29/08/14.
//  Copyright (c) 2014 Mattias Levin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DatatistDispatcher.h"


/**
 A dispatcher that will use NSURLSession to send requests to the Datatist server.
 */
@interface DatatistNSURLSessionDispatcher : NSObject <DatatistDispatcher>

@property (nonatomic, strong) NSString *userAgent;

- (instancetype)initWithDatatistURL:(NSURL*)datatistURL;

+ (NSString *)dicToJSONString:(id)dic;

+ (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString;

@end
