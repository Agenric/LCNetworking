//
//  LCAPIBaseManager.h
//  LCNetworking
//
//  Created by Agenric on 2017/3/2.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LCURLResponse.h"

@class LCAPIBaseManager;

// 在调用成功之后的params字典里面，用这个key可以取出requestID
static NSString * const kLCAPIBaseManagerRequestID = @"kLCAPIBaseManagerRequestID";

typedef NS_ENUM (NSUInteger, LCAPIManagerErrorType){
    LCAPIManagerErrorTypeDefault,       //没有产生过API请求，这个是manager的默认状态。
    LCAPIManagerErrorTypeSuccess,       //API请求成功且返回数据正确，此时manager的数据是可以直接拿来使用的。
    LCAPIManagerErrorTypeNoContent,     //API请求成功但返回数据不正确。如果回调数据验证函数返回值为NO，manager的状态就会是这个。
    LCAPIManagerErrorTypeParamsError,   //参数错误，此时manager不会调用API，因为参数验证是在调用API之前做的。
    LCAPIManagerErrorTypeTimeout,       //请求超时。LCAPIProxy设置的是20秒超时，具体超时时间的设置请自己去看LCAPIProxy的相关代码。
    LCAPIManagerErrorTypeNoNetWork      //网络不通。在调用API之前会判断一下当前网络是否通畅，这个也是在调用API之前验证的，和上面超时的状态是有区别的。
};

typedef NS_ENUM (NSUInteger, LCAPIManagerRequestType){
    LCAPIManagerRequestTypeGet,
    LCAPIManagerRequestTypePost,
    LCAPIManagerRequestTypePut,
    LCAPIManagerRequestTypeDelete
};


/*************************************************************************************************/
/*                               LCAPIManagerApiCallBackDelegate                                 */
/*************************************************************************************************/
//api回调
@protocol LCAPIManagerCallBackDelegate <NSObject>
@required
- (void)managerCallAPIDidSuccess:(LCAPIBaseManager *)manager;
- (void)managerCallAPIDidFailed:(LCAPIBaseManager *)manager;
@end



/*************************************************************************************************/
/*                               LCAPIManagerCallbackDataReformer                                */
/*************************************************************************************************/
//负责重新组装API数据的对象
@protocol LCAPIManagerDataReformer <NSObject>
@required
- (id)manager:(LCAPIBaseManager *)manager reformData:(NSDictionary *)data;
@end



/*************************************************************************************************/
/*                                     LCAPIManagerValidator                                     */
/*************************************************************************************************/
//验证器，用于验证API的返回或者调用API的参数是否正确
@protocol LCAPIManagerValidator <NSObject>
@required
- (BOOL)manager:(LCAPIBaseManager *)manager isCorrectWithCallBackData:(NSDictionary *)data;

- (BOOL)manager:(LCAPIBaseManager *)manager isCorrectWithParamsData:(NSDictionary *)data;
@end



/*************************************************************************************************/
/*                                LCAPIManagerParamSourceDelegate                                */
/*************************************************************************************************/
//让manager能够获取调用API所需要的数据
@protocol LCAPIManagerParamSource <NSObject>
@required
- (NSDictionary *)paramsForApi:(LCAPIBaseManager *)manager;
@end



/*************************************************************************************************/
/*                                         LCAPIManager                                          */
/*************************************************************************************************/
// LCAPIBaseManager的派生类必须符合这些protocal
@protocol LCAPIManager <NSObject>

@required
- (NSString *)methodName;
- (NSString *)serviceType;
- (LCAPIManagerRequestType)requestType;
- (BOOL)shouldCache;

// used for pagable API Managers mainly
@optional
- (void)cleanData;
- (NSDictionary *)reformParams:(NSDictionary *)params;
- (NSInteger)loadDataWithParams:(NSDictionary *)params;
- (BOOL)shouldLoadFromNative;

@end



/*************************************************************************************************/
/*                                    LCAPIManagerInterceptor                                    */
/*************************************************************************************************/
/*
 LCAPIBaseManager的派生类必须符合这些protocal
 */
@protocol LCAPIManagerInterceptor <NSObject>

@optional
- (BOOL)manager:(LCAPIBaseManager *)manager beforePerformSuccessWithResponse:(LCURLResponse *)response;
- (void)manager:(LCAPIBaseManager *)manager afterPerformSuccessWithResponse:(LCURLResponse *)response;

