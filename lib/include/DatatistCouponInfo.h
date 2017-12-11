//
//  DatatistCouponInfo.h
//  DatatistTracker
//
//  Created by 张继鹏 on 17/10/2017.
//  Copyright © 2017 Datatist. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DatatistCouponInfo : NSObject

@property (nonatomic, strong) NSString *couponType;  // 优惠券类型
@property (nonatomic) double couponAMT;      // 优惠券金额

@end
