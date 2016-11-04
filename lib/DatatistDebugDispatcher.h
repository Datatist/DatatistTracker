//
//  DatatistDebugDispatcher.h
//  DatatistTracker
//
//  Created by Mattias Levin on 29/08/14.
//  Copyright (c) 2014 Mattias Levin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DatatistDispatcher.h"


/**
 A dispatcher that will only print events to the console and never send anything to the Datatist server.
 */
@interface DatatistDebugDispatcher : NSObject <DatatistDispatcher>

@property (nonatomic, strong) id<DatatistDispatcher> wrappedDispatcher;

@end