- (BOOL)manager:(LCAPIBaseManager *)manager beforePerformFailWithResponse:(LCURLResponse *)response;
- (void)manager:(LCAPIBaseManager *)manager afterPerformFailWithResponse:(LCURLResponse *)response;

- (BOOL)manager:(LCAPIBaseManager *)manager shouldCallAPIWithParams:(NSDictionary *)params;
- (void)manager:(LCAPIBaseManager *)manager afterCallingAPIWithParams:(NSDictionary *)params;

@end




/*************************************************************************************************/
/*                                       LCAPIBaseManager                                        */
/*************************************************************************************************/
@interface LCAPIBaseManager : NSObject

@property (nonatomic, weak) id<LCAPIManagerCallBackDelegate> delegate;
@property (nonatomic, weak) id<LCAPIManagerParamSource> paramSource;
@property (nonatomic, weak) id<LCAPIManagerValidator> validator;
@property (nonatomic, weak) NSObject<LCAPIManager> *child; //里面会调用到NSObject的方法，所以这里不用id
@property (nonatomic, weak) id<LCAPIManagerInterceptor> interceptor;

/*
 baseManager是不会去设置errorMessage的，派生的子类manager可能需要给controller提供错误信息。所以为了统一外部调用的入口，设置了这个变量。
 派生的子类需要通过extension来在保证errorMessage在对外只读的情况下使派生的manager子类对errorMessage具有写权限。
 */
@property (nonatomic, copy, readonly) NSString *errorMessage;
@property (nonatomic, readonly) LCAPIManagerErrorType errorType;
@property (nonatomic, strong) LCURLResponse *response;

@property (nonatomic, assign, readonly) BOOL isReachable;
@property (nonatomic, assign, readonly) BOOL isLoading;

- (id)fetchDataWithReformer:(id<LCAPIManagerDataReformer>)reformer;

//尽量使用loadData这个方法,这个方法会通过param source来获得参数，这使得参数的生成逻辑位于controller中的固定位置
- (NSInteger)loadData;

- (void)cancelAllRequests;
- (void)cancelRequestWithRequestId:(NSInteger)requestID;

// 拦截器方法，继承之后需要调用一下super
- (BOOL)beforePerformSuccessWithResponse:(LCURLResponse *)response NS_REQUIRES_SUPER;
- (void)afterPerformSuccessWithResponse:(LCURLResponse *)response NS_REQUIRES_SUPER;

- (BOOL)beforePerformFailWithResponse:(LCURLResponse *)response NS_REQUIRES_SUPER;
- (void)afterPerformFailWithResponse:(LCURLResponse *)response NS_REQUIRES_SUPER;

- (BOOL)shouldCallAPIWithParams:(NSDictionary *)params NS_REQUIRES_SUPER;
- (void)afterCallingAPIWithParams:(NSDictionary *)params NS_REQUIRES_SUPER;

/*
 用于给继承的类做重载，在调用API之前额外添加一些参数,但不应该在这个函数里面修改已有的参数。
 子类中覆盖这个函数的时候就不需要调用[super reformParams:params]了
 LCAPIBaseManager会先调用这个函数，然后才会调用到 id<LCAPIManagerValidator> 中的 manager:isCorrectWithParamsData:
 所以这里返回的参数字典还是会被后面的验证函数去验证的。
 
 假设同一个翻页Manager，ManagerA的paramSource提供page_size=15参数，ManagerB的paramSource提供page_size=2参数
 如果在这个函数里面将page_size改成10，那么最终调用API的时候，page_size就变成10了。然而外面却觉察不到这一点，因此这个函数要慎用。
 
 这个函数的适用场景：
 当两类数据走的是同一个API时，为了避免不必要的判断，我们将这一个API当作两个API来处理。
 那么在传递参数要求不同的返回时，可以在这里给返回参数指定类型。
 
 具体请参考AJKHDXFLoupanCategoryRecommendSamePriceAPIManager和AJKHDXFLoupanCategoryRecommendSameAreaAPIManager
 
 */
- (NSDictionary *)reformParams:(NSDictionary *)params;
- (void)cleanData;
- (BOOL)shouldCache;

- (void)successedOnCallingAPI:(LCURLResponse *)response;
- (void)failedOnCallingAPI:(LCURLResponse *)response withErrorType:(LCAPIManagerErrorType)errorType;

@end
