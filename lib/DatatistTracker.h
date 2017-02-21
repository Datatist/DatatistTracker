//
//  DatatistTracker.h
//  DatatistTracker
//
//  Created by Mattias Levin on 3/12/13.
//  Copyright 2013 Mattias Levin. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "DatatistTransaction.h"
#import "DatatistTransactionBuilder.h"
#import "DatatistDebugDispatcher.h"
#import "DatatistDispatcher.h"

@class DatatistTransaction;

typedef NS_ENUM(NSInteger, DatatistPushType) {
    DatatistPushTypeJPush = 0,      // 极光
    DatatistPushTypeGetui = 1,      // 个推
    DatatistPushTypeUmeng = 2,      // 友盟
    DatatistPushTypeOthers = 256,   // 其他
};

typedef NS_ENUM(NSInteger, DatatistAPIRequestResult) {
    DatatistAPIRequestResultSuccess = 0,  // 成功
    DatatistAPIRequestResultFailed  = 1,  // 失败
};

/**
 
 The DatatistTracker is an Objective-C framework (iOS and OSX) for sending analytics to a Datatist server.
 
 Datatist server is a downloadable, Free/Libre (GPLv3 licensed) real time web analytics software, [http://datatist.org](http://datatist.org).
 This framework implements the Datatist tracking REST API [http://datatist.org/docs/tracking-api/reference.](http://datatist.org/docs/tracking-api/reference/)
 
 ###How does it work
 
 1. Create and configure the tracker
 2. Track screen views, events, errors, social interaction, search, goals and more
 3. Let the SDK dispatch events to the Datatist server automatically, or dispatch events manually
 
 All events are persisted locally in Core Data until they are dispatched and successfully received by the Datatist server.
 
 All methods are asynchronous and will return immediately.
 */
@interface DatatistTracker : NSObject


extern NSString * const DatatistSessionStartNotification;


typedef NS_ENUM(NSUInteger, CustomVariableScope) {
    VisitCustomVariableScope,
    ScreenCustomVariableScope
};


/**
 @name Creating a Datatist tracker
 */

/**
 Create and configure a shared Datatist tracker.
 
 A default dispatcher will be selected and created based on the dependencies available:
 1) AFNetworking v2
 2) NSURLSession (fallback, will always work)
 
 @param siteID The unique site id generated by the the Datatist server when a new site is created
 @param baseURL The base URL of the Datatist server. The URL should not include the tracking endpoint path component (/datatist.php)
 @return The newly created DatatistTracker
 */
+ (instancetype)sharedInstanceWithSiteID:(NSString*)siteID baseURL:(NSURL*)baseURL;

/**
 Create and configure a shared Datatist tracker (designated initialiser).
 
 Developers can provide their own dispatchers when creating the tracker in order to implement specific security schemas, http client frameworks or network and server configurations.
 Consider inheriting from the `AFNetworking2Dispatcher` to minimise the implementation effort.
 
 @param siteID The unique site id generated by the the Datatist server when the tracked application is created
 @param dispatcher The dispatcher that will perform the network request to the Datatist server
 @return The newly created DatatistTracker
 */
+ (instancetype)sharedInstanceWithSiteID:(NSString*)siteID dispatcher:(id<DatatistDispatcher>)dispatcher;

/**
 Return the shared Datatist tracker.
 
 The Datatist tracker must have been created and configured for this method to return the tracker.
 
 @return The existing DatatistTracker object
 @see sharedInstanceWithSiteID:baseURL:
 */
+ (instancetype)sharedInstance;


/**
 sync JSPatchC patch
 */
+ (void)sync;


/**
 Datatist site id.
 
 The value can be found in the Datatist server -> Settings -> Websites.
 */
@property (nonatomic, readonly) NSString *siteID;

/**
 The dispatcher will execute the actual network request to the Datatist server.
 
 Developers can provide their own dispatchers when creating the tracker in order to implement specific security schemas, http client frameworks or network and server configurations.
 */
@property (readonly) id<DatatistDispatcher> dispatcher;


/**
 @name Tracker configuration
 */


