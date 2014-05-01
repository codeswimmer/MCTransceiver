//
//  MCTEViewController.m
//  MCTransceiverExample
//
//  Created by Keith Ermel on 5/1/14.
//  Copyright (c) 2014 Keith Ermel. All rights reserved.
//

#import "MCTEViewController.h"
#import "UIStoryboardSegue+Utils.h"
#import "MCTransceiverViewController.h"


NSString *const kTransceiverHostSegue   = @"transceiverHostSegue";
NSString *const kTransceiverJoinSegue   = @"transceiverJoinSegue";


@interface MCTEViewController ()
@end


@implementation MCTEViewController

#pragma mark - Configuration

-(void)configureHostVC:(UIStoryboardSegue *)segue
{
    ((MCTransceiverViewController *)segue.destinationViewController).mode = MCTransceiverModeAdvertiser;
}

-(void)configureJoinVC:(UIStoryboardSegue *)segue
{
    ((MCTransceiverViewController *)segue.destinationViewController).mode = MCTransceiverModeBrowser;
}


#pragma mark - Segue

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue isNamed:kTransceiverHostSegue]) {[self configureHostVC:segue];}
    else if ([segue isNamed:kTransceiverJoinSegue]) {[self configureJoinVC:segue];}
}

@end
