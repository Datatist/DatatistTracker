//
//  DatatistTransaction.h
//  DatatistTracker
//
//  Created by Mattias Levin on 19/01/14.
//  Copyright (c) 2014 Mattias Levin. All rights reserved.
//

#import <Foundation/Foundation.h>


@class DatatistTransactionBuilder;


typedef void (^TransactionBuilderBlock)(DatatistTransactionBuilder *builder);


/**
 A transaction is a composite object containing transaction information as well as an optional list of items included in the transaction.
 */
@interface DatatistTransaction : NSObject

/**
 A unique transaction identifier. Mandatory.
 */
@property (nonatomic, readonly) NSString *identifier;

/**
 The grand total for the ecommerce order. Mandatory.
 */
@property (nonatomic, readonly) NSNumber *grandTotal;

/**
 The sub total of the transaction (excluding shipping cost). Optional.
 */
@property (nonatomic, readonly) NSNumber *subTotal DEPRECATED_ATTRIBUTE;

/**
 The total tax. Optional.
 */
@property (nonatomic, readonly) NSNumber *tax DEPRECATED_ATTRIBUTE;

/**
 The total shipping cost. Optional.
 */
@property (nonatomic, readonly) NSNumber *shippingCost;

/**
 The total offered discount. Optional.
 */
@property (nonatomic, readonly) NSNumber *discount;

/**
 A list of items included in the transaction. Optional.
 @see DatatistTransactionItem
 */
@property (nonatomic, readonly) NSArray *items;


/**
 Create a transaction using a transaction builder.
 @param block a transaction builder block
 @return a new transaction
 @see DatatistTransactionBuilder
 */
+ (instancetype)transactionWithBuilder:(TransactionBuilderBlock)block;


/**
 Create a transaction from the builder.
 Use the builder method to create a new instance.
 @param builder the transaction will be created from this builder
 @return a new transaction
 @see transactionWithBuilder:
 */
- (id)initWithBuilder:(DatatistTransactionBuilder*)builder;


@end


