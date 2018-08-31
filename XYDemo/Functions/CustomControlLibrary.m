//
//  CustomControlLibrary.m
//  CustomControlLibrary
//
//  Created by luck on 2018/5/11.
//  Copyright © 2018年 luck. All rights reserved.
//

#import "CustomControlLibrary.h"
#import <objc/runtime.h>

//@property (nonatomic, strong) NSMutableDictionary *cachedTarget;

@implementation CustomControlLibrary

#pragma mark - public methods
//+ (instancetype)sharedInstance
//{
//    static CustomControlLibrary *customControlLibrary;
//    static dispatch_once_t onceToken;
//    dispatch_once(&onceToken, ^{
//        customControlLibrary = [[CustomControlLibrary alloc] init];
//    });
//
//    return customControlLibrary;
//}

+ (id)performTarget:(NSString *)targetName action:(NSString *)actionName params:(NSArray *)params additionParams:(NSDictionary *)additionParams isClassAction:(BOOL)isClassAction shouldCacheTarget:(BOOL)shouldCacheTarget
{
    //swift自定义的类实际上还存在一个module名字，也就是类定义在内存中的名称是{moduleName}.{className}
    //NSString *appName = Bundle.main.infoDictionary["CFBundleExecutable"];

    //OC静态库里NSClassFromString得到nil的解决
    //首先, 你需要在你的主项目(的target)对build setting进行更改, 而不是静态库的项目!
    //其次, -all_load有效, -force_load甚至编译都过不了
    //最后, 结合上面, 就是在主项目(引用静态库的项目)的build setting里面搜索other linker flags, 然后把-all_load加进去就行了
    //-force_load ./CustomTest/libCustomControlLibrary.a
    Class targetClass = NSClassFromString(targetName);
    
    SEL action = NSSelectorFromString(actionName);
    
    NSObject *target = nil;
    if(targetClass)
    {
        if(isClassAction)
        {
            if([targetClass respondsToSelector:action])
            {
                return [CustomControlLibrary safePerformAction:action target:target params:params additionParams:additionParams targetClass:targetClass];
            }
        }
        else
        {
            target = [[targetClass alloc] init];
        }
    }
    
    //NSObject *target = self.cachedTarget[targetClassString];
    //if(target == nil)
    //{
    //    targetClass = NSClassFromString(targetClassString);
    //    target = [[targetClass alloc] init];
    //}

    if(target == nil)
    {
        // 这里是处理无响应请求的地方之一，这个demo做得比较简单，如果没有可以响应的target，就直接return了。实际开发过程中是可以事先给一个固定的target专门用于在这个时候顶上，然后处理这种请求的
        //[self NoTargetActionResponseWithTargetString:targetClassString selectorString:actionString originParams:params];
        
        return nil;
    }
    
    //if(shouldCacheTarget)
    //{
    //    self.cachedTarget[targetClassString] = target;
    //}
    
    if([target respondsToSelector:action])
    {
        return [CustomControlLibrary safePerformAction:action target:target params:params additionParams:additionParams targetClass:nil];
    }
    else
    {
        // 有可能target是Swift对象
        //actionString = [NSString stringWithFormat:@"Action_%@WithParams:", actionName];
        //action = NSSelectorFromString(actionString);
        if([target respondsToSelector:action])
        {
            return [CustomControlLibrary safePerformAction:action target:target params:params additionParams:additionParams targetClass:nil];
        }
        else
        {
            // 这里是处理无响应请求的地方，如果无响应，则尝试调用对应target的notFound方法统一处理
            SEL action = NSSelectorFromString(@"notFound:");
            if([target respondsToSelector:action])
            {
                //return [self safePerformAction:action target:target params:params];
            }
            else
            {
                // 这里也是处理无响应请求的地方，在notFound都没有的时候，这个demo是直接return了。实际开发过程中，可以用前面提到的固定的target顶上的。
                //[self NoTargetActionResponseWithTargetString:targetClassString selectorString:actionString originParams:params];
                //[self.cachedTarget removeObjectForKey:targetClassString];
                
                return nil;
            }
        }
    }

    return nil;
}

//- (void)releaseCachedTargetWithTargetName:(NSString *)targetName
//{
//    NSString *targetClassString = [NSString stringWithFormat:@"Target_%@", targetName];
//    [self.cachedTarget removeObjectForKey:targetClassString];
//}