/**
 The user id is any non empty unique string identifying the user, such as an email address or a username.
 
 Set this value when you have a way of uniquely identifying the user in the app, e.g. after the user signed in. The user id will appear in the Datatist server and is available for segmentation reports.
 It is important that the user id is saved locally in the app and set each time directly after the tracker is started. Otherwise tracked events sent before setting this property will not be attributed to the user id.
 
 The user id allow events from different platforms, e.g. iOS and Android, to be associated in the Datatist server to the same user as long as the same user id is used on all platforms.
 
 To stop associating tracked events to a specific user set this property to nil, e.g. after user signs out.
 
 If no user id is provided, an internal random id will be managed by the SDK to track unique users and visits. This value will be persisted across app restarts. If the app is uninstalled/installed again or the user change device, a new id will be generated and events tracked as a new unique user.
 */
@property (nonatomic, strong) NSString *userID;


/**
 Views, exceptions and social tracking will be prefixed based on type.
 
 This will allow for logical separation and grouping of statistics in the Datatist web interface.
 Screen views will prefixed with "screen".
 Exceptions will be prefixed with "exception".
 Social interaction will be prefixed with "social".
 
 Default value is YES which would be the preferred option for most developers. Set to NO to avoid prefixing or implement a custom prefixing schema.
 */
@property (nonatomic) BOOL isPrefixingEnabled;

/**
 Run the tracker in debug mode.
 
 Instead of sending events to the Datatist server, events will be printed to the console. Useful during development.
 */
@property(nonatomic) BOOL debug;

/**
 Opt out of tracking.
 
 No events will be sent to the Datatist server. This feature can be used to allow the user to opt out of tracking due to privacy. The value will be retained across app restart and upgrades.
 */
@property(nonatomic) BOOL optOut;

/**
 The probability of an event actually being sampled and sent to the Datatist server. Value 1-100, default 100.
 
 Use the sample rate to only send a sample of all events generated by the app. This can be useful for applications that generate a lot of events.
 */
@property (nonatomic) NSUInteger sampleRate;


// Removed for now. This feature still depends on the auth_token being sent to the Datatist server.
// The auth_token should not be used any longer in the clients due to security reasons.
// Keep the code and enable once the Datatist server allow location information without passing the auth_token.

///**
// Events sent to the Datatist server will include the users current position when the event was generated. This can be used to improve showing visitors location. Default NO. This value must be set before the tracker is used the first time.
//
// Please note that the position will only be used when showing the location in a users profile. It will not affect the visitor map.
//
// The user will be asked for permission to use current location when the first event is sent. The user can also disable the location service from the Settings location.
//
// Think about users privacy. Provide information why their location is tracked and give the user the option to opt out.
//
// Turning this ON will potentially use more battery power. The tracker will only react to significant location changes to reduce battery impact. Location changes will not be tracked when the app is terminated or running in the background.
// Please note that users can decided to not allow the app to access location information from the general Settings app.
// */
//@property (nonatomic) BOOL includeLocationInformation;


/**
 If set to YES the SDK will use custom variable index 1-3 to provide default information about the app and users device (App version, OS version and HW) for each visit.
 Set to NO to free up additional custom variable indexes for your own reporting purpose.
 
 Default values it YES.
 */
@property (nonatomic) BOOL includeDefaultCustomVariable;


/**
 @name Session control
 */

/**
 Set this value to YES to force a new session start when the next event is sent to the Datatist server.
 
 By default a new session is started each time the application in launched.
 */
@property (nonatomic) BOOL sessionStart;

/**
 A new session will be generated if the application spent longer time in the background then the session timeout value. Default value 120 seconds.
 
 The Datatist server will also create a new session if the event is recorded 30 minutes after the previous received event.
 */
@property (nonatomic) NSTimeInterval sessionTimeout;


/**
 @name Track screen views, events, goals and more
 */

/**
 Track a single screen view.
 
 Screen views are prefixed with "screen" by default unless prefixing scheme is turned off.
 
 @param screen The name of the screen to track.
 @return YES if the event was queued for dispatching.
 @see isPrefixingEnabled
 */
