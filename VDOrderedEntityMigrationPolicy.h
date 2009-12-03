//
// VDOrderedEntityMigrationPolicy.m
// 
// General entity migration policy implementation for migrating Core Data entities
// that inherit from Brian Webster's BWOrderedManagedObject.
// 
// Created by Vincent Driessen.
// 
// Sources freely available at Github:
//   http://github.com/nvie/VDOrderedEntityMigrationPolicy
//

#import <Foundation/Foundation.h>

@interface VDOrderedEntityMigrationPolicy : NSEntityMigrationPolicy {
}

- (BOOL)createDestinationInstancesForSourceInstance:(NSManagedObject *)sInstance
									  entityMapping:(NSEntityMapping *)mapping
											manager:(NSMigrationManager *)manager
											  error:(NSError **)error;

// We don't need to implement the other NSEntityMigrationPolicy methods
//- (BOOL)beginEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;
//- (BOOL)endInstanceCreationForEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;
//- (BOOL)createRelationshipsForDestinationInstance:(NSManagedObject *)dInstance entityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;
//- (BOOL)endRelationshipCreationForEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;
//- (BOOL)performCustomValidationForEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;
//- (BOOL)endEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;

@end