#pragma mark - private methods
+ (void)NoTargetActionResponseWithTargetString:(NSString *)targetString selectorString:(NSString *)selectorString originParams:(NSDictionary *)originParams
{
    SEL action = NSSelectorFromString(@"Action_response:");
    NSObject *target = [[NSClassFromString(@"Target_NoTargetAction") alloc] init];
    
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    params[@"originParams"] = originParams;
    params[@"targetString"] = targetString;
    params[@"selectorString"] = selectorString;
    
    [CustomControlLibrary safePerformAction:action target:target params:nil additionParams:params targetClass:nil];
}

+ (id)safePerformAction:(SEL)action target:(NSObject *)target params:(NSArray *)params additionParams:(NSDictionary *)additionParams targetClass:(Class)targetClass
{
    NSMethodSignature* methodSig;//通过选择器获取方法签名
    if(!target)
    {
        methodSig = [targetClass methodSignatureForSelector:action];
    }
    else
    {
        methodSig = [target methodSignatureForSelector:action];
    }
    
    if(methodSig == nil)
    {
        return nil;
    }
    
    NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:methodSig];//通过方法签名获得调用对象
    //[invocation setArgument:&params atIndex:2];//(NSDictionary *)params
    [invocation setSelector:action];
    if(!target)
    {
        [invocation setTarget:targetClass];
    }
    else
    {
        [invocation setTarget:target];
    }
    
    // invocation 有2个隐藏参数，所以 argument 从2开始
    if([params isKindOfClass:[NSArray class]])
    {
        //此处不能通过遍历参数数组来设置参数，因为外界传进来的参数个数是不可控的
        //因此通过numberOfArguments方法获取的参数个数,是包含self和_cmd的，然后比较方法需要的参数和外界传进来的参数个数，并且取它们之间的最小值
        NSInteger count = MIN(params.count, methodSig.numberOfArguments - 2);
        for(int i = 0; i < count; i++)
        {
            const char *type = [methodSig getArgumentTypeAtIndex:2 + i];
            //需要做参数类型判断然后解析成对应类型，这里默认所有参数均为OC对象
            id argument = params[i];
            if(strcmp(type, "@") == 0)
            {
                if([argument isKindOfClass:[NSNull class]])
                {
                    argument = nil;
                }
                [invocation setArgument:&argument atIndex:2 + i];
            }
            else if(strcmp(type, @encode(CGPoint)) == 0)
            {
                CGPoint value = CGPointZero;
                [(NSValue *)argument getValue:&value];
                [invocation setArgument:&value atIndex:2 + i];
            }
            else if(strcmp(type, @encode(CGRect)) == 0)
            {
                CGRect value = CGRectZero;
                [(NSValue *)argument getValue:&value];
                [invocation setArgument:&value atIndex:2 + i];
            }
            else if(strcmp(type, @encode(int)) == 0)
            {
                int value = 0;
                value = [(NSNumber *)argument intValue];
                [invocation setArgument:&value atIndex:2 + i];
            }
            else if(strcmp(type, @encode(float)) == 0)
            {
                float value = 0;
                value = [(NSNumber *)argument floatValue];
                [invocation setArgument:&value atIndex:2 + i];
            }
            else if(strcmp(type, @encode(double)) == 0)
            {
                double value = 0;
                value = [(NSNumber *)argument doubleValue];
                [invocation setArgument:&value atIndex:2 + i];
            }
        }
    }
    
    [invocation invoke];
    
    const char* retType = [methodSig methodReturnType];
    
    if(strcmp(retType, @encode(void)) == 0)
    {
        return nil;
    }
    
    if(strcmp(retType, @encode(id)) == 0)
    {
        //id returnValue = nil;//会崩溃
        void *returnValue = nil;
        [invocation getReturnValue:&returnValue];
        
        return (__bridge id)returnValue;
    }
    
    if(strcmp(retType, @encode(NSInteger)) == 0)
    {
        NSInteger result = 0;
        [invocation getReturnValue:&result];
        
        return @(result);
    }
    
    if(strcmp(retType, @encode(BOOL)) == 0)
    {
        BOOL result = 0;
        [invocation getReturnValue:&result];
        
        return @(result);
    }
    
    if(strcmp(retType, @encode(CGFloat)) == 0)
    {
        CGFloat result = 0;
        [invocation getReturnValue:&result];
        
        return @(result);
    }
    
    if(strcmp(retType, @encode(NSUInteger)) == 0)
    {
        NSUInteger result = 0;
        [invocation getReturnValue:&result];
        
        return @(result);
    }
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
    return [target performSelector:action withObject:params];
#pragma clang diagnostic pop
}

#pragma mark - getters and setters
//- (NSMutableDictionary *)cachedTarget
//{
//    if(_cachedTarget == nil)
//    {
//        _cachedTarget = [[NSMutableDictionary alloc] init];
//    }
//
//    return _cachedTarget;
//}

@end