- (BOOL)sendView:(NSString*)screen DEPRECATED_ATTRIBUTE;
- (BOOL)sendView:(NSString*)screen withCustomVariable:(NSDictionary *)vars;

/**
 Track a single hierarchical screen view.
 
 Datatist support hierarchical screen names, e.g. screen/settings/register. Use this to create a hierarchical and logical grouping of screen views in the Datatist web interface.
 
 Screen views are prefixed with "screen" by default unless prefixing scheme is turned off.
 
 @param screen A list of names of the screen to track.
 @param ... A nil terminated list of names of the screen to track.
 @return YES if the event was queued for dispatching.
 @see isPrefixingEnabled
 */
- (BOOL)sendViews:(NSString*)screen, ... DEPRECATED_ATTRIBUTE;
- (BOOL)sendWithCustomVariable:(NSDictionary *)vars Views:(NSString*)screen, ...;


/**
 Track a single hierarchical screen view specified as an array.
 
 Datatist support hierarchical screen names, e.g. screen/settings/register. Use this to create a hierarchical and logical grouping of screen views in the Datatist web interface.
 
 Screen views are prefixed with "screen" by default unless prefixing scheme is turned off.
 
 @param screens An array of screen names to track.
 @return YES if the event was queued for dispatching.
 @see isPrefixingEnabled
 */
- (BOOL)sendViewsFromArray:(NSArray*)screens DEPRECATED_ATTRIBUTE;
- (BOOL)sendViewsFromArray:(NSArray*)screens withCustomVariable:(NSDictionary *)vars;

/**
 Track an user interaction as a custom event.
 
 @warning As of Datatist server 2.3 events are presented in a separate section and support sending a numeric value (float or integer). The Datatist tracker support this out of the box.
 
 @param category The category of the event
 @param action The name of the action, e.g Play, Pause, Download
 @param name Event name, e.g. song name, file name. Optional.
 @return YES if the event was queued for dispatching.
 */
- (BOOL)sendEventWithCategory:(NSString*)category action:(NSString*)action name:(NSString*)name value:(NSString *)value DEPRECATED_ATTRIBUTE;
- (BOOL)sendEventWithCategory:(NSString*)category action:(NSString*)action name:(NSString*)name value:(NSString *)value withCustomVariable:(NSDictionary *)vars DEPRECATED_ATTRIBUTE;
- (BOOL)sendEventWithCategory:(NSString*)category action:(NSString*)action name:(NSString*)name withCustomVariable:(NSDictionary *)vars;

/**
 Track a caught exception or error.
 
 Exception are prefixed with "exception" by default unless prefixing scheme is turned off.
 
 @param description A description of the exception. Maximum 50 characters
 @param isFatal YES if the exception will lead to a fatal application crash
 @return YES if the event was queued for dispatching.
 @see isPrefixingEnabled
 */
- (BOOL)sendExceptionWithDescription:(NSString*)description isFatal:(BOOL)isFatal DEPRECATED_ATTRIBUTE;
- (BOOL)sendExceptionWithDescription:(NSString*)description isFatal:(BOOL)isFatal withCustomVariable:(NSDictionary *)vars  DEPRECATED_ATTRIBUTE;

/**
 Track a users interaction with social networks.
 
 Exception are prefixed with "social" by default unless prefixing scheme is turned off.
 
 @param action The action taken by the user, e.g. like, tweet
 @param target The target of the action, e.g. a comment, picture or video (often an unique id or name)
 @param network The social network the user is interacting with, e.g. Facebook
 @return YES if the event was queued for dispatching.
 @see isPrefixingEnabled
 */
- (BOOL)sendSocialInteraction:(NSString*)action target:(NSString*)target forNetwork:(NSString*)network DEPRECATED_ATTRIBUTE;
- (BOOL)sendSocialInteraction:(NSString*)action target:(NSString*)target forNetwork:(NSString*)network withCustomVariable:(NSDictionary *)vars;

