//
//  FlipView.m
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import "FlipView.h"

@implementation FlipView

- (instancetype)initWithFrame:(CGRect)frame offset:(int)offset
{
    self = [super initWithFrame:frame];
    if(self)
    {
        self.text = @"0";
        
        CGPoint startPos = CGPointZero;
        CGSize size = frame.size;
        CGRect rect = CGRectMake(startPos.x, startPos.y + size.height / 2, size.width, size.height / 2);
        
        UIView *view = [self segment:rect isTop:NO];
        if(view)
        {
            self.bottomView = view;
            
            [self addSubview:view];
        }
        
        rect.origin.y = startPos.y;
        view = [self segment:rect isTop:YES];
        if(view)
        {
            self.topView = view;
            
            [self addSubview:view];
        }
        
        /* Beneath - the ones that show underneath the animation */
        view = [self segment:rect isTop:YES];
        if(view)
        {
            self.topViewBeneath = view;
            
            [self insertSubview:view atIndex:0];
        }
        
        rect.origin.y += rect.size.height;
        view = [self segment:rect isTop:NO];
        if(view)
        {
            self.bottomViewBeneath = view;
            
            [self insertSubview:view atIndex:0];
        }
        
        UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"SegmentStack.png"]];
        imageView.frame = CGRectMake(0, 0, frame.size.width, frame.size.height + offset + offset);
        imageView.layer.anchorPoint = CGPointMake(0, 0);
        imageView.layer.position = CGPointMake(startPos.x, startPos.y - offset);
        [self insertSubview:imageView atIndex:0];
        
        CALayer *layer = self.topView.layer;
        layer.position = CGPointMake(layer.position.x - rect.size.width / 2, layer.position.y + rect.size.height / 2);
        layer.anchorPoint = CGPointMake(0, 1);
        
        layer = self.bottomView.layer;
        layer.position = CGPointMake(layer.position.x - rect.size.width / 2, layer.position.y - rect.size.height / 2);
        layer.anchorPoint = CGPointMake(0, 0);
        
        CATransform3D sublayerTransform = CATransform3DIdentity;
        sublayerTransform.m34 = -1.0 / 420.0;
        [self.layer setSublayerTransform:sublayerTransform];
    }
    
    return self;
}

- (UILabel *)createLabel
{
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectZero];
    if(label)
    {
        label.backgroundColor = nil;
        label.opaque = NO;
        label.font = [UIFont boldSystemFontOfSize:84];
        label.textAlignment = NSTextAlignmentCenter;
        label.text = @"0";
        label.textColor = [UIColor darkGrayColor];
        label.shadowColor = [UIColor colorWithWhite:0.2 alpha:1.0];
        label.shadowOffset = CGSizeMake(0, -1);
        label.tag = 10;
    }
    
    return label;
}

- (UIView *)segment:(CGRect)rect isTop:(BOOL)isTop
{
    UIView *view = [[UIView alloc] initWithFrame:rect];
    if(view)
    {
        view.clipsToBounds = YES;
        
        UIImage *image = [UIImage imageNamed:@"Segment.png"];
        if(image)
        {
            CGSize imageSize = rect.size;
            
            UIGraphicsBeginImageContext(imageSize);
            
            [image drawInRect:CGRectMake(0, 0, imageSize.width, imageSize.height)];
            
            UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
            UIGraphicsEndImageContext();
            
            if(isTop) // I'm flipping the image here for the top; same happens with the gloss later
            {
                UIGraphicsBeginImageContext(imageSize);
                
                CGContextScaleCTM(UIGraphicsGetCurrentContext(), 1.0, -1.0);
                
                //[image drawAtPoint:CGPointMake(0.0, -imageSize.height)];
                [newImage drawAtPoint:CGPointMake(0.0, -imageSize.height)];
                
                UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
                UIGraphicsEndImageContext();
                
                view.backgroundColor = [UIColor colorWithPatternImage:newImage];
            }
            else
            {
                view.backgroundColor = [UIColor colorWithPatternImage:newImage];
                //view.backgroundColor = [UIColor colorWithPatternImage:image];
            }
        }
        
        UILabel *label = [self createLabel];
        
        if(isTop)
        {
            label.frame = CGRectOffset(view.bounds, 0, +rect.size.height / 2);
        }
        else
        {
            label.frame = CGRectOffset(view.bounds, 0, -rect.size.height / 2);
        }
        
        [view addSubview:label];
        
        UIImageView *glossView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"SegmentGloss.png"]];
        if(glossView)
        {
            CGRect frame = rect;
            frame.origin = CGPointZero;
            glossView.frame = frame;
            
            if(isTop)
            {
                glossView.layer.transform = CATransform3DMakeScale(1.0, -1.0, 1.0);
            }
            
            [view addSubview:glossView];
        }
    }
    
    return view;
}

- (void)doFlip:(float)duration text:(NSString *)text
{
    NSString *oldText = self.text;
    
    NSInteger tag = 10;
    
    UILabel *label = [self.topViewBeneath viewWithTag:tag];
    label.text = text;
    
    label = [self.bottomViewBeneath viewWithTag:tag];
    label.text = oldText;
    
    [UIView animateWithDuration:duration animations:^{
        self.topView.layer.transform = CATransform3DMakeRotation(M_PI_2, -1.0, 0.0, 0.0);
    } completion:^(BOOL finished) {
        UILabel *label = [self.topView viewWithTag:tag];
        label.text = text;
        
        label = [self.bottomView viewWithTag:tag];
        label.text = text;
        
        self.topView.layer.transform = CATransform3DIdentity;
        
        self.bottomView.layer.transform = CATransform3DMakeRotation(M_PI_2, 1.0, 0.0, 0.0);
        
        [UIView animateWithDuration:duration animations:^{
            self.bottomView.layer.transform = CATransform3DIdentity;
        } completion:^(BOOL finished) {
            
        }];
    }];
    
    self.text = text;
}

@end
