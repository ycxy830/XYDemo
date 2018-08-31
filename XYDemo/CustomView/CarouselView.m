//
//  CarouselView.m
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import "CarouselView.h"

#define kDegree2Radians(degrees) degrees * M_PI / 180.0
#define kRadians2Degree(radians) radians * 180.0 / M_PI

@interface NSMutableArray(Circular)
///**Get object in circular array
// @param index: index of object.
// */
- (id)circularObjectAtIndex:(NSInteger)index;

///**Get object previous to another in circular array
// @param object: object that exists in array.
// @return the previous object
// */
- (id)circularPreviusObject:(NSObject *)object;

///**Get object next to another in circular array
// @param object: object that exists in array.
// @return the next object
// */
- (id)circularNextObject:(NSObject *)object;
@end

@implementation NSMutableArray(Circular)

- (id)circularObjectAtIndex:(NSInteger)index
{
    while(index < 0)
    {
        index = index + [self count];
    }
    
    NSInteger i = index % [self count];
    
    return [self objectAtIndex:i];
}

- (id)circularPreviusObject:(NSObject *)object
{
    NSUInteger index = [self indexOfObject:object];
    if(index != NSNotFound)
    {
        return [self circularObjectAtIndex:index - 1];
    }
    
    return nil;
}

- (id)circularNextObject:(NSObject *)object
{
    NSUInteger index = [self indexOfObject:object];
    if(index != NSNotFound)
    {
        return [self circularObjectAtIndex:index + 1];
    }
    
    return nil;
}

@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface CarouselItem : UIView

@property(nonatomic, strong)UIImageView *imageView;
@property (nonatomic, strong)UILabel *titleLabel;

@property CGFloat angle;

@end

@implementation CarouselItem

//- (id)initWithFrame:(CGRect)aRect
//{
//    if((self = [super initWithFrame:aRect]))
//    {
//        [self communSetup];
//    }
//
//    return self;
//}
//
//- (id)initWithCoder:(NSCoder *)decoder
//{
//    if((self = [super initWithCoder:decoder]))
//    {
//        [self communSetup];
//    }
//
//    return self;
//}
//
//- (void)drawRect:(CGRect)rect
//{
//    CGContextRef context = UIGraphicsGetCurrentContext();
//    CGContextSetShouldAntialias(context, YES);
//}
//
//- (void)communSetup
//{
//    self.userInteractionEnabled = YES;
//}

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface CarouselView ()

@property(nonatomic, strong)CarouselItem *topView;
@property(nonatomic, strong)CarouselItem *bottomView;
@property(nonatomic, strong)CarouselItem *leftView;
@property(nonatomic, strong)CarouselItem *rightView;
@property(nonatomic, strong)CarouselItem *frontView;
@property(nonatomic, strong)CarouselItem *backView;

//constants
@property(nonatomic, assign)CGFloat inclinationAngle;
@property(nonatomic, assign)CGFloat backItemAlpha;
@property(nonatomic, assign)BOOL centerSelectedItem;

//
@property(nonatomic, assign)int selectedIndex;

@property(nonatomic, strong)NSMutableArray *carouselItems;

@property(nonatomic, assign)CGFloat startPosition;

@property(nonatomic, assign)Boolean isSingleTap;
@property(nonatomic, assign)Boolean isDoubleTap;

@property(nonatomic, assign)Boolean isRightMove;
@property(nonatomic, assign)Boolean isLeftMove;

@property(nonatomic, assign)CGFloat separationAngle;
@property(nonatomic, assign)CGFloat radius;

@end

NSDate *startingTime = nil;

@implementation CarouselView

- (CarouselView *)initWithFrame:(CGRect)frame inclination:(float)inclination backItemAlpha:(float)backItemAlpha itemCount:(int)itemCount
{
    if((self = [super initWithFrame:frame]))
    {
        [self setFrame:frame];
        [self setUpInitialState:frame];
        
        [self setCarouselInclination:inclination];    //optional//-0.15
        [self setBackItemAlpha:backItemAlpha];            //optional//0.8
        [self shouldCenterSelectedItem:YES];    //optional

        float value = 20;
        int count = 6;
        if(itemCount > 0)
        {
            count = itemCount;
        }
        int margin = 10;
        CGRect rect = CGRectMake(10, 0, (frame.size.width - margin - margin) / (count / 2), frame.size.height / (count / 2));
        for(int i = 0; i < count; i++)
        {
            CarouselItem *item = [[CarouselItem alloc] initWithFrame:rect];
            if(item)
            {
                UIColor *color = [UIColor colorWithRed:i * value / 255.0 green:i * value / 255.0 blue:i * value / 255.0 alpha:1.0];
                item.backgroundColor = color;

                UILabel *label = [[UILabel alloc] initWithFrame:rect];
                if(label)
                {
                    item.titleLabel = label;
                    
                    label.textColor = [UIColor blueColor];
                    [label setFont:[UIFont fontWithName:@"helvetica" size:30.0]];
                    [label setAdjustsFontSizeToFitWidth:YES];
                    [label setText:[NSString stringWithFormat:@"View_%d", i + 1]];
                    
                    [item addSubview:label];
                }

                [self addItem:item refreshPosition:i == count - 1];
            }
        }
    }
    
    return self;
}