/**
 Track a goal conversion.
 
 @param goalID The unique goal ID as configured in the Datatist server.
 @param revenue The monetary value of the conversion.
 @return YES if the event was queued for dispatching.
 */
- (BOOL)sendGoalWithID:(NSUInteger)goalID revenue:(NSUInteger)revenue DEPRECATED_ATTRIBUTE;
- (BOOL)sendGoalWithID:(NSUInteger)goalID revenue:(NSUInteger)revenue withCustomVariable:(NSDictionary *)vars;

/**
 Track a search performed in the application. The search could be local or towards a server.
 
 Searches will be presented as Site Search requests in the Datatist web interface.
 
 @param keyword The search keyword entered by the user.
 @param category An optional search category.
 @param numberOfHits The number of results found (optional).
 @return YES if the event was queued for dispatching.
 */
- (BOOL)sendSearchWithKeyword:(NSString*)keyword category:(NSString*)category numberOfHits:(NSNumber*)numberOfHits DEPRECATED_ATTRIBUTE;
- (BOOL)sendSearchWithKeyword:(NSString*)keyword category:(NSString*)category numberOfHits:(NSNumber*)numberOfHits withCustomVariable:(NSDictionary *)vars;

/**
 Track an ecommerce transaction.
 
 A transaction contains transaction information as well as an optional list of items included in the transaction.
 
 Use the transaction builder to create the transaction object.
 
 @param transaction The transaction.
 @return YES if the event was queued for dispatching.
 @see DatatistTransactionBuilder
 @see DatatistTransaction
 @see DatatistTransactionItem
 */
- (BOOL)sendTransaction:(DatatistTransaction*)transaction DEPRECATED_ATTRIBUTE;
- (BOOL)sendTransaction:(DatatistTransaction*)transaction withCustomVariable:(NSDictionary *)vars;

/**
 Track an outlink to an external website or app.
 
 @param url The url which leads to an external website or app.
 @return YES if the event was queued for dispatching.
 */
- (BOOL)sendOutlink:(NSString*)url DEPRECATED_ATTRIBUTE;
- (BOOL)sendOutlink:(NSString*)url withCustomVariable:(NSDictionary *)vars DEPRECATED_ATTRIBUTE;

/**
 Track a download initiated by the app.
 
 @param url The url of the downloaded content.
 @return YES if the event was queued for dispatching.
 */
- (BOOL)sendDownload:(NSString*)url DEPRECATED_ATTRIBUTE;
- (BOOL)sendDownload:(NSString*)url withCustomVariable:(NSDictionary *)vars;

/**
 Track that the app was launched from a Datatist campaign URL.
 The campaign information will be sent to the server with the next Datatist event.
 
 A Datatist campaign URL contains one or two special parameters for tracking campaigns.
 * pk_campaign - The name of the campaign
 * pk_keyword - A specific call to action within a campaign
 Example URL http://example.org/landing.html?pk_campaign=Email-Nov2011&pk_kwd=LearnMore
 
 1. Register a custom URL schema in your app info.plist file. This is needed to launch your app when tapping on the campaign link
 2. Detect app launches coming from your campaign links in the `AppDelegate`
 3. Generate Datatist campaigns urls using the [Datatist URL builder tool](http://datatist.org/docs/tracking-campaigns-url-builder/)
 4. Distribute your urls
 
 If no Datatist campaign parameters are detected in the URL will be ignored and no tracking performed.
 
 @warning Experimental feature. Not fully applicable in app context.
 
 @param campaignURLString A custom app URL containing campaign parameters.
 @return YES if URL was detected to contain Datatist campaign parameter.
 */
- (BOOL)sendCampaign:(NSString*)campaignURLString DEPRECATED_ATTRIBUTE;
- (BOOL)sendCampaign:(NSString*)campaignURLString withCustomVariable:(NSDictionary *)vars;

/**
 Track how often a specific ad or banner is displayed in the app.
 
 Check out the [content tracking user guide at Datatist](http://datatist.org/docs/content-tracking/) for additional details.
 
 @param name A human readable display name of the content.
 @param piece A more technical name/id of the content, e.g. the image name or ads id. Optional.
 @param target The outgoing target, e.g. an URL. Optional.
 @return YES if the event was queued for dispatching.
 @see sendContentInteractionWithName:piece:target:
 */
