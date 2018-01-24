//
//  DatatistProductInfo.h
//  DatatistTracker
//
//  Created by 张继鹏 on 17/10/2017.
//  Copyright © 2017 Datatist. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DatatistProductInfo : NSObject

@property (nonatomic, strong) NSString *productSKU;
@property (nonatomic, strong) NSString *productTitle;  // 产品名称
@property (nonatomic, strong) NSString *productCategory;  // 产品名称
@property (nonatomic) double productRealPrice;  // 产品实际成交价格
@property (nonatomic) double productOriPrice;   // 产品原价
@property (nonatomic) long productQuantity;   // 产品数量
@property (nonatomic, strong) NSString *productSourceSku; // 活动商品来源（例如赠品产品。传原商品sku，标识原商品的绑定关系）

@end

