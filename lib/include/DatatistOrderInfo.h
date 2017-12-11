//
//  DatatistOrderInfo.h
//  DatatistTracker
//
//  Created by 张继鹏 on 17/10/2017.
//  Copyright © 2017 Datatist. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DatatistOrderInfo : NSObject

@property (nonatomic, strong) NSString *orderID;
@property (nonatomic) double orderAMT;   // 订单总价（含运费）
@property (nonatomic) double shipAMT;    // 运费总价
@property (nonatomic, strong) NSString *shipAddress; // 收货地址
@property (nonatomic, strong) NSString *shipMethod;  // 配送方式

@end
