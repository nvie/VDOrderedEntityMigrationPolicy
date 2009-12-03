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

// Override this method in a subclass to provide information on both which keys
// are ordered and which entity mappings are used to construct the destination
// equivalents of the entities these ordered keys refer to.
// 
// For example, when specifying the order for a Playlist refering to Tracks, use:
// 
// - (NSDictionary *)entityMappingForOrderedKeys {
//     return [NSDictionary dictionaryWithObjectsAndKeys:
//             @"TracksToTracks", @"tracksOrdering",
//             nil];
// }
//
- (NSDictionary *)entityMappingForOrderedKeys;

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
