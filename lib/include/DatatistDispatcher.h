//
//  DatatistDispatcher.h
//  DatatistTracker
//
//  Created by Mattias Levin on 29/08/14.
//  Copyright (c) 2014 Mattias Levin. All rights reserved.
//


/**
 The dispatcher is responsible for performing the actual network request to the Datatist server.
 
 A default dispatcher will be selected and created by the tracker based on the dependencies available:
 1) DTNetworking v2
 2) DTNetworking v1 (due to backwards compatibility, will be removed in the future)
 3) NSURLSession (fallback, will always work)
 
 Developers can provide their own dispatchers by implementing this protocol. This may be necessary if the app a require specific security schema, authentication, http client frameworks or network and server configurations.
 Consider inheriting from the `DTNetworking2Dispatcher` to minimise the effort.
 */
@protocol DatatistDispatcher <NSObject>

/**
 Send a single tracking event to the Datatist server.
 
 The dispatcher must send a GET request to the Datatist server, appending the parameters as a URL encoded query string.
 
 @param parameters Event parameters. These parameters should be added to the path as a URL encoded query string
 @param successBlock Run the block if the dispatch to the Datatist server is successful.
 @param failureBlock Run this block if the dispatch to the Datatist server fails. Provide a YES to indicate if the SDK should attempt to send any pending event or NO if pending events should be saved until next dispatch. E.g. there is no use trying to send pending events if there is no network connection.
 */
- (void)sendSingleEventWithParameters:(NSDictionary*)parameters
                              success:(void (^)(void))successBlock
                              failure:(void (^)(BOOL shouldContinue))failureBlock;

/**
 Send a a bulk of tracking events to the Datatist server.
 
 The dispatcher must send a POST request to the Datatist server, adding the parameters as a JSON encoded body to the request.
 
 @param parameters Event parameters. These parameters should be JSON encoded and added to the request body.
 @param successBlock Run the block if the dispatch to the Datatist server is successful.
 @param failureBlock Run this block if the dispatch to the Datatist server fails. Provide a YES to indicate if the SDK should attempt to send any pending event or NO if pending events should be saved until next dispatch. E.g. there is no use trying to send pending events if there is no network connection.
 */
- (void)sendBulkEventWithParameters:(NSDictionary*)parameters
                            success:(void (^)(void))successBlock
                            failure:(void (^)(BOOL shouldContinue))failureBlock;


@optional

/**
 *  Set a custom user agent the dispatchers will use for requests.
 *
 *  @param userAgent The user agent string.
 */
- (void)setUserAgent:(NSString*)userAgent;

@property (nonatomic, assign) BOOL isOldVersion;

@end