- (void)setUpInitialState:(CGRect)frame
{
    //setup constants
    _inclinationAngle = -0.1;
    _backItemAlpha = 0.7;
    _centerSelectedItem = YES;
    
    //carouselItems never will be nil
    _carouselItems = [NSMutableArray array];
    
    self.multipleTouchEnabled = NO;
    self.userInteractionEnabled = YES;
    self.autoresizesSubviews = YES;
    self.layer.position = CGPointMake(self.frame.size.width / 2, self.frame.size.height / 2);
    
    [self setFrame:frame];
    [self setBounds:self.frame];
    [self setClipsToBounds:YES];
    
    _selectedIndex = -1;
    _separationAngle = 0;
}

- (void)setAntialiasing:(BOOL)flag
{
    CGContextSetAllowsAntialiasing(UIGraphicsGetCurrentContext(),flag);
    CGContextSetShouldAntialias(UIGraphicsGetCurrentContext(), flag);
}

#pragma mark - add item methods
- (CarouselItem *)addItem:(UIImage *)image withTitle:(NSString *)aTitle refreshPosition:(BOOL)refreshPosition
{
    //create carousel item
    CarouselItem *item = [[NSBundle mainBundle] loadNibNamed:@"CarouselItem" owner:self options:nil][0];
    item.imageView.image = image;
    item.imageView.clipsToBounds = YES;
    [item.imageView.layer setEdgeAntialiasingMask:(kCALayerLeftEdge | kCALayerRightEdge | kCALayerBottomEdge | kCALayerTopEdge)];
    
    [item.titleLabel setFont:[UIFont fontWithName:@"helvetica" size:30.0]];
    [item.titleLabel setAdjustsFontSizeToFitWidth:YES];
    [item.titleLabel setText:aTitle];
    
    if(_selectedIndex == -1)
    {
        //first item added
        _selectedIndex = 0;
    }

    __weak typeof(self)weakSelf = self;
    //New item added in main queue
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.layer addSublayer:item.layer];//[self.layer insertSublayer:item.layer atIndex:[carouselItems count]];
        
        // place the carousel just in the middle of the view
        [item.layer setPosition:CGPointMake(self.frame.size.width / 2, self.frame.size.height / 2)];

        [weakSelf.carouselItems addObject:item];
        
        if(refreshPosition)
        {
            [self refreshItemsPositionWithAnimated:YES];
        }
    });
    
    return item;
}

- (void)addItem:(CarouselItem *)item refreshPosition:(BOOL)refreshPosition
{
    if(!item)
    {
        return;
    }
    
    if(_selectedIndex == -1)
    {
        //first item added
        _selectedIndex = 0;
    }
    
    __weak typeof(self)weakSelf = self;
    //New item added in main queue
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.layer addSublayer:item.layer];//[self.layer insertSublayer:item.layer atIndex:[carouselItems count]];
        // place the carousel just in the middle of the view
        [item.layer setPosition:CGPointMake(self.frame.size.width / 2, self.frame.size.height / 2)];
        
        [weakSelf.carouselItems addObject:item];
        
        if(refreshPosition)
        {
            [self refreshItemsPositionWithAnimated:YES];
        }
    });
}

- (void)removeItem:(CarouselItem *)item
{
    if(!item)
    {
        return;
    }

    __weak typeof(self)weakSelf = self;
    //Item removed in main queue
    dispatch_async(dispatch_get_main_queue(), ^{
        [item.layer removeFromSuperlayer];
        [weakSelf.carouselItems removeObject:item];
        [self refreshItemsPositionWithAnimated:YES];
    });
}

- (CarouselItem *)getItemAtIndex:(NSInteger)index
{
    if(!_carouselItems || [_carouselItems count] == 0)
    {
        return nil;
    }

    return [_carouselItems circularObjectAtIndex:index];
}

