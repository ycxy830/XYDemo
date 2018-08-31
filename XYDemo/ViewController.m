//
//  ViewController.m
//  XYDemo
//
//  Created by luck on 2018/5/11.
//  Copyright © 2018年 luck. All rights reserved.
//

#import "ViewController.h"
#import "ContentViewController.h"

@interface ViewController ()<UITableViewDataSource, UITableViewDelegate>

//@property(nonatomic, strong)UITableView *tableView;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    CGRect rect = self.view.frame;
    UITableView *tableView = [[UITableView alloc] initWithFrame:rect style:UITableViewStyleGrouped];
    if(tableView)
    {
        tableView.backgroundColor = [UIColor whiteColor];
        
        tableView.dataSource = self;
        tableView.delegate = self;
        
        tableView.estimatedRowHeight = 0;
        tableView.estimatedSectionHeaderHeight = 0;
        tableView.estimatedSectionFooterHeight = 0;
        
        [self.view addSubview:tableView];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 20;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *cellIdentifier = @"viewControllerCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if(!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
    }
    
    if(cell)
    {
        NSString *text = @"";

        switch(indexPath.row)
        {
            case 0:
            {
                text = @"ChartView";
            }
                break;
            case 1:
            {
                text = @"立方体";
            }
                break;
            case 2:
            {
                text = @"FlipView";
            }
                break;
            case 4:
            {
                text = @"UIView(RoundCorner)";
            }
                break;
        }
        
        cell.textLabel.text = text;
    }

    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 60;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    CGFloat headerHeight = 0.0001;//0
    
    return headerHeight;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 0.0001;//0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    ContentViewController *viewController = [[ContentViewController alloc] init];
    if(viewController)
    {
        viewController.contentType = (int)indexPath.row;
        
        [self.navigationController pushViewController:viewController animated:YES];
    }
}

@end