- (BOOL)sendContentImpressionWithName:(NSString*)name piece:(NSString*)piece target:(NSString*)target DEPRECATED_ATTRIBUTE;
- (BOOL)sendContentImpressionWithName:(NSString*)name piece:(NSString*)piece target:(NSString*)target withCustomVariable:(NSDictionary *)vars;

/**
 Track when a user interact with an ad or banner.
 
 When used together with content impression the conversion rate can be calculated. Make sure the same name and piece is used to accuratly calculate the conversion rate.
 
 @param name A human readable display name of the content.
 @param piece A more technical name/id of the content, e.g. the image name or ads id. Optional.
 @param target The outgoing target, e.g. an URL. Optional.
 @return YES if the event was queued for dispatching.
 @see sendContentImpressionWithName:piece:target:
 */
- (BOOL)sendContentInteractionWithName:(NSString*)name piece:(NSString*)piece target:(NSString*)target DEPRECATED_ATTRIBUTE;
- (BOOL)sendContentInteractionWithName:(NSString*)name piece:(NSString*)piece target:(NSString*)target withCustomVariable:(NSDictionary *)vars;


/**
 add custom variable

 @param proterties proterties description
 */
- (void)addvisitproperty:(NSDictionary *)proterties;

/**
 @name Dispatch pending events
 */

/**
 The tracker will automatically dispatch all pending events on a timer. Default value 120 seconds.
 
 If a negative value is set the dispatch timer will never run and manual dispatch must be used. If 0 is set the event is dispatched as as quick as possible after it has been queued.
 
 @see dispatch
 */
@property(nonatomic) NSTimeInterval dispatchInterval;

/**
 Specifies the maximum number of events queued in core date. Default 500.
 
 If the number of queued events exceed this value events will no longer be queued.
 */
@property (nonatomic) NSUInteger maxNumberOfQueuedEvents;

/**
 Specifies how many events should be sent to the Datatist server in each request. Default 20 events per request.
 
 The Datatist server support sending one event at the time or in bulk mode.
 */
@property (nonatomic) NSUInteger eventsPerRequest;

/**
 SDK version
*/
+ (NSString *)version;

/**
 Manually start a dispatch of all pending events.
 
 @return YES if the dispatch process was started.
 */
- (BOOL)dispatch;

/**
 Delete all pending events.
 */
- (void)deleteQueuedEvents;



/**
 Specifies push client id and push type

 @param cid push client id
 @param type push type
 */
- (void)setPushClientId:(NSString *)cid andType:(DatatistPushType)type;



/**
 Track when receive push message

 @param dic push user info
  @param vars custom variable
 */
- (void)sendPushReceiveEventWithUserInfo:(NSDictionary *)dic withCustomVariable:(NSDictionary *)vars;



/**
 Track when user read push message

 @param dic push user info
  @param vars custom variable
 */
- (void)sendPushOpenEventWithUserInfo:(NSDictionary *)dic withCustomVariable:(NSDictionary *)vars;



/**
 Track when send API request

 @param path request path
 @param start when send request, yyyy-MM-dd HH:mm:ss.SSS
 @param result request resutl
 @param ms request duratiion
 @param vars custom variable
 */
- (void)sendAPIEventWithPath:(NSString *)path andStarttime:(NSString *)start andResult:(DatatistAPIRequestResult)result andDuration:(NSInteger)ms withCustomVariable:(NSDictionary *)vars;


/**
 @name Custom visit variables
 */

/**
 The application name.
 
 The application name will be sent as a custom variable (index 2). By default the application name stored in CFBundleDisplayName will be used.
 */
@property (nonatomic, strong) NSString *appName;

/**
 The application version.
 
 The application version will be sent as a custom variable (index 3). By default the application version stored in CFBundleVersion will be used.
 */
@property (nonatomic, strong) NSString *appVersion;

@end