/** returns current items
 */
- (NSArray *)getItems
{
    return _carouselItems;
}

///when an item is added  radius and separationAngle must change  and all the items have to be redrawn
- (void)refreshItemsPositionWithAnimated:(BOOL)animated
{
    if(!_carouselItems || [_carouselItems count] == 0)
    {
        return;
    }
    
    NSInteger numberOfImages = [_carouselItems count];
    UIView *itemView = (UIView *)[_carouselItems objectAtIndex:0];
    _radius = (itemView.bounds.size.width / 2) / tan((M_PI / numberOfImages));
    //WARNING  itemView.frame.size.width depends on the position of view, we must use the bounds property...
    
    _separationAngle = (2 * M_PI) / numberOfImages;
    
    if(animated)
    {
        [UIView beginAnimations:nil context:NULL];
        [UIView setAnimationCurve:UIViewAnimationCurveLinear];
        [UIView setAnimationBeginsFromCurrentState:YES];
    }
    
    CGFloat angle = 0.0;
    for(CarouselItem *item in _carouselItems)
    {
        [item setAngle:angle];
        [item.layer setAnchorPoint:CGPointMake(0.5, 0.5)];
        [item.layer setAnchorPointZ:-_radius];
        item.layer.transform = CATransform3DMakeRotation(item.angle, 0, 1, 0);
        item.layer.transform = CATransform3DConcat(item.layer.transform, CATransform3DMakeRotation(_inclinationAngle, 1, 0, 0));

        if(angle > M_PI / 2 && angle < (1.5 * M_PI))
        {
            item.alpha = _backItemAlpha;
        }
        else
        {
            item.alpha = 1;
        }
        
        angle += _separationAngle;
    }
    
    if(animated)
    {
        [UIView commitAnimations];
    }
}

#pragma mark - touch methods
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    CGPoint startPoint = [[touches anyObject] locationInView:self];
    _startPosition = startPoint.x;
    startingTime = [[NSDate alloc] init];
    
    UITouch *touch = [touches anyObject];
    
    _isSingleTap = ([touch tapCount] == 1);
    _isDoubleTap = ([touch tapCount] > 1);
    
    _isRightMove = NO;
    _isLeftMove = NO;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    _isSingleTap = NO;
    _isDoubleTap = NO;
    
    if(startingTime)
    {
        NSDate *now = [NSDate date];
        
        if(fabs([now timeIntervalSinceDate:startingTime]) > 0.5)
        {
            //isSlowMovement = YES;
        }
    }
    
    CGPoint movedPoint = [[touches anyObject] locationInView:self];
    CGFloat offset = _startPosition - movedPoint.x;

    // we need to convert offset to radian angle because carousel moves radians
    CGFloat offsetToMove = -atan(offset / _radius);
    
    _startPosition = movedPoint.x;
    
    if(offset > 0)
    {
        _isRightMove = YES;
        _isLeftMove = NO;
    }
    else
    {
        _isLeftMove = YES;
        _isRightMove = NO;
    }
    
    [self moveCarousel:offsetToMove];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if(startingTime)
    {
        NSDate *now = [[NSDate alloc] init];
        
        if(fabs([now timeIntervalSinceDate:startingTime]) > 0.5)
        {
            //isSlowMovement = YES;
        }
    }
    
    if(_isSingleTap)
    {
        // Which item did the user tap? move carousel to center that item
        CGPoint targetPoint = [[touches anyObject] locationInView:self];
        CALayer *targetLayer = (CALayer *)[self.layer hitTest:targetPoint];
        CarouselItem *targetItem = [self findItemOnscreen:targetLayer];
        
        if(targetItem != nil)
        {
            [self setSelectedItemAndCenter:targetItem];
        }
    }
    else if(_isDoubleTap)
    {
        //SELECT directly item that user taps
//        CGPoint targetPoint = [[touches anyObject] locationInView:self];
//        CALayer *targetLayer = (CALayer *)[self.layer hitTest:targetPoint];
//        CarouselItem *targetItem = [self findItemOnscreen:targetLayer];
        
//        if(targetItem != nil && self.selectionDelegate != nil)
//        {
//            //[self setSelectedItemAndCenter: targetItem.number];
//            [self.selectionDelegate carousel:self itemSelected:targetItem];
//        }
    }
    else
    {
        if(_centerSelectedItem)
        {
            // center the item nearest to 0 angle.
            CarouselItem *selectedItem = [self getSelectedItem];
            
            [self setSelectedItemAndCenter:selectedItem];
            
            //TODO Future feature, if it is not a slow movement launch the carousel to rotate
        }
    }
    
    _isRightMove = NO;
    _isLeftMove = NO;
    
    _isSingleTap = NO;
    _isDoubleTap = NO;
    
    //isSlowMovement = NO;
}

