//
//  XYGlobalFunctions.m
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import "XYGlobalFunctions.h"

//#define USE_RUNTIME

#import <objc/runtime.h>

#ifdef USE_RUNTIME

@interface NSObject(XYForwardInvocation)

@end

@implementation NSObject(XYForwardInvocation)

+ (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector
{
    if([self respondsToSelector:aSelector])
    {
        // 已实现不做处理
        return [self methodSignatureForSelector:aSelector];
    }
    
    return [NSMethodSignature signatureWithObjCTypes:"v@:"];
}

+ (void)forwardInvocation:(NSInvocation *)anInvocation
{
    NSLog(@"在 %@ 类中, 调用了没有实现的类方法: %@ ", NSStringFromClass([self class]), NSStringFromSelector(anInvocation.selector));
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector
{
    if([self respondsToSelector:aSelector])
    {
        // 已实现不做处理
        return [self methodSignatureForSelector:aSelector];
    }
    
    return [NSMethodSignature signatureWithObjCTypes:"v@:"];
}

- (void)forwardInvocation:(NSInvocation *)anInvocation
{
    NSLog(@"在 %@ 类中, 调用了没有实现的实例方法: %@ ", NSStringFromClass([self class]), NSStringFromSelector(anInvocation.selector));
}

@end

#endif//USE_RUNTIME

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@implementation UIButton(XYAddBlock)

static char btnBlock;
//static void *kBtnBlock = "kBtnBlock";

//@dynamic buttonBlock;

#ifdef DEBUG
- (void)dealloc
{
    objc_setAssociatedObject(self, &btnBlock, nil, OBJC_ASSOCIATION_ASSIGN);//断开关联
}
#endif//DEBUG

- (void)setBlock:(ButtonClickBlock)block
{
    objc_removeAssociatedObjects(self);
    
    objc_setAssociatedObject(self, &btnBlock, block, OBJC_ASSOCIATION_RETAIN_NONATOMIC);//创建关联

    [self addTarget:self action:@selector(buttonClicked:) forControlEvents:(UIControlEventTouchUpInside)];
}

- (ButtonClickBlock)getBlock
{
    return objc_getAssociatedObject(self, &btnBlock);//获取相关联的对象
}

- (void)buttonClicked:(id)sender
{
    ButtonClickBlock block = [self getBlock];
    if(block)
    {
        block(sender);
    }
}

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@implementation XYGlobalFunctions

+ (CGSize)calcTextWidth:(NSString *)text textFont:(UIFont *)textFont
{
    NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithObject:textFont forKey:NSFontAttributeName];
    CGSize size = [text boundingRectWithSize:CGSizeMake(MAXFLOAT, 0.0) options:NSStringDrawingUsesLineFragmentOrigin attributes:dic context:nil].size;
    
    return size;
}

//获取拼音首字母(传入汉字字符串, 返回大写拼音首字母)
+ (NSString *)getFirstCharactor:(NSString *)aString
{
    //转成了可变字符串
    NSMutableString *str = [NSMutableString stringWithString:aString];
    if(str)
    {
        //先转换为带声调的拼音
        CFStringTransform((CFMutableStringRef)str, NULL, kCFStringTransformMandarinLatin, NO);
        //再转换为不带声调的拼音
        CFStringTransform((CFMutableStringRef)str, NULL, kCFStringTransformStripDiacritics, NO);
        //转化为大写拼音
        NSString *pinYin = [str capitalizedString];
        //获取并返回首字母
        return [pinYin substringToIndex:1];
    }
    
    return nil;
}

+ (NSMutableAttributedString *)createAttributedString:(NSString *)preStr valueStr:(NSString *)valueStr suffStr:(NSString *)suffStr valueColor:(UIColor *)valueColor valueFont:(UIFont *)valueFont
{
    NSString *str1 = preStr;
    NSInteger str1Len = 0;
    
    NSString *str2 = nil;
    NSInteger str2Len = 0;
    
    NSString *str3 = nil;
    
    str1Len = [str1 length];
    
    str2 = [str1 stringByAppendingString:valueStr];
    str2Len = [str2 length];
    
    str3 = [str2 stringByAppendingString:suffStr];
    
    NSRange range = {0, 0};
    NSMutableAttributedString *str = nil;
    if(str3)
    {
        range.location = str1Len;
        range.length = str2Len - str1Len;
        str = [[NSMutableAttributedString alloc] initWithString:str3];
    }
    
    if(str)
    {
        if(valueColor)
        {
            [str addAttribute:NSForegroundColorAttributeName value:valueColor range:range];//设置字体颜色
        }
        
        if(valueFont)
        {
            [str addAttribute:NSFontAttributeName value:valueFont range:range];//设置字体颜色
        }
        //设置字间距
        //long number = 3;
        //CFNumberRef num = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt8Type, &number);
        //[str addAttribute:(id)kCTKernAttributeName value:(__bridge id)num range:NSMakeRange(str1Len - 1, 1)];
        //if(str5)
        //{
        //    [str addAttribute:(id)kCTKernAttributeName value:(__bridge id)num range:NSMakeRange(str2Len - 1, 1)];
        //
        //    range.location = str3Len;
        //    range.length = str4Len - str3Len;
        //    [str addAttribute:NSForegroundColorAttributeName value:textColor range:range];//设置字体颜色
        //
        //    [str addAttribute:(id)kCTKernAttributeName value:(__bridge id)num range:NSMakeRange(str3Len - 1, 1)];
        //    [str addAttribute:(id)kCTKernAttributeName value:(__bridge id)num range:NSMakeRange(str4Len - 1, 1)];
        //}
        //CFRelease(num);
    }
    
    return str;
}

+ (NSMutableAttributedString *)getAttributedString:(NSString *)text font:(UIFont *)font lineSpace:(int)lineSpace
{
    NSMutableAttributedString *attrStr = [[NSMutableAttributedString alloc] initWithString:text];
    
    NSRange allRange = NSMakeRange(0, [text length]);
    [attrStr addAttribute:NSFontAttributeName value:font range:allRange];
    
    if(lineSpace > 0)
    {
        NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
        paragraphStyle.lineSpacing = lineSpace;//调整行间距
        [attrStr addAttribute:NSParagraphStyleAttributeName value:paragraphStyle range:allRange];
    }
    
    return attrStr;
}

+ (float)calcAttributedStringHeight:(NSString *)content contentWidth:(float)contentWidth font:(UIFont *)font lineSpace:(int)lineSpace
{
    //NSAttributedString 的每个部分都要至少设置两个属性:NSFontAttributeName,NSForegroundColorAttributeName;NSStringDrawingOptions 的值, 在多行的情况下, 至少要有NSStringDrawingUsesLineFragmentOrigin,NSStringDrawingUsesFontLeading;如果文字中可能会出现emoji表情的话, emoji的高度比文字要高一点点,的简单的方法是在高度基础上加了两个像素.
    NSMutableAttributedString *attrStr = [XYGlobalFunctions getAttributedString:content font:font lineSpace:lineSpace];
    
    NSStringDrawingOptions options =  NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading;
    CGRect rect = [attrStr boundingRectWithSize:CGSizeMake(contentWidth, CGFLOAT_MAX) options:options context:nil];
    CGFloat contentHeight = rect.size.height;//ceilf(rect.size.height);
    
    return contentHeight;//+2加两个像素,防止emoji被切掉.
}

+ (BOOL)canInputValue:(NSString *)inputValue keyboardType:(UIKeyboardType)keyboardType textField:(UITextField *)textField textView:(UITextView *)textView showMessage:(BOOL)showMessage filterSymbol:(BOOL)filterSymbol andBlock:(void(^)(NSString *message))block
{
    if([inputValue length])
    {
        NSString *filterStr = nil;
        
        switch(keyboardType)
        {
            case UIKeyboardTypeNumberPad:
            case UIKeyboardTypePhonePad:
            {
                //请注意这个\n，如果不写这个，Done按键将不会触发，如果用在SearchBar中，将会不触发Search事件
                filterStr = @"0123456789\n";
            }
                break;
            case UIKeyboardTypeDecimalPad:
            {
                //请注意这个\n，如果不写这个，Done按键将不会触发，如果用在SearchBar中，将会不触发Search事件
                filterStr = @"0123456789.\n";
            }
                break;
            case UIKeyboardTypeASCIICapable:
            {
                if(filterSymbol)
                {
                    //请注意这个\n，如果不写这个，Done按键将不会触发，如果用在SearchBar中，将会不触发Search事件
                    filterStr = @"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
                }
            }
                break;
            default:
                break;
        }
        
        if(filterStr)
        {
            NSCharacterSet *characterSet = [[NSCharacterSet characterSetWithCharactersInString:filterStr] invertedSet];
            if(characterSet)
            {
                NSString *filteredStr = [[inputValue componentsSeparatedByCharactersInSet:characterSet] componentsJoinedByString:@""];
                if(filteredStr)
                {
                    BOOL canInput = [inputValue isEqualToString:filteredStr];
                    
                    if(showMessage && !canInput)
                    {
                        NSString *message = nil;
                        switch(keyboardType)
                        {
                            case UIKeyboardTypeNumberPad:
                            case UIKeyboardTypePhonePad:
                            {
                                message = @"只能输入数字";
                            }
                                break;
                            case UIKeyboardTypeDecimalPad:
                            {
                                message = @"只能输入数字和小数点";
                            }
                                break;
                            case UIKeyboardTypeASCIICapable:
                            {
                                message = @"只能输入数字和字母";
                            }
                                break;
                            default:
                                break;
                        }
                        
                        //[KTAlert showAlertOnKeyboard:KTAlertTypeToast withMessage:message andDuration:kAlertDuration];
                        if(block)
                        {
                            block(message);
                        }
                    }
                    
                    return canInput;
                }
            }
        }
    }
    
    return YES;
}

+ (BOOL)canInputDecimal:(NSString *)inputValue textField:(UITextField *)textField textView:(UITextView *)textView maxLength:(int)maxLength maxDecimalLength:(int)maxDecimalLength showMessage:(BOOL)showMessage message:(NSString *)message message2:(NSString *)message2 andBlock:(void(^)(NSString *message))block
{
    NSInteger length = [inputValue length];
    if(length)
    {
        int errorType = 0;
        BOOL canInput = YES;
        
        if(maxLength > 0)
        {
            if(length > maxLength)
            {
                errorType = 1;
                canInput = NO;
            }
        }
        
        if(canInput)
        {
            NSRange range = [inputValue rangeOfString:@"."];
            if(range.location != NSNotFound)
            {
                NSString *string = [inputValue substringFromIndex:range.location + range.length];
                if(maxDecimalLength > 0)
                {
                    if([string length] > maxDecimalLength)
                    {
                        errorType = 2;
                        canInput = NO;
                    }
                }
                
                if(canInput)
                {
                    NSRange range = [string rangeOfString:@"."];
                    if(range.location != NSNotFound)
                    {
                        errorType = 3;
                        canInput = NO;
                    }
                }
            }
        }
        
        if(!canInput)
        {
            if(showMessage)
            {
                switch(errorType)
                {
                    case 3:
                    {
                        message = message2;
                        if(!message)
                        {
                            message = @"输入不正确，小数点只能输入一个";
                        }
                    }
                        break;
                    default:
                    {
                        if(!message)
                        {
                            switch(errorType)
                            {
                                case 1:
                                {
                                    message = [NSString stringWithFormat:@"输入不正确，包含小数点长度不能超过%d位", maxLength];
                                }
                                    break;
                                case 2:
                                {
                                    message = [NSString stringWithFormat:@"输入不正确，小数长度不能超过%d位", maxDecimalLength];
                                }
                                    break;
                            }
                        }
                    }
                        break;
                }
                
                //[KTAlert showAlertOnKeyboard:KTAlertTypeToast withMessage:message andDuration:kAlertDuration];
                if(block)
                {
                    block(message);
                }
            }
        }
        
        return canInput;
    }
    
    return YES;
}

+ (NSString *)getFormatValue:(NSString *)prefix value:(float)value valueType:(int)valueType precisionType:(int)precisionType newValue:(CGFloat *)newValue valuePrecision:(int *)valuePrecision
{
    int precision = 100;
    NSString *formatValue = nil;
    
    switch(precisionType)
    {
        case 0://保留2位小数
        {
            if(valuePrecision)
            {
                precision = 100;
            }
            else
            {
                formatValue = [NSString stringWithFormat:@"%.2f", value];
            }
        }
            break;
        case 1://保留整数（四舍五入）
        {
            if(valuePrecision)
            {
                precision = 1;
            }
            else
            {
                formatValue = [NSString stringWithFormat:@"%d", (int)roundf(value)];
            }
        }
            break;
        case 2://保留整数（舍弃小数）
        {
            if(valuePrecision)
            {
                precision = 1;
            }
            else
            {
                formatValue = [NSString stringWithFormat:@"%d", (int)floorf(value)];
            }
        }
            break;
        case 3://保留1位小数
        {
            if(valuePrecision)
            {
                precision = 10;
            }
            else
            {
                formatValue = [NSString stringWithFormat:@"%.1f", value];
            }
        }
            break;
        case 4://保留3位小数
        {
            if(valuePrecision)
            {
                precision = 1000;
            }
            else
            {
                formatValue = [NSString stringWithFormat:@"%.3f", value];
            }
        }
            break;
    }

    if(valuePrecision)
    {
        *valuePrecision = precision;
        
        return nil;
    }
    else
    {
        if(!formatValue)
        {
            formatValue = [NSString stringWithFormat:@"%.2f", value];
        }
        
        if(newValue)
        {
            *newValue = [formatValue floatValue];
        }
        
        if(!prefix)
        {
            prefix = @"";
        }
        
        return [prefix stringByAppendingString:formatValue];
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
+ (UIView *)createView:(CGRect)frame backColor:(UIColor *)backColor borderColor:(UIColor *)borderColor borderWidth:(NSInteger)borderWidth cornerRadius:(float)cornerRadius
{
    UIView *view = [[UIView alloc] initWithFrame:frame];
    if(view)
    {
        if(borderColor)
        {
            CALayer *layer = view.layer;
            layer.borderWidth = borderWidth;
            layer.borderColor = borderColor.CGColor;
            
            if(cornerRadius > 0)
            {
                layer.masksToBounds = YES;
                layer.cornerRadius = cornerRadius;
            }
        }

        view.backgroundColor = backColor;
    }
    
    return view;
}

+ (UILabel *)createLabel:(CGRect)frame text:(NSString *)text textFont:(UIFont *)textFont textColor:(UIColor *)textColor textAlignment:(NSTextAlignment)textAlignment calcWidth:(BOOL)calcWidth
{
    if(calcWidth)
    {
        NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithObject:textFont forKey:NSFontAttributeName];
        CGSize size = [text boundingRectWithSize:CGSizeMake(MAXFLOAT, 0.0) options:NSStringDrawingUsesLineFragmentOrigin attributes:dic context:nil].size;
        frame.size.width = size.width;
    }
    
    UILabel *label = [[UILabel alloc] initWithFrame:frame];
    if(label)
    {
        label.text = text;
        label.font = textFont;
        label.textColor = textColor;
        label.textAlignment = textAlignment;
    }
    
    return label;
}

+ (UIButton *)createButton:(CGRect)frame tag:(NSInteger)tag title:(NSString *)title titleFont:(UIFont *)titleFont titleColor:(UIColor *)titleColor titleAlignment:(NSTextAlignment)titleAlignment image:(UIImage *)image edgeInsets:(UIEdgeInsets)edgeInsets borderColor:(UIColor *)borderColor borderWidth:(NSInteger)borderWidth cornerRadius:(float)cornerRadius andBlock:(ButtonClickBlock)block
{
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    if(button)
    {
        if(borderColor)
        {
            CALayer *layer = button.layer;
            layer.borderWidth = borderWidth;
            layer.borderColor = borderColor.CGColor;
            
            if(cornerRadius > 0)
            {
                layer.masksToBounds = YES;
                layer.cornerRadius = cornerRadius;
            }
            
            //int margin = 4;
            //button.titleEdgeInsets = UIEdgeInsetsMake(margin, margin, margin, margin);
        }
        
        button.frame = frame;
        button.tag = tag;
        
        if(image)
        {
            [button setImage:image forState:UIControlStateNormal];
            
            button.imageEdgeInsets = edgeInsets;
        }
        else
        {
            button.titleLabel.font = titleFont;
            switch(titleAlignment)
            {
                case NSTextAlignmentLeft:
                {
                    button.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
                }
                    break;
                case NSTextAlignmentRight:
                {
                    button.contentHorizontalAlignment = UIControlContentHorizontalAlignmentRight;
                }
                    break;
                default:
                    break;
            }
            
            [button setTitle:title forState:UIControlStateNormal];
            [button setTitleColor:titleColor forState:UIControlStateNormal];
            
            button.titleEdgeInsets = edgeInsets;
        }
        
        [button setBlock:block];
        //[button addTarget:inputItem action:@selector(showDatePickerView:) forControlEvents:UIControlEventTouchUpInside];
    }
    
    return button;
}

+ (UITextField *)createTextField:(CGRect)frame placeHolder:(NSString *)placeHolder textFont:(UIFont *)textFont textAlignment:(NSTextAlignment)textAlignment textColor:(UIColor *)textColor placeHolderColor:(UIColor *)placeHolderColor keyboardType:(UIKeyboardType)keyboardType
{
    UITextField *textField = [[UITextField alloc] initWithFrame:frame];
    if(textField)
    {
        textField.clearButtonMode = UITextFieldViewModeUnlessEditing;//UITextFieldViewModeAlways;
        textField.autocapitalizationType = UITextAutocapitalizationTypeNone;
        textField.keyboardType = keyboardType;
        
        textField.textAlignment = textAlignment;
        //inputTextField.text = value;
        textField.placeholder = placeHolder;
        textField.textColor = textColor;
        textField.font = textFont;
        
        if(placeHolder)
        {
            if(placeHolderColor)
            {
                NSMutableDictionary *attrs = [NSMutableDictionary dictionary];
                if(attrs)
                {
                    attrs[NSForegroundColorAttributeName] = placeHolderColor;
                    
                    //NSAttributedString : 带有属性的文字(富文本技术)
                    NSAttributedString *placeholder = [[NSAttributedString alloc] initWithString:placeHolder attributes:attrs];
                    textField.attributedPlaceholder = placeholder;
                }
            }
        }
    }
    
    return textField;
}

+ (void)setTextFieldDelegate:(UITextField *)textField delegate:(id)delegate beginAction:(SEL)beginAction endAction:(SEL)endAction changeAction:(SEL)changeAction setDelegate:(BOOL)setDelegate
{
    if(textField)
    {
        if(setDelegate)
        {
            textField.delegate = delegate;
        }
        
        if(beginAction)
        {
            [textField addTarget:delegate action:beginAction forControlEvents:UIControlEventEditingDidBegin];
        }
        
        if(endAction)
        {
            [textField addTarget:delegate action:endAction forControlEvents:UIControlEventEditingDidEnd];
        }
        
        if(changeAction)
        {
            [textField addTarget:delegate action:changeAction forControlEvents:UIControlEventEditingChanged];
        }
    }
}

@end