#pragma mark - selection, move and find methods

- (void)setSelectedItemAndCenter:(CarouselItem *)newSelectedItem
{
    //Select the correct rotation way
    if(newSelectedItem.angle >= M_PI)
    {
        newSelectedItem.angle = newSelectedItem.angle - (2 * M_PI);
    }
    
    [self moveCarousel:-newSelectedItem.angle];
}

- (CarouselItem *)findItemOnscreen:(CALayer *)targetLayer
{
    CarouselItem *foundItem = nil;
    
    @try{
        for(int h = 0; h < [_carouselItems count]; h++)
        {
            CarouselItem *aItem = (CarouselItem *)[_carouselItems circularObjectAtIndex:h];
            
            for(int i = 0; i < [[aItem subviews] count]; i++)
            {
                UIView *subview = [[aItem subviews] objectAtIndex:i];
                
                if([[subview layer] isEqual:targetLayer])
                {
                    foundItem = aItem;
                    
                    break;
                }
                
                for(int j = 0; j < [[subview subviews] count]; j++)
                {
                    UIView *subSubview = [[subview subviews] objectAtIndex:j];
                    if([[subSubview layer] isEqual:targetLayer])
                    {
                        foundItem = aItem;

                        break;
                    }
                }
            }
        }
    }
    @catch(NSException * e)
    {
    }

    return foundItem;
}

- (void)moveCarousel:(CGFloat)angleOffset
{
    [self logCarouselItems];
    
    if(fabs(angleOffset) == 0.0f)
        return;

    CGFloat itemsMoved = fabs(angleOffset / _separationAngle);

    __weak typeof(self)weakSelf = self;
    for(int i = 0; i < [_carouselItems count]; i++)
    {
        CarouselItem *aItem = (CarouselItem *)[_carouselItems circularObjectAtIndex:i];
        [aItem setAngle:(aItem.angle + angleOffset)];

        [UIView animateWithDuration:(0.2 * itemsMoved) delay:0 options:UIViewAnimationOptionCurveLinear | UIViewAnimationOptionBeginFromCurrentState animations:^{
            aItem.layer.transform = CATransform3DConcat(CATransform3DMakeRotation(angleOffset, 0, 1, 0), aItem.layer.transform);
            
            if(aItem.angle > M_PI / 2 && aItem.angle < (1.5 * M_PI))
            {
                aItem.alpha = weakSelf.backItemAlpha;
            }
            else
            {
                aItem.alpha = 1;
            }
        } completion:^(BOOL finished){
            // reorder angles.
            while(aItem.angle > (2 * M_PI))
            {
                aItem.angle = aItem.angle - (2 * M_PI);
            }
            
            while(aItem.angle < 0)
            {
                aItem.angle = aItem.angle + (2 * M_PI);
            }
            
            [self logCarouselItems];
        }];
    }
}

/// return selected item
- (CarouselItem *)getSelectedItem
{
    if(!_carouselItems)
    {
        return nil;
    }
    
    float minimumAngle = M_PI;
    CarouselItem *selected = nil;
    
    for(int i = 0; i < [_carouselItems count]; i++)
    {
        CarouselItem *aItem = (CarouselItem *)[_carouselItems circularObjectAtIndex:i];
        float angle = aItem.angle;
        angle = fabs(angle);
        
        while(angle > (2 * M_PI))
        {
            angle = angle - (2 * M_PI);
        }
        
        if(angle < minimumAngle)
        {
            minimumAngle = angle;
            selected = aItem;
        }
    }
    
    return selected;
}

#pragma mark - set constants methods
- (void)setCarouselInclination:(CGFloat)angle
{
    _inclinationAngle = angle;
}

- (void)setBackItemAlpha:(CGFloat)alpha
{
    if(alpha >= 0 && alpha <= 1)
    {
        _backItemAlpha = alpha;
    }
    else
    {
    }
}

- (void)shouldCenterSelectedItem:(BOOL)center
{
    _centerSelectedItem = center;
}

#pragma mark - log methods
- (void)logCarouselItems
{
    return;
    
    //DBLog(@"------------------");
    //for(CarouselItem *item in carouselItems)
    //{
    //    DBLog(@"item %@: %f", item.titleLabel.text, item.angle);
    //}
    //DBLog(@"------------------");
}

@end
